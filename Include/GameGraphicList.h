//=================================================================================================
//
// ◆GameGraphicList
//		グラフィック表示の前後を全体で統一する
//		Z値を用いてソートするGameGpraphicのリストのポインタを保持する
//		オブジェクトの所有を超えて登録するグラフィックのリスト
//		【シングルトン】を用いてグローバルからアクセスする
//		GameSystemが実体を持ち、各位ゲームタスクを登録する
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "GameTask.h"
#include "GameGraphicCore.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	using LP_GrpCr = std::list < P_GrpCr >;
	using UPLP_GrpCr = std::unique_ptr < LP_GrpCr >;
	using UP_RndrTx = std::unique_ptr < s3d::RenderTexture >;


	class GameGraphicList
	{
	//---------------------------------------------------------------------
	//シングルトンパターン
	private:
		using _GrpLst = GameGraphicList;
		using _P_GrpLst = std::unique_ptr < _GrpLst >;
		static _P_GrpLst	m_inst;		//シングルトンインスタンス
		GameGraphicList ();		//private コンストラクタで通常の実体化は禁止
	public:
		~GameGraphicList ();	//デストラクタはstd::unique_ptrのためpublic
		static void Create() { if ( ! m_inst ) { m_inst = _P_GrpLst ( new _GrpLst () ); } }
		static _P_GrpLst & Inst () { return m_inst; }	//インスタンス取得
	//---------------------------------------------------------------------
	
	private:
		UPLP_GrpCr		mplp_GrpMain;		//グラフィック メイン リスト

		//test
		UP_RndrTx		m_renderTx;			//レンダーテクスチャ

	public:

		//@info 動作はタスクリスト側で行う

		//全消去
		void Clear ();

		//描画
		void Draw ();

		//Z値で降順ソートされた位置に挿入
		//描画Z位置(後:1.f ～ 0.0f:前) "GameGraphicConst.h"に Z_BG などで定数が宣言してある
		void InsertByZ ( P_GrpCr pGrpCr );

		//対象タスクを取外
		void Remove ( P_GrpCr p ) { mplp_GrpMain->remove ( p ); }

		//個数
		size_t GetNumList () const { return mplp_GrpMain->size (); }


		//レンダーテクスチャ移譲
		UP_RndrTx Handover_RndrTx () { return std::move ( m_renderTx ); }
		//レンダーテクスチャ返還
		void Refund_RndrTx ( UP_RndrTx&& up ) { m_renderTx = std::move ( up ); }


	private:
		bool m_startMv { F };
		std::unique_ptr < s3d::VideoTexture > mp_vtx;

	public:
		void SetupVtx ( std::unique_ptr < s3d::VideoTexture > p_vtx )
		{
			mp_vtx = std::move ( p_vtx );
		}
		void StartVtx () { m_startMv = T; }
	};

	using GrpLst = GameGraphicList;
	using UP_GrpLst = std::unique_ptr < GrpLst >;


#define		GRPLST_CREATE	GrpLst::Create
#define		GRPLST_DRAW		GrpLst::Inst()->Draw
#define		GRPLST_INSERT	GrpLst::Inst()->InsertByZ
#define		GRPLST_REMOVE	GrpLst::Inst()->Remove
#define		GRPLST_CLEAR	GrpLst::Inst()->Clear


}	//namespace GAME


