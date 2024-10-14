//=================================================================================================
//
// GrpEf ヘッダファイル
//	PosをBaseとRevisedで計算する
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "GameGraphic.h"
#include "Timer.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class GrpEf : public GameGraphic
	{
		VEC2	m_base { 0, 0 };		//基準位置
		VEC2	m_revised { 0, 0 };		//補正位置	//GrpAcvとの混同に注意
//		V_VEC2	m_vPosMatrix;			//複数オブジェクト使用時の個別補正位置
		VEC2	m_dispBase { 0, 0 };	//外部補正位置(キャラ同士による画面補正)

		VEC2	m_startScaling { 1.f, 1.f };	//開始
		VEC2	m_targetScaling { 1.f, 1.f };	//目標
		VEC2	m_vec { 0, 0 };
		VEC2	m_vel { 0, 0 };
		VEC2	m_acc { 0, 0 };

		Timer	m_tmr;

		//表示をテクスチャ中心位置にする(毎F指定)
		bool	m_bCenterOfTx { F };


	public:
		GrpEf ();
		GrpEf ( const GrpEf & rhs ) = delete;
		~GrpEf ();

		void Load ();
		void Init ();
		void Move ();

		void On ();
		void Off ();

		void Advance ();		//テクスチャを次に進める　最後まで行ったらOff()
		void Advance_Loop ();	//テクスチャを次に進める　最後まで行ったら最初に戻る

		//プリセット
		void Preset_Ef_Action ();

		//キャラ位置によるゲーム画面補正
		void SetDispBase ( VEC2 v ) { m_dispBase = v; }

		//ベースにゲーム位置を代入する
		void SetBase ( VEC2 vec ) { m_base = vec; }

		//リバイズドが表示位置を修正する(テクスチャの中心など)
		VEC2 GetRevised () const { return m_revised; }
		void SetRevised ( VEC2 vec ) { m_revised = vec; }

//		void SetTimer ( UINT n ) { m_timer = n; }
		void SetStartScaling ( VEC2 vec ) { m_startScaling = vec; }
		void SetTargetScaling ( VEC2 vec ) { m_targetScaling = vec; }

		void SetVel ( VEC2 vec ) { m_vel = vec; }
		void SetAcc ( VEC2 vec ) { m_acc = vec; }

		//複数オブジェクトの初期設定
//		void ResetObjectNUm ( UINT n ) {}

#if 0

		void AddObject () 
		{
			m_vPosMatrix.push_back ( VEC2 ( 0, 0 ) );
//			GameGraphic::AddObject ();
		}

		void AddObject ( UINT n )
		{
			for ( UINT i = 0; i < n; ++i ) { AddObject (); }
		}
		
		void AddpObject ( P_Ob p )
		{
			m_vPosMatrix.push_back ( VEC2 ( 0, 0 ) );
			GameGraphic::AddpObject ( p );
		}
		
		void SetPosMatrix ( UINT i, VEC2 pos )
		{
			m_vPosMatrix[i] = pos;
		}

#endif // 0

		//計算後の最終位置を取得
		VEC2 GetCalcPos ( UINT i )
		{
			(void)i;

			//基準位置 + 補正位置 + 外部補正位置 + 個別位置
//			return m_base + m_revised + m_dispBase + m_vPosMatrix[i];
			return m_base + m_revised + m_dispBase;

		}

		//インデックスで指定したテクスチャで中心を設定する
		void SetCenterOfTexture ();


		//位置指定開始
		void Start ( VEC2 v, uint32 t );

		//テクスチャ中心位置で表示
		void SetbCenterOfTx ( bool b ) { m_bCenterOfTx = b; }
	};

	using P_GrpEf = std::shared_ptr < GrpEf >;


}	//namespace GAME


