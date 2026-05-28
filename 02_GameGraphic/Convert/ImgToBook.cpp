//=================================================================================================
//
//	ImgToBookソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Convert/ImgToBook.h"
#include <filesystem>


#include "lz4.h"
#pragma comment ( lib, "lz4.lib" )
//@info .dllファイルはコピーして参照できる位置に置く


using namespace std;
namespace FS = std::filesystem;


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//.png画像.imgフォルダから作成
	Book CreateBookFromDir ( const s3d::String & dirpath )
	{
		//-----------------------------------------------
		//戻り値で返してもコピーは発生しません（ほぼ常に）
		//C++17 以降では、以下の最適化が標準で保証されます：
		//	・NRVO（Named Return Value Optimization）
		//	・ムーブ省略（C++17 で強化）
		//-----------------------------------------------
		Book book;	//戻値


		//ファイルパス存在確認
		if ( ! FS::exists  ( dirpath.str() ) ) { return book; }

		//ファイル列挙
		auto files = FileSystem::DirectoryContents ( dirpath );
		const size_t nFile = files.size();


		//キャンバス保存
		s3d::Array < Canvas > cvss ( nFile );


		//ハッシュのためのTile保存
		std::unordered_map < uint32_t, Tile > map_hash_tile;


		//ファイルでループ
		uint32_t indexFile = 0;
		for ( const String name : files )
		{
			//1ファイルの記録
			Canvas canvas;
			canvas.SetName ( name );

			//.pngからImageに変換
			s3d::Image img { name, s3d::ImageFormat::PNG };

			//ImageをCompress
			Compress cmpr;
			cmpr.Do ( img, canvas );

			//Bookに追加
			book.AddCompress ( cmpr, canvas, map_hash_tile );
			book.AddMap ( name, canvas );

			cvss [ indexFile ] = canvas;

			++ indexFile;
		}

		//まとめてBookにコピー
		book.CopyFromAryCanvas(cvss);

		return book;
	}

	//Bookから.atlsの保存 Tip単位
	void SaveAtlas ( const s3d::String & filepath, const Book & book )
	{
		const Array < Page > & pages = book.GetPages ();

		MemoryWriter mw;

		//ページ枚数
		mw.write ( static_cast < uint32 > ( pages.size() ) );

		for ( const Page & page : pages )
		{
			page.ToMemStrm ( mw );
		}


		//ファイルに書き出し
		BinaryWriter bw { filepath };
		bw.write ( mw.retrieve().data(), mw.size() );
	}


	//Bookから.atlsの保存 Image形式
	void SaveAtlasImg ( const s3d::String & filepath, const Book & book )
	{
		const Array < Page > & pages = book.GetPages ();
		BinaryWriter bw { filepath };

		//-------------------------------------------------------
		//キャンバス辞書の保存
		SaveCanvasDic ( bw, book );

		//-------------------------------------------------------
		//ページ枚数
		bw.write ( static_cast < uint32 > ( pages.size() ) );

		//各ページ
		for ( const Page & page : pages )
		{
			Image img = page.Image();
			size_t img_bytes = img.size_bytes();
			int32 w = img.width();
			int32 h = img.height();

			//サイズ ( 全体, w, h )
			bw.write ( & img_bytes, sizeof ( size_t ) );
			bw.write ( & w, sizeof ( int32 ) );
			bw.write ( & h, sizeof ( int32 ) );

			//実データ
			bw.write ( img.data (), img_bytes );
		}
	}


	//Bookから.atlsの保存 Image+lz4形式
	void SaveAtlasImgLz4 ( const s3d::String & filepath, const Book & book )
	{
		const Array < Page > & pages = book.GetPages ();

		//一旦メモリに書出
		MemoryWriter mw;

		//-------------------------------------------------------
		//キャンバス辞書の保存
		SaveCanvasDic ( mw, book );

		//-------------------------------------------------------
		//ページ枚数
		mw.write ( static_cast < uint32 > ( pages.size() ) );

		//各ページ
		for ( const Page & page : pages )
		{
			Image img = page.Image();
			size_t img_bytes = img.size_bytes();
			int32 w = img.width();
			int32 h = img.height();

			//サイズ ( 全体, w, h )
			mw.write ( & img_bytes, sizeof ( size_t ) );
			mw.write ( & w, sizeof ( int32 ) );
			mw.write ( & h, sizeof ( int32 ) );

			//実データ
			mw.write ( img.data (), img_bytes );
		}

		//---------------------------------------
		//圧縮
		size_t srcSz = mw.size();
		int maxSz = LZ4_compressBound ( static_cast < int > ( srcSz ) );
		Blob compressed ( maxSz );
		int compressed_size = LZ4_compress_default
		(
			reinterpret_cast <const char*> (mw.retrieve().data()),
			reinterpret_cast <char*> (compressed.data()),
			static_cast <int> (srcSz),
			maxSz
		);


		//---------------------------------------
		//ファイルに書出
		BinaryWriter bw { filepath };

		//先頭に元のファイルサイズを記録する [size_t : 8byte]
		bw.write ( & srcSz, sizeof ( srcSz ) );
		bw.write ( compressed.data(), compressed_size );
	}


	//Bookから.atlsの保存 png形式
	void SaveAtlasPng ( const s3d::String & filepath, const Book & book )
	{
		const Array < Page > & pages = book.GetPages ();
		BinaryWriter bw { filepath };

		//-------------------------------------------------------
		//キャンバス辞書の保存
		SaveCanvasDic ( bw, book );

		//-------------------------------------------------------
		//ページ枚数
		bw.write ( static_cast < uint32 > ( pages.size() ) );

		//各ページ
		for ( const Page & page : pages )
		{
			Blob blob = page.Image().encodePNG();
			size_t img_bytes = blob.size_bytes();

			//サイズ ( 全体 )
			bw.write ( & img_bytes, sizeof ( size_t ) );

			//実データ
			bw.write ( blob.data (), img_bytes );
		}
	}

	//Bookから.atlsの保存 png+lz4形式
	void SaveAtlasPngLz4 ( const s3d::String & filepath, const Book & book )
	{
		const Array < Page > & pages = book.GetPages ();

		//一旦メモリに書出
		MemoryWriter mw;

		//-------------------------------------------------------
		//キャンバス辞書の保存
		SaveCanvasDic ( mw, book );

		//-------------------------------------------------------
		//ページ枚数
		mw.write ( static_cast < uint32 > ( pages.size() ) );

		//各ページ
		for ( const Page & page : pages )
		{
			Blob blob = page.Image().encodePNG();
			size_t img_bytes = blob.size_bytes();

			//サイズ ( 全体 )
			mw.write ( & img_bytes, sizeof ( size_t ) );

			//実データ
			mw.write ( blob.data (), img_bytes );
		}


		//---------------------------------------
		//圧縮
		size_t srcSz = mw.size();
		int maxSz = LZ4_compressBound ( static_cast < int > ( srcSz ) );
		Blob compressed ( maxSz );
		int compressed_size = LZ4_compress_default
		(
			reinterpret_cast <const char*> (mw.retrieve().data()),
			reinterpret_cast <char*> (compressed.data()),
			static_cast <int> (srcSz),
			maxSz
		);


		//---------------------------------------
		//ファイルに書出
		BinaryWriter bw { filepath };

		//先頭に元のファイルサイズを記録する [size_t : 8byte]
		bw.write ( & srcSz, sizeof ( srcSz ) );
		bw.write ( compressed.data(), compressed_size );
	}


	void SaveCanvasDic( BinaryWriter & bw, const Book & book )
	{
		//キャンバス辞書の保存
		const AryCanvas & aryCvs = book.GetAryCanvas ();

		//元ファイル数
		bw.write ( static_cast < uint32 > ( aryCvs.size() ) );

		//各キャンバス
		for ( const Canvas & canvas : aryCvs )
		{
			//タイル配列
			const Array < Tile > & tiles = canvas.GetTiles ();

			//名前は保存しない

			//タイル数
			bw.write ( static_cast < uint32 > ( tiles.size() ) );

			//タイルの保存
			for ( const Tile & tile : tiles )
			{
				bw.write ( tile.X() );
				bw.write ( tile.Y() );
				bw.write ( tile.GetPage() );
				bw.write ( tile.U() );
				bw.write ( tile.V() );
				bw.write ( tile.GetHash() );

				if (tile.GetHash())
				{
					continue;
				}
			}

			//タイル縦横
			bw.write ( canvas.W() );
			bw.write ( canvas.H() );
		}
	}


	void SaveCanvasDic( IWriter & writer, const Book & book )
	{
		//キャンバス辞書の保存
		const AryCanvas & aryCvs = book.GetAryCanvas ();

		//元ファイル数
		writer.write ( static_cast < uint32 > ( aryCvs.size() ) );

		//各キャンバス
		for ( const Canvas & canvas : aryCvs )
		{
			//タイル配列
			const Array < Tile > & tiles = canvas.GetTiles ();

			//名前は保存しない

			//タイル数
			writer.write ( static_cast < uint32 > ( tiles.size() ) );

			//タイルの保存
			for ( const Tile & tile : tiles )
			{
				writer.write ( tile.X() );
				writer.write ( tile.Y() );
				writer.write ( tile.GetPage() );
				writer.write ( tile.U() );
				writer.write ( tile.V() );
				writer.write ( tile.GetHash() );

				if (tile.GetHash())
				{
					continue;
				}
			}

			//タイル縦横
			writer.write ( canvas.W() );
			writer.write ( canvas.H() );
		}
	}


	//C#からバイナリで.png形式をまとめた.imgファイルから作成
	Book CreateBookImg ( const s3d::String & filepath )
	{
		//-----------------------------------------------
		//戻り値で返してもコピーは発生しません（ほぼ常に）
		//C++17 以降では、以下の最適化が標準で保証されます：
		//	・NRVO（Named Return Value Optimization）
		//	・ムーブ省略（C++17 で強化）
		//-----------------------------------------------
		Book book;	//戻値

		//ファイルパス存在確認
		if ( ! FS::exists  ( filepath.str() ) ) { return book; }


		//バイナリリーダ
		s3d::BinaryReader br { filepath };
		if ( not br ) { throw s3d::Error { filepath }; }

		//ファイル数
		uint32 filenum = 0;
		br.read ( filenum );

		//キャンバス保存
		s3d::Array < Canvas > cvss ( filenum );


		//ファイルでループ
		for ( uint32 nf = 0; nf < filenum; ++ nf )
		{
			//名前サイズ(1バイト)
			uint8_t namesize = 0;
			br.read ( namesize );

			//名前
			vector < byte > buf ( namesize );
			br.read ( buf.data(), buf.size() );
			std::string name( reinterpret_cast < char* > ( buf.data() ), buf.size() );

			s3d::String s3dStr = s3d::Unicode::FromUTF8 ( name );
			s3d::Logger << s3dStr << U"\n";

			//1ファイルの記録
			Canvas canvas;
			canvas.SetName ( s3dStr );


			//ハッシュのためのTile保存
			std::unordered_map < uint32_t, Tile > map_hash_tile;


			//実データサイズ
			uint32 imgsize = 0;
			br.read ( imgsize );

			vector < byte > bufImg ( imgsize );
			br.read ( bufImg.data(), bufImg.size() );

			//メモリ上の.pngからImageに変換
			s3d::MemoryReader mr ( bufImg.data(), imgsize );
			s3d::Image img { std::move ( mr ), s3d::ImageFormat::PNG };

			//ImageをCompress
			Compress cmpr;
			cmpr.Do ( img, canvas );

			//Bookに追加
			book.AddCompress ( cmpr, canvas, map_hash_tile );
			book.AddMap ( s3dStr, canvas );

			cvss [ nf ] = canvas;
		}

		//まとめてBookにコピー
		book.CopyFromAryCanvas(cvss);

		return book;
	}


	//.Imgファイルを.atlsファイルに変換
	void ImgToAtlasFile ( const s3d::String & filepath )
	{
		Book book = CreateBookImg ( filepath );

		String filename = FileSystem::FileName ( filepath );
		String atlsPath = FileSystem::BaseName(filename) + U".atls";
		SaveAtlasImg ( atlsPath, book );
	}



}	//namespace GAME
