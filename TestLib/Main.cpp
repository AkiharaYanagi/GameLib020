//=================================================================================================
//
// メイン ソースコード
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
//	ヘッダファイル　インクルード
//-------------------------------------------------------------------------------------------------
//#include <Siv3D.hpp> // Siv3D v0.6.13
#include "Game.h"
#include "GameMain.h"
#include "Mov.h"


//-------------------------------------------------------------------------------------------------
//	実装
//-------------------------------------------------------------------------------------------------
using namespace GAME;


//前方宣言
void Load ();
void Init ();
void Move ();
void Draw ();


//ゲームシステム
GameSystem gameSystem;

//ブレンド用 レンダーテクスチャ
std::unique_ptr < RenderTexture > p_rd_tx;


#if 0

//メインループ
void Main()
{
	//-----------------------------------
	//	SivInput::Create();

	GameMain gameMain;

//	P_Grp grp = std::make_shared < GrpBs > ();
//	grp->SetTextureName ( U"test.png" );
//	gameMain.AddpTask ( grp );

	gameMain.Load ();

//	s3d::Texture tx ( ( U"test.png") );


	//-----------------------------------
	//バイナリリーダ テスト
//	std::unique_ptr < s3d::BinaryReader > pbr = std::make_unique < s3d::BinaryReader > ();
//	pbr->open ( U"test.png" );
	s3d::BinaryReader br ( U"000_立ち_00.png" );
	s3d::Texture tx_from_bin ( std::move ( br ) );


//	s3d::TextureAsset::Register ();

#if 0

//-----------------------------------
	//メモリリーダ テスト
	s3d::BinaryReader br1 ( U"000_立ち_00.png" );
	size_t filesize = br1.size ();
	Byte bb_0[4];
	br1.read ( &bb_0, 4 );
	br1.setPos ( 0 );

	s3d::Array < Byte > array_byte { filesize };
	s3d::BinaryWriter bw1;
	bw1.write ( br1.read ( array_byte.data(), filesize ) );

	Byte b0 = array_byte[0];
	Byte b1 = array_byte[1];
	Byte b2 = array_byte[2];
	Byte b3 = array_byte[3];

	s3d::Image img ( U"000_立ち_00.png" );
//	img.encodePNG ();


	byte bt = 255;

//	s3d::MemoryViewReader mr;
//	s3d::MemoryReader mr ( &bt, 1 );
	s3d::MemoryReader mr ( (void*)array_byte.data(), filesize );


//	mr.read ( (void*)array_byte.data(), filesize );
	int64 nRead = mr.read ( (void*)&bt, 1 );
	ZIPReader zr;
//	zr.extract (U"");

	bool bOpen = mr.isOpen ();

	size_t mr_size = mr.size();
	int64 pos = mr.getPos ();
	mr.setPos ( 0 );
	
	s3d::Texture tx_from_mem ( std::move ( mr ) );


#endif // 0
//-----------------------------------
//test
//	GameKeyCommand gkc;

//-----------------------------------

//	const PixelShader ps = HLSL { U"example/shader/hlsl/rgb_to_bgr.hlsl", U"PS" };
	const PixelShader ps = HLSL { U"ScreenBlend.hlsl", U"PS" };
	s3d::Texture tx_ef{ U"ef_001.png" };
//	s3d::Texture tx_ef{ U"ef_004.png" };

	//レンダーテクスチャ
	RenderTexture rd_tx{1280, 960, Palette::Lightgreen };

	Texture tx_bg{ U"BG0.png" };


	//-----------------------------------

	//test
	Triangle tri{400, 10, 1200, 20, 1100, 800 };
	Circle crc(480, 240, 100);
	RenderTexture rd_tx_tri{1280, 960, Palette::Lightblue };


	//-----------------------------------
	P_PrmRect pPrmRect = std::make_shared < PrmRect > ();
	gameMain.AddpTask ( pPrmRect );


	//==============================================================
	//メインループ
	bool init = F;
	while ( System::Update() )
	{
		//初期化
		if ( ! init )
		{
			Init ();
			init = T;
		}


		gameMain.Move ();

#if 0

//		tx.draw ( 200, 200 );
//		tx_from_bin.draw ( 500, 500 );

//		Graphics2D::SetPSTexture(1, tx_from_bin);
		Graphics2D::SetPSTexture(1, tx_ef);
		{
			const ScopedCustomShader2D shader{ ps };
//			tx_ef.draw(100, 150);
			tx_from_bin.draw(140, 180);
			
		}
#endif // 0

#if 0
#endif // 0
		//レンダーターゲット
		{
			const ScopedRenderTarget2D target{ rd_tx };

			tx_bg.draw(0, 0);
			tx_from_bin.draw(140, 320);

		}
		//ピクセルシェーダ指定
//		Graphics2D::SetPSTexture(1, rd_tx);
		Graphics2D::SetPSTexture(1, tx_ef);
		{
			const ScopedCustomShader2D shader{ ps };
	//		tx_ef.draw(100, 100);
			rd_tx.draw(20, 20);
		}
//		rd_tx.draw(20, 20);


#if 0
		tri.draw();
//		tri(tx_bg(0, 0, 100, 100 )).draw();


		crc.draw();
		crc(tx_bg(0, 0, 100, 100)).draw();
#endif // 0


#if 0
		{
			const ScopedRenderTarget2D target( rd_tx_tri );

			tri.draw();
		}
		rd_tx_tri.draw();
#endif // 0


		//----------------------------
//		tx_from_mem.draw ( 700, 500 );
		tx_from_bin.draw ( 500, 500 );



//		SivInput::Inst()->Is_Keyboard ( SIK_Z );

		gameMain.Draw ();

//		Rect { 200, 200, 200, 200 }.draw ();
	}
}

