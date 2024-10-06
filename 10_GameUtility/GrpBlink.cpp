//=================================================================================================
//
// GrpEf ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "GrpBlink.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	GrpBlink::GrpBlink ()
	{
	}

	GrpBlink::~GrpBlink ()
	{
	}

	void GrpBlink::Move ()
	{
		//点滅
		if ( m_active )
		{
			Blink ();
		}
		GameGraphic::Move ();
	}

	void GrpBlink::Blink ()
	{
		//点滅
		if ( m_blink )
		{
			if ( m_timer == m_blinkTime )
			{
				m_blink = false;
			}
			else
			{
				++m_timer;
			}
		}
		else
		{
			if ( m_timer == 0 )
			{
				m_blink = true;
			}
			else
			{
				--m_timer;
			}
		}

		//α値を算出して設定
		uint32 alpha = (0xff / m_blinkTime) * m_timer;

		//半分で折り返し
		if ( m_half )
		{
			alpha = 0x80 + (0xff / m_blinkTime) / 2 * m_timer;
		}

		_CLR color = _CLR ( alpha << 24 ^ 0x00ffffff );
		SetColor ( color );
	}

	void GrpBlink::Stop ()
	{
		m_active = false;
		SetColor ( 0xffffffff );
	}

	void GrpBlink::Start ()
	{
		m_active = true;
	}



}	//namespace GAME

