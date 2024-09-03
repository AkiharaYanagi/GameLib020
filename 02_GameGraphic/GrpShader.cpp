//=================================================================================================
//
// ゲームグラフィック　シェーダ利用
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイル　インクルード
//-------------------------------------------------------------------------------------------------
#include "GrpShader.h"
#include "G_GrpTx.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	GrpShader::GrpShader ()
	{
	}

	GrpShader::~GrpShader ()
	{
	}


	void GrpShader::Draw ()
	{
		PAP_Ob papOb = Getpap_ob ();
		PAP_Tx paptx = Getpap_tx ();

		//ピクセルシェーダ用テクスチャ unique_ptrを取得
		UP_RndrTx upPSTx = G_GrpTx::Inst()->Handover_PSTx ();

		for ( P_Ob pob : * papOb )
		{
			P_Tx ptx = paptx->at ( pob->GetIndexTexture () );

			//位置合わせレンダーテクスチャ
			{
				const ScopedRenderTarget2D target { * upPSTx };
				upPSTx->clear ( Palette::Black );
				GameGraphicBase::Draw ();
			}


			//スクリーンオーバーレイのシェーダを適用
			P_PxShd p_pxshd = G_GrpTx::Inst()->GetpPxShd ();
			
			//メインテクスチャ unique_ptrを取得
			UP_RndrTx upRndTx = G_GrpTx::Inst()->Handover_RndrTx ();

			//s3d::Graphics2D::SetPSTexture ( 1, m_rndrTx );
			s3d::Graphics2D::SetPSTexture ( 1, * upPSTx );
			{
				const s3d::ScopedCustomShader2D shader ( * p_pxshd );
				upRndTx->draw( 0, 0 );
			}

			//メインテクスチャ unique_ptrを返す
			G_GrpTx::Inst()->Refund_RndrTx ( std::move ( upRndTx ) );
		}

		//ピクセルシェーダ用テクスチャ unique_ptrを返す
		G_GrpTx::Inst()->Refund_PSTx ( std::move ( upPSTx ) );
	}



}	//namespace GAME

