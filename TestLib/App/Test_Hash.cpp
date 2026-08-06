//=================================================================================================
//
//	テスト
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Test_Hash.h"
#include "02_GameGraphic.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	Test::Test ()
	{
		m_grpAtlas = std::make_shared < GrpAtlas > ();
		m_grpAtlas->SetPos ( 0, 480 );
		GRPLST_INSERT ( m_grpAtlas );

		m_grpAtlasRow = std::make_shared < GrpAtlas > ();
		m_grpAtlasRow->SetPos ( 0, 0 );
		GRPLST_INSERT ( m_grpAtlasRow );

		m_grpAtlasPoster = std::make_shared < GrpAtlas > ();
		m_grpAtlasPoster->SetPos ( 640, 0 );
		GRPLST_INSERT ( m_grpAtlasPoster );
	}

	Test::~Test ()
	{
	}

	void Test::Load ()
	{
		Base ();

		//ResetHashHit ();

		//Row ();

		//ResetHashHit ();

		//Poster ();

		m_tx = Texture ( U"B1_03_row.png" );

		TASK_VEC::Load ();
	}

	void Test::Base ()
	{
		Book book;	//戻値
		//ハッシュのためのTile保存
		std::unordered_map < uint32_t, Tile > map_hash_tile;
		//キャンバス保存
		s3d::Array < Canvas > cvss ( 1 );

		//s3d::String name = U"B1_03.png";
		s3d::String name = U"B1_03_pst4.png";


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

		cvss [ 0 ] = canvas;
		//まとめてBookにコピー
		book.CopyFromAryCanvas(cvss);

		m_grpAtlas->SetpAtlas ( BookToP_Atlas (book) );

		PRINT_F_S ( U"Hash Hit = {}"_fmt( GetHashHit () ) );

	}


	void Test::Row ()
	{
		Book book;	//戻値
		//ハッシュのためのTile保存
		std::unordered_map < uint32_t, Tile > map_hash_tile;
		//キャンバス保存
		s3d::Array < Canvas > cvss ( 1 );

		s3d::String name = U"B1_03_row.png";


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

		cvss [ 0 ] = canvas;
		//まとめてBookにコピー
		book.CopyFromAryCanvas(cvss);

		m_grpAtlasRow->SetpAtlas ( BookToP_Atlas (book) );

		PRINT_F_S ( U"Hash Hit = {}"_fmt( GetHashHit () ) );

	}

	void Test::Poster ()
	{
		Book book;	//戻値
		//ハッシュのためのTile保存
		std::unordered_map < uint32_t, Tile > map_hash_tile;

		//キャンバス保存
		s3d::Array < Canvas > cvss ( 1 );

		s3d::String name = U"B1_03_poster.png";


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

		cvss [ 0 ] = canvas;
		//まとめてBookにコピー
		book.CopyFromAryCanvas(cvss);

		m_grpAtlasPoster->SetpAtlas ( BookToP_Atlas (book) );

		PRINT_F_S ( U"Hash Hit = {}"_fmt( GetHashHit () ) );

	}




}	//namespace GAME

