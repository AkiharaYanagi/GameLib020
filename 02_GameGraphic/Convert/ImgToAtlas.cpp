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
		uint32 filenum = 0;
		br.read ( & filenum, sizeof ( uint32 ) );

		//各キャンバス
		for ( uint32 i = 0; i < filenum; ++ i )
		{
			Canvas cnvs;

			//タイル数
			uint32 tilenum = 0;
			br.read ( & tilenum, sizeof ( uint32 ) );
			cnvs.SetTileSize ( tilenum );

			for ( uint32 t = 0; t < tilenum; ++ t )
			{
				Tile tile;
				int32 x, y;
				br.read ( & x, sizeof ( int32 ) );
				br.read ( & y, sizeof ( int32 ) );
				tile.SetPos ( x, y );

				uint32 page = 0;
				br.read(&page, sizeof(uint32));
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

			int32 w, h;
			br.read ( & w, sizeof ( int32 ) );
			br.read ( & h, sizeof ( int32 ) );
			cnvs.SetTileWH ( w, h );

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
		uint32 filenum = 0;
		br.read ( & filenum, sizeof ( uint32 ) );

		AryCanvas ary_cvs(filenum);

		for ( uint32 i = 0; i < filenum; ++ i )
		{
			Canvas cnvs;

			//タイル数
			uint32 tilenum = 0;
			br.read ( & tilenum, sizeof ( uint32 ) );

			cnvs.SetTileSize ( tilenum );

			for ( uint32 t = 0; t < tilenum; ++ t )
			{
				Tile tile;

				int32 x, y;
				br.read ( & x, sizeof ( int32 ) );
				br.read ( & y, sizeof ( int32 ) );
				tile.SetPos ( x, y );

				uint32 page = 0;
				br.read(&page, sizeof(uint32));
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

			int32 w, h;
			br.read ( & w, sizeof ( int32 ) );
			br.read ( & h, sizeof ( int32 ) );
			cnvs.SetTileWH ( w, h );

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


}	//namespace GAME
