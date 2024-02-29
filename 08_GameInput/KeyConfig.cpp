//=================================================================================================
//
//	キーコンフィグ
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "KeyConfig.h"
#include "SivInput.h"
#include <fstream>
#include "SivKeyboardDefine.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//------------------------------------------
	//	Static実体
	//------------------------------------------
	//	シングルトン　インスタンス
	KeyConfig::P_KeyConfig		KeyConfig::m_inst;

	KeyConfig::KeyConfig ()
	{
		SetInitial ();
	}

	KeyConfig::~KeyConfig ()
	{
	}
	//------------------------------------------


	//--------------------------------------------------
	//ゲーム利用
	bool KeyConfig::IsKey ( GAME_USE_KEY key ) const
	{
		bool ret = false;
		DeviceInput di = m_deviceInput [ key ];

		INPUT_DEVICE_TYPE type = di.GetType ();
		switch ( type )
		{
		case GAMEPAD: ret = Is_Joy ( di.GetPad () ); break;
		case KEYBOARD: ret = Is_Keyboard ( di.GetKey () ); break;
		}
		return ret;
	}

	bool KeyConfig::OffKey ( GAME_USE_KEY key ) const
	{
		return ! IsKey ( key );
	}

	bool KeyConfig::PushKey ( GAME_USE_KEY key ) const
	{
		bool ret = false;
		DeviceInput di = m_deviceInput [ key ];

		INPUT_DEVICE_TYPE type = di.GetType ();
		switch ( type )
		{
		case GAMEPAD: ret = Push_Joy ( di.GetPad () ); break;
		case KEYBOARD: ret = Push_Keyboard ( di.GetKey () ); break;
		}
		return ret;
	}

	bool KeyConfig::ReleKey ( GAME_USE_KEY key ) const
	{
		bool ret = false;
		DeviceInput di = m_deviceInput [ key ];
		INPUT_DEVICE_TYPE type = di.GetType ();
		switch ( type )
		{
		case GAMEPAD: ret = Rele_Joy ( di.GetPad () ); break;
		case KEYBOARD: ret = Rele_Keyboard ( di.GetKey () ); break;
		}
		return ret;
	}


	//----------------------------------------------------------------------------------
	//初期化
	void KeyConfig::SetInitial ()
	{
		const INPUT_DEVICE_TYPE IDT = INPUT_DEVICE_TYPE::KEYBOARD;

		m_deviceInput [ P1_UP   ].SetKey ( IDT, SIK_UP );
		m_deviceInput [ P1_DOWN ].SetKey ( IDT, SIK_DOWN );
		m_deviceInput [ P1_LEFT ].SetKey ( IDT, SIK_LEFT );
		m_deviceInput [ P1_RIGHT].SetKey ( IDT, SIK_RIGHT );
		m_deviceInput [ P1_BTN0 ].SetKey ( IDT, SIK_Z );
		m_deviceInput [ P1_BTN1 ].SetKey ( IDT, SIK_X );
		m_deviceInput [ P1_BTN2 ].SetKey ( IDT, SIK_C );
		m_deviceInput [ P1_BTN3 ].SetKey ( IDT, SIK_V );
		m_deviceInput [ P1_BTN4 ].SetKey ( IDT, SIK_COMMA );
		m_deviceInput [ P1_BTN5 ].SetKey ( IDT, SIK_PERIOD );
		m_deviceInput [ P1_BTN6 ].SetKey ( IDT, SIK_SLASH );
		m_deviceInput [ P1_BTN7 ].SetKey ( IDT, SIK_BACKSLASH );

		m_deviceInput [ P2_UP   ].SetKey ( IDT, SIK_HOME );
		m_deviceInput [ P2_DOWN ].SetKey ( IDT, SIK_END );
		m_deviceInput [ P2_LEFT ].SetKey ( IDT, SIK_DELETE );
		m_deviceInput [ P2_RIGHT].SetKey ( IDT, SIK_PAGEUP );
		m_deviceInput [ P2_BTN0 ].SetKey ( IDT, SIK_A );
		m_deviceInput [ P2_BTN1 ].SetKey ( IDT, SIK_S );
		m_deviceInput [ P2_BTN2 ].SetKey ( IDT, SIK_D );
		m_deviceInput [ P2_BTN3 ].SetKey ( IDT, SIK_F );
		m_deviceInput [ P2_BTN4 ].SetKey ( IDT, SIK_L );
		m_deviceInput [ P2_BTN5 ].SetKey ( IDT, SIK_SEMICOLON_JIS );
		m_deviceInput [ P2_BTN6 ].SetKey ( IDT, SIK_COLON_JIS );
		m_deviceInput [ P2_BTN7 ].SetKey ( IDT, SIK_RBRACKET );
	}


	//--------------------------------------------------
	//保存
	void KeyConfig::Save ()
	{
		std::fstream fs ( _T ( "keyConfig.dat" ), std::ios::out, std::ios::binary );
			 
		for ( int i = 0; i < GAME_USE_KEY_NUM; ++ i )
		{
			DeviceInput di = m_deviceInput [ i ];
			INPUT_DEVICE_TYPE type = di.GetType ();
			fs.write ( (char*)type, sizeof (INPUT_DEVICE_TYPE) );

			switch ( type )
			{
			case KEYBOARD:
//				fs.write ( (char*)di.GetKey (), sizeof ( DWORD ) );
				fs << di.GetKey();
			break;
	
			case GAMEPAD:
				GamePadInput ji = di.GetPad ();
				DWORD id = ji.GetID ();
//				fs.write ( (char*)id, sizeof ( DWORD ) );
				fs << id;
				PAD_INPUT_TYPE joytype = ji.GetInputType ();
//				fs.write ( (char*)joytype, sizeof ( PAD_INPUT_TYPE ) );
				fs << joytype;
				DWORD btn = ji.GetButtonID ();
//				fs.write ( (char*)btn, sizeof ( DWORD ) );
				fs << btn;
				LEVER_DIR lvr = ji.GetLever ();
//				fs.write ( (char*)lvr, sizeof ( LEVER_DIR ) );
				fs << lvr;
			break;
			}
		}
	}

	//--------------------------------------------------
	//読込
	void KeyConfig::Load ()
	{
		//設定ファイル読込
		std::fstream fs ( _T("keyConfig.dat"), std::ios::in, std::ios::binary );

		//エラーのとき
		if ( fs.fail () )
		{
			//新規ファイルの作成
			SetInitial ();
			Save ();
			return;
		}

		//各キーに対して対応デバイス入力を読込
		for ( int i = 0; i < GAME_USE_KEY_NUM; ++ i )
		{
			DeviceInput di;

			const size_t BUF_SIZE = 4;
			char buf [ BUF_SIZE ];
			fs.read ( buf, BUF_SIZE );
			INPUT_DEVICE_TYPE type = (INPUT_DEVICE_TYPE)*buf;

			DWORD key = 0;
			DWORD joystickID = 0;
			PAD_INPUT_TYPE joytype = PAD_INPUT_TYPE::PIT_AXIS;
			DWORD buttonID = 0;
			LEVER_DIR lvr = LEVER_DIR::LVR_UP;

			GamePadInput ji;
			DWORD bufdw;

			switch ( type )
			{
			case KEYBOARD:
				fs.read ( (char*)&bufdw, BUF_SIZE );
				key = bufdw;
				di.SetKey ( KEYBOARD, key );
				break;

			case GAMEPAD:
				fs.read ( buf, BUF_SIZE );
				joystickID = (DWORD)*buf;
				fs.read ( buf, BUF_SIZE );
				joytype = (PAD_INPUT_TYPE)(int)*buf;
				fs.read ( buf, BUF_SIZE );
				buttonID = (DWORD)*buf;
				fs.read ( buf, BUF_SIZE );
				lvr = (LEVER_DIR)(int)*buf;

				ji.Set ( joystickID, joytype, buttonID, lvr );
				di.SetPad ( ji );
				break;
			}

			m_deviceInput [ i ] = di;	//代入OK
		}
	}



	//----------------------------------------------------------------------------------
	//押された状態かどうか
	bool KeyConfig::Is_Joy ( GamePadInput ji ) const
	{
		DWORD id = ji.GetID ();
		PAD_INPUT_TYPE type = ji.GetInputType ();
		switch ( type )
		{
		case PIT_AXIS: return Is_Axis_Lvr ( id, ji.GetLever () ); break;
		case PIT_POINT_OF_VIEW: return Is_POV_Lvr ( id, ji.GetLever () ); break;
		case PIT_BUTTON: return SVINP->IsJoyButton ( id, ji.GetButtonID () ); break;
		}
		return false;
	}

	bool KeyConfig::Is_Axis_Lvr ( uint32 ID, LEVER_DIR lvr ) const
	{
		bool ret = false;
		switch ( lvr )
		{
		case LEVER_DIR::LVR_UP:		ret = SVINP->IsAxisUp ( ID );		break;
		case LEVER_DIR::LVR_DOWN:	ret = SVINP->IsAxisDown ( ID );		break;
		case LEVER_DIR::LVR_LEFT:	ret = SVINP->IsAxisLeft ( ID );		break;
		case LEVER_DIR::LVR_RIGHT:	ret = SVINP->IsAxisRight ( ID );	break;
		}
		return ret;
	}
	
	bool KeyConfig::Is_POV_Lvr ( uint32 ID, LEVER_DIR lvr ) const
	{
		bool ret = false;
		switch ( lvr )
		{
		case LEVER_DIR::LVR_UP:		ret = SVINP->IsPovUp ( ID );	break;
		case LEVER_DIR::LVR_DOWN:	ret = SVINP->IsPovDown ( ID );	break;
		case LEVER_DIR::LVR_LEFT:	ret = SVINP->IsPovLeft ( ID );	break;
		case LEVER_DIR::LVR_RIGHT:	ret = SVINP->IsPovRight ( ID );	break;
		}
		return ret;
	}

	bool KeyConfig::Is_Keyboard ( uint32 key ) const
	{
//		return DxInput::instance ()->IsOneKeyboard ( key );
		return SivInput::instance ()->IsKey ( key );
	}

	//----------------------------------------------------------------------------------
	//押された瞬間かどうか
	bool KeyConfig::Push_Joy ( GamePadInput ji ) const
	{
		DWORD id = ji.GetID ();
		PAD_INPUT_TYPE type = ji.GetInputType ();
		switch ( type )
		{
		case PIT_AXIS: return Push_Axis_Lvr ( id, ji.GetLever () ); break;
		case PIT_POINT_OF_VIEW: return Push_POV_Lvr ( id, ji.GetLever () ); break;
		case PIT_BUTTON: return DXINP->PushJoyButton ( id, ji.GetButtonID () ); break;
		}
		return false;
	}

	bool KeyConfig::Push_Axis_Lvr ( uint32 ID, LEVER_DIR lvr ) const
	{
		bool ret = false;
		switch ( lvr )
		{
		case LEVER_DIR::LVR_UP:		ret = DXINP->PushAxisUp ( ID );		break;
		case LEVER_DIR::LVR_DOWN:	ret = DXINP->PushAxisDown ( ID );		break;
		case LEVER_DIR::LVR_LEFT:	ret = DXINP->PushAxisLeft ( ID );		break;
		case LEVER_DIR::LVR_RIGHT:	ret = DXINP->PushAxisRight ( ID );	break;
		}
		return ret;
	}

	bool KeyConfig::Push_POV_Lvr ( uint32 ID, LEVER_DIR lvr ) const
	{
		bool ret = false;
		switch ( lvr )
		{
		case LEVER_DIR::LVR_UP:		ret = DXINP->PushPovUp ( ID );	break;
		case LEVER_DIR::LVR_DOWN:	ret = DXINP->PushPovDown ( ID );	break;
		case LEVER_DIR::LVR_LEFT:	ret = DXINP->PushPovLeft ( ID );	break;
		case LEVER_DIR::LVR_RIGHT:	ret = DXINP->PushPovRight ( ID );	break;
		}
		return ret;
	}

	bool KeyConfig::Push_Keyboard ( uint32 key ) const
	{
		return SVINP->PushOneKeyboard ( key );
	}

	//----------------------------------------------------------------------------------


}	//namespace GAME

