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
	const int32 G_Font::FONT_SIZE_60 = 60;

	G_Font::G_Font ()
	{
	}

	G_Font::~G_Font ()
	{
	}

	void G_Font::Load ()
	{
//		s3d::FontAsset::Register ( ASYNC_FONT, 60 );

//		m_font_20 = s3d::Font ( FONT_SIZE_20 );
		s3d::FontAsset::Register ( FONT_20, 20 );
		s3d::FontAsset::LoadAsync ( FONT_20 );

//		m_font_30 = s3d::Font ( s3d::FontMethod::SDF, FONT_SIZE_30 );
		s3d::FontAsset::Register ( FONT_30, s3d::FontMethod::SDF, FONT_SIZE_30 );
		s3d::FontAsset::LoadAsync ( FONT_30 );

//		m_font_40 = s3d::Font { s3d::FontMethod::SDF, FONT_SIZE_40 };
		s3d::FontAsset::Register ( FONT_40, s3d::FontMethod::SDF, FONT_SIZE_40 );
		s3d::FontAsset::LoadAsync ( FONT_40 );

//		m_font_Menu = s3d::Font { s3d::FontMethod::MSDF, 60 };
		s3d::FontAsset::Register ( FONT_60, s3d::FontMethod::MSDF, FONT_SIZE_60 );
		s3d::FontAsset::LoadAsync ( FONT_60 );
	}


	void G_Font::Draw ( FONT_SIZE size, const s3d::String & str, double x, double y, s3d::ColorF clr ) const
	{
		switch ( size )
		{
		case SIZE_20:
			//m_font_20 ( str ).draw ( x, y, clr );
			s3d::FontAsset( FONT_20 )( str ).draw ( x, y, clr );
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
		//m_font_30 ( str ).draw ( txs, x, y, clr );
		s3d::FontAsset( FONT_30 )( str ).draw ( txs, x, y, clr );
	}

	void G_Font::Draw_40 ( s3d::String str, double x, double y, s3d::ColorF clr ) const
	{
		const double outline = 0.2;
		const s3d::ColorF oClr { 0.0, 0.1, 0.5 };
		s3d::TextStyle txs = s3d::TextStyle::Outline ( outline, oClr );
		//m_font_40 ( str ).draw ( txs, x, y, clr );
		s3d::FontAsset( FONT_40 )( str ).draw ( txs, x, y, clr );
	}

	void G_Font::DrawMenuStr ( s3d::String str, double x, double y )
	{
		const double outline = 0.2;
		const s3d::ColorF oClr { 0.0, 0.3, 0.6 };
		s3d::TextStyle txs = s3d::TextStyle::Outline ( outline, oClr );
		//m_font_Menu ( str ).draw ( txs, x, y );
		s3d::FontAsset( FONT_60 )( str ).draw ( txs, x, y );
	}

#if 0

	void G_Font::DrawAsset ()
	{
		s3d::FontAsset( ASYNC_FONT )( U"DrawAsset()" ).draw ( 200, 200, ColorF{ 0.f, 1.f, 1.f } );
	}

#endif // 0


}	//namespace GAME

