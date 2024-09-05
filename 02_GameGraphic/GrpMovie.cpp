//=================================================================================================
//
// ゲームグラフィック　クラス　
//		ゲームで用いる画像を扱うオブジェクトを定義する。
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイル　インクルード
//-------------------------------------------------------------------------------------------------
#include "GrpMovie.h"
#include "G_GrpTx.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	GrpMovie::GrpMovie ()
	{
	}

	GrpMovie::~GrpMovie ()
	{
	}

	void GrpMovie::Load ()
	{
		s3d::Loop loop = m_loop ? s3d::Loop::Yes : s3d::Loop::No;
		mp_vtx = std::make_unique < s3d::VideoTexture > ( m_filename, loop );

		GameGraphicBase::Load ();
	}

	void GrpMovie::Draw ()
	{
		//稼働フラグ
		if ( ! m_valid ) { return; }

		//開始フラグ
		if ( ! m_startMv ) { return; }

		//unique_ptrを取得
		UP_RndrTx upOutTx = G_GrpTx::Inst()->Handover_OutTx ();

		{
			const s3d::ScopedRenderTarget2D target ( * upOutTx );
			_Draw ();
		}

		//unique_ptrを返す
		G_GrpTx::Inst()->Refund_OutTx ( std::move ( upOutTx ) );
	}

	void GrpMovie::_Draw ()
	{
		//描画
		int32 w = mp_vtx->width ();
		int32 h = mp_vtx->height ();
		double dx = ( (double)GAME_WINDOW_WIDTH - w ) * 0.5;
		double dy = ( (double)GAME_WINDOW_HEIGHT - h ) * 0.5;
		mp_vtx->advance ();
		mp_vtx->draw ( dx, dy );

		//終了
		if ( m_loop )
		{
			double length = mp_vtx->lengthSec ();
			double sec = mp_vtx->posSec ();
			if ( sec >= length )
			{
				m_startMv = false;
				mp_vtx->reset ();
			}
		}

	}

	void GrpMovie::SetMovName ( s3d::String filename )
	{
		m_filename.assign ( filename );
	}



}	//namespace GAME

