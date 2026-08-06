//=================================================================================================
//
//	テスト
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Test_LoadTime.h"
using namespace std::chrono;
using CLK = std::chrono::high_resolution_clock;


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	Test::Test ()
	{
	}

	Test::~Test ()
	{
	}

	void Test::Load ()
	{
		//ゲーム内表示のオフ
		DBGOUT_WND_OFF ();

		Print << U"時間計測開始";
		//Siv3D時間計測
		s3d::Stopwatch sw;

		//-----------------------------------------------
		Print << U"Gabadaruga_bhv_png.atls";
		sw.restart ();



		Print << U"img.lz4" << sw.msF () << U"[ms]";

		//-----------------------------------------------
		Print << U"Gabadaruga_bhv_png.atls";
		sw.restart ();


		//対象処理
		P_Atlas pAtls_png = LoadAtlasFilePng ( U"Gabadaruga_bhv_png.atls" );
		Print << U"Page size = " << pAtls_png->GetnPage ();
		Print << U"Meta size = " << pAtls_png->GetMetaSize ();


		Print << U"png.atls" << sw.msF () << U"[ms]";

		//-----------------------------------------------
		Print << U"Gabadaruga_bhv_img.atls";
		sw.restart ();

		//対象処理
		P_Atlas pAtls_img = LoadAtlasFile ( U"Gabadaruga_bhv_img.atls" );

		Print << U"img.atls" << sw.msF () << U"[ms]";

		//-----------------------------------------------




		TASK_VEC::Load ();
	}

	void Test::Move ()
	{
		TASK_VEC::Move ();
	}


}	//namespace GAME

