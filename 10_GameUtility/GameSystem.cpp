//=================================================================================================
//
// ゲームシステム　クラス定義
//		ゲーム内容の前に必要になるアプリケーションやライブラリとの連動を記述する。
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "GameSystem.h"
#include "DebugOutGameWindow.h"
#include "AppSettingFile.h"

#include "01_GameStructure.h"
#include "02_GameGraphic.h"
#include "03_GameInput.h"
#include "04_GameFile.h"

using namespace std::chrono;


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//static実体
	bool GameSystem::m_bMakeArchive = true;


	//各種シングルトンのクリエイトなど1回のみの初期化
	void GameSystem::SystemLoad ()
	{
		//----------------------------
		//	システム初期化
		//----------------------------

		//ウィンドウハンドル保存
		HWnd::_Get();

		//アプリケーション設定ファイルを読込
		APP_STG()->Create ();
		APP_STG()->Load ();

		//入力
		SivInput::Create ();

		//キーコンフィグ
		KeyConfig::Create ();
		KeyConfig::Inst()->Load ();


		//共通フォント
		G_Font::Create ();
		G_Font::Inst()->Load ();

		//Graphic配列の初期化
		GRPLST_CREATE ();

		//ゲーム画面デバッグ表示
		DebugOutGameWindow::Create ();
		DebugOutGameWindow::Inst()->Load ();


		//グラフィックファイルアーカイバの初期化
		Archiver::Create ();
#if	_DEBUG
		//デバッグ時 かつ フラグON のみアーカイブファイルを生成する
		if ( m_bMakeArchive )
		{
			Archiver::Inst()->Make ();
		}
#endif	//_DEBUG
		Archiver::Inst()->Open ();		//アーカイブファイルの読込




		//サウンドアーカイバの初期化
#if 0


		//新規サウンド
		GameSound::Create ();
		GameSound::Inst()->Load ();
#if	_DEBUG
		//デバッグ時 かつ フラグON のみアーカイブファイルを生成する
		if ( m_bMakeArchive )
		{
			GameSound::Inst()->Make ();
	}
#endif	//_DEBUG
		GameSound::Inst()->Open ();		//アーカイブファイルの読込


		//設定ファイルから音量設定
		//設定値(0-100) => 実効値( 0.0 ~ 1.0 )
		int32 vlm = APP_STG()->GetSoundVolume ();
		SND()->SetVolume ( (double)vlm / 100.0 );

#if 0
		//LONG vlm = AppSettingFile::Inst()->GetSoundVolume();	//0-100
		LONG vlm = 50;	//0-100

//		LONG revised_vlm = 4 * ( vlm * 10 - 1000 );
		LONG revised_vlm = -( 100 - vlm ) * ( 100 - vlm );
		SOUND->SetVolume ( revised_vlm );
#endif // 0

#endif // 0


		//設定ファイルから音量設定
		//設定値(0-100) => 実効値( 0.0 ~ 1.0 )
		int32 vlm = APP_STG()->GetSoundVolume ();

		//グローバルオーディオの初期化
		G_Audio::Create();
		G_Audio::Inst()->Asset();
		G_Audio::Inst()->SetVolume((double)vlm / 100.0);
		G_Audio::Inst()->HandLoadAsync ();

		//-------------------------------


		//ディスプレイ位置の取得
		m_rectWindow = s3d::Window::GetState().bounds;
		mnt_info = s3d::System::EnumerateMonitors ();

		int32_t mnt_id = -1;

		for ( const auto& info : mnt_info )
		{
			if ( info.displayRect.intersects(m_rectWindow) )
			{
				break;
			}
			++ mnt_id;
		}

		m_refreshRate = mnt_info[mnt_id].refreshRate;


		//-------------------------------
		m_sw.Start ();
	}


	void GameSystem::SystemRele ()
	{
		//Graphic配列の解放
		GRPLST_CLEAR ();

	}


	//フレーム毎動作
	void GameSystem::Move ()
	{
		_WindowMove();	//ウィンドウ移動感知
//		Frame ();
//		_Move ();
		_Frame ();
	}

