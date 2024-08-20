//=================================================================================================
//
// FadeRect ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "FadeRect.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	FadeRect::FadeRect ()
	: m_color0 ( 0x00000000UL ), m_color1 ( 0xff000000UL )
	{
		PrmRect::SetValid ( false );
//		PrmRect::SetRect ( 0, 0, 1.f * 1280, 1.f * 960 );
		PrmRect::SetRect(0, 0, GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT);
		PrmRect::SetZ ( Z_FADE );
		m_timer = std::make_shared < Timer > ();
	}

	FadeRect::~FadeRect ()
	{
	}

	void FadeRect::Move ()
	{
		UINT t = m_timer->GetTime ();

		//初期色->目標色( m_color0 → m_color1 )
//		if ( 0 != m_targetTime )
		if ( m_timer->IsActive () )
		{
			//終了時
			if ( m_timer->IsLast () )
			{
				m_timer->Clear ();
				PrmRect::SetColor ( m_color1 );
				PrmRect::SetValid ( ! m_after_clear );
			}
			else
			{
				float alpha = (1.f / m_timer->GetTargetTime () ) * t;	//α値を算出
				if ( m_color0.a > m_color1.a )	//減少の場合は1.fから
				{
					alpha = 1.f - alpha;
				};
				s3d::ColorF c = s3d::ColorF ( m_color1.r, m_color1.g, m_color1.b, alpha );
				PrmRect::SetColor ( c );
			}
		}

#if 0
		//ホワイトアウト( 0x00ffffff → 0xffffffff )
		if ( 0 != m_whiteOutTime )
		{
			if ( t == m_whiteOutTime )
			{
				m_timer->Reset ();
				m_whiteOutTime = 0;
				PrmRect::SetAllColor ( _CLR ( 0xffffffff ) );
				PrmRect::SetValid ( false );
			}
			else
			{
//				UINT alpha = (0xff / m_whiteOutTime) * t;		//α値を算出
				UCHAR alpha = (UCHAR)((255.f / m_whiteOutTime) * t);		//α値を算出
				UINT alpha_s = alpha << 24;
				UINT U_color = alpha_s ^ 0x00ffffff;
				//				_CLR color = _CLR ( alpha_s ^ 0x00ffffff );
				_CLR color = _CLR ( U_color );
				TRACE_F ( _T ( "alpha = %x, alpha_s = %x, color = %x\n" ), alpha, alpha_s, U_color );
				PrmRect::SetAllColor ( color );
			}
		}

		//ブラックイン ( 0xff000000 → 0x00000000 )
		if ( 0 != m_darkInTime ) 
		{
			if ( t == m_darkInTime )
			{
				m_timer->Reset ();
				m_darkInTime = 0;
				PrmRect::SetAllColor ( _CLR ( 0x00ffffff ) );
				PrmRect::SetValid ( false );
			}
			else
			{
				UINT alpha = 0xff - ( 0xff / m_darkInTime ) * t;			//α値を算出
				_CLR color = _CLR ( alpha << 24 ^ 0x00000000 );
				PrmRect::SetAllColor ( color );
			}
		}

		//ブラックアウト( 0x00000000 → 0xff000000 )
		if ( 0 != m_darkOutTime )
		{
			if ( t == m_darkOutTime )
			{
				m_timer->Reset ();
				m_darkOutTime = 0;
				PrmRect::SetAllColor ( _CLR ( 0xff000000 ) );
			}
			else
			{
				UINT alpha = ( 0xff / m_darkOutTime ) * t;			//α値を算出
				_CLR color = _CLR ( alpha << 24 ^ 0x00000000 );
				PrmRect::SetAllColor ( color );
			}
		}
#endif // 0


		m_timer->Move ();
		PrmRect::Move ();
	}

	//ホワイトイン( 0xffffffff → 0x00ffffff )
	void FadeRect::SetWhiteIn ( UINT time )
	{
		s3d::ColorF clr0 = s3d::ColorF ( 1.0, 1.0, 1.0, 1.0 );
		s3d::ColorF clr1 = s3d::ColorF ( 1.0, 1.0, 1.0, 0.0 );
		SetColor ( clr0, clr1 ); Start ( time );
	}

	//ホワイトアウト( 0x00ffffff → 0xffffffff )
	void FadeRect::SetWhiteOut ( UINT time )
	{
		s3d::ColorF clr0 = s3d::ColorF ( 1.0, 1.0, 1.0, 0.0 );
		s3d::ColorF clr1 = s3d::ColorF ( 1.0, 1.0, 1.0, 1.0 );
		SetColor ( clr0, clr1 ); Start ( time );
	}

	//ブラックイン ( 0xff000000 → 0x00000000 )
	void FadeRect::SetBlackIn ( UINT time )
	{
		s3d::ColorF clr0 = s3d::ColorF ( 0.0, 0.0, 0.0, 1.0 );
		s3d::ColorF clr1 = s3d::ColorF ( 0.0, 0.0, 0.0, 0.0 );
		SetColor ( clr0, clr1 ); Start ( time );
	}

	//ブラックアウト( 0x00000000 → 0xff000000 )
	void FadeRect::SetBlackOut ( UINT time )
	{
		s3d::ColorF clr0 = s3d::ColorF ( 0.0, 0.0, 0.0, 0.0 );
		s3d::ColorF clr1 = s3d::ColorF ( 0.0, 0.0, 0.0, 1.0 );
		SetColor ( clr0, clr1 ); Start ( time );
	}

}	//namespace GAME

