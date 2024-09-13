//=================================================================================================
//
// GrpEfShd ヘッダファイル
// シェーダ
//	キャラ同士による位置補正を用いるエフェクト
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "02_GameGraphic.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class GrpEfShd : public GrpShd
	{
		VEC2	m_base { 0, 0 };		//基準位置
		VEC2	m_revised { 0, 0 };		//補正位置	//GrpAcvとの混同に注意
		V_VEC2	m_vPosMatrix;			//複数マトリックス使用時の補正位置
		VEC2	m_dispBase { 0, 0 };	//外部補正位置

		UINT	m_timer { 0 };
		VEC2	m_startScaling { 1.f, 1.f };	//開始
		VEC2	m_targetScaling { 1.f, 1.f };	//目標
		VEC2	m_vec { 0, 0 };
		VEC2	m_vel { 0, 0 };
		VEC2	m_acc { 0, 0 };


	public:
		GrpEfShd ();
		GrpEfShd ( const GrpEfShd & rhs ) = delete;
		~GrpEfShd ();

		void Load ();
		void Init ();
		void Move ();

		void On ();
		void Off ();

		void Advance ();	//次に進める

		//プリセット
		void Preset_Ef_Action ();

		//キャラ位置による画面補正
		void SetDispBase ( VEC2 v ) { m_dispBase = v; }

		void SetBase ( VEC2 vec ) { m_base = vec; }
		VEC2 GetRevised () const { return m_revised; }
		void SetRevised ( VEC2 vec ) { m_revised = vec; }

		void SetTimer ( UINT n ) { m_timer = n; }
		void SetStartScaling ( VEC2 vec ) { m_startScaling = vec; }
		void SetTargetScaling ( VEC2 vec ) { m_targetScaling = vec; }

		void SetVel ( VEC2 vec ) { m_vel = vec; }
		void SetAcc ( VEC2 vec ) { m_acc = vec; }

		//複数オブジェクトの初期設定
//		void ResetObjectNUm ( UINT n ) {}

		void AddObject () 
		{
			m_vPosMatrix.push_back ( VEC2 ( 0, 0 ) );
//			GrpShd::AddObject ();
		}

		void AddObject ( UINT n )
		{
			for ( UINT i = 0; i < n; ++i ) { AddObject (); }
		}
		
		void AddpObject ( P_Ob p )
		{
			m_vPosMatrix.push_back ( VEC2 ( 0, 0 ) );
			GrpShd::AddpObject ( p );
		}
		
		void SetPosMatrix ( UINT i, VEC2 pos )
		{
			m_vPosMatrix[i] = pos;
		}

		//計算後の最終位置を取得
		VEC2 GetCalcPos ( UINT i )
		{
			//基準位置 + 補正位置 + 外部補正位置 + 個別位置
			return m_base + m_revised + m_dispBase + m_vPosMatrix[i];

		}

		//インデックスで指定したテクスチャで中心を設定する
		void SetCenterOfTexture ();
	};

	using P_GrpEfShd = std::shared_ptr < GrpEfShd >;


}	//namespace GAME


