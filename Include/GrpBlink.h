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
		bool	m_blink { T };
		uint32	m_timer { 0 };
		uint32	m_blinkTime { 30 };
		bool	m_active { T };

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
	};

	using P_GrpBlink = std::shared_ptr < GrpBlink >;


}	//namespace GAME


