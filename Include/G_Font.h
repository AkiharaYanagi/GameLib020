//=================================================================================================
//
// グローバル　フォント
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイル　インクルード
//-------------------------------------------------------------------------------------------------
#include "Define_Siv3D.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class G_Font;
	using P_G_Font = std::unique_ptr < G_Font >;
	
	class G_Font
	{
	//--------------------------------------------------
	//シングルトンパターン
	private:
		static P_G_Font	m_inst;
		G_Font ();
		G_Font ( const G_Font & rhs ) = delete;
	public:
		~G_Font ();
		static void Create() { if ( ! m_inst ) { m_inst = P_G_Font ( new G_Font () ); } }
		static P_G_Font & Inst() { return m_inst; }
	//--------------------------------------------------

		s3d::Font	m_font;
		s3d::String m_str { U"GrpStr" };		
		int32		m_size { 20 };
		VEC2		m_pos { 0, 0 };		//基準位置
		s3d::ColorF	m_colorF { 1.f, 1.f, 1.f, 1.f };

	public:

		void Load ();
		void Draw ();
		void Draw ( double x, double y, s3d::ColorF clr );

		void SetSize ( int32 size ) { m_size = size; }
		void SetPos ( VEC2 v );
		void SetStr ( s3d::String str );
		void SetColorF ( s3d::ColorF clrf );
	};

#define	G_FONT_DRAW		G_Font::Inst()->Draw;


}	//namespace GAME

