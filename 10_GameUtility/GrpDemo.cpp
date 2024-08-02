﻿//=================================================================================================
//
// GrpDemo ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "GrpDemo.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	GrpDemo::GrpDemo () : 
		m_startScaling ( VEC2 ( 1.8f, 1.8f ) ), 
		m_targetScaling ( VEC2 ( 1.2f, 1.2f ) ), 
		m_mag ( VEC2 ( 0.f, 0.f ) ), 
		m_vel ( VEC2 ( 0.f, 0.f ) ), m_acc ( VEC2 ( -0.01f, -0.01f ) ), 
		m_secondVel ( VEC2 ( 0.f, 0.f ) )
	{
	}

	GrpDemo::~GrpDemo ()
	{
	}

	void GrpDemo::Init ()
	{
		m_vel = VEC2 ( 0, 0 );
		m_mag = m_startScaling;
		GameGraphic::Init ();
	}

	void GrpDemo::Start ()
	{
		m_vel = VEC2 ( 0, 0 );
		m_mag = m_startScaling;
		m_timer = 1;
		SetValid ( T );
	}

	void GrpDemo::Move ()
	{	
		if ( m_timer == 0 )
		{
			GameGraphic::Move ();
			return;
		}

		if ( m_timer >= m_endTime )
		{
			m_end = true;
			SetValid ( false );
		}
		else
		{
			++ m_timer;
		}

		//目標値に達したら終了
		if ( m_mag.x > m_targetScaling.x || m_mag.y > m_targetScaling.y )
		{
			m_vel += m_acc;
			m_mag += m_vel;
		}
		else
		{
			m_mag += m_secondVel;
		}

		GameGraphic::SetScaling ( m_mag );
		GameGraphic::Move ();
	}



}	//namespace GAME

