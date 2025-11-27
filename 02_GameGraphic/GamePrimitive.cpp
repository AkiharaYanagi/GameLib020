//=================================================================================================//
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

			if ( m_frame )
			{
				m_rect.drawFrame ( 1.0, 0.0, m_color );
			}
			else
			{
				m_rect.draw ( m_color );
			}
		}

		//unique_ptrを返す
		G_GrpTx::Inst()->Refund_OutTx ( std::move ( upRndTx ) );
	}


	void GamePrimitiveRect::SetPos ( VEC2 vec )
	{
		m_rect.setPos ( s3d::Point ( (int32)vec.x, (int32)vec.y ) );
	}

	void GamePrimitiveRect::SetSize ( int32 w, int32 h )
	{
		m_rect.setSize ( s3d::Size ( w, h ) );
	}

	void GamePrimitiveRect::SetSize ( VEC2 vec )
	{
		m_rect.setSize ( s3d::Size ( (int32)vec.x, (int32)vec.y ) );
	}

	void GamePrimitiveRect::SetColor ( const s3d::ColorF color )
	{
		m_color = color;
		GameGraphicCore::SetColor ( color.toColor().asUint32() );
	}

	void GamePrimitiveRect::SetColor ( const _CLR color )
	{
		m_color = s3d::ColorF { (double)color.r, (double)color.g, (double)color.b, (double)color.a };
		GameGraphicCore::SetColor ( color );
	}

}	//namespace GAME

