//=================================================================================================
//
// ゲームプリミティブ グラフィック
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイル　インクルード
//-------------------------------------------------------------------------------------------------
#include "Define_Siv3D.h"
#include "GameGraphicCore.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//=======================================================================
	//	Rect 
	//=======================================================================
	class GamePrimitiveRect : public GameGraphicCore
	{
		s3d::Rect		m_rect { 100, 200, 300, 400 };
		s3d::ColorF		m_color { 1.f, 1.f, 1.f, 1.f };

		bool			m_frame { F };
		
	public:
		GamePrimitiveRect ();
		GamePrimitiveRect ( const GamePrimitiveRect & rhs ) = delete;
		~GamePrimitiveRect ();

		//---------------------------------------------------------------------
		void Draw ();

		void SetRect ( const s3d::Rect rect ) { m_rect.set( rect ); }
		void SetRect ( int32 x, int32 y, int32 w, int32 h ) { m_rect.set( x, y, w, h ); }
		
		void SetPos ( const s3d::Rect::position_type pos ) { m_rect.setPos ( pos ); }
		void SetPos ( int32 x, int32 y ) { m_rect.setPos ( s3d::Point ( x, y ) ); }
		void SetPos ( VEC2 vec );
		s3d::Point GetPos () const { return m_rect.pos; }

		void SetSize ( const s3d::Rect::size_type size ) { m_rect.setSize ( size ); }
		void SetSize ( int32 w, int32 h );
		void SetSize ( VEC2 vec );
		VEC2 GetSize () const { return VEC2 ( (float)m_rect.w, (float)m_rect.h ); }

		void SetColor ( const s3d::ColorF color );
		void SetColor ( const _CLR color );

		void SetZero () { m_rect.set( 0, 0, 0, 0 ); }

		void SetFrame ( bool b ) { m_frame = b; }	
	};

	using PrmRect = GamePrimitiveRect;
	using P_PrmRect = std::shared_ptr < PrmRect >;



}	//namespace GAME

