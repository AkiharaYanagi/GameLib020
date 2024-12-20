//=================================================================================================
//
// Timer ヘッダファイル
//		GameTask状のカウントアップタイマ
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "GameTask.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//============================
	//	t = 0 から開始
	//	active時に++;
	//	targetTime時に終了してt = 0に戻り、deactive
	//
	//============================

	class Timer : public GameTask
	{
		bool	m_active { F };
		UINT	m_time { 0 };			//現在時間
		UINT	m_targetTime { 0 };		//目標時間
		UINT	m_wait { 0 };

	public:
		Timer ();
		Timer ( UINT targetTime );	//目標時間
		Timer ( const Timer & rhs ) = delete;
		~Timer ();

		//@info このクラスはTask型継承だが、手動でMove()のみを毎フレーム行えばAddpTask()の必要はない
		void Move ();

		//可動初期状態
		bool IsStart() const { return m_active && m_time == 0; }

		//可動状態
		bool IsActive () const { return m_active; }

		//最終状態(同値になったらリセットされるので( 1 + m_time )で判定する)
		bool IsLast () const { return (m_targetTime == 1 + m_time); }

		void SetTime ( UINT i ) { m_time = i; }
		UINT GetTime () const { return m_time; }
		
		//目標時間
		void SetTargetTime ( UINT time ) { m_targetTime = time; }
		UINT GetTargetTime () const { return m_targetTime; }

		//0からスタート
		void Start () { m_time = 0; m_active = true; }

		//目標時間を指定してスタート
		void Start ( UINT n ) { SetTargetTime ( n ); Start (); }

		//wait分だけ待機してからスタート
		void WaitStart ( UINT wait );
		
		//前回の続きからスタート
		void ReStart () { m_active = true; }

		//ストップ(一時停止(カウントは保存))
		void Stop () { m_active = false; }

		//クリア
		void Clear () { m_time = 0; m_active = false; }
	};

	using P_Timer = std::shared_ptr < Timer >;
	using VP_Timer = std::vector < P_Timer >;
	using PVP_Timer = std::shared_ptr < VP_Timer >;


}	//namespace GAME


