//=================================================================================================
//
// Siv キーボード の実装
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "SivKeyboard.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	SivKeyboard::SivKeyboard()
	{
		ma_keyState.resize ( SIV_KEYBOARD_NUM );
		ma_preKeyState.resize ( SIV_KEYBOARD_NUM );
	}

	SivKeyboard::~SivKeyboard()
	{
	}

	//--------------------------------------------------------------------------
	//ゲーム利用
	//--------------------------------------------------------------------------
	void SivKeyboard::Update()
	{
		//キーボード状態を取得
		const Array<Input> & keys = s3d::Keyboard::GetAllInputs();

		//以前の状態を記録
		uint32 index = 0; 
		for ( bool b : ma_keyState )
		{
			ma_preKeyState [ index ] = b;
			ma_keyState [ index ] = F;
			++ index;
		}

		//キー状態の取得
		Array < Input >::const_iterator it = keys.begin ();
		Array < Input >::const_iterator end = keys.end ();

		//先頭から検索してコードが該当する箇所をTとする
		for ( ; it != end; ++ it )
		{
			ma_keyState [ it->code() ] = T;
		}
	}



	//指定したキーが押されているか
	bool SivKeyboard::IsKey( KEY_NAME nKey )
	{
		return ma_keyState [ nKey ];
	}


	//指定したキーが押された瞬間か
	bool SivKeyboard::PushKey ( KEY_NAME nKey )
	{
		return ma_keyState [ nKey ] && ! ma_preKeyState [ nKey ];
	}


	//指定したキーが離された瞬間か
	bool SivKeyboard::ReleaseKey ( KEY_NAME nKey )
	{
		return ! ma_keyState [ nKey ] && ma_preKeyState [ nKey ];
	}


	//キー設定用
	//いずれかの押された瞬間のキーを返す
	KEY_NAME SivKeyboard::WhichInput ()
	{
		for ( uint8 nKey = 0; nKey < SIV_KEYBOARD_NUM; ++ nKey )
		{
			if ( ma_keyState [ nKey ] && ! ma_preKeyState [ nKey ] )
			{
				return (KEY_NAME)nKey;
			}
		}

		return SIK_NODATA;
	}


}	//namespace GAME


