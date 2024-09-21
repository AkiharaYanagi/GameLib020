//=================================================================================================
//
// ◆ ShaderList
//		シェーダを用いたグラフィックリスト
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "GameTask.h"
#include "GameGraphic.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	using RndrTx = s3d::RenderTexture;
	using UP_RndrTx = std::unique_ptr < RndrTx >;



	class ShaderList
	{
	//---------------------------------------------------------------------
	//シングルトンパターン
	private:
		using _SdrLst = ShaderList;
		using UP_SdrLst = std::unique_ptr < _SdrLst >;
		static UP_SdrLst	m_inst;		//シングルトンインスタンス
		ShaderList ();		//private コンストラクタで通常の実体化は禁止
	public:
		~ShaderList ();		//デストラクタはstd::unique_ptrのためpublic
		static void Create() { if ( ! m_inst ) { m_inst = UP_SdrLst ( new _SdrLst () ); } }
		static UP_SdrLst & Inst () { return m_inst; }	//インスタンス取得
	//---------------------------------------------------------------------
	
	private:
		UPAP_Grp		mpap_GrpMain;		//グラフィック メイン リスト

		//ピクセルシェーダ
		PixelShader		m_ps;
		PixelShader		m_ps_screen;

		s3d::Texture	m_emoji;
		s3d::Texture	m_windmill;

		RndrTx			m_rndrTx { 1280, 960 };		//位置合わせ用レンダーテクスチャ

	public:

		void Load ();
		void Draw ();
		void Clear ();

		void InsertByZ ( P_Grp	pGrp );

		//対象タスクを取外
		void Remove ( P_Grp p ) { mpap_GrpMain->remove ( p ); }
	};

	using SdrLst = ShaderList;
	using UP_SrdLst = std::unique_ptr < SdrLst >;


#define		SDRLST_CREATE	SdrLst::Create
#define		SDRLST_LOAD		SdrLst::Inst()->Load
#define		SDRLST_DRAW		SdrLst::Inst()->Draw
#define		SDRLST_INSERT	SdrLst::Inst()->InsertByZ
#define		SDRLST_REMOVE	SdrLst::Inst()->Remove
#define		SDRLST_CLEAR	SdrLst::Inst()->Clear


}	//namespace GAME


