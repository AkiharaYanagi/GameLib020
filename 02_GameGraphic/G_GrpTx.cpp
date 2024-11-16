//=================================================================================================
//
// グローバル　テクスチャ
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイル　インクルード
//-------------------------------------------------------------------------------------------------
#include "G_GrpTx.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//--------------------------------------------------
	//シングルトンパターン	static実体
	P_G_GrpTx	G_GrpTx::m_inst = nullptr;
	//--------------------------------------------------

	//=======================================================================
	//	Rect 
	//=======================================================================
	G_GrpTx::G_GrpTx ()
	{
	}

	G_GrpTx::~G_GrpTx ()
	{
	}

	void G_GrpTx::Load ()
	{
		m_renderTx = std::make_unique < s3d::RenderTexture > ( 1280, 960 );
		m_psTx = std::make_unique < s3d::RenderTexture > ( 1280, 960 );
//		m_ps_screen = std::make_shared < s3d::PixelShader > ( HLSL { Resource(U"ScreenBlend.hlsl"), U"PS" } );
//		m_ps_screen = std::make_shared < s3d::PixelShader > ( HLSL { U"ScreenBlend.hlsl", U"PS" } );
		m_ps_screen = std::make_shared < s3d::PixelShader > ( HLSL { U"ScreenBlend.ps" } );
		m_outTx = std::make_unique < s3d::RenderTexture > ( 1280, 960 );
	}

	void G_GrpTx::Draw ()
	{
		//振動
		//初期値０以外になっていたら振動開始
		if ( m_vib != 0 )
		{
			m_vib = ( m_vib == VIB_N ) ? - VIB_N : + VIB_N;
		}

		//m_outTx->draw ( 0, 0 );
		//m_outTx->draw ( m_vib, 100 );
		m_outTx->draw ( m_vib, 0 );
	}

	void G_GrpTx::Clear ()
	{
		//何も描画しないときの背景色
		m_outTx->clear ( s3d::Color ( 50, 50, 50, 255 ) );
//		m_outTx->clear ( s3d::Color ( 50, 255, 50, 255 ) );
	}


	void G_GrpTx::VibOn ()
	{
		m_vib = VIB_N;
	}

	void G_GrpTx::VibOff ()
	{
		m_vib = 0;
	}


	const int32 G_GrpTx::VIB_N = 5;

}	//namespace GAME

