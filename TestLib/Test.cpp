//=================================================================================================
//
//	テスト
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "test.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	Test::Test ()
	{
		m_bg = std::make_shared < GameGraphic > ();
		m_bg->AddTexture_FromArchive ( U"BG0.png" );
		m_bg->SetPos ( 10, 20 );
		m_bg->SetZ ( Z_BG );
		//		m_bg->SetRectF ( s3d::RectF { 20, 30, 400, 500 } );
		AddpTask ( m_bg );
		GRPLST_INSERT ( m_bg );


		m_rect = std::make_shared < GamePrimitiveRect > ();
		m_rect->SetPos ( s3d::Point ( 20, 100 ) );
		m_rect->SetSize ( s3d::Point ( 1012, 50 ) );
		m_rect->SetZ ( Z_CH );
		AddpTask ( m_rect );
//		GRPLST_INSERT ( m_rect );

		m_testGrp = std::make_shared < GameGraphic > ();
		m_testGrp->AddTexture ( U"000_立ち_00.png" );
		m_testGrp->SetPos ( 100, 100 );
		//		m_testGrp->SetScaling ( 2, 2 );
		m_testGrp->SetZ ( Z_CH );
		AddpTask ( m_testGrp );
//		GRPLST_INSERT ( m_testGrp );

		m_testGrp1 = std::make_shared < GameGraphic > ();
		m_testGrp1->AddTexture ( U"待機0001.png" );
		m_testGrp1->SetPos ( 150, 150 );
		//		m_testGrp->SetScaling ( 2, 2 );
		m_testGrp1->SetZ ( Z_EFB );
		AddpTask ( m_testGrp1 );
//		GRPLST_INSERT ( m_testGrp1 );

		m_testEf = std::make_shared < GameGraphic > ();
//		m_testEf->AddTexture ( U"ef_004.png" );
		m_testEf->AddTexture ( U"Ef_Circle_11.png" );
		m_testEf->SetPos ( 50, 50 );
		m_testEf->SetZ ( 0.6f );
		AddpTask ( m_testEf );
//		GRPLST_INSERT ( m_testEf );
//		SDRLST_INSERT ( m_testEf );


		m_mov = std::make_shared < GrpMov > ();
		m_mov->SetMovName ( U"raiden.mp4" );
		m_mov->Loop ( T );
		m_mov->SetZ ( Z_SHADOW );
		AddpTask ( m_mov );
//		GRPLST_INSERT ( m_mov );

//		m_mov->Start ();



		m_str = std::make_shared < GrpStr > ();
		m_str->SetStr ( U"test." );
		AddpTask ( m_str );
		GRPLST_INSERT ( m_str );


		//DBGOUT_WND_OFF ();
		DBGOUT_WND_ON ();
	}

	Test::~Test ()
	{
	}

	void Test::Init ()
	{
		TRACE_F ( (LPCTSTR) KeyConfig::Inst()->ToString().toWstr().c_str() );

//		DBGOUT_WND_ON ();

		TASK_VEC::Init ();
	}

	void Test::Move ()
	{
		DBGOUT_WND()->DebugOutf ( 0, U"Test::Move" );

#if 0
		if ( CFG_IS_KEY ( P1_UP ) )
		{
			int i = 0; (void)i;
		}


		TRACE_F ( (LPCTSTR) KeyConfig::Inst()->ToString().toWstr().c_str() );
		if ( CFG_PUSH_KEY ( P1_UP ) || CFG_PUSH_KEY ( P2_UP ) )
		{
			int i = 0; (void)i;
		}
#endif // 0

		DeviceInput di = SivInput::Inst()->PushInput ();
//		s3d::Print ( di.ToString () );
		s3d::String di_str = di.ToString ();
		DBGOUT_WND_F ( 1, di_str );
//		DBGOUT_WND_F ( 1, U"test" );

		TASK_VEC::Move ();
	}


}	//namespace GAME

