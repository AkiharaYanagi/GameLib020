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
#include "G_GrpTx.h"


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
//		m_ps_screen = HLSL { U"ScreenBlend_0.hlsl", U"PS" };
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



		//メインテクスチャ unique_ptrを取得
		UP_RndrTx upMainTx = G_GrpTx::Inst()->Handover_RndrTx ();

		//最終テクスチャ unique_ptrを取得
		UP_RndrTx upOutTx = G_GrpTx::Inst()->Handover_OutTx ();


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
					pGrp->_Draw ();
				}

#if 0

				//メイン　レンダーテクスチャ
				{
					const ScopedRenderTarget2D target { * upRndTx };

					//スクリーンオーバーレイのシェーダを適用
					//s3d::Graphics2D::SetPSTexture ( 1, m_windmill );
					s3d::Graphics2D::SetPSTexture ( 1, m_rndrTx );
					//s3d::Graphics2D::SetPSTexture ( 1, * ptx );
					//s3d::Graphics2D::SetPSTexture ( 1, * upRndTx );
					{
						//const s3d::ScopedCustomShader2D shader ( m_ps );
						const s3d::ScopedCustomShader2D shader ( m_ps_screen );

						m_emoji.scaled(2).drawAt ( s3d::Scene::Center() );
						//pGrp->_Draw ();
						upRndTx->draw( 0, 0 );
						//m_rndrTx.draw();
					}
#if 0
#endif // 0
				}

#endif // 0
				{
					//最終描画対象を指定
					const ScopedRenderTarget2D target { * upOutTx };
					{
						//シェーダを適用するテクスチャを指定
						s3d::Graphics2D::SetPSTexture ( 1, m_rndrTx );
						const s3d::ScopedCustomShader2D shader ( m_ps_screen );


						//m_rndrTx.draw();
						//m_emoji.scaled(2).drawAt ( s3d::Scene::Center() );
						//pGrp->_Draw ();

						//シェーダを適用したものを対象に描画
						upMainTx->draw();
					}
				}

	//				ptx->draw();
			}

		}


#if 0

		s3d::Graphics2D::SetPSTexture ( 1, * ptx );
		{

			//全体レンダーテクスチャの描画
			upRndrTx->draw ( 200, 100 );
		}

		//メイングラフィックにレンダーテクスチャを返還
		//GrpLst::Inst()->Refund_RndrTx ( std::move ( upRndrTx ) );


		//全体レンダーテクスチャの描画
		//		upRndTx->draw ( 200, 100 );
		//		upRndTx->draw ( 0, 0 );

//		m_rndrTx.draw();
//
//
// 

#endif // 0

		//メインテクスチャ unique_ptrを返す
		G_GrpTx::Inst()->Refund_RndrTx ( std::move ( upMainTx ) );

		//最終テクスチャ unique_ptrを返す
		G_GrpTx::Inst()->Refund_OutTx ( std::move ( upOutTx ) );

		//全体レンダーテクスチャの描画
		G_GrpTx::Inst()->Draw ();
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

