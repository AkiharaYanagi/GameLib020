//=================================================================================================
//
// メイン ソースコード
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
//	ヘッダファイル　インクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "GameMain.h"
//#include "CharaData.h"
#include "DebugDisp.h"

#include "Test_Atlas2.h"


//-------------------------------------------------------------------------------------------------
//	実装
//-------------------------------------------------------------------------------------------------
using namespace GAME;



//前方宣言
void Load ( GameSystem & gameSystem );
void Init ( GameSystem & gameSystem );
void Move ( GameSystem & gameSystem );
void Draw ( GameSystem & gameSystem );
void Rele ( GameSystem & gameSystem );



//StopWatch g_sw;



//メインループ
void Main()
{
	//g_sw.Start ();	//時間計測開始

	Test test_atlas2;

	test_atlas2.Init ();


	//ゲームシステム
	GameSystem gameSystem;

	Load ( gameSystem );	//読込

	//========================================
	//メインループ
	bool init = F;
	while ( System::Update() )
	{
		//g_sw.ReStart ();


		//初期化
		if ( ! init ) { Init ( gameSystem ); init = T; }

		Move ( gameSystem );	//動作
		Draw ( gameSystem );	//描画



		test_atlas2.Move ();



		//g_sw.Disp ( DBGOUT_0, U"メインループ (Move + Draw)" );
		//g_sw.Count ();
	}
	//========================================

	Rele ( gameSystem );	//解放
}



//---------------------------------------------------
//起動後１回のみの初期化
void Load ( GameSystem & gameSystem )
{
	//-------------------------------------
	//タイトル
	Window::SetTitle ( U"剣撃クロスゾーン" );

	//-------------------------------------
	//デバッグ用コマンドプロンプト表示
	if ( g_bCMDPRMPT_DISP )
	{
		DebugOutPrint::OpenPrompt ();
		PRINT_F_S ( U"start DebugOutPrint.\n" );
	}

	//-------------------------------------
	//システム初期化
	gameSystem.SystemLoad ();


	//ゲームメイン
	UP_GameMain gameMain = std::make_unique < GameMain > ();
	gameMain->Load ();
	gameMain->Init ();


	
	//開始時一時停止
	if ( g_bWAIT_START )
	{
		gameSystem.SetbStop ( T );
	}


	//-------------------------------------
	//ゲームシステムにゲームメインオブジェクトを追加
	gameSystem.SetpGameMain ( std::move ( gameMain ) );
}


//---------------------------------------------------
//メインループ中の最初の１回のみの初期化
void Init ( GameSystem & gameSystem )
{
	( void ) gameSystem;	//未使用対策

	//-------------------------------------
	//ウィンドウ設定
	GameInit gameInit;
	gameInit.SetStartCursorPos ( g_bSTART_CURSOR_POS );
	gameInit.Do ();
}


//---------------------------------------------------
// 動作
void Move ( GameSystem & gameSystem )
{
	gameSystem.Move ();
}

//---------------------------------------------------
// 描画
void Draw ( GameSystem & gameSystem )
{
	gameSystem.Draw ();
}

//---------------------------------------------------
// 解放
void Rele ( GameSystem & gameSystem )
{
	gameSystem.SystemRele ();
}


