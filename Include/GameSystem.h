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

#include "StopWatch.h"


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
		int64 nSumSleep { 0 };
		int64 disp_nSumSleep { 0 };
		double sumSleep { 0 };
		double aveSleep { 0 };

		int64 move { 0 };
		int64 nSumMove { 0 };
		int64 disp_nSumMove { 0 };
		double sumMove { 0 };
		double aveMove { 0 };

		int64 draw { 0 };
		int64 nSumDraw { 0 };
		int64 disp_nSumDraw { 0 };
		double sumDraw { 0 };
		double aveDraw { 0 };

		StopWatch	m_sw;


		//一時停止用
		bool		m_bStop { F };

		//稼働フレーム数
		uint32_t	 frame_time { 0 };

	public:
		GameSystem () {}
		GameSystem ( const GameSystem& rhs ) = delete;
		~GameSystem () {}

		void SystemLoad ();		//シングルトンのクリエイトなど初期化
		void SystemRele	();		//解放

		void Move ();
		void Draw ();

		//メインオブジェクトの設定
		void SetpGameMain ( UP_GameMainBase pGameMain );

		void SetbStop ( bool b ) { m_bStop = b; }

	private:
		static bool m_bMakeArchive;		//アーカイブ作成フラグ

		//フレーム制御
//		void Frame ();
		void _Frame ();
		void _Move ();

		double	m_frame { 0 };
		double	m_start_time { 0 };
		double	m_progress_time { 0 };

		//デバッグ表示切替トグル
		bool m_bDispDebug { T };
		bool m_pre_bDispDebug { T };
		void FlipToggle ();

		//--------------------------------------
		//ディスプレイ位置
		void _DisplayPos ();
		s3d::Rect	m_rectWindow { 0, 0, 0, 0 };
		Array < s3d::MonitorInfo > mnt_info;
		Optional<double> m_refreshRate;

		//ウィンドウ移動感知
		void _WindowMove ();

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

