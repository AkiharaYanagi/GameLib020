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
			float x = GetPos().x;
			float y = GetPos().y;
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

			//最終描画
			if ( atlas ) { atlas->DrawPosScl ( index, pos, scaling ); }

		}
	}

	void GrpAtlas::In ()
	{
	}


	void GrpAtlas::DrawPos ( uint32_t txid, float x, float y )
	{
		atlas->DrawPos ( txid, x, y );
	}



}	//namespace GAME
