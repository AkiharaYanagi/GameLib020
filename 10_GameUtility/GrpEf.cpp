//=================================================================================================
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
	GrpEf::GrpEf ()
	{
		SetValid ( F );
//		m_vPosMatrix.push_back ( VEC2 ( 0, 0 ) );
	}

	GrpEf::~GrpEf ()
	{
	}

	void GrpEf::Load ()
	{
		GameGraphic::Load ();

		//読み込んだテクスチャのサイズによるので Load() 後
//		m_vPosMatrix.clear ();

		//テクスチャの中心にする
//		SetCenterOfTexture ();
	}

	void GrpEf::Init ()
	{
		m_vec = m_startScaling;
		m_vel = VEC2 ( 0.f, 0.f );
		m_tmr.Clear ();

		for ( P_Ob pOb : * Getpap_ob () )
		{
			pOb->SetIndexTexture ( 0 );
		}
	}

	void GrpEf::Move ()
	{
		//-----------------------------------------------
		//タイマ
		if ( m_tmr.IsActive () )
		{
			if ( m_tmr.IsLast () )
			{
				Off ();
			}
		}
		m_tmr.Move ();

		//-----------------------------------------------
		//位置
		PAP_Ob pvpObj = GameGraphic::Getpap_ob ();
		size_t size = pvpObj->size ();
		for ( size_t i = 0; i < size; ++ i )
		{
			//テクスチャ中心位置
			if ( m_bCenterOfTx )
			{
				uint32 indexTx = (*pvpObj)[i]->GetIndexTexture ();
				PAP_Tx papTx = GameGraphic::Getpap_tx ();
				if ( papTx->size() <= indexTx ) { continue; }

				P_Tx pTx = papTx->at ( indexTx );
				m_revised = -1 * s3d_UTL::GetTxCenter ( * pTx );
			}

			//基準位置 + 補正位置 + 外部補正位置 + 個別位置
//			(*pvpObj)[i]->SetPos ( m_base + m_revised + m_dispBase + m_vPosMatrix[i] );
			(*pvpObj)[i]->SetPos ( m_base + m_revised + m_dispBase );

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

	void GrpEf::On ()
	{
		Init();

		//GraphicのValid
		SetValid ( T );

		//ObjectのValid
		for ( P_Ob pOb : * Getpap_ob () )
		{
			pOb->SetValid ( T );
		}
	}

	void GrpEf::Off ()
	{
		//GraphicのValid
		SetValid ( F );

		//ObjectのValid
		for ( P_Ob pOb : * Getpap_ob () )
		{
			pOb->SetValid ( F );
		}
	}

	void GrpEf::Advance ()
	{
		//オブジェクトの個数チェック
		PAP_Ob papOb = GameGraphic::Getpap_ob ();
		size_t size_ob = papOb->size ();
		if ( size_ob == 0 ) { return; }

		//テクスチャの個数チェック
		PAP_Tx papTx = GameGraphic::Getpap_tx ();
		size_t size_tx = papTx->size ();
		if ( size_tx <= 1 ) { return; }

		for ( size_t i = 0; i < size_ob; ++ i )
		{
			//次に進める
			P_Ob pOb = papOb->at ( i );
			uint32 indexTx = pOb->GetIndexTexture ();

			//最後のとき稼働終了
			if ( ++ indexTx >= size_tx )
			{
				indexTx = 0;
				Off ();
			}

			pOb->SetIndexTexture ( indexTx );
		}

	}

	void GrpEf::Advance_Loop ()
	{
		//オブジェクトの個数チェック
		PAP_Ob papOb = GameGraphic::Getpap_ob ();
		size_t size_ob = papOb->size ();
		if ( size_ob == 0 ) { return; }

		//テクスチャの個数チェック
		PAP_Tx papTx = GameGraphic::Getpap_tx ();
		size_t size_tx = papTx->size ();
		if ( size_tx <= 1 ) { return; }

		for ( size_t i = 0; i < size_ob; ++ i )
		{
			//次に進める
			P_Ob pOb = papOb->at ( i );
			uint32 indexTx = pOb->GetIndexTexture ();

			//最後のとき最初に戻る
			if ( ++ indexTx >= size_tx )
			{
				indexTx = 0;
			}

			pOb->SetIndexTexture ( indexTx );
		}

	}

	void GrpEf::Preset_Ef_Action ()
	{
		m_base = VEC2 ( 0.f, 0.f );
		m_revised = VEC2 ( 0.f, 0.f ); 
		m_dispBase = VEC2 ( 0.f, 0.f ); 
		//m_timer = 0; 
		m_startScaling = VEC2 ( 1.8f, 1.8f ); 
		m_targetScaling = VEC2 ( 1.2f, 1.2f );
		m_vec = VEC2 ( 0.f, 0.f ); 
		m_vel = VEC2 ( 0.f, 0.f );
		m_acc = VEC2 ( 0.01f, 0.01f );
	}


	void GrpEf::SetCenterOfTexture ()
	{
		//デフォルトでScalingCenterとRotationCenterをテクスチャの中心にする
		PAP_Ob pvpObj = GameGraphic::Getpap_ob ();
		size_t size = pvpObj->size ();
		for ( size_t i = 0; i < size; ++i )
		{
			//VEC2 vec = GetCenterOfTexture ( (uint32) i );
			(*pvpObj)[i]->SetbScalingCntrOfTx ( T );
			(*pvpObj)[i]->SetbRotationCntrOfTx ( T );
			//m_revised = vec;
		}
	}

	void GrpEf::Start ( VEC2 v, uint32 time )
	{
		m_base = v;
		m_tmr.Start ( time );
	}

	void GrpEf::Start_Rnd ( VEC2 v, uint32 time, int32 rnd )
	{
		VEC2 rv = v;
		rv.x += ( +rnd + s3d::RandomInt32() % 100 );
		rv.y += ( -rnd + s3d::RandomInt32() % 100 );
		m_base = rv;
		m_tmr.Start ( time );
	}

}	//namespace GAME

