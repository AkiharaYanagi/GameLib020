//=================================================================================================
//
// ゲーム グラフィック　ストリング
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイル　インクルード
//-------------------------------------------------------------------------------------------------
#include "G_Font.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//--------------------------------------------------
	//シングルトンパターン	static実体
	P_G_Font	G_Font::m_inst = nullptr;
	//--------------------------------------------------

	const int32 G_Font::FONT_SIZE_20 = 20;
	const int32 G_Font::FONT_SIZE_30 = 30;
	const int32 G_Font::FONT_SIZE_40 = 40;

	G_Font::G_Font ()
	{
	}

	G_Font::~G_Font ()
	{
	}

	void G_Font::Load ()
	{
		m_font_20 = s3d::Font ( FONT_SIZE_20 );
		m_font_30 = s3d::Font ( s3d::FontMethod::SDF, FONT_SIZE_30 );
		m_font_40 = s3d::Font { s3d::FontMethod::SDF, FONT_SIZE_40 };
		m_font_Menu = s3d::Font { s3d::FontMethod::MSDF, 60 };
	}


	void G_Font::Draw ( FONT_SIZE size, s3d::String str, double x, double y, s3d::ColorF clr ) const
	{
		switch ( size )
		{
		case SIZE_20:
			m_font_20 ( str ).draw ( x, y, clr );
			break;

		case SIZE_30:
			Draw_30 ( str, x, y, clr );
			break;

		case SIZE_40:
			Draw_40 ( str, x, y, clr );
			break;
		}

	}

	void G_Font::Draw_30 ( s3d::String str, double x, double y, s3d::ColorF clr ) const
	{
		const double outline = 0.2;
		const s3d::ColorF oClr { 0.0, 0.1, 0.5 };
		s3d::TextStyle txs = s3d::TextStyle::Outline ( outline, oClr );
		m_font_30 ( str ).draw ( txs, x, y, clr );
	}

	void G_Font::Draw_40 ( s3d::String str, double x, double y, s3d::ColorF clr ) const
	{
		const double outline = 0.2;
		const s3d::ColorF oClr { 0.0, 0.1, 0.5 };
		s3d::TextStyle txs = s3d::TextStyle::Outline ( outline, oClr );
		m_font_40 ( str ).draw ( txs, x, y, clr );
	}

	void G_Font::DrawMenuStr ( s3d::String str, double x, double y )
	{
		const double outline = 0.2;
		const s3d::ColorF oClr { 0.0, 0.3, 0.6 };
		s3d::TextStyle txs = s3d::TextStyle::Outline ( outline, oClr );
		m_font_Menu ( str ).draw ( txs, x, y );
	}


}	//namespace GAME

