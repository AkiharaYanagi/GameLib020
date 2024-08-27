//=================================================================================================
//
// GameGraphicList ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "GameGraphicList.h"
#include "GameLibConst.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//------------------------------------------
	//	Static実体
	//------------------------------------------
	// シングルトンオブジェクト
	UP_GrpLst	GrpLst::m_inst;

	//コンストラクタ
	GameGraphicList::GameGraphicList ()
	{
		mplp_GrpMain = std::make_unique < LP_GrpCr > ();

		m_renderTx = std::make_unique < s3d::RenderTexture > ( 1280, 960 );
	}

	GameGraphicList::~GameGraphicList ()
	{
	}

	void GameGraphicList::Clear ()
	{
		mplp_GrpMain->clear ();
	}

	void GameGraphicList::Draw ()
	{
		//リストのグラフィックを描画
		{
			const s3d::ScopedRenderTarget2D target ( * m_renderTx );

			for ( P_GrpCr p : *mplp_GrpMain ) { p->Draw (); }
		}

//		m_renderTx->draw ( 200, 100 );


#if 0
		for ( P_GrpCr p : *mplp_GrpMain ) { p->Draw (); }
#endif // 0



		//動画
		if ( m_startMv )
		{
			int32 w = mp_vtx->width ();
			int32 h = mp_vtx->height ();
			double dx = ( (double)GAME_WINDOW_WIDTH - w ) * 0.5;
			double dy = ( (double)GAME_WINDOW_HEIGHT - h ) * 0.5;
			mp_vtx->advance ();
			mp_vtx->draw ( dx, dy );

			//終了
			double length = mp_vtx->lengthSec ();
			double sec = mp_vtx->posSec ();
			if ( sec >= length )
			{
				m_startMv = false;
				mp_vtx->reset ();
			}
		}

	}

	//Z値で降順ソートされた位置に挿入
	void GameGraphicList::InsertByZ ( P_GrpCr pGrpCr )
	{
		//既存が１つも無いとき、通常の追加
		if ( 0 == mplp_GrpMain->size () ) { mplp_GrpMain->push_back ( pGrpCr ); return; }

		//Z値をチェックして指定位置に挿入
		float z = pGrpCr->GetZ ();
		for ( LP_GrpCr::iterator it = mplp_GrpMain->begin (); mplp_GrpMain->end () != it; ++ it )
		{
			float pz = ( *it )->GetZ ();
			if ( z > pz )
			{
				mplp_GrpMain->insert ( it, pGrpCr );
				return;
			}
		}

		//すべての値より小さい場合、末尾に追加
		mplp_GrpMain->push_back ( pGrpCr );
		return;
	}


}	//namespace GAME

