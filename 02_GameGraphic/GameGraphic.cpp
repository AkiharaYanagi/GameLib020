//=================================================================================================
//
// ゲームグラフィック　クラス　
//		ゲームで用いる画像を扱うオブジェクトを定義する。
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイル　インクルード
//-------------------------------------------------------------------------------------------------
#include "GameGraphic.h"
#include "G_GrpTx.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//■=======================================================================
	// ゲームグラフィック　ベース
	//■=======================================================================
	GameGraphicBase::GameGraphicBase ()
	{
		mpap_Texture = std::make_shared < AP_Tx > ();
		mpap_Object = std::make_shared < AP_Ob > ();
		mpap_Object->push_back ( std::make_shared < GameObject > () );
	}

	GameGraphicBase::~GameGraphicBase ()
	{
		mpap_Object->clear ();
	}

	//---------------------------------------------------------------------
	void GameGraphicBase::Move ()
	{
		for ( P_Ob pob : *mpap_Object ) { pob->PreMove (); }
	}

	void GameGraphicBase::Draw ()
	{
		//稼働フラグ
		if ( ! m_valid ) { return; }

		//テクスチャが０のときは描画しない
		if ( mpap_Texture->size () <= 0 ) { return; }

		//シェーダ利用は分岐
		if ( m_shader ) { ShaderDraw (); return; }


		//最終描画テクスチャ unique_ptrを取得
		UP_RndrTx upOutTx = G_GrpTx::Inst()->Handover_OutTx ();

		{
			const s3d::ScopedRenderTarget2D target ( * upOutTx );
			_Draw ();
		}

		//unique_ptrを返す
		G_GrpTx::Inst()->Refund_OutTx ( std::move ( upOutTx ) );
	}

	void GameGraphicBase::_Draw ()
	{
		//オブジェクトの数だけ描画
		for ( P_Ob pob : *mpap_Object )
		{
			//稼働フラグ
			if ( ! pob->GetValid () ) { continue; }


			//テクスチャ範囲の指定
			uint32 indexTexture = pob->GetIndexTexture ();
			s3d::RectF rectf = pob->GetRectF ();
			double x = pob->GetPos().x;
			double y = pob->GetPos().y;

			P_Tx ptx = mpap_Texture->at ( indexTexture );

			//初期値０(エリアなし)ならテクスチャ全体を描画
			if ( ! rectf.hasArea () )
			{
				s3d::Size sz = ptx->size ();
				s3d::Point pt = sz.xy ();
				rectf.set ( 0, 0, sz );
			}

			//テクスチャ中心位置
			VEC2 txCntr = s3d_UTL::GetTxCenter ( * ptx );

			//拡大縮小
			VEC2 v = pob->GetScaling();
			s3d::Vec2 vScaling { v.x, v.y };

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

			//原点に戻してから指定位置にする
			x += SclCntr.x - (SclCntr.x * v.x);
			y += SclCntr.y - (SclCntr.y * v.y);


			//回転中心位置
			VEC2 vec_rtt_cntr = pob->GetRotationCenter ();
			if ( pob->GetbRotationCntrOfTx () )
			{
				vec_rtt_cntr = txCntr;
			}
			else
			{
				vec_rtt_cntr = pob->GetRotationCenter ();
			}

			s3d::Vec2 rtt_cntr { vec_rtt_cntr.x, vec_rtt_cntr.y };
			//回転角
			double r = pob->GetRadian ();


			//色補正(アルファ値は透明, RGBは乗算)
			_CLR clr = pob->GetColor ();
			s3d::ColorF clrf { clr.r, clr.g, clr.b, clr.a };

			(*ptx)( rectf ).scaled ( vScaling ).rotatedAt( rtt_cntr, r ).draw ( x, y, clrf );
		}
	}

	//---------------------------------------------------------------------
	void GameGraphicBase::AddpTexture ( P_Tx ptx )
	{
		mpap_Texture->push_back ( ptx );
	}

	void GameGraphicBase::AddTexture ()
	{
		P_Tx ptx = std::make_shared < s3d::Texture > ();
		mpap_Texture->push_back ( ptx );
	}

	void GameGraphicBase::AddTexture ( s3d::String filename )
	{
		P_Tx ptx = std::make_shared < s3d::Texture > ( filename );
		mpap_Texture->push_back ( ptx );

		s3d::Size sz = ptx->size ();
		s3d::Point pt = sz.xy ();
	}

	void GameGraphicBase::AddTexture_FromArchive ( s3d::String filename )
	{
		//アーカイブからファイルを取得
		ARCHIVE_FILE_USE file = ACVR()->GetFilePointer ( filename.toWstr().c_str() );

		if ( file.filePointer == nullptr )
		{
			//TRACE_F ( TEXT("アーカイブにファイルが見つかりませんでした\n") );
			return;
		}

		//テクスチャの作成
//		P_Tx ptx = std::make_shared < s3d::Texture > ( filename );

		//メモリ上からテクスチャに変換
		s3d::MemoryReader mr ( (void*)(file.filePointer), file.fileSize );
		mr.setPos ( 0 );

		P_Tx pTx = std::make_shared < s3d::Texture > ( std::move ( mr ) );

		//テクスチャの設定
		mpap_Texture->push_back ( pTx );
	}

	void GameGraphicBase::SetpTexture ( P_Tx ptx )
	{
		//0の位置にテクスチャを設定します
		//map_Texture->at ( 0 ) = ptx;
		mpap_Texture->remove_at ( 0 );
		mpap_Texture->push_back ( ptx );
	}

	VEC2 GameGraphicBase::GetCenterOfTexture ( uint32 index )
	{
		VEC2 ret { 0, 0 };
		if ( mpap_Texture->size () < index ) { return ret; }

		P_Tx pTx = mpap_Texture->at ( index );
		ret = s3d_UTL::GetTxCenter ( * pTx );
#if 0
		s3d::Size size = mpap_Texture->at ( index )->size ();
		ret.x = 0.5f * (float)size.x;
		ret.y = 0.5f * (float)size.y;
#endif // 0
		return ret;
	}

	//---------------------------------------------------------------------
	void GameGraphicBase::AddObject ()
	{
		P_Ob pOb = std::make_shared < GameObject > ();
		if ( mpap_Texture->size () > 0 )
		{
			ApplyTxSize_ToOb ( mpap_Texture->at(0), pOb );
		}
		mpap_Object->push_back ( pOb );
	}

	void GameGraphicBase::AddpObject ( P_Ob pOb )
	{
		if ( mpap_Texture->size () > 0 )
		{
			ApplyTxSize_ToOb ( mpap_Texture->at(0), pOb );
		}
		mpap_Object->push_back ( pOb );
	}

	void GameGraphicBase::SetAllRectF ( s3d::RectF rectf )
	{
		for ( P_Ob pob : * mpap_Object )
		{
			pob->SetRectF ( rectf );
		}
	}

	void GameGraphicBase::SetAllRectF_Size ( s3d::Size size )
	{
		s3d::Point pt = size.xy ();

		for ( P_Ob pob : * mpap_Object )
		{
			pob->SetRectF ( s3d::RectF { 0, 0, pt.x, pt.y } );
		}
	}

	void GameGraphicBase::ApplyTxSize_ToOb ( P_Tx ptx, P_Ob pob )
	{
		s3d::Point pt = ptx->size().xy ();
		pob->SetRectF ( s3d::RectF { 0, 0, pt.x, pt.y } );
	}


	void GameGraphicBase::NextIndexTexture ()
	{
		size_t size = mpap_Texture->size ();
		P_Ob pob = mpap_Object->at ( 0 );
		size_t i = pob->GetIndexTexture ();

		i = ( i >= size - 1 ) ? 0: i + 1;
		pob->SetIndexTexture ( (uint32)i );
	}

	void GameGraphicBase::PrevIndexTexture ()
	{
		size_t size = mpap_Texture->size ();
		P_Ob pob = mpap_Object->at ( 0 );
		size_t i = pob->GetIndexTexture ();

		i = ( i == 0 ) ? size - 1 : i - 1;
		pob->SetIndexTexture ( (uint32)i );
	}




	void GameGraphicBase::ShaderDraw ()
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

