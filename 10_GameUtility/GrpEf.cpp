﻿//=================================================================================================
//
// GrpEf ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "GrpEf.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	GrpEf::GrpEf () :
		m_base ( VEC2 ( 0.f, 0.f ) ), 
		m_revised ( VEC2 ( 0.f, 0.f ) ), 
		m_dispBase ( VEC2 ( 0.f, 0.f ) ), 
		m_timer ( 0 ), 
		m_startScaling ( VEC2 ( 1.8f, 1.8f ) ), 
		m_targetScaling ( VEC2 ( 1.2f, 1.2f ) ),
		m_vec ( VEC2 ( 0.f, 0.f ) ), 
		m_vel ( VEC2 ( 0.f, 0.f ) ),
		m_acc ( VEC2 ( 0.01f, 0.01f ) )
	{
		SetValid ( false );
		m_vPosMatrix.push_back ( VEC2 ( 0, 0 ) );
	}

	GrpEf::~GrpEf ()
	{
	}

	void GrpEf::TxLoad ()
	{
//		GameGraphic::TxLoad ();

		//読み込んだテクスチャのサイズによるので Load() 後
		SetCenterOfTexture ( 0 );
	}

	void GrpEf::Move ()
	{
		//-----------------------------------------------
		//位置
		PAP_Ob pvpObj = GameGraphic::Getpap_ob ();
		size_t size = pvpObj->size ();
		for ( size_t i = 0; i < size; ++ i )
		{
			//基準位置 + 補正位置 + 外部補正位置 + 個別位置
			(*pvpObj)[i]->SetPos ( m_base + m_revised + m_dispBase + m_vPosMatrix[i] );
		}
		
		//-----------------------------------------------
		//拡縮
		for ( UINT i = 0; i < size; ++i )
		{
			if ( ! (*pvpObj)[i]->GetValid () ) { continue; }

			//目標値に達したら終了
			if ( m_targetScaling.x < 0 )
			{
				if ( m_vec.x > m_targetScaling.x || m_vec.y > m_targetScaling.y )
				{
					m_vel += m_acc;
					m_vec += m_vel;
				}
			}
			else
			{
				if ( m_vec.x < m_targetScaling.x || m_vec.y < m_targetScaling.y )
				{
					m_vel += m_acc;
					m_vec += m_vel;
				}
			}

			(*pvpObj)[i]->SetScaling ( m_vec );
		}

		GameGraphic::Move ();
	}

	void GrpEf::On ()
	{
		m_vec = m_startScaling;
		m_vel = VEC2 ( 0.f, 0.f );
//		SetIndexTexture ( 0 );
	}



	void GrpEf::SetCenterOfTexture ( UINT index )
	{
		++ index;
#if 0
		//デフォルトでScalingCenterとRotationCenterをテクスチャの中心にする
		VEC2 vec = GetCenterOfTexture ( index );
		PAP_Ob pvpObj = GameGraphic::Getpap_ob ();
		UINT size = pvpObj->size ();
		for ( UINT i = 0; i < size; ++i )
		{
			(*pvpObj)[i]->SetScalingCenter ( vec );
			(*pvpObj)[i]->SetRotationCenter ( vec );
		}
		m_base = -1.f * vec;		//表示位置をテクスチャの中心にする

#endif // 0
	}



}	//namespace GAME

