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
		m_bg->SetPos ( 300, 200 );
//		m_bg->SetRectF ( s3d::RectF { 20, 30, 400, 500 } );
		AddpTask ( m_bg );
		GRPLST_INSERT ( m_bg );


		m_rect = std::make_shared < GamePrimitiveRect > ();
		m_rect->SetPos ( s3d::Point ( 100, 100 ) );
		m_rect->SetSize ( s3d::Point ( 512, 512 ) );
		AddpTask ( m_rect );
//		GRPLST_INSERT ( m_rect );

		m_testGrp = std::make_shared < GameGraphic > ();
		m_testGrp->AddTexture ( U"000_立ち_00.png" );
		m_testGrp->SetPos ( 100, 100 );
		m_testGrp->SetScaling ( 2, 2 );
		AddpTask ( m_testGrp );
		GRPLST_INSERT ( m_testGrp );

#if 0
		m_testEf = std::make_shared < GameGraphic > ();
		m_testEf->AddTexture ( U"ef_004.png" );
		m_testEf->SetPos ( 50, 50 );
		AddpTask ( m_testEf );
		SDRLST_INSERT ( m_testEf );
#endif // 0
	}

	Test::~Test ()
	{
	}

	void Test::Move ()
	{
		DBGOUT_WND()->DebugOutf ( 0, U"Test::Move" );
		TASK_VEC::Move ();
	}


}	//namespace GAME

