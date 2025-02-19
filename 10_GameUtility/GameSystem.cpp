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

		//アプリケーション設定ファイル
#if 0
		//設定からウィンドウ状態の取得
		UINT window_w = AppSettingFile::Inst ()->GetWindowW ();
		UINT window_h = AppSettingFile::Inst ()->GetWindowH ();
		bool bFullScreen = AppSettingFile::Inst ()->GetbFullscreen ();
		int displayNum = AppSettingFile::Inst ()->GetDisplayNum ();
#endif // 0
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


#if 0
		//サウンドの生成
		DxSound::Create ();
		DxSound::instance()->Load();
#endif // 0

		//サウンドアーカイバの初期化

#if 0

		SoundArchiver::Create ();

#if	_DEBUG
		//デバッグ時 かつ フラグON のみアーカイブファイルを生成する
		if ( m_bMakeArchive )
		{
			SoundArchiver::Inst ()->Make ();
		}
#endif	//_DEBUG
		SoundArchiver::Inst()->Open ();		//アーカイブファイルの読込

		//設定ファイルから音量設定

		//音量の設定
		//設定値(0-100) => 実効値( 0.0 ~ 1.0 )
		int32 vlm = APP_STG()->GetSoundVolume ();
		SOUND->SetVolume ( (double)vlm / 100.0 );

#endif // 0


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


	}


	//フレーム毎動作
	void GameSystem::Move ()
	{
//		Frame ();
//		_Move ();
		_Frame ();
	}


	void GameSystem::Frame ()
	{
		//----------------------------------------------
		//時間計測
		const double FPS = 60;
		const double IDEAL_TIME = 1.0 / FPS;

		//現在時間
		double now_time = s3d::Scene::DeltaTime ();


		//経過時間
		m_progress_time += now_time;

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


	void GameSystem::_Frame ()
	{
		//フレーム制御
		now_time = CLK::now ();
		duration drtn = duration_cast < microseconds > ( now_time - start_time );
		long long mcsec = drtn.count ();

#if 0
#endif // 0


		//144Hz など規定時刻より早いとき
		if ( 16666 > mcsec )
		{
			//早い時間だけスリープ
			sleep = 16666 - mcsec - 700;
			std::this_thread::sleep_for ( microseconds ( sleep ) );
			aveSleep += sleep;
		}
		//遅いときはそのまま実行

		start_time = CLK::now ();

		//動作
		_Move ();

		++ frame;
		++ frame_ps;


		//FPS計測
		duration drtn_fps = duration_cast < microseconds > ( now_time - fps_time );
		long long mcsec_fps = drtn_fps.count ();

		if ( 1000000 <= mcsec_fps )
		{
			fps = frame_ps;
			frame_ps = 1;

			dispSleep = aveSleep / frame;
			aveSleep = 0;

			fps_time = CLK::now ();
			disp_fps = mcsec_fps;
		}

		s3d::ClearPrint ();
		s3d::Print << U"Frame:" << frame;
		s3d::Print << U"FPS:" << fps;
		s3d::Print << U"sleep:" << dispSleep;
		s3d::Print << U"drtn_fps:" << disp_fps;
	}


	//フレーム毎動作
	void GameSystem::_Move ()
	{
		//----------------------------------------------
		//稼働フレーム数
		static UINT frame_time = 0;

		//----------------------------------------------
		// 'W'キーでスタート/ストップのトグル切替
		static bool bStop = false;
		if( WND_UTL::AscKey ( 'W' ) )
		{
			bStop ^= true; 
		}
		//----------------------------------------------
		// ストップ時、'Q'キーで 1 フレームずつ進ませる
		if( ! bStop || WND_UTL::AscKey ( 'Q' ) )
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
		//全体レンダーテクスチャのクリア
		G_GrpTx::Inst()->Clear ();

		//グラフィックリストから描画
		GRPLST_DRAW ();

		//デバッグ表示から描画
		DBGOUT_WND()->Draw ();

		//全体レンダーテクスチャの描画
		G_GrpTx::Inst()->Draw ();
	}


	//メインオブジェクトの設定
	void GameSystem::SetpGameMain ( UP_GameMainBase pGameMain )
	{
		m_pGameMain = std::move ( pGameMain ); 
	}


}	//namespace GAME

