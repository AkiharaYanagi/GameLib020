//=================================================================================================
//
//	テスト
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Test_Atlas.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//Test
	Test::Test ()
	{
		m_grpAtlas = std::make_shared < GrpAtlas > ();
		P_Atlas pAtlas = LoadAtlasFilePng ( U"Sae_bhv.atls" );
		m_grpAtlas->SetpAtlas ( pAtlas );
		AddpTask ( m_grpAtlas );
		GRPLST_INSERT ( m_grpAtlas );
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
		if ( s3d::KeyZ.pressed () )
		{
			m_indexTexture --;
			size_t sz = m_grpAtlas->GetpAtlas ()->GetIdCanvas ().size();
			if ( m_indexTexture < 0 ) { m_indexTexture = (int32_t)sz - 1; }
		}
		if ( s3d::KeyX.pressed () )
		{
			m_indexTexture ++;
			size_t sz = m_grpAtlas->GetpAtlas ()->GetIdCanvas ().size();
			if ( m_indexTexture >= (int32_t)sz ) { m_indexTexture = 0; }
		}

		m_grpAtlas->SetIndexTexture ( m_indexTexture );

		TASK_VEC::Move ();
	}


}	//namespace GAME

