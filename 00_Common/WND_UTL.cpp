//=================================================================================================
//
//	ウィンドウズ ユーティリティ
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "WND_UTL.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	bool WND_UTL::AscKey ( int vKey )
	{
		//仮想キー "VK_**"

		//@info
		//関数の呼び出し時にキーが押されているかどうか、
		//および GetAsyncKeyState の前回の呼び出し後にキーが押されたかどうかを判別します。
		//
		//-> 同一フレームで２回以上判定すると２回め移行 False

		return ( ::GetAsyncKeyState ( vKey ) & 0x0001 );
	}

	void WND_UTL::MoveWindow_toCursor ()
	{
		//カーソル位置の取得
		POINT cursorPos;
		::GetCursorPos ( & cursorPos );
		cursorPos.x -= 400;
		cursorPos.y -= 15;
		s3d::Point pt { cursorPos.x, cursorPos.y };

		//ウィンドウの移動
		s3d::Window::SetPos ( pt );
	}

	void WND_UTL::MoveWindow_toCenter_onCursor ()
	{
		//ウィンドウサイズ
		//	s3d::Window::Resize ( 1600, 900 );
		int32 wnd_w = 1728;
		int32 wnd_h = 972;
		//16:9 で(1280,960)が入るサイズ

		//マウス位置にウィンドウを移動
		s3d::Point pt = s3d::Cursor::Pos () ;
		s3d::Window::SetPos ( pt );

		//ウィンドウ位置のモニタIDを取得
		size_t monitorIndex = s3d::System::GetCurrentMonitorIndex ();
		s3d::Array < s3d::MonitorInfo > a_mInfo = s3d::System::EnumerateMonitors ();
		s3d::MonitorInfo mInfo = a_mInfo [ monitorIndex ];
		s3d::Vec2 mCenter = mInfo.displayRect.center();
		const int32 dev_y = - 32;
		s3d::Window::SetPos ( (int32)mCenter.x - wnd_w / 2, dev_y + (int32)mCenter.y - wnd_h / 2 );

	}

}	//namespace GAME

