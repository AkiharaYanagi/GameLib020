//=================================================================================================
//
// ゲーム グラフィック　ストリング
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイル　インクルード
//-------------------------------------------------------------------------------------------------
#include "GameGrpStr.h"
#include "G_GrpTx.h"
#include "G_Font.h"


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
		m_size = G_Font::SIZE_20;
	}

	GameGraphicString::~GameGraphicString ()
	{
	}

	void GameGraphicString::Draw ()
	{
		//稼働フラグ
		if ( ! m_valid ) { return; }

		//シェーダ利用は分岐
//		if ( m_shader ) { ShaderDraw (); return; }


		//最終描画テクスチャ unique_ptrを取得
		UP_RndrTx upOutTx = G_GrpTx::Inst()->Handover_OutTx ();

		{
			const s3d::ScopedRenderTarget2D target ( * upOutTx );
			_Draw ();
		}

		//unique_ptrを返す
		G_GrpTx::Inst()->Refund_OutTx ( std::move ( upOutTx ) );
	}


	void GameGraphicString::_Draw ()
	{
		if ( m_bMenu )
		{
			//メニュ
			G_FONT_DRAW_MENU ( m_str, m_pos.x, m_pos.y );
		}
		else
		{
			//通常フォント(サイズ指定)
			G_FONT_DRAW ( m_size, m_str, m_pos.x, m_pos.y, m_colorF );

		}
	}

	void GameGraphicString::SetPos ( VEC2 v )
	{
		m_pos = v;
	}

	void GameGraphicString::SetStr ( const s3d::String & str )
	{
		m_str = str;
	}

	void GameGraphicString::SetColorF ( s3d::ColorF clrf )
	{
		m_colorF = clrf;
	}


}	//namespace GAME

