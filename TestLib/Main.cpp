//=================================================================================================
//
// メイン ソースコード
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
//	ヘッダファイル　インクルード
//-------------------------------------------------------------------------------------------------
# include <Siv3D.hpp> // Siv3D v0.6.13
#include "Game.h"
#include "GameMain.h"


//-------------------------------------------------------------------------------------------------
//	実装
//-------------------------------------------------------------------------------------------------
using namespace GAME;


//メインループ中の最初の１回
void Init ()
{
#if 0
	//マウス位置にウィンドウを移動
	s3d::Point pt = s3d::Cursor::Pos () ;
	s3d::Window::SetPos ( pt );
#endif // 0

	//カーソル位置の取得
	POINT cursorPos;
	::GetCursorPos ( & cursorPos );
	cursorPos.x -= 700;
	cursorPos.y -= 15;
	s3d::Point pt { cursorPos.x, cursorPos.y };

	s3d::Window::SetPos ( pt );

}


//メインループ
void Main()
{
#if 0
	// 背景の色を設定する | Set the background color
	Scene::SetBackground(ColorF{ 0.6, 0.8, 0.7 });

	// 画像ファイルからテクスチャを作成する | Create a texture from an image file
	const Texture texture{ U"example/windmill.png" };

	// 絵文字からテクスチャを作成する | Create a texture from an emoji
	const Texture emoji{ U"🦖"_emoji };

	// 太文字のフォントを作成する | Create a bold font with MSDF method
	const Font font{ FontMethod::MSDF, 48, Typeface::Bold };

	// テキストに含まれる絵文字のためのフォントを作成し、font に追加する | Create a font for emojis in text and add it to font as a fallback
	const Font emojiFont{ 48, Typeface::ColorEmoji };
	font.addFallback(emojiFont);

	// ボタンを押した回数 | Number of button presses
	int32 count = 0;

	// チェックボックスの状態 | Checkbox state
	bool checked = false;

	// プレイヤーの移動スピード | Player's movement speed
	double speed = 200.0;

	// プレイヤーの X 座標 | Player's X position
	double playerPosX = 400;

	// プレイヤーが右を向いているか | Whether player is facing right
	bool isPlayerFacingRight = true;
#endif // 0

	//ウィンドウ設定
	s3d::Size size = s3d::Scene::Size ();
	s3d::Scene::SetResizeMode ( s3d::ResizeMode::Virtual );
	s3d::Scene::Resize ( 1280, 960 );

	s3d::Scene::SetResizeMode ( s3d::ResizeMode::Keep );
	s3d::Window::Resize ( 1600, 900 );
	s3d::Window::SetStyle ( s3d::WindowStyle::Sizable );
	s3d::Window::Centering ();

	//マウス位置にウィンドウを移動
	s3d::Point pt = s3d::Cursor::Pos () ;
	s3d::Window::SetPos ( pt );


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


	//test
//	GameKeyCommand gkc;


//	const PixelShader ps = HLSL { U"example/shader/hlsl/rgb_to_bgr.hlsl", U"PS" };
	const PixelShader ps = HLSL { U"ScreenBlend.hlsl", U"PS" };
	s3d::Texture tx_ef{ U"ef_001.png" };
//	s3d::Texture tx_ef{ U"ef_004.png" };

	//レンダーテクスチャ
	RenderTexture rd_tx{1280, 960, Palette::Lightgreen };

	Texture tx_bg{ U"BG0.png" };



	//test
	Triangle tri{400, 10, 1200, 20, 1100, 800 };
	Circle crc(480, 240, 100);
	RenderTexture rd_tx_tri{1280, 960, Palette::Lightblue };


	//==============================================================
	//メインループ
	bool init = F;
	while ( System::Update() )
	{
#if 0
		// テクスチャを描く | Draw the texture
		texture.draw(20, 20);

		// テキストを描く | Draw text
		font(U"Hello, Siv3D!🎮").draw(64, Vec2{ 20, 340 }, ColorF{ 0.2, 0.4, 0.8 });

		// 指定した範囲内にテキストを描く | Draw text within a specified area
		font(U"Siv3D (シブスリーディー) は、ゲームやアプリを楽しく簡単な C++ コードで開発できるフレームワークです。")
			.draw(18, Rect{ 20, 430, 480, 200 }, Palette::Black);

		// 長方形を描く | Draw a rectangle
		Rect{ 540, 20, 80, 80 }.draw();

		// 角丸長方形を描く | Draw a rounded rectangle
		RoundRect{ 680, 20, 80, 200, 20 }.draw(ColorF{ 0.0, 0.4, 0.6 });

		// 円を描く | Draw a circle
		Circle{ 580, 180, 40 }.draw(Palette::Seagreen);

		// 矢印を描く | Draw an arrow
		Line{ 540, 330, 760, 260 }.drawArrow(8, SizeF{ 20, 20 }, ColorF{ 0.4 });

		// 半透明の円を描く | Draw a semi-transparent circle
		Circle{ Cursor::Pos(), 40 }.draw(ColorF{ 1.0, 0.0, 0.0, 0.5 });

		// ボタン | Button
		if (SimpleGUI::Button(U"count: {}"_fmt(count), Vec2{ 520, 370 }, 120, (checked == false)))
		{
			// カウントを増やす | Increase the count
			++count;
		}

		// チェックボックス | Checkbox
		SimpleGUI::CheckBox(checked, U"Lock \U000F033E", Vec2{ 660, 370 }, 120);

		// スライダー | Slider
		SimpleGUI::Slider(U"speed: {:.1f}"_fmt(speed), speed, 100, 400, Vec2{ 520, 420 }, 140, 120);

		// 左キーが押されていたら | If left key is pressed
		if (KeyLeft.pressed())
		{
			// プレイヤーが左に移動する | Player moves left
			playerPosX = Max((playerPosX - speed * Scene::DeltaTime()), 60.0);
			isPlayerFacingRight = false;
		}

		// 右キーが押されていたら | If right key is pressed
		if (KeyRight.pressed())
		{
			// プレイヤーが右に移動する | Player moves right
			playerPosX = Min((playerPosX + speed * Scene::DeltaTime()), 740.0);
			isPlayerFacingRight = true;
		}

		// プレイヤーを描く | Draw the player
		emoji.scaled(0.75).mirrored(isPlayerFacingRight).drawAt(playerPosX, 540);
#endif // 0

		//初期化
		if ( ! init )
		{
			Init ();
			init = T;
		}


		gameMain.Move ();
		gameMain.Draw ();


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



//		SivInput::Inst()->Is_Keyboard ( SIK_Z );
	}
}

