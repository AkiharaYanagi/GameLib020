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

	s3d::String GamePadInput::ToString () const
	{
		PAD_INPUT_TYPE pit = GetInputType ();

		s3d::String str = U"P{}_"_fmt ( GetID () );

		switch ( pit )
		{
		case PIT_AXIS:			str += U"AXIS_";		break;
		case PIT_POINT_OF_VIEW:	str += U"POV_";		break;

		case PIT_BUTTON:
			str += U"BTN_";
			str += U"{}"_fmt ( GetButtonID() );
			break;

		case PIT_NO_DATA:		str += U"NO_DATA";	break;
		default:break;
		}
		return str;
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

	void DeviceInput::SetKeyboard ( KEY_NAME key )
	{
		m_dvc_type = KEYBOARD;
		m_keyboardInput = key;
	}

	void DeviceInput::SetPad ( GamePadInput gamePadInput )
	{
		m_dvc_type = INPUT_DEVICE_TYPE::GAMEPAD;
		m_gamepadnput = gamePadInput;
	}


	s3d::String DeviceInput::ToString ()
	{
		INPUT_DEVICE_TYPE idt = GetType ();

		s3d::String str;
		switch ( idt )
		{
		case KEYBOARD:	str = U"Key_{}"_fmt( GetKeyName () );	break;
		case GAMEPAD:	str = m_gamepadnput.ToString ();		break;
		case MOUSE:		str = Unicode::Widen ( STR(MOUSE) );	break;
		default:break;
		}

		return str;
	}



}	//namespace GAME

