//=================================================================================================
//
//	デバイスインプット
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "DeviceInput.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//============================================================
	//ゲームパッドの入力定義
	GamePadInput::GamePadInput ()
	{
	}

	void GamePadInput::Set ( uint32 pad_id, PAD_INPUT_TYPE type, uint32 btn_id, LEVER_DIR lvr )
	{
		m_gamepadID = pad_id;
		m_type = type;
		m_buttonID = btn_id;
		m_lever = lvr;
	}

	//============================================================


	DeviceInput::DeviceInput ()
	{
	}

	DeviceInput::DeviceInput ( const DeviceInput & rhs )
	{
		m_dvc_type = rhs.m_dvc_type;
		m_keyboardInput = rhs.m_keyboardInput;
		m_gamepadnput = rhs.m_gamepadnput;
	}

	DeviceInput::~DeviceInput ()
	{
	}

	void DeviceInput::SetKey ( INPUT_DEVICE_TYPE dvc_type, KEY_NAME key )
	{
		m_dvc_type = dvc_type;
		m_keyboardInput = key;
	}

	void DeviceInput::SetPad ( GamePadInput gamePadInput )
	{
		m_dvc_type = INPUT_DEVICE_TYPE::GAMEPAD;
		m_gamepadnput = gamePadInput;
	}



}	//namespace GAME

