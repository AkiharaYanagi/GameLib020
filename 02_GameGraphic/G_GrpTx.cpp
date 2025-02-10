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
		m_vibStart = VIB_N;
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
		double x = 0;
		double y = 0;

		//振動
		//初期値０以外になっていたら振動開始
		if ( m_vib != 0 )
		{
			//反転
//			m_vib = ( m_vib == VIB_N ) ? - VIB_N : + VIB_N;


			//ランダム：円周
			x = s3d::Random ( 0.0, m_vib ); 
			y = std::sqrt ( m_vib * m_vib - x * x );

			//象限
			x *= s3d::Random ( 0, 1 ) ? 1 : -1;
			y *= s3d::Random ( 0, 1 ) ? 1 : -1;


			//最初の２フレームは拡大
#if 0
			if ( 1 <= m_vibCount && m_vibCount < 4 )
			{
				x *= 16 / m_vibCount;
				y *= 16 / m_vibCount;
			}
			if ( 4 <= m_vibCount && m_vibCount < 8 )
			{
				x *= 16 / m_vibCount;
				y *= 16 / m_vibCount;
			}
#endif // 0

			double d = 1;

			switch ( m_vibCount )
			{
			case 1: d = 9.0; break;
			case 2: d = 8.5; break;
			case 3: d = 5.0; break;
			case 4: d = 4.5; break;
			case 5: d = 2.0; break;
			case 6: d = 1.8; break;
			case 7: d = 1.4; break;
			case 8: d = 1.2; break;
			}

			x *= d;
			y *= d;

			++ m_vibCount;
		}

		//描画
		m_outTx->draw ( x, y );
	}

	void G_GrpTx::Clear ()
	{
		//何も描画しないときの背景色
		m_outTx->clear ( s3d::Color ( 50, 50, 50, 255 ) );
//		m_outTx->clear ( s3d::Color ( 50, 255, 50, 255 ) );
	}


	void G_GrpTx::VibOn ()
	{
		m_vib = m_vibStart;
		m_vibCount = 1;
	}

	void G_GrpTx::VibOff ()
	{
		m_vib = 0;
		m_vibCount = 0;
	}


	const double G_GrpTx::VIB_N = 5;

}	//namespace GAME

