//=================================================================================================
//
// SgaderList ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "ShaderList.h"
#include "GameLibConst.h"
#include "GameGraphicList.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//------------------------------------------
	//	Static実体
	//------------------------------------------
	// シングルトンオブジェクト
	UP_SrdLst	ShaderList::m_inst;

	//コンストラクタ
	ShaderList::ShaderList ()
	{
		mpap_GrpMain = std::make_unique < AP_Grp > ();
	}

	ShaderList::~ShaderList ()
	{
	}

	void ShaderList::Load ()
	{
		m_ps = HLSL { U"example/shader/hlsl/multi_texture_blend.hlsl", U"PS" };
		m_ps_screen = HLSL { U"ScreenBlend.hlsl", U"PS" };
		//		m_ps_screen = HLSL { U"example/shader/hlsl/rgb_shift.hlsl", U"PS" };
		m_emoji = s3d::Texture ( U"🐈️"_emoji );
		m_windmill = s3d::Texture ( U"example/windmill.png", TextureDesc::Mipped );
	}

	void ShaderList::Draw ()
	{
#if 0
		//メイングラフィックからレンダーテクスチャを取得
		UP_RndrTx upRndrTx = GrpLst::Inst()->Handover_RndrTx ();

		//個数が０のとき通常描画を１回して終了
		if ( 0 == mpap_GrpMain->size() )
		{
			upRndrTx->draw( 0, 0 );

			//メイングラフィックにレンダーテクスチャを返還
			GrpLst::Inst()->Refund_RndrTx ( std::move ( upRndrTx ) );
			return;
		}
#endif // 0



#if 0

		//シェーダの利用
		{
			const ScopedRenderTarget2D target { * upRndrTx };

			//各グラフィックの描画
			for ( P_Grp pGrp : * mpap_GrpMain )
			{
				PAP_Tx paptx = pGrp->Getpap_tx ();

				for ( P_Ob pob : * pGrp->Getpap_ob () )
				{
					P_Tx ptx = paptx->at ( pob->GetIndexTexture () );

//					s3d::Graphics2D::SetPSTexture ( 1, * ptx );

					//適用テクスチャを指定
					//s3d::Graphics2D::SetPSTexture ( 1, * upRndrTx );
					s3d::Graphics2D::SetPSTexture ( 0, * ptx );
					{
						//シェーダの利用
						const ScopedCustomShader2D shader { m_ps_screen };
						pGrp->Draw ();
					}
				}
			}
		}

		//全体レンダーテクスチャの描画
		upRndrTx->draw ( 200, 100 );

#endif // 0




		//各グラフィックの描画
		for ( P_Grp pGrp : * mpap_GrpMain )
		{
			PAP_Tx paptx = pGrp->Getpap_tx ();

			for ( P_Ob pob : * pGrp->Getpap_ob () )
			{
				P_Tx ptx = paptx->at ( pob->GetIndexTexture () );

				//位置合わせレンダーテクスチャ
				{
					const ScopedRenderTarget2D target { m_rndrTx };
					m_rndrTx.clear ( Palette::Black );
					pGrp->Draw ();
				}


				//スクリーンオーバーレイのシェーダを適用
				//s3d::Graphics2D::SetPSTexture ( 1, m_windmill );
				s3d::Graphics2D::SetPSTexture ( 1, m_rndrTx );
				//		s3d::Graphics2D::SetPSTexture ( 1, * upRndrTx );
				{
		//			const s3d::ScopedCustomShader2D shader ( m_ps );
					const s3d::ScopedCustomShader2D shader ( m_ps_screen );
		//			m_emoji.scaled(2).drawAt ( s3d::Scene::Center() );
//					upRndrTx->draw( 200, 100 );
					//upRndrTx->draw( 0, 0 );
				}
			}
		}


#if 0

		s3d::Graphics2D::SetPSTexture ( 1, * ptx );
		{

			//全体レンダーテクスチャの描画
			upRndrTx->draw ( 200, 100 );
		}

#endif // 0

		//メイングラフィックにレンダーテクスチャを返還
//		GrpLst::Inst()->Refund_RndrTx ( std::move ( upRndrTx ) );
	}

	//Z値で降順ソートされた位置に挿入
	void ShaderList::InsertByZ ( P_Grp pGrp )
	{
		//既存が１つも無いとき、通常の追加
		if ( 0 == mpap_GrpMain->size () ) { mpap_GrpMain->push_back ( pGrp ); return; }

		//Z値をチェックして指定位置に挿入
		float z = pGrp->GetZ ();
		for ( AP_Grp::iterator it = mpap_GrpMain->begin (); mpap_GrpMain->end () != it; ++ it )
		{
			float pz = ( *it )->GetZ ();
			if ( z > pz )
			{
				mpap_GrpMain->insert ( it, pGrp );
				return;
			}
		}

		//すべての値より小さい場合、末尾に追加
		mpap_GrpMain->push_back ( pGrp );
		return;
	}

	void ShaderList::Clear ()
	{
		mpap_GrpMain->clear ();
	}


}	//namespace GAME

