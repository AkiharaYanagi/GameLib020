//=================================================================================================
//
// GameInit ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "GameInit.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	GameInit::GameInit ()
	{
	}

	GameInit::~GameInit ()
	{
	}

	//メインループ中の最初の１回のみの初期化
	void GameInit::Do ()
	{
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

		//OS解像度と拡大率のためウィンドウサイズを再取得
	//	int32 w = s3d::Window::Get;
	//	int32 h = s3d::Window::Get;


		//ウィンドウ開始位置
	#define CURSOR_POS_START 1
	#if CURSOR_POS_START
		//カーソル位置のモニタの中心
		WND_UTL::MoveWindow_toCenter_onCursor ( wnd_w, wnd_h );
	#else
		s3d::Window::Centering ();	//モニタ中央
	#endif // CURSOR_POS_START


		//----------------------------------------
		//カーソル位置を画面外にする
		WindowState winStt = s3d::Window::GetState();
	//	s3d::Cursor::SetPos ( winStt.virtualSize );	//右下
		s3d::Cursor::SetPos ( winStt.virtualSize.x - 165 , -20 );	//右上

	}	

}	//namespace GAME