#endif // 0


//動画テスト
std::unique_ptr < s3d::VideoTexture > p_vtx;


//メイン
void Main()
{
	//読込
	Load ();

#if 0
	//-------------------------------------
	//test
	ColorF color { 1.0, 1.0, 1.0, 1.0 };
	//	ColorF color { 1.0, 0.5, 0.5, 1.0 };
	s3d::Texture ef1 ( U"ef_001.png" );
	s3d::Texture ef4 ( U"ef_004.png" );

	const PixelShader ps = HLSL { U"example/shader/hlsl/rgb_shift.hlsl", U"PS" };
	const PixelShader ps_screen = HLSL { U"ScreenBlend.hlsl", U"PS" };
	//-------------------------------------
#endif // 0

#if 0
	//ブレンド用 レンダーテクスチャ
	p_rd_tx = std::make_unique < RenderTexture > ( 1280, 960, Palette::Lightgreen );

	p_vtx = std::make_unique < s3d::VideoTexture > ( U"raiden.mp4", s3d::Loop::No );
#endif // 0


//test
#if 0
	int i = 0;
	for ( String str : KEYBOARD_STR )
	{
		Console << U"{} "_fmt(i) << str;
		++ i;
	}
#endif // 0


	//========================================
	//メインループ
	bool init = F;
	while ( System::Update() )
	{
		//初期化
		if ( ! init ) { Init (); init = T; }

		//動作
		Move ();

		//描画
		Draw ();
	}
	//========================================
}


//起動後１回のみの初期化
void Load ()
{
#if 0

	//ウィンドウ設定

	//ゲーム表示サイズ
	s3d::Size size = s3d::Scene::Size ();
	s3d::Scene::SetResizeMode ( s3d::ResizeMode::Virtual );
	s3d::Scene::Resize ( 1280, 960 );

	//ウィンドウサイズ
	s3d::Scene::SetResizeMode ( s3d::ResizeMode::Keep );
	s3d::Window::Resize ( 1600, 900 );
	s3d::Window::SetStyle ( s3d::WindowStyle::Sizable );
	s3d::Window::Centering ();

	//マウス位置にウィンドウを移動
	s3d::Point pt = s3d::Cursor::Pos () ;
	s3d::Window::SetPos ( pt );

#endif // 0

	//-------------------------------------
	//システム初期化
	gameSystem.SystemLoad ();

	//ゲームメイン
	UP_GameMain gameMain = std::make_unique < GameMain > ();
	gameMain->Load ();
	gameMain->Init ();

	gameSystem.SetpGameMain ( std::move ( gameMain ) );
}


