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


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//=======================================================================
	//	Rect 
	//=======================================================================
	class GameGraphicString : public GameGraphicBase
	{
		s3d::String m_str { U"GrpStr" };		
		int32		m_size { 20 };
		VEC2		m_pos { 0, 0 };		//基準位置
		s3d::ColorF	m_colorF { 1.f, 1.f, 1.f, 1.f };

	public:
		GameGraphicString ();
		GameGraphicString ( const GameGraphicString & rhs ) = delete;
		~GameGraphicString ();

		void Draw ();
		void _Draw ();

		void SetSize ( int32 size ) { m_size = size; }
		void SetPos ( VEC2 v );
		void SetStr ( s3d::String str );
		void SetColorF ( s3d::ColorF clrf );
	};

	using GrpStr = GameGraphicString;
	using P_GrpStr = std::shared_ptr < GrpStr >;



}	//namespace GAME

