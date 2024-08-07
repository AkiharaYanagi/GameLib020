//=================================================================================================
//
//	ゲームグラフィック コア
//		・ゲームグラフィック(スプライト描画)と、
//		・ゲームプリミティブ(頂点のみ描画)も含んだグラフィック全般
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "GameTask.h"
#include "GameGraphicConst.h"
#include "GameObject.h"
#include "Fade.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//■=======================================================================
	// ゲームグラフィック　コア
	//■=======================================================================
	class GameGraphicCore : public GameTask
	{
	protected:
		bool		m_valid { T };		//有効フラグ
		float		m_z { Z_CH };		//疑似Z値（描画の前後）

	private:
		Fade		m_fade;			//フェード

	public:
		GameGraphicCore ();
		GameGraphicCore ( const GameGraphicCore & rhs ) = delete;
		~GameGraphicCore () {}

		//基本動作
#if 0
		virtual void TxLoad () {}		//読込
		virtual void TxRele () {}		//解放
		virtual void TxReset () {}		//再設定
#endif // 0

		virtual void Draw () {}			//描画


		//毎フレーム事前動作
		void PreMove ();

		//有効・無効
		void SetValid ( bool b ) { m_valid = b; }
		bool GetValid () const { return m_valid; }

		//Z値
		void SetZ ( float z ) { m_z = z; }
		float GetZ () const { return m_z; }

		//色
		void SetColor ( _CLR clr ) { m_fade.SetColor ( clr ); }
		_CLR GetColor () const { return m_fade.GetColor (); }

		//フェード
		void SetFade ( UINT time, _CLR clr_start, _CLR clr_end )
		{
			m_valid = true;
			m_fade.SetFade ( time, clr_start, clr_end ); 
		}
		void SetFadeIn ( UINT time )
		{
			m_valid = true;
			m_fade.SetFade ( time, 0x00ffffff, 0xffffffff );
		}
		void SetFadeIn ( UINT time, _CLR endColor )
		{
			m_valid = true;
			_CLR startColor = _CLR ( endColor.r, endColor.g, endColor.b, 0 );
			m_fade.SetFade ( time, startColor, endColor );
		}
		void SetFadeOut ( UINT time )
		{
			m_valid = true;
			m_fade.SetFade ( time, 0xffffffff, 0x00ffffff );
		}
		void SetFadeOut ( UINT time, _CLR startColor )
		{
			m_valid = true;
			_CLR endColor = _CLR ( startColor.r, startColor.g, startColor.b, 0 );
			m_fade.SetFade ( time, startColor, endColor );
		}
		void EndFade ( _CLR clr ) { m_fade.End ( clr ); }

		UINT GetFadeTimer () const { return m_fade.GetTimer (); }
	};


	//型指定
	using	GrpCr = GameGraphicCore;
	using	P_GrpCr = std::shared_ptr < GrpCr >;

	using	LP_GrpCr = std::list < P_GrpCr >;
	using	PLP_GrpCr = std::shared_ptr < LP_GrpCr >;
	using	UPLP_GrpCr = std::unique_ptr < LP_GrpCr >;


}	//namespace GAME

