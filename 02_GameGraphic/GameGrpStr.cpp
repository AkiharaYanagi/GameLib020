﻿//=================================================================================================
//
// ゲーム グラフィック　ストリング
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイル　インクルード
//-------------------------------------------------------------------------------------------------
#include "GameGrpStr.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//=======================================================================
	//	Rect 
	//=======================================================================
	GameGraphicString::GameGraphicString ()
	{
	}

	GameGraphicString::~GameGraphicString ()
	{
	}

	void GameGraphicString::Load ()
	{
		m_font = s3d::Font ( m_size );
		GameGraphicCore::Load ();
	}

	void GameGraphicString::Draw ()
	{
		if ( ! m_valid ) { return; }

		m_font ( m_str ).draw ( m_pos.x, m_pos.y, m_colorF );
	}

	void GameGraphicString::SetPos ( VEC2 v )
	{
		m_pos = v;
	}

	void GameGraphicString::SetStr ( s3d::String str )
	{
		m_str = str;
	}

	void GameGraphicString::SetColorF ( s3d::ColorF clrf )
	{
		m_colorF = clrf;
	}


}	//namespace GAME
