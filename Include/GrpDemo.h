//=================================================================================================
//
// GrpDemo ヘッダファイル
//	キャラ位置によらず一定の位置で表示
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

	class GrpDemo : public GameGraphic
	{
		UINT		m_timer { 0 };		//タイマ現在値
		UINT		m_endTime { 10 };	//タイマ終了
		bool		m_end { F };		//終了フラグ

		VEC2		m_startScaling { 1.f, 1.f };	//開始
		VEC2		m_targetScaling { 1.f, 1.f };	//目標
		VEC2		m_mag { 1.f, 1.f };		//倍率
		VEC2		m_vel { 0, 0 };			//倍率変化速度
		VEC2		m_acc { 0, 0 };			//倍率変化加速度
		VEC2		m_secondVel { 0, 0 };	//第2速度

	public:
		GrpDemo ();
		GrpDemo ( const GrpDemo& rhs ) = delete;
		~GrpDemo ();

		void DemoInit ();	//動作する初期値
		void Init ();
		void Move ();

		void Start ();

		void SetTimer ( UINT n ) { m_timer = n; }
		void SetStartScaling ( VEC2 vec ) { m_startScaling = vec; }
		void SetTargetScaling ( VEC2 vec ) { m_targetScaling = vec; }

		void SetVel ( VEC2 vec ) { m_vel = vec; }
		void SetAcc ( VEC2 vec ) { m_acc = vec; }
		void SetSecondVel ( VEC2 vec ) { m_secondVel = vec; }

		void SetEnd ( UINT n ) { m_end = false; m_endTime = n; }
		void ResetEnd () { m_end = false; }
	};

	using P_GrpDemo = std::shared_ptr < GrpDemo >;


}	//namespace GAME


