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
		
	public:
		GamePrimitiveRect ();
		GamePrimitiveRect ( const GamePrimitiveRect & rhs ) = delete;
		~GamePrimitiveRect ();

		//---------------------------------------------------------------------
		void Draw ();

		void SetRect ( const s3d::Rect rect ) { m_rect.set( rect ); }
		void SetRect ( int32 x, int32 y, int32 w, int32 h ) { m_rect.set( x, y, w, h ); }
		
		void SetPos ( int32 x, int32 y ) { m_rect.setPos ( s3d::Point ( x, y ) ); }
		void SetPos ( const s3d::Rect::position_type pos ) { m_rect.setPos ( pos ); }
		s3d::Point GetPos () const { return m_rect.pos; }

		void SetSize ( const s3d::Rect::size_type size ) { m_rect.setSize ( size ); }
		void SetColor ( const s3d::ColorF color );

		void SetZero () { m_rect.set( 0, 0, 0, 0 ); }
	};

	using PrmRect = GamePrimitiveRect;
	using P_PrmRect = std::shared_ptr < PrmRect >;



}	//namespace GAME

