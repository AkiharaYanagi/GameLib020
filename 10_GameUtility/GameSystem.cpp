﻿//=================================================================================================
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

#include "01_GameStructure.h"
#include "02_GameGraphic.h"
#include "03_GameInput.h"
#include "04_GameFile.h"


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

		//ゲーム設定ファイル
#if 0
		//設定からウィンドウ状態の取得
		UINT window_w = AppSettingFile::Inst ()->GetWindowW ();
		UINT window_h = AppSettingFile::Inst ()->GetWindowH ();
		bool bFullScreen = AppSettingFile::Inst ()->GetbFullscreen ();
		int displayNum = AppSettingFile::Inst ()->GetDisplayNum ();

#endif // 0


		//入力
		SivInput::Create ();

		//キーコンフィグ
		KeyConfig::Create ();
		KeyConfig::Inst()->Load ();

		//ゲーム画面デバッグ表示
		DebugOutGameWindow::Create ();

		//Graphic配列の初期化
		GRPLST_CREATE ();


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

		//サウンドアーカイバの初期化
		SoundArchiver::Create ();

		//設定ファイルから音量設定
		LONG vlm = AppSettingFile::Inst()->GetSoundVolume();	//0-100
//		LONG revised_vlm = 4 * ( vlm * 10 - 1000 );
		LONG revised_vlm = -( 100 - vlm ) * ( 100 - vlm );
		SOUND->SetVolume ( revised_vlm );

#if	_DEBUG
		//デバッグ時 かつ フラグON のみアーカイブファイルを生成する
		if ( m_bMakeArchive )
		{
			SoundArchiver::instance ()->Make ();
		}
#endif	//_DEBUG
		SoundArchiver::instance()->Open ();		//アーカイブファイルの読込

#endif // 0

	}


	//フレーム毎動作
	void GameSystem::Move ()
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
			//フレーム毎の動作	
			m_pGameMain->Move ();

			//ゲーム画面におけるデバッグ表示の動作
//			DBGOUT_WND()->Move ();
			
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
		GRPLST_DRAW ();

		DBGOUT_WND()->Draw ();
	}


	//メインオブジェクトの設定
	void GameSystem::SetpGameMain ( UP_GameMainBase pGameMain )
	{
		m_pGameMain = std::move ( pGameMain ); 
	}


}	//namespace GAME
