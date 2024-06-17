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
	GamePadInput::GamePadInput ()
		: m_gamepadID ( 0 ), m_type ( PAD_INPUT_TYPE::PIT_AXIS )
		, m_buttonID ( 0 ), m_lever ( LEVER_DIR::LVR_UP )
	{
	}

	void GamePadInput::Set ( uint32 joy_id, PAD_INPUT_TYPE type, uint32 btn_id, LEVER_DIR lvr )
	{
		m_gamepadID = joy_id;
		m_type = type;
		m_buttonID = btn_id;
		m_lever = lvr;
	}


	//============================================================
	DeviceInput::DeviceInput ()
		: m_dvc_type ( INPUT_DEVICE_TYPE::NODEVICE ), m_keyboardInput ( 0 )
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

	void DeviceInput::SetKey ( INPUT_DEVICE_TYPE dvc_type, DWORD key )
	{
		m_dvc_type = dvc_type;
		m_keyboardInput = key;
	}

	void DeviceInput::SetPad ( GamePadInput ji )
	{
		m_dvc_type = INPUT_DEVICE_TYPE::GAMEPAD;
		m_gamepadnput = ji;
	}



}	//namespace GAME

