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

		//オブジェクトの数だけ描画
		for ( P_Ob pob : *mpap_Object )
		{
			if ( ! pob->GetValid () ) { continue; }

			//拡大縮小
			VEC2 v = pob->GetScaling();
			s3d::Vec2 vScaling { v.x, v.y };

			//描画テクスチャの指定
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

			//拡縮中心位置
			//原点に戻してから指定位置にする
			VEC2 cnt = pob->GetScalingCenter ();
			x += cnt.x - (cnt.x * v.x);
			y += cnt.y - (cnt.y * v.y);

			(*ptx)( rectf ).scaled ( vScaling ).draw ( x, y );
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
//		ARCHIVE_FILE_USE file = ACVR()->GetFilePointer ( (LPCTSTR)filename.c_str() );
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

	//---------------------------------------------------------------------
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


#if 0
	float GameGraphicBase::GetZ () const
	{
		if ( mpap_Object->size() > 0 )
		{
			return mpap_Object->at ( 0 )->GetZ ();
		}
		return 0;
	}

	void GameGraphicBase::SetZ ( float z )
	{
		if ( mpap_Object->size() > 0 )
		{
			mpap_Object->at ( 0 )->SetZ ( z );
		}
	}
#endif // 0


}	//namespace GAME