#if 0

	void GameSystem::Frame ()
	{
		//----------------------------------------------
		//時間計測
		const double FPS = 60;
		const double IDEAL_TIME = 1.0 / FPS;

		//現在時間
		double _now_time = s3d::Scene::DeltaTime ();


		//経過時間
		m_progress_time += _now_time;

#if 0

		double sleep_time = 0;
		if ( m_progress_time < IDEAL_TIME )
		{
			sleep_time = IDEAL_TIME - m_progress_time;
			auto t = std::chrono::duration < double > ( sleep_time );
			std::this_thread::sleep_for ( t );
			s3d::ClearPrint ();
			s3d::Print ( IDEAL_TIME );
			s3d::Print ( m_progress_time );
			s3d::Print ( sleep_time );
		}

#endif // 0

		//経過時間が理想時間より過ぎていたら動作
		if ( IDEAL_TIME <= m_progress_time )
		{
			m_progress_time = 0;

			//フレーム毎動作
			_Move ();

			//FPSの更新 : 1[Second]
			if ( m_frame > FPS )
			{
				s3d::ClearPrint ();
				s3d::Print ( m_frame );

				auto now_fps = std::chrono::system_clock::now ();
				auto dulation_fps = std::chrono::duration_cast < std::chrono::milliseconds > ( now_fps.time_since_epoch () );
				double dulation_time = (double)dulation_fps.count ();
				double fps_d = m_frame / ( dulation_time - m_start_time ); 
				s3d::Print ( dulation_time - m_start_time );
				s3d::Print ( fps_d );

				m_frame = 0;
				m_start_time = dulation_time;
			}
			else
			{
				++ m_frame;
			}
		}
	}

