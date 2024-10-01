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
	UP_GrpLst	GrpLst::m_inst;

	//コンストラクタ
	GameGraphicList::GameGraphicList ()
	{
		mplp_GrpMain = std::make_unique < LP_GrpCr > ();

		//グラフィック共通テクスチャ
		G_GrpTx::Create ();
		G_GrpTx::Inst()->Load ();
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
		//クリア
		G_GrpTx::Inst()->Clear ();

		//リストのグラフィックを描画
		for ( P_GrpCr p : *mplp_GrpMain ) { p->Draw (); }

		//全体レンダーテクスチャの描画
		G_GrpTx::Inst()->Draw ();
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

