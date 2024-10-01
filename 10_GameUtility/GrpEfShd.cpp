//=================================================================================================
//
// GrpEfShd ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "GrpEfShd.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	GrpEfShd::GrpEfShd ()
	{
		SetShader ( T );
		SetValid ( F );
		m_vPosMatrix.push_back ( VEC2 ( 0, 0 ) );
	}

	GrpEfShd::~GrpEfShd ()
	{
	}

	void GrpEfShd::Load ()
	{
		GameGraphic::Load ();

#if 0
		//読み込んだテクスチャのサイズによるので Load() 後
		m_vPosMatrix.clear ();
		SetCenterOfTexture ();
#endif // 0
	}

	void GrpEfShd::Init ()
	{
		m_vec = m_startScaling;
		m_vel = VEC2 ( 0.f, 0.f );
		SetIndexTexture ( 0 );
	}

	void GrpEfShd::Move ()
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


#if 0

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

#endif // 0

		GameGraphic::Move ();
	}

	void GrpEfShd::On ()
	{
		Init();
		SetValid ( T );
	}

	void GrpEfShd::Off ()
	{
		SetValid ( F );
	}

	void GrpEfShd::Advance ()
	{
		//オブジェクトの個数チェック
		PAP_Ob papOb = GameGraphic::Getpap_ob ();
		size_t size_ob = papOb->size ();
		if ( size_ob == 0 ) { return; }

		//テクスチャの個数チェック
		PAP_Tx papTx = GameGraphic::Getpap_tx ();
		size_t size_tx = papTx->size ();
		if ( size_tx <= 1 ) { return; }

		//次に進める
		P_Ob pOb = papOb->at ( 0 );
		uint32 indexTx = pOb->GetIndexTexture ();

		//最後のとき稼働終了
		if ( ++ indexTx >= size_tx )
		{
			indexTx = 0;
			Off ();
		}

		pOb->SetIndexTexture ( indexTx );
	}

	void GrpEfShd::Preset_Ef_Action ()
	{
		m_base = VEC2 ( 0.f, 0.f );
		m_revised = VEC2 ( 0.f, 0.f ); 
		m_dispBase = VEC2 ( 0.f, 0.f ); 
		m_timer = 0; 
		m_startScaling = VEC2 ( 1.8f, 1.8f ); 
		m_targetScaling = VEC2 ( 1.2f, 1.2f );
		m_vec = VEC2 ( 0.f, 0.f ); 
		m_vel = VEC2 ( 0.f, 0.f );
		m_acc = VEC2 ( 0.01f, 0.01f );
	}


	void GrpEfShd::SetCenterOfTexture ()
	{
		//デフォルトでScalingCenterとRotationCenterをテクスチャの中心にする
		PAP_Ob pvpObj = GameGraphic::Getpap_ob ();
		size_t size = pvpObj->size ();
		for ( size_t i = 0; i < size; ++i )
		{
			VEC2 vec = GetCenterOfTexture ( (uint32) i );
//			(*pvpObj)[i]->SetScalingCenter ( vec );
			(*pvpObj)[i]->SetRotationCenter ( vec );
		}
	}


}	//namespace GAME

