//=================================================================================================
//
//	Sivインプット
//		入力記録を毎フレームで記録し、押されている状態かどうかを取得する
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Define.h"
#include "SivKeyboard.h"
#include "SivGamePad.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class SivInput
	{
	//---------------------------------------------------------------------
	//シングルトン　パターン
	private:
		using P_SivInput = std::unique_ptr < SivInput >;	//ポインタ型定義
		static P_SivInput	m_inst;		//シングルトンインスタンス(実体は.cppで定義)
		SivInput ();		//private コンストラクタで通常の実体化は禁止
	public:
		~SivInput (){}		//デストラクタはstd::unique_ptrのためpublic
		static void Create () { if ( ! m_inst ) { m_inst = P_SivInput ( new SivInput () ); } }
		static P_SivInput & Inst () { return m_inst; }
	//---------------------------------------------------------------------


		//キーボード
		SivKeyboard		m_keyboard;

		//ゲームパッド
		SivGamePad		m_gamepad;


	public:

		//Keyboard
		bool Is_Keyboard ( KEY_NAME k );
		bool Push_Keyboard ( KEY_NAME k );
		bool Rele_Keyboard ( KEY_NAME k );


	};

#define	SVINP	SivInput::Inst();

}
