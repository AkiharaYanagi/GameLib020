//=================================================================================================
//
//	GrpAtlasソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "GrpAtlas.h"
#include "G_GrpTx.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	GrpAtlas::GrpAtlas ()
	{
		//オブジェクトの拡大縮小基準をテクスチャの中心にする
		//　オブエクト追加時は手動で設定する
		PAP_Ob papob = Getpap_ob ();
		papob->at ( 0 )->SetbScalingCntrOfTx ( T );
	}


	GrpAtlas::~GrpAtlas ()
	{
	}

	void GrpAtlas::Load ()
	{
		//ファイル名からアトラスを読込
		//atlas.Load ();
	}


	void GrpAtlas::Draw ()
	{
		//稼働フラグ
		if ( ! GetValid () ) { return; }

		//シェーダ利用は分岐
		if ( GetShader () ) { GrpAtlas::ShaderDraw (); return; }


		//最終描画テクスチャ unique_ptrを取得
		UP_RndrTx upOutTx = G_GrpTx::Inst()->Handover_OutTx ();

		{
			const s3d::ScopedRenderTarget2D target ( * upOutTx );
			_Draw ();
		}

		//unique_ptrを返す
		G_GrpTx::Inst()->Refund_OutTx ( std::move ( upOutTx ) );
	}

	void GrpAtlas::_Draw ()
	{
		//オブジェクトの数だけ描画
		for ( P_Ob pob : * Getpap_ob() )
		{
			VEC2 pos = pob->GetPos();
			//float x = GetPos().x;
			//float y = GetPos().y;
			uint32_t index = GetIndexTexture ();

			VEC2 scaling = pob->GetScaling();

#if 0

			//中心位置
			Canvas cvs = atlas->GetIdCanvas ( index );
			float txw = (float)cvs.TxW ();
			float txh = (float)cvs.TxH ();
			VEC2 txCntr = VEC2 ( txw / 2.f, txh / 2.f );

			//拡大縮小(反転)
			VEC2 scaling = pob->GetScaling();
			s3d::Vec2 vScaling { scaling.x, scaling.y };

			//拡縮中心位置
			VEC2 SclCntr = { 0, 0 };
			if ( pob->GetbScalingCntrOfTx () )
			{
				SclCntr = txCntr;
			}
			else
			{
				//指定値を利用
				SclCntr.x = pob->GetScalingCenter ().x;
				SclCntr.y = pob->GetScalingCenter ().y;
			}

			//原点に戻してから拡縮し、元の位置にする
			x += SclCntr.x - (SclCntr.x * scaling.x);
			y += SclCntr.y - (SclCntr.y * scaling.y);


#endif // 0

			//色補正(アルファ値は透明, RGBは乗算)
			_CLR clr = pob->GetColor ();
			if ( _CLR ( 0xffffffff ) == clr )
			{
				//オブジェクト色指定がある場合はそちらを優先
				clr = GetColor ();	//Core
			}
			s3d::ColorF clrf { clr.r, clr.g, clr.b, clr.a };


			//最終描画
//			if ( atlas ) { atlas->DrawPosScl ( index, pos, scaling ); }
			if ( atlas ) { atlas->Draw ( index, pos, scaling, clrf ); }

		}
	}

	void GrpAtlas::In ()
	{
	}


	void GrpAtlas::DrawPos ( uint32_t txid, float x, float y )
	{
		atlas->DrawPos ( txid, x, y );
	}


	void GrpAtlas::ShaderDraw ()
	{
		PAP_Ob papOb = Getpap_ob ();

		//ピクセルシェーダ用テクスチャ unique_ptrを取得
		UP_RndrTx upPSTx = G_GrpTx::Inst()->Handover_PSTx ();

		//メインテクスチャ unique_ptrを取得
		UP_RndrTx upRndTx = G_GrpTx::Inst()->Handover_RndrTx ();

		//最終テクスチャ unique_ptrを取得
		UP_RndrTx upOutTx = G_GrpTx::Inst()->Handover_OutTx ();


		for ( P_Ob pob : * papOb )
		{
			//位置合わせ
			//ピクセルシェーダ用レンダーテクスチャ
			{
				const ScopedRenderTarget2D target { * upPSTx };
				upPSTx->clear ( Palette::Black );
				GrpAtlas::_Draw ();
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
