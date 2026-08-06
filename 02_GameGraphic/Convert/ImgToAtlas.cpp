//=================================================================================================
//
//	ImgToAtlasソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Convert/ImgToAtlas.h"
#include <filesystem>

#include "Convert/ImgToBook.h"

#include "../Atlas/G_Log.h"


#include "lz4.h"
#pragma comment ( lib, "lz4.lib" )
//@info .dllファイルはコピーして参照できる位置に置く


using namespace std;
namespace FS = std::filesystem;
using namespace s3d;


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//----------------------------------------------
	Atlas BookToAtlas ( const Book & book )
	{
		Atlas atlas;

		//辞書をコピー
		atlas.DeepCopyFrom ( book.GetMap () );
		atlas.SetIdCanvas ( book.GetAryCanvas () );

		//テクスチャを設定
		for ( const auto & page : book.GetPages () )
		{
			atlas.AddTexture ( page.Texture () );
		}

		return atlas;
	}

	P_Atlas BookToP_Atlas ( const Book & book )
	{
		P_Atlas atlas = std::make_shared < Atlas > ();

		//辞書をコピー
		atlas->DeepCopyFrom ( book.GetMap () );
		atlas->SetIdCanvas ( book.GetAryCanvas () );

		//テクスチャを設定
		for ( const auto & page : book.GetPages () )
		{
			atlas->AddTexture ( page.Texture () );
		}

		return atlas;
	}


	//----------------------------------------------
	//Atlasの読込(メモリ上でTip単位)
	Atlas LoadAtlas ( const String & filename )
	{
		Atlas atlas;

		s3d::BinaryReader br { filename };
		if (not br) { throw s3d::Error{ filename }; }

		//ページ枚数
		uint32 pagenum = 0;
		br.read ( & pagenum, sizeof ( uint32 ) );

		for ( uint32 i = 0; i < pagenum; ++ i )
		{
			Page page;
			page.FromMemStrm ( br );

			//ページからテクスチャを作成してAtlasに追加
			atlas.AddTexture(page.Texture());
		}

		return atlas;
	}

	//Atlasの読込(メモリ上でImage単位)
	Atlas LoadAtlasImg ( const String & filename )
	{
		Atlas atlas;

		s3d::BinaryReader br { filename };
		if (not br) { throw s3d::Error{ filename }; }

		//-------------------------------------------------------
		//キャンバス辞書の読込
		LoadCanvasDic ( br, atlas );

		//-------------------------------------------------------
		//ページ枚数
		uint32 pagenum = 0;
		br.read ( & pagenum, sizeof ( uint32 ) );

		//各ページ
		for ( uint32 i = 0; i < pagenum; ++ i )
		{
			//サイズ
			size_t imgsize = 0;
			br.read ( & imgsize, sizeof ( size_t ) );
			int32 w = 0;
			br.read ( & w, sizeof ( int32 ) );
			int32 h = 0;
			br.read ( & h, sizeof ( int32 ) );

			//一旦メモリに読み込んで
			//unique_ptr < byte[] > buf = make_unique < byte[] > ( imgsize );		
			//br.read ( buf.get(), imgsize );

			//イメージの作成
			Image img { static_cast < size_t > ( w ), static_cast < size_t > ( h ) };
			br.read ( img.data(), imgsize );
			

			//イメージからテクスチャを作成してAtlasに追加
			atlas.AddTexture( Texture ( img ) );
		}

		return atlas;
	}


	//Atlasの読込(メモリ上でpng形式)
	Atlas LoadAtlasPng ( const String & filename )
	{
		Atlas atlas;

		s3d::BinaryReader br { filename };
		if (not br) { throw s3d::Error{ filename }; }

		//-------------------------------------------------------
		//キャンバス辞書の読込
		LoadCanvasDic ( br, atlas );

		//-------------------------------------------------------
		//ページ枚数
		uint32 pagenum = 0;
		br.read ( & pagenum, sizeof ( uint32 ) );

		//各ページ
		for ( uint32 i = 0; i < pagenum; ++ i )
		{
			//サイズ
			size_t imgsize = 0;
			br.read ( & imgsize, sizeof ( size_t ) );

			//一旦メモリに読み込んで
			Blob buf ( imgsize );
			br.read ( buf.data (), imgsize );

			MemoryReader mr ( buf.data(), imgsize );
			
			//pngからテクスチャを作成してAtlasに追加
			Texture tx { std::move ( mr ) };
			atlas.AddTexture ( tx );
		}

		return atlas;
	}


	//Atlasの読込(メモリ上でpng+lz4形式)
	Atlas LoadAtlasPngLz4 ( const String & filename )
	{
		Atlas atlas;

		s3d::BinaryReader br { filename };
		if (not br) { throw s3d::Error{ filename }; }

		//-------------------------------------------------------
		//キャンバス辞書の読込
		LoadCanvasDic ( br, atlas );

		//-------------------------------------------------------
		//ページ枚数
		uint32 pagenum = 0;
		br.read ( & pagenum, sizeof ( uint32 ) );

		//各ページ
		for ( uint32 i = 0; i < pagenum; ++ i )
		{
			//サイズ
			size_t imgsize = 0;
			br.read ( & imgsize, sizeof ( size_t ) );

			//一旦メモリに読み込んで
			Blob buf ( imgsize );
			br.read ( buf.data (), imgsize );

			MemoryReader mr ( buf.data(), imgsize );
			
			//pngからテクスチャを作成してAtlasに追加
			Texture tx { std::move ( mr ) };
			atlas.AddTexture ( tx );
		}

		return atlas;
	}


	void LoadCanvasDic ( BinaryReader & br, Atlas & atlas )
	{
		//-------------------------------------------------------
		//キャンバス辞書の読込

		//元ファイル数
		uint32_t filenum = 0;
		br.read ( & filenum, sizeof ( uint32_t ) );

		//各キャンバス
		for ( uint32_t i = 0; i < filenum; ++ i )
		{
			Canvas cnvs;

			//タイル数
			uint32_t tilenum = 0;
			br.read ( & tilenum, sizeof ( uint32_t ) );
			cnvs.SetTileSize ( tilenum );

			for ( uint32_t t = 0; t < tilenum; ++ t )
			{
				Tile tile;
				int32_t x, y;
				br.read ( & x, sizeof ( int32_t ) );
				br.read ( & y, sizeof ( int32_t ) );
				tile.SetPos ( x, y );

				uint32_t page = 0;
				br.read( & page, sizeof ( uint32_t ) );
				tile.SetPage ( page );

				float u, v;
				br.read(&u, sizeof(float));
				br.read(&v, sizeof(float));
				tile.SetUV(u, v);

				bool hash;
				br.read ( & hash, sizeof(bool) );
				tile.SetHash ( hash );
				cnvs.SetTile ( t, tile );
			}

			//タイル縦横
			int32 w, h;
			br.read ( & w, sizeof ( int32_t ) );
			br.read ( & h, sizeof ( int32_t ) );
			cnvs.SetTileWH ( w, h );

			//元テクスチャ縦横
			int32 txw, txh;
			br.read ( & txw, sizeof ( int32_t ) );
			br.read ( & txh, sizeof ( int32_t ) );
			cnvs.SetTxWH ( txw, txh );

			atlas.AddCanvas( cnvs );
		}
	}



	//----------------------------------------------
	//.imgファイルからBookを経由してP_Atlasを作成
	P_Atlas CreateAtlasImg ( const s3d::String & filepath )
	{
		Book book = CreateBookImg ( filepath );

		P_Atlas pAtls = BookToP_Atlas ( book );
		return pAtls;
	}

	//.atlasファイルからP_Atlasを作成
	P_Atlas LoadpAtlasImg ( const String & filename )
	{
		P_Atlas atlas = make_shared < Atlas > ();

		s3d::BinaryReader br { filename };
		if (not br) { throw s3d::Error{ filename }; }


		//Canvas読込
		uint32_t filenum = 0;
		br.read ( & filenum, sizeof ( uint32_t ) );

		AryCanvas ary_cvs ( filenum );

		for ( uint32_t i = 0; i < filenum; ++ i )
		{
			Canvas cnvs;

			//タイル数
			uint32_t tilenum = 0;
			br.read ( & tilenum, sizeof ( uint32_t ) );

			cnvs.SetTileSize ( tilenum );

			for ( uint32_t t = 0; t < tilenum; ++ t )
			{
				Tile tile;

				int32_t x, y;
				br.read ( & x, sizeof ( int32_t ) );
				br.read ( & y, sizeof ( int32_t ) );
				tile.SetPos ( x, y );

				uint32_t page = 0;
				br.read(&page, sizeof(uint32_t));
				tile.SetPage(page);

				float u, v;
				br.read(&u, sizeof(float));
				br.read(&v, sizeof(float));
				tile.SetUV(u, v);

				bool hash;
				br.read ( & hash, sizeof(bool) );
				tile.SetHash ( hash );

				cnvs.SetTile ( t, tile );
			}

			//タイル数
			int32_t w, h;
			br.read ( & w, sizeof ( int32_t ) );
			br.read ( & h, sizeof ( int32_t ) );
			cnvs.SetTileWH ( w, h );

			//元テクスチャサイズ
			int32_t txw, txh;
			br.read ( & txw, sizeof ( int32_t ) );
			br.read ( & txh, sizeof ( int32_t ) );
			cnvs.SetTxWH ( txw, txh );

			//配列に設定
			ary_cvs [ i ] = cnvs;
		}


		//ページ枚数
		uint32 pagenum = 0;
		br.read ( & pagenum, sizeof ( uint32 ) );

		//各ページ
		for ( uint32 i = 0; i < pagenum; ++ i )
		{
			//サイズ
			size_t imgsize = 0;
			br.read ( & imgsize, sizeof ( size_t ) );
			int32 w = 0;
			br.read ( & w, sizeof ( int32 ) );
			int32 h = 0;
			br.read ( & h, sizeof ( int32 ) );

			//イメージの作成
			Image img { static_cast < size_t > ( w ), static_cast < size_t > ( h ) };
			br.read ( img.data(), imgsize );

			//イメージからテクスチャを作成してAtlasに追加
			atlas->AddTexture( Texture ( img ) );

			//キャンバス
			atlas->SetIdCanvas ( ary_cvs );
		}

		return atlas;
	}

	//imgディレクトリからBookを経由してP_Atlasを作成
	P_Atlas CreateAtlasImgDir ( const s3d::String & dirpath )
	{
		Book book = CreateBookFromDir ( dirpath );

		P_Atlas pAtls = BookToP_Atlas ( book );
		return pAtls;
	}


	//.Imgファイルを.atlsファイルに変換
	void ImgToAtlasFile ( const s3d::String & filepath )
	{
		//.ImgファイルからBookを作成
		Book book = CreateBookImg ( filepath );

		//ファイルパス
		String parent_path = FileSystem::ParentPath ( filepath );
		String filename = FileSystem::FileName ( filepath );
		String atlsPath = parent_path + FileSystem::BaseName(filename) + U".atls";

		//.atlsファイルに保存
		SaveAtlasImg ( atlsPath, book );
	}


	//.Imgファイルをpng形式.atlsファイルに変換
	void ImgToAtlasFilePng ( const s3d::String & filepath )
	{
		//.ImgファイルからBookを作成
		Book book = CreateBookImg ( filepath );

		//ファイルパス
		String parent_path = FileSystem::ParentPath ( filepath );
		String filename = FileSystem::FileName ( filepath );
		String atlsPath = parent_path + FileSystem::BaseName(filename) + U".atls";

		//.atlsファイルに保存
		SaveAtlasPng ( atlsPath, book );
	}

	//.atlasファイルからP_Atlasを読込
	P_Atlas LoadAtlasFile ( const s3d::String & filename )
	{
		P_Atlas pAtls = std::make_shared < Atlas > ();

		s3d::BinaryReader br { filename };
		if (not br) { throw s3d::Error{ filename }; }

		//-------------------------------------------------------
		//キャンバス辞書の読込
		LoadCanvasDic ( br, *pAtls );

		//-------------------------------------------------------
		//ページ枚数
		uint32 pagenum = 0;
		br.read ( & pagenum, sizeof ( uint32 ) );

		//各ページ
		for ( uint32 i = 0; i < pagenum; ++ i )
		{
			//サイズ
			size_t imgsize = 0;
			br.read ( & imgsize, sizeof ( size_t ) );
			int32 w = 0;
			br.read ( & w, sizeof ( int32 ) );
			int32 h = 0;
			br.read ( & h, sizeof ( int32 ) );

			//イメージの作成
			Image img { static_cast < size_t > ( w ), static_cast < size_t > ( h ) };
			br.read ( img.data(), imgsize );
			

			//イメージからテクスチャを作成してAtlasに追加
			pAtls->AddTexture( Texture ( img ) );
		}

		return pAtls;
	}

	//.atlasファイルからPng形式でP_Atlasを読込
	P_Atlas LoadAtlasFilePng ( const s3d::String & filename )
	{
		P_Atlas pAtls = std::make_shared < Atlas > ();

		s3d::BinaryReader br { filename };
		if (not br) { throw s3d::Error{ filename }; }

		//-------------------------------------------------------
		//キャンバス辞書の読込
		LoadCanvasDic ( br, *pAtls );

		//-------------------------------------------------------
		//ページ枚数
		uint32 pagenum = 0;
		br.read ( & pagenum, sizeof ( uint32 ) );

		//各ページ
		for ( uint32 i = 0; i < pagenum; ++ i )
		{
			//サイズ
			size_t imgsize = 0;
			br.read ( & imgsize, sizeof ( size_t ) );

			//一旦メモリに読み込んで
			Blob buf ( imgsize );
			br.read ( buf.data (), imgsize );

			MemoryReader mr ( buf.data(), imgsize );
			
			//pngからテクスチャを作成してAtlasに追加
			Texture tx { std::move ( mr ) };
			pAtls->AddTexture ( tx );
		}

		return pAtls;
	}


	void ResetHashHit() { G_HASH_HIT = 0; }
	int32_t GetHashHit() { return G_HASH_HIT; }


}	//namespace GAME
