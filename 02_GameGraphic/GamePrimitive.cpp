//=================================================================================================
//
// ゲームプリミティブ グラフィック
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイル　インクルード
//-------------------------------------------------------------------------------------------------
#include "GamePrimitive.h"
#include "G_GrpTx.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//=======================================================================
	//	Rect 
	//=======================================================================
	GamePrimitiveRect::GamePrimitiveRect ()
	{
	}

	GamePrimitiveRect::~GamePrimitiveRect ()
	{
	}

	void GamePrimitiveRect::Draw ()
	{
		if ( ! m_valid ) { return; }

		//unique_ptrを取得
		UP_RndrTx upRndTx = G_GrpTx::Inst()->Handover_OutTx ();

		{
			const s3d::ScopedRenderTarget2D target ( * upRndTx );
			m_rect.draw ( m_color );
		}

		//unique_ptrを返す
		G_GrpTx::Inst()->Refund_OutTx ( std::move ( upRndTx ) );
	}

	void GamePrimitiveRect::SetColor ( const s3d::ColorF color )
	{
		m_color = color;
		GameGraphicCore::SetColor ( color.toColor().asUint32() );
	}

}	//namespace GAME

