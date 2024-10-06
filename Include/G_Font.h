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

	private:
		s3d::Font	m_font_20;
		static const int32		FONT_SIZE_20;

		s3d::Font	m_font_40;
		static const int32		FONT_SIZE_40;

		//メニュ用フォント
		s3d::Font	m_font_Menu;

	public:
		enum FONT_SIZE
		{
			SIZE_20,
			SIZE_40,
		};

		void Load ();
		void Draw ( FONT_SIZE size, s3d::String str, double x, double y, s3d::ColorF clr ) const;
		void Draw_40 ( s3d::String str, double x, double y, s3d::ColorF clr ) const;

		void DrawMenuStr ( s3d::String str, double x, double y );
	};

#define	G_FONT_DRAW		G_Font::Inst()->Draw


}	//namespace GAME

