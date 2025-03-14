//=================================================================================================
//
// Rect　ヘッダファイル
//		矩形共通処理を定義
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Define.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//-------------------------------------------------------------------------------------------------
	// RECT型 宣言
	//-------------------------------------------------------------------------------------------------
	using V_RECT = std::vector < RECT >;
	using PV_RECT = std::shared_ptr < V_RECT >;

	using P_RECT = std::shared_ptr < RECT >;
	using VP_RECT = std::vector < P_RECT >;
	using PVP_RECT = std::shared_ptr < VP_RECT >;

	//-------------------------------------------------------------------------------------------------
	//	グローバル関数プロトタイプ宣言
	//-------------------------------------------------------------------------------------------------

	//ゼロで初期化する
	void ZeroRect ( RECT & rect );

	//空枠(すべて0)かどうか
	bool IsZeroRect ( const RECT & rect );

	//矩形の値を設定する
	void SetRect ( RECT & rect, LONG left, LONG top, LONG right, LONG bottom );

	//矩形をrhsからlhsにコピーする
	void CopyRect ( RECT & lhs, const RECT & rhs );

	//枠配列の値をゼロ初期化する(配列サイズは固定)
	void ZeroVecRect ( PV_RECT pvRect );

	//-------------------------------------
	//重なり判定

	//点と矩形の重なり判定
	bool OverlapPoint ( const VEC2 & pt, const RECT & rect );

	//矩形２つで重なり判定
	bool OverlapRect ( const RECT & rect1, const RECT & rect2 );

	//枠配列に行う重なり判定
	bool OverlapAryRect ( PV_RECT pvRect1, PV_RECT pvRect2 );

	//枠重なり部分の中心位置を取得
	VEC2 GetOverlayCenterRects ( const RECT & rect1, const RECT & rect2 );

	//枠配列に行う重なり判定(重なりの中心付き)
	bool OverlapAryRect_Center ( PV_RECT pvRect1, PV_RECT pvRect2, VEC2 & center );	//中心も求める


}	//namespace GAME