//メインループ中の最初の１回のみの初期化
void Init ()
{
#if 0
#define CURSOR_POS_START 1
#if CURSOR_POS_START
	//カーソル位置にウィンドウを移動
//	WND_UTL::MoveWindow_toCursor ();
	WND_UTL::MoveWindow_toCenter_onCursor ();
#else
	//中央
	s3d::Window::Centering ();
#endif // 0


	//test サウンド
	//	SOUND->Play_BGM ( 1 );
#endif // 0


	//ウィンドウ設定

	//ゲーム表示サイズ
	s3d::Size size = s3d::Scene::Size ();
	s3d::Scene::SetResizeMode ( s3d::ResizeMode::Virtual );
	s3d::Scene::Resize ( 1280, 960 );
	//	s3d::Scene::Resize ( 1200, 900 );

	//ウィンドウサイズ
	s3d::Scene::SetResizeMode ( s3d::ResizeMode::Keep );
	//	s3d::Window::Resize ( 1600, 900 );
	int32 wnd_w = 1728;
	int32 wnd_h = 972;
	s3d::Window::Resize ( wnd_w, wnd_h );	//16:9 で(1280,960)が入るサイズ
	s3d::Window::SetStyle ( s3d::WindowStyle::Sizable );

	//位置
#define CURSOR_POS_START 0
#if CURSOR_POS_START
	s3d::Window::Centering ();	//モニタ中央
#else
	//カーソル位置のモニタの中心
	WND_UTL::MoveWindow_toCenter_onCursor ( wnd_w, wnd_h );
#endif // 0

}



void Move ()
{
	//---------------------------------------------------
	// 動作
	//---------------------------------------------------
#if 0
	//毎回の更新
	const Array<Input> & keys = s3d::Keyboard::GetAllInputs();
	SivInput::Inst()->Update ( keys );
#endif // 0

	//ゲームメイン
	//gameMain->Move ();
	gameSystem.Move ();
}



void Draw ()
{
//	s3d::ClearPrint();

	//---------------------------------------------------
	// 描画
	//---------------------------------------------------
	gameSystem.Draw ();


	//ブレンドテスト
#if 0
	{
		const ScopedColorMul2D colorMul { color };
		//			const ScopedRenderStates2D blend { BlendState::Multiplicative };
		ef4.draw ( 250, 400 );
		ef1.draw ( 30, 390 );

		//イメージ
		//ブレンド：スクリーン
		// 1 - ( 1 - A )( 1 - B );
	}

	{
		//			const ScopedCustomShader2D shader { ps };
		const ScopedCustomShader2D shader { ps_screen };
		ef1.draw ( 30, 390 );
	}
#endif // 0


	//レンダーターゲット指定
#if 0

	{
		const s3d::ScopedRenderTarget2D target { * p_rd_tx };

		//ゲームメイン描画
		//gameMain->Draw ();
		gameSystem.Draw ();

	}
	p_rd_tx->draw ();

#endif // 0



	//ピクセルシェーダ指定
#if 0
	//		s3d::Graphics2D::SetPSTexture ( 1, rd_tx );	//適用テクスチャを指定
	s3d::Graphics2D::SetPSTexture ( 1, ef1 );	//適用テクスチャを指定
	//		s3d::Graphics2D::SetPSTexture ( 1, ef4 );	//適用テクスチャを指定
	{
		//			const s3d::ScopedCustomShader2D shader { ps };
		const s3d::ScopedCustomShader2D shader { ps_screen };
		//			ef1.draw ( 30, 390 );
		//			ef4.draw ( 250, 400 );
		rd_tx.draw ();
	}
#endif // 0


//	p_vtx->advance ();
//	p_vtx->draw();

}
