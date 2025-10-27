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

//	constexpr char32_t ASYNC_FONT[] = U"AsyncFont";
	constexpr char32_t FONT_20[] = U"Font_20";
	constexpr char32_t FONT_30[] = U"Font_30";
	constexpr char32_t FONT_40[] = U"Font_40";
	constexpr char32_t FONT_60[] = U"Font_60";


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

//		s3d::Font	m_font_async;


//		s3d::Font	m_font_20;
		static const int32		FONT_SIZE_20;

//		s3d::Font	m_font_30;
		static const int32		FONT_SIZE_30;

//		s3d::Font	m_font_40;
		static const int32		FONT_SIZE_40;

		//メニュ用フォント
//		s3d::Font	m_font_Menu;
		static const int32		FONT_SIZE_60;

	public:
		enum FONT_SIZE
		{
			SIZE_20,
			SIZE_30,
			SIZE_40,
		};

		void Load ();
		void Draw ( FONT_SIZE size, const s3d::String & str, double x, double y, s3d::ColorF clr ) const;
		void Draw_30 ( s3d::String str, double x, double y, s3d::ColorF clr ) const;
		void Draw_40 ( s3d::String str, double x, double y, s3d::ColorF clr ) const;

		void DrawMenuStr ( s3d::String str, double x, double y );

//		void DrawAsset ();
	};

#define	G_FONT_DRAW		G_Font::Inst()->Draw
#define	G_FONT_DRAW_MENU		G_Font::Inst()->DrawMenuStr


}	//namespace GAME

