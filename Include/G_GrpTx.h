﻿//=================================================================================================
//
// グローバル　テクスチャ
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイル　インクルード
//-------------------------------------------------------------------------------------------------
#include "Define_Siv3D.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class G_GrpTx;
	using P_G_GrpTx = std::unique_ptr < G_GrpTx >;
	using UP_RndrTx = std::unique_ptr < s3d::RenderTexture >;
	using P_PxShd = std::shared_ptr < s3d::PixelShader >;


	class G_GrpTx
	{
	//--------------------------------------------------
	//シングルトンパターン
	private:
		static P_G_GrpTx	m_inst;
		G_GrpTx ();
		G_GrpTx ( const G_GrpTx & rhs ) = delete;
	public:
		~G_GrpTx ();
		static void Create() { if ( ! m_inst ) { m_inst = P_G_GrpTx ( new G_GrpTx () ); } }
		static P_G_GrpTx & Inst() { return m_inst; }
	//--------------------------------------------------

	private:
		UP_RndrTx		m_renderTx;		//メイン レンダーテクスチャ
		UP_RndrTx		m_psTx;			//ピクセルシェーダ用 レンダーテクスチャ
		P_PxShd			m_ps_screen;	//ピクセルシェーダ

	public:

		void Load ();
		void Draw ();


		//レンダーテクスチャ移譲
		UP_RndrTx Handover_RndrTx () { return std::move ( m_renderTx ); }
		//レンダーテクスチャ返還
		void Refund_RndrTx ( UP_RndrTx&& up ) { m_renderTx = std::move ( up ); }

		//レンダーテクスチャ移譲
		UP_RndrTx Handover_PSTx () { return std::move ( m_psTx ); }
		//レンダーテクスチャ返還
		void Refund_PSTx ( UP_RndrTx&& up ) { m_psTx = std::move ( up ); }

		//ピクセルシェーダ
		P_PxShd GetpPxShd () const { return m_ps_screen; }
	};



}	//namespace GAME
