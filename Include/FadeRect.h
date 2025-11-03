//=================================================================================================
//
// FadeRect ヘッダファイル
//		最前面に配置した画面サイズの半透明グラフィックで、フェードイン・アウトを行う
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "02_GameGraphic.h"
#include "Define_Siv3D.h"
#include "Timer.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class FadeRect : public PrmRect
	{
		P_Timer	m_timer;
		//_CLR	m_color0;	//初期色
		//_CLR	m_color1;	//目標色
		s3d::ColorF		m_color0;	//初期色
		s3d::ColorF		m_color1;	//目標色

		bool	m_after_clear { F };	//終了時に非表示にするかどうか

	public:
		FadeRect ();
		FadeRect ( UINT time ) { SetTime ( time ); };
		FadeRect ( const FadeRect & rhs ) = delete;
		~FadeRect ();

		void Move ();

		//色設定
		//void SetColor ( _CLR clr0, _CLR clr1 ) { m_color0 = clr0; m_color1 = clr1; }
		void SetColor ( s3d::ColorF clr0, s3d::ColorF clr1 ) { m_color0 = clr0; m_color1 = clr1; }
		void SetTime ( UINT t )
		{ 
			m_timer->SetTargetTime ( t ); 
		}

		void Start ()
		{
			m_timer->Start ();
			PrmRect::SetValid ( true );
		}

		void Start ( UINT time )
		{
			m_timer->SetTargetTime ( time );
			m_timer->Start ();
			PrmRect::SetColor ( m_color0 );
			PrmRect::SetValid ( true );
		}

		void Off ()
		{
			m_timer->Clear ();
			PrmRect::SetColor ( m_color1 );
			PrmRect::SetValid ( F );
		}

		bool IsActive () const { return m_timer->IsActive (); }
		bool IsLast () const { return m_timer->IsLast (); }

		//終了時に非表示にするかどうか
		void SetAfterClear ( bool b ) { m_after_clear = b; }

		//目標値にする
		void ShiftTargetColor ();

		//-----------------------------------
		//具体設定
		//@info 0x00000000 を指定するときD3DXCOLORの初期化のため整数リテラル UL を付ける
		
		//ホワイトイン( 0xffffffff → 0x00ffffff )
		void SetWhiteIn ( UINT time );
		void StartWhiteIn ( UINT time ) { SetWhiteIn ( time ); Start (); }

		//ホワイトアウト( 0x00ffffff → 0xffffffff )
		void SetWhiteOut ( UINT time );
		void StartWhiteOut ( UINT time ) { SetWhiteOut ( time ); Start (); }

		//ブラックイン ( 0xff000000 → 0x00000000 )
		void SetBlackIn ( UINT time );
		void StartBlackIn ( UINT time ) { SetBlackIn ( time ); Start (); }

		//ブラックアウト( 0x00000000 → 0xff000000 )
		void SetBlackOut ( UINT time );
		void StartBlackOut ( UINT time ) { SetBlackOut ( time ); Start (); }
	};

	using P_FadeRect = std::shared_ptr < FadeRect >;


}	//namespace GAME


