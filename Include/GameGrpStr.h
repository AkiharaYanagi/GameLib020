//=================================================================================================
//
// ゲーム グラフィック　ストリング
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイル　インクルード
//-------------------------------------------------------------------------------------------------
#include "Define_Siv3D.h"
#include "GameGraphic.h"
#include "G_Font.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//=======================================================================
	//	String 
	//=======================================================================
	class GameGraphicString : public GameGraphicBase
	{
		s3d::String m_str { U"GrpStr" };		
		VEC2		m_pos { 0, 0 };		//基準位置
		s3d::ColorF	m_colorF { 1.f, 1.f, 1.f, 1.f };

		//int32		m_size { 20 };
		G_Font::FONT_SIZE		m_size;
		bool		m_bMenu { F };		//メニュ分岐

	public:
		GameGraphicString ();
		GameGraphicString ( const GameGraphicString & rhs ) = delete;
		~GameGraphicString ();

		void Draw ();
		void _Draw ();

		void SetSize ( G_Font::FONT_SIZE size ) { m_size = size; }
		void SetPos ( VEC2 v );
		void SetPos ( float x, float y ) { m_pos.x = x; m_pos.y = y; }
		void SetStr ( const s3d::String & str );
		void SetColorF ( s3d::ColorF clrf );

		void SetbMenu ( bool b ) { m_bMenu = b; }
	};

	using GrpStr = GameGraphicString;
	using P_GrpStr = std::shared_ptr < GrpStr >;



}	//namespace GAME

