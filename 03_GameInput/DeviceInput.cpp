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

	void GamePadInput::Set ( uint32 pad_id, PAD_INPUT_TYPE type, uint32 btn, LEVER_DIR lvr, AXIS_VALUE axis, POV_VALUE pov )
	{
		m_gamepadID = pad_id;
		m_type = type;
		m_buttonID = btn;
		m_lever = lvr;
		m_axis = axis;
		m_pov = pov;
	}


	void GamePadInput::SetBtn ( uint32 pad_id, uint32 btn )
	{
		m_gamepadID = pad_id;
		m_type = PIT_BUTTON;
		m_buttonID = btn;
	}

	void GamePadInput::SetLvr ( uint32 pad_id, LEVER_DIR lvr )
	{
		m_gamepadID = pad_id;
		m_type = PIT_LEVER;
		m_lever = lvr;
	}

	void GamePadInput::SetAxis ( uint32 pad_id, AXIS_VALUE axis )
	{
		m_gamepadID = pad_id;
		m_type = PIT_AXIS;
		m_axis = axis;
	}

	void GamePadInput::SetPov ( uint32 pad_id, POV_VALUE pov )
	{
		m_gamepadID = pad_id;
		m_type = PIT_POINT_OF_VIEW;
		m_pov = pov;
	}


	s3d::String GamePadInput::ToString () const
	{
		PAD_INPUT_TYPE pit = GetInputType ();

		s3d::String str = U"P{}_"_fmt ( GetID () );

		switch ( pit )
		{
		case PIT_AXIS:			str += GetStrAxis ( m_axis ); break;
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

	s3d::String GamePadInput::GetStrAxis ( AXIS_VALUE axis ) const
	{
		s3d::String str = U"AXIS_";

		switch ( axis )
		{
		case AXIS_X_P:	str += U"X:+";		break;
		case AXIS_X_M:	str += U"X:-";		break;
		case AXIS_Y_P:	str += U"Y:+";		break;
		case AXIS_Y_M:	str += U"Y:-";		break;
		case AXIS_Z_P:	str += U"Z:+";		break;
		case AXIS_Z_M:	str += U"Z:-";		break;
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




	void DeviceInput::Save ( s3d::BinaryWriter & bw )
	{
		//デバイスタイプ
		INPUT_DEVICE_TYPE type = GetType ();
		bw.write ( (uint8)type );

		//デバイスタイプが何であれすべてを記録する
		GamePadInput ji = GetPad ();
		bw.write ( (uint8)ji.GetID () );
		bw.write ( (uint8)ji.GetInputType () );
		bw.write ( (uint8)ji.GetButtonID () );
		bw.write ( (uint8)ji.GetLever () );
		bw.write ( (uint8)ji.GetAxis () );
		bw.write ( (uint8)ji.GetPov () );

		bw.write ( (uint8)GetKey() );
	}

	void DeviceInput::Load ( s3d::BinaryReader & br )
	{
		//読込
		INPUT_DEVICE_TYPE idt = (INPUT_DEVICE_TYPE)s3d_UTL::ReadUInt8 ( br );
		uint32 pad_id = s3d_UTL::ReadUInt8 ( br );
		PAD_INPUT_TYPE input_type = (PAD_INPUT_TYPE)s3d_UTL::ReadUInt8 ( br );
		uint32 btn = s3d_UTL::ReadUInt8 ( br );
		LEVER_DIR lvr = (LEVER_DIR)s3d_UTL::ReadUInt8 ( br );
		AXIS_VALUE axis = (AXIS_VALUE)s3d_UTL::ReadUInt8 ( br );
		POV_VALUE pov = (POV_VALUE)s3d_UTL::ReadUInt8 ( br );
		KEY_NAME key = (KEY_NAME)s3d_UTL::ReadUInt8 ( br );

		//一時保存
		GamePadInput gpi;

		//デバイス種類による分岐
		switch ( idt )
		{
		case KEYBOARD:
			SetKeyboard ( key );
			break;

		case GAMEPAD:
			gpi.Set ( pad_id, input_type, btn, lvr, axis, pov );
			SetPad ( gpi );
			break;

		default:break;
		}
	}


}	//namespace GAME

