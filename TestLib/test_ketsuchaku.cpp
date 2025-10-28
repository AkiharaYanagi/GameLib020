//=================================================================================================
//
//	テスト
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "test_ketsuchaku.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//Test
	Test::Test ()
	{

		//test プロンプト表示
//		DebugOutPrint::Create ();

		PRINT_F_S ( U"test prompt." );

		m_grp = std::make_shared < GameGraphic > ();
//		m_grp->AddTexture_FromArchive ( U"decision_ketsu.png" );
		m_grp->AddTexture_FromArchive ( U"BG0.png" );
		AddpTask ( m_grp );
		GRPLST_INSERT ( m_grp );
		m_grp->SetValid ( F );


		m_grpStr = std::make_shared < GrpStr >();
		m_grpStr->SetPos ( VEC2 ( 100, 100 ) );
		m_grpStr->SetStr(U"KetsuChaku Test");
		AddpTask ( m_grpStr );
		GRPLST_INSERT ( m_grpStr );

//		FontAsset::Register ( U"test", 60 );


		m_grp_chaku = std::make_shared < GrpDemo > ();
		m_grp_chaku->AddTexture_FromArchive ( U"decision_chaku.png" );
		m_grp_chaku->SetPos ( VEC2 ( 750, 550 ) );
		m_grp_chaku->SetZ ( Z_SYS );	//@info SetZはGRPLST_INSERT()の後では行わない(リストが崩れる)
		m_grp_chaku->SetStartScaling ( VEC2 ( 8.f, 8.f ) );
		m_grp_chaku->SetTargetScaling ( VEC2 ( 1.5f, 1.5f ) );
		m_grp_chaku->SetSecondVel ( VEC2 ( -0.001f, -0.001f ) );
		m_grp_chaku->SetValid ( F );
		m_grp_chaku->SetEnd ( 120 );
		AddpTask ( m_grp_chaku );
		GRPLST_INSERT ( m_grp_chaku );

		m_grp_Ketsu = std::make_shared < GrpDemo > ();
		m_grp_Ketsu->AddTexture_FromArchive ( U"decision_ketsu.png" );
		m_grp_Ketsu->SetPos ( VEC2 ( 250, 250 ) );
		m_grp_Ketsu->SetZ ( Z_SYS );	//@info SetZはGRPLST_INSERT()の後では行わない(リストが崩れる)
		m_grp_Ketsu->SetStartScaling ( VEC2 ( 8.f, 8.f ) );
		m_grp_Ketsu->SetTargetScaling ( VEC2 ( 1.5f, 1.5f ) );
		m_grp_Ketsu->SetSecondVel ( VEC2 ( -0.001f, -0.001f ) );
		m_grp_Ketsu->SetValid ( F );
		m_grp_Ketsu->SetEnd ( 120 );
		AddpTask ( m_grp_Ketsu );
		GRPLST_INSERT ( m_grp_Ketsu );

		m_grpLight0 = std::make_shared < GrpDemo > ();
		m_grpLight0->AddTexture_FromArchive ( U"decision_light0.png" );
		m_grpLight0->SetShader ( T );
		m_grpLight0->SetPos ( VEC2 ( 800, 480 ) );
		m_grpLight0->SetZ ( Z_SYS );	//@info SetZはGRPLST_INSERT()の後では行わない(リストが崩れる)
		m_grpLight0->SetStartScaling ( VEC2 ( 2.f, 2.f ) );
		m_grpLight0->SetVel ( VEC2 ( 0.f, 0.f ) );
		m_grpLight0->SetAcc ( VEC2 ( 0.1f, 0.f ) );
		m_grpLight0->SetTargetScaling ( VEC2 ( 10.f, 2.f ) );
		m_grpLight0->SetSecondVel ( VEC2 ( 0.f, 0.f ) );
		m_grpLight0->SetValid ( F );
		m_grpLight0->SetEnd ( 120 );
		AddpTask ( m_grpLight0 );
		GRPLST_INSERT ( m_grpLight0 );

		m_grpLight1 = std::make_shared < GrpDemo > ();
		m_grpLight1->AddTexture_FromArchive ( U"decision_light1.png" );
		m_grpLight1->SetPos ( VEC2 ( 800, 500 ) );
		m_grpLight1->SetZ ( Z_SYS );	//@info SetZはGRPLST_INSERT()の後では行わない(リストが崩れる)
		m_grpLight1->SetStartScaling ( VEC2 ( 2.f, 2.f ) );
		m_grpLight1->SetVel ( VEC2 ( 0.f, 0.f ) );
		m_grpLight1->SetAcc ( VEC2 ( 0.1f, 0.f ) );
		m_grpLight1->SetTargetScaling ( VEC2 ( 10.f, 2.f ) );
		m_grpLight1->SetSecondVel ( VEC2 ( 0.f, 0.f ) );
		m_grpLight1->SetValid ( F );
		m_grpLight1->SetEnd ( 120 );
		AddpTask ( m_grpLight1 );
		GRPLST_INSERT ( m_grpLight1 );

	}

	Test::~Test ()
	{
	}

	void Test::Init ()
	{
		TASK_VEC::Init ();
	}

	void Test::Move ()
	{
		s3d::ClearPrint ();
		s3d::Print << FONT_20 << FontAsset::IsReady ( FONT_20 );
		s3d::Print << FONT_30 << FontAsset::IsReady ( FONT_30 );
		s3d::Print << FONT_40 << FontAsset::IsReady ( FONT_40 );
		s3d::Print << FONT_60 << FontAsset::IsReady ( FONT_60 );

		G_Audio::Inst()->CheckAudio ();


		if ( CFG_PUSH_KEY ( P1_BTN0 ) )
		{
			G_Audio::Inst()->HandLoad ();
#if 0


			m_grp_Ketsu->Start ();
			m_grp_chaku->Start ();
			m_grpLight0->Start ();
			m_grpLight1->Start ();
#endif // 0
		}


		TASK_VEC::Move ();

//		FontAsset(ASYNC_FONT)(U"Press P1 BTN0 to Start KetsuChaku").drawAt(60, 50, 50, ColorF{ 1.0, 1.0, 0.0 });
//		FontAsset(U"test")(U"testAsset").drawAt( 40, s3d::Vec2{120, 120}, ColorF{ 1.0 } );
	}



}	//namespace GAME