#endif // 0


	void GameSystem::_Frame ()
	{
		m_sw.ReStart();


		//フレーム制御
		now_time = CLK::now ();
		duration drtn = duration_cast < microseconds > ( now_time - start_time );
		long long mcsec = drtn.count ();


		//144Hz など規定時刻より早いとき
		if ( 16666 - 700 > mcsec )
		{
			//早い時間だけスリープ	Draw()分700減算
			sleep = 16666 - 700 - mcsec;
			std::this_thread::sleep_for ( microseconds ( sleep ) );
			nSumSleep += sleep;
			sumSleep += sleep;
		}
		//遅いときはそのまま実行



		m_sw.Lap ( DBGOUT_4, U"Sleep" );

		start_time = CLK::now ();



		//動作
		_Move ();

		//m_sw.Lap ( DBGOUT_5, U"_Move" );


		duration drtn_move = duration_cast <microseconds> ( CLK::now() - start_time );
		nSumMove += static_cast < int64 > ( drtn_move.count() );
		sumMove += static_cast < int64 > ( drtn_move.count() );


		++ frame;
		++ frame_ps;


		//FPS計測
		duration drtn_fps = duration_cast < microseconds > ( now_time - fps_time );
		long long mcsec_fps = drtn_fps.count ();

		if ( 1000000 <= mcsec_fps )
		{
			fps = frame_ps;
			frame_ps = 1;

			//累計をフレーム数で割って平均値を算出
			aveSleep = sumSleep / frame;
			disp_nSumSleep = nSumSleep;
			nSumSleep = 0;
			sumSleep = 0;
			
			aveMove = sumMove / frame;
			disp_nSumMove = nSumMove;
			nSumMove = 0;
			sumMove = 0;
			
			aveDraw = sumDraw / frame;
			disp_nSumDraw = nSumDraw;
			nSumDraw = 0;
			sumDraw = 0;

			fps_time = CLK::now ();


			//余剰分[mcsec]を次の60FPSのパーセンテージで減算
			disp_fps = (double)fps - 60.0 * ( (double)mcsec_fps - 1000000 ) / 1000000;
		}


		//デバッグ表示
		double rr = ( m_refreshRate.has_value () ) ? m_refreshRate.value() : 60;
		DBGOUT_WND()->DebugOutWnd_FPS ( rr, disp_fps );

		m_sw.Lap ( DBGOUT_2, U"Move" );
	}


	//フレーム毎動作
	void GameSystem::_Move ()
	{
		//----------------------------------------------

		FlipToggle ();	//デバッグ表示切替トグル

		//----------------------------------------------
		// 'W'キーでスタート/ストップのトグル切替
//		static bool bStop = false;
		if( WND_UTL::AscKey ( 'W' ) )
		{
//			bStop ^= true; 
			m_bStop ^= true; 
		}
		//----------------------------------------------
		// ストップ時、'Q'キーで 1 フレームずつ進ませる
//		if( ! bStop || WND_UTL::AscKey ( 'Q' ) )
		if( ! m_bStop || WND_UTL::AscKey ( 'Q' ) )
		{
			//入力の更新
			SivInput::Inst()->Update ();

			//フレーム毎の動作	
			m_pGameMain->Move ();

			//ゲーム画面におけるデバッグ表示の動作
//			DBGOUT_WND()->Move ();
			
			//入力の保存
			SivInput::Inst()->Store ();

			DBGOUT_WND()->DebugOutWnd_Frame ( frame_time );
			++ frame_time;
		}
		//----------------------------------------------

#if 0
		DxSound::instance ()->Move ();	//サウンドの更新
#endif // 0

	}


	//描画
	void GameSystem::Draw()
	{
		//--------------------------------------------
		CLK::time_point s = CLK::now ();
		//--------------------------------------------


		m_sw.ReStart ();
		//--------------------------------------------

		//全体レンダーテクスチャのクリア
		G_GrpTx::Inst()->Clear ();

		//グラフィックリストから描画
		GRPLST_DRAW ();

		//デバッグ表示から描画
		DBGOUT_WND()->Draw ();

		//全体レンダーテクスチャの描画
		G_GrpTx::Inst()->Draw ();

		//--------------------------------------------
		CLK::time_point draw_time = CLK::now();
		duration drtn_draw = duration_cast <microseconds> (draw_time - s);
		nSumDraw += static_cast < int64 > ( drtn_draw.count() );
		sumDraw += static_cast < int64 > ( drtn_draw.count() );
		//--------------------------------------------
		m_sw.Lap ( DBGOUT_3, U"Draw" );

		double sw_aveMove = m_sw.GetAve(DBGOUT_2);
		double sw_aveDraw = m_sw.GetAve(DBGOUT_3);
		double sw_aveSleep = m_sw.GetAve(DBGOUT_4);
		double add = sw_aveMove + sw_aveDraw + sw_aveSleep;
		String str = U"{:2.4f}={:2.4f}+{:2.4f}+{:2.4f}[ms] {}"_fmt(add, sw_aveMove, sw_aveDraw, sw_aveSleep, U"Sum");
		//DBGOUT_WND_F ( DBGOUT_1, str );

		DBGOUT_WND()->DebugOutWnd_SleepMoveDraw ( sw_aveMove, sw_aveMove, sw_aveDraw );
		//DBGOUT_WND()->DebugOutWnd_SleepMoveDraw ( disp_nSumSleep, disp_nSumMove, disp_nSumDraw );

		m_sw.Count ();
	}


	//メインオブジェクトの設定
	void GameSystem::SetpGameMain ( UP_GameMainBase pGameMain )
	{
		m_pGameMain = std::move ( pGameMain ); 
	}


	//デバッグ表示切替トグル
	void GameSystem::FlipToggle()
	{
		bool is_bDispDebug = WND_UTL::AscKey ( VK_F8 );

		//今回押した瞬間ならば、1回のみ切替
		if ( ! m_pre_bDispDebug && is_bDispDebug )	// false -> true
		{
			if ( m_bDispDebug )
			{
				//デバッグ表示オフ
				DBGOUT_WND_OFF ();
				m_bDispDebug = F;
			}
			else
			{
				//デバッグ表示オン
				DBGOUT_WND_ON ();
				m_bDispDebug = T;
			}
		}
		//今回の保存
		m_pre_bDispDebug = is_bDispDebug;

	}


	void GameSystem::_DisplayPos()
	{
		//ディスプレイ位置の取得
		m_rectWindow = s3d::Window::GetState().bounds;
	}


	void GameSystem::_WindowMove()
	{
		//ウィンドウの移動を感知する
		s3d::Rect window_rect = s3d::Window::GetState().bounds;
		if ( window_rect != m_rectWindow )
		{
			m_rectWindow = window_rect;

			//再取得
			mnt_info = s3d::System::EnumerateMonitors ();
			int32_t mnt_id = 0;

			for ( const auto& info : mnt_info )
			{
				if ( info.displayRect.intersects(m_rectWindow) )
				{
					break;
				}
				++ mnt_id;
			}

			m_refreshRate = mnt_info[mnt_id].refreshRate;

		}

	}

}	//namespace GAME

