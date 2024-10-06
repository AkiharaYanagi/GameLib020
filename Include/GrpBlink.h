//=================================================================================================
//
// GrpBlink ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "GameGraphic.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class GrpBlink : public GameGraphic
	{
		bool	m_blink { T };		//点滅方向(T:全色, F:透明)
		uint32	m_timer { 0 };		//現在時間
		uint32	m_blinkTime { 30 };	//点滅時間
		bool	m_active { T };		//稼働フラグ
		bool	m_half { F };		//半分までで折り返し

		void Blink ();

	public:
		GrpBlink ();
		GrpBlink ( const GrpBlink & rhs ) = delete;
		~GrpBlink ();

		void Move ();

		void SetTimer ( uint32 n ) { m_timer = n; }
		void SetBlinkTime ( uint32 n ) { m_blinkTime = n; }
		void Stop ();
		void Start ();
		void SetHalf ( bool b ) { m_half = b; }
	};

	using P_GrpBlink = std::shared_ptr < GrpBlink >;


}	//namespace GAME


