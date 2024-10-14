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
				//稼働時
				float alpha = (1.f / m_timer->GetTargetTime () ) * t;	//α値を算出
				if ( m_color0.a > m_color1.a )	//減少の場合は1.fから
				{
					alpha = 1.f - alpha;
				};
				s3d::ColorF c = s3d::ColorF ( m_color1.r, m_color1.g, m_color1.b, alpha );
				PrmRect::SetColor ( c );
			}
		}

		m_timer->Move ();
		PrmRect::Move ();
	}

	//ホワイトイン( 0xffffffff → 0x00ffffff )
	void FadeRect::SetWhiteIn ( UINT time )
	{
		m_timer->SetTargetTime ( time );
		s3d::ColorF clr0 = s3d::ColorF ( 1.0, 1.0, 1.0, 1.0 );
		s3d::ColorF clr1 = s3d::ColorF ( 1.0, 1.0, 1.0, 0.0 );
		SetColor ( clr0, clr1 );
	}

	//ホワイトアウト( 0x00ffffff → 0xffffffff )
	void FadeRect::SetWhiteOut ( UINT time )
	{
		m_timer->SetTargetTime ( time );
		s3d::ColorF clr0 = s3d::ColorF ( 1.0, 1.0, 1.0, 0.0 );
		s3d::ColorF clr1 = s3d::ColorF ( 1.0, 1.0, 1.0, 1.0 );
		SetColor ( clr0, clr1 );
	}

	//ブラックイン ( 0xff000000 → 0x00000000 )
	void FadeRect::SetBlackIn ( UINT time )
	{
		m_timer->SetTargetTime ( time );
		s3d::ColorF clr0 = s3d::ColorF ( 0.0, 0.0, 0.0, 1.0 );
		s3d::ColorF clr1 = s3d::ColorF ( 0.0, 0.0, 0.0, 0.0 );
		SetColor ( clr0, clr1 );;
	}

	//ブラックアウト( 0x00000000 → 0xff000000 )
	void FadeRect::SetBlackOut ( UINT time )
	{
		m_timer->SetTargetTime ( time );
		s3d::ColorF clr0 = s3d::ColorF ( 0.0, 0.0, 0.0, 0.0 );
		s3d::ColorF clr1 = s3d::ColorF ( 0.0, 0.0, 0.0, 1.0 );
		SetColor ( clr0, clr1 );
	}


	void FadeRect::ShiftTargetColor ()
	{
		PrmRect::SetColor ( m_color1 );
	}

}	//namespace GAME

