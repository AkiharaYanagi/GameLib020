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

		//メインテクスチャ unique_ptrを取得
		UP_RndrTx upRndTx = G_GrpTx::Inst()->Handover_RndrTx ();

		//最終テクスチャ unique_ptrを取得
		UP_RndrTx upOutTx = G_GrpTx::Inst()->Handover_OutTx ();


		for ( P_Ob pob : * papOb )
		{
			P_Tx ptx = paptx->at ( pob->GetIndexTexture () );

			//位置合わせ
			//ピクセルシェーダ用レンダーテクスチャ
			{
				const ScopedRenderTarget2D target { * upPSTx };
				upPSTx->clear ( Palette::Black );
				GameGraphicBase::_Draw ();
			}

			//一時領域に現在描画を書込
			{
				const ScopedRenderTarget2D target { * upRndTx };
				upOutTx->draw();
			}

			//最終描画対象を指定
			{
				const ScopedRenderTarget2D target{ * upOutTx };
				{
					//シェーダを適用するテクスチャを指定
					s3d::Graphics2D::SetPSTexture ( 1, * upPSTx );

					//スクリーンオーバーレイのシェーダを適用
					P_PxShd p_pxshd = G_GrpTx::Inst()->GetpPxShd ();
					const s3d::ScopedCustomShader2D shader ( * p_pxshd );

					//シェーダを適用したものを対象に描画
					upRndTx->draw();
				}
			}
		}
			
		//最終テクスチャ unique_ptrを返す
		G_GrpTx::Inst()->Refund_OutTx ( std::move ( upOutTx ) );

		//メインテクスチャ unique_ptrを返す
		G_GrpTx::Inst()->Refund_RndrTx ( std::move ( upRndTx ) );

		//ピクセルシェーダ用テクスチャ unique_ptrを返す
		G_GrpTx::Inst()->Refund_PSTx ( std::move ( upPSTx ) );
	}



}	//namespace GAME

