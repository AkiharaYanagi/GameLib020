//=================================================================================================
//
// ゲームシステム　ヘッダ
//		ゲーム内容の前に必要になるアプリケーションやライブラリとの連動を記述する。
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
//	ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "00_Common.h"
#include "GameMainBase.h"
using CLK = std::chrono::high_resolution_clock;


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//-------------------------------------------------------------------------------------------------
	//	ゲーム内のライブラリ使用など
	//-------------------------------------------------------------------------------------------------
	class GameSystem
	{
		UP_GameMainBase		m_pGameMain;


		//時間計測
		CLK::time_point start_time;
		CLK::time_point now_time;
		CLK::time_point end_time;
		uint32 frame { 0 };
		uint32 frame_ps { 0 };

		CLK::time_point fps_time;
		uint32 fps { 60 };
		double disp_fps { 0 };
		int64 sleep { 0 };
		double aveSleep { 0 };
		double dispSleep { 0 };

		//一時停止用
		bool		m_bStop { F };

	public:
		GameSystem () {}
		GameSystem ( const GameSystem& rhs ) = delete;
		~GameSystem () {}

		void SystemLoad ();		//シングルトンのクリエイトなど初期化

		void Move ();
		void Draw ();

		//メインオブジェクトの設定
		void SetpGameMain ( UP_GameMainBase pGameMain );

		void SetbStop ( bool b ) { m_bStop = b; }

	private:
		static bool m_bMakeArchive;		//アーカイブ作成フラグ

		//フレーム制御
		void Frame ();
		void _Frame ();
		void _Move ();

		double	m_frame { 0 };
		double	m_start_time { 0 };
		double	m_progress_time { 0 };

		//デバッグ表示切替トグル
		bool m_bDispDebug { T };
		bool m_pre_bDispDebug { T };
		void FlipToggle ();

	public:
		//-----------------------------
		//	static 環境設定
		//-----------------------------

		//デバッグ表示をすべてON
		//		static void FullDebugMode () { m_bDispTimer = T; }

		//デバッグ表示をすべてON
		//		static void NoDebugMode () { m_bDispTimer = F; }

		//アーカイブを作成して読み込み
		static void SetFlag_MakeArchive ( bool b ) { m_bMakeArchive = b; }
	};

}

