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
		Array < bool > ary { F, F };
	}

	SivKeyboard::~SivKeyboard()
	{
	}


	//指定したキーが押されているか
	bool SivKeyboard::IsKey( int nKey )
	{
#if 0
		//デバイスの直接データを取得する
		BYTE byKeyState[DI_KEYBOARD];
		HRESULT hr = m_lpDIKeyboard->GetDeviceState ( DI_KEYBOARD, byKeyState );

		if ( SUCCEEDED ( hr ) )
		{
			//キーが押されているか調べる
			if ( m_keyState[nKey] & 0x80 )	//key番目のキーが押されているかどうか
			{
				return true;
			}
		}
		else if ( hr == DIERR_INPUTLOST )		//アクセス権を失った場合
		{
			m_lpDIKeyboard->Acquire ();		//アクセス権の再取得
		}

		return false;	//対象のキーが押された状態でないときはfalseを返す
#endif // 0

		return ma_keyState [ nKey ];
	}


	//指定したキーが押された瞬間か
	bool SivKeyboard::PushKey( int nKey )
	{
#if 0
		if ( m_lpDIKeyboard == nullptr ) return false;	//キーボードのない状態はfalseを返す

		//デバイスの直接データを取得する
		BYTE byKeyState[DI_KEYBOARD];
		HRESULT hr = m_lpDIKeyboard->GetDeviceState ( DI_KEYBOARD, byKeyState );

		if ( SUCCEEDED ( hr ) )
		{
			//キーが押されているか調べる
			if ( (m_keyState[nKey] & 0x80) && ( ! (m_preKeyState[nKey] & 0x80) ) )	//key番目のキーが押された瞬間かどうか
			{
				return true;
			}
		}
		else if ( hr == DIERR_INPUTLOST )		//アクセス権を失った場合
		{
			m_lpDIKeyboard->Acquire ();		//アクセス権の再取得
		}

		return false;	//対象のキーが押された状態でないときはfalseを返す
#endif // 0

		return ma_keyState [ nKey ] && ! ma_preKeyState [ nKey ];
	}


	//指定したキーが離された瞬間か
	bool SivKeyboard::ReleaseKey( int nKey )
	{
#if 0
		if ( m_lpDIKeyboard == nullptr ) return false;	//キーボードのない状態はfalseを返す

		//デバイスの直接データを取得する
		BYTE byKeyState[DI_KEYBOARD];
		HRESULT hr = m_lpDIKeyboard->GetDeviceState ( DI_KEYBOARD, byKeyState );

		if ( SUCCEEDED ( hr ) )
		{
			//キーが押されているか調べる
			if ( ( ! (m_keyState[nKey] & 0x80) ) && (m_preKeyState[nKey] & 0x80) )	//key番目のキーが押された瞬間かどうか
			{
				return true;
			}
		}
		else if ( hr == DIERR_INPUTLOST )		//アクセス権を失った場合
		{
			m_lpDIKeyboard->Acquire ();		//アクセス権の再取得
		}

		return false;	//対象のキーが押された状態でないときはfalseを返す
#endif // 0

		return ! ma_keyState [ nKey ] && ma_preKeyState [ nKey ];
	}


	//--------------------------------------------------------------------------
	//ゲーム利用
	//--------------------------------------------------------------------------
	void SivKeyboard::Update( Array < Input > & keys )
	{
#if 0
		if ( m_lpDIKeyboard )
		{
			for ( DWORD dw = 0; dw < DI_KEYBOARD; dw++ )
			{
				m_preKeyState[dw] = m_keyState[dw];	//以前の状態の記録
			}

			HRESULT hr = m_lpDIKeyboard->GetDeviceState ( DI_KEYBOARD, m_keyState );
			if ( hr == DIERR_INPUTLOST )	//アクセス権を失った場合
			{
				m_lpDIKeyboard->Acquire();	//再取得
			}
		}
#endif // 0

		//以前の状態を記録
		uint32 index = 0; 
		for ( bool b : ma_keyState )
		{
			ma_preKeyState [ index ++ ] = b;
		}


		//キー状態の取得

		//メインオブジェクトから取得
//		Array < Input > keys = Keyboard::GetAllInputs ();


		Array < Input >::iterator it = keys.begin ();

		//先頭から検索してコードが該当する箇所をTとする
		for ( uint8 i = 0; i < SIV_KEYBOARD_NUM; ++ i )
		{
			if ( it->code() == i )
			{
				ma_keyState [ i ] = T;
				++ it;
			}
			else
			{
				ma_keyState [ i ] = F;
			}
		}
	}


}	//namespace GAME


