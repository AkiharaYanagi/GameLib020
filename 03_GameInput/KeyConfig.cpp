//=================================================================================================
//
//	キーコンフィグ
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "KeyConfig.h"
#include <fstream>
#include "SivKeyboardDefine.h"
#include "SivInput.h"


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
	//ゲーム利用 (1p/2p指定)
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
	//ゲーム利用 (1p/2p共通)
	bool KeyConfig::IsKey_12 ( PLAYER_INPUT key ) const
	{
		GAME_USE_KEY key1p = InputFromPlayer ( PLAYER_ID_1, key );
		GAME_USE_KEY key2p = InputFromPlayer ( PLAYER_ID_2, key );
		return IsKey ( key1p ) || IsKey ( key2p );
	}

	bool KeyConfig::OffKey_12 ( PLAYER_INPUT key ) const
	{
		GAME_USE_KEY key1p = InputFromPlayer ( PLAYER_ID_1, key );
		GAME_USE_KEY key2p = InputFromPlayer ( PLAYER_ID_2, key );
		return OffKey ( key1p ) || OffKey ( key2p );
	}

	bool KeyConfig::PushKey_12 ( PLAYER_INPUT key ) const
	{
		GAME_USE_KEY key1p = InputFromPlayer ( PLAYER_ID_1, key );
		GAME_USE_KEY key2p = InputFromPlayer ( PLAYER_ID_2, key );
		return PushKey ( key1p ) || PushKey ( key2p );
	}

	bool KeyConfig::ReleKey_12 ( PLAYER_INPUT key ) const
	{
		GAME_USE_KEY key1p = InputFromPlayer ( PLAYER_ID_1, key );
		GAME_USE_KEY key2p = InputFromPlayer ( PLAYER_ID_2, key );
		return ReleKey ( key1p ) || ReleKey ( key2p );
	}


	//----------------------------------------------------------------------------------
	//ゲーム利用 (引数で1p/2pを指定)
	bool KeyConfig::IsKey_PL ( PLAYER_ID id, PLAYER_INPUT key ) const
	{
		GAME_USE_KEY use_key = InputFromPlayer ( id, key );
		return IsKey ( use_key );
	}

	bool KeyConfig::OffKey_PL ( PLAYER_ID id, PLAYER_INPUT key ) const
	{
		GAME_USE_KEY use_key = InputFromPlayer ( id, key );
		return OffKey ( use_key );
	}

	bool KeyConfig::PushKey_PL ( PLAYER_ID id, PLAYER_INPUT key ) const
	{
		GAME_USE_KEY use_key = InputFromPlayer ( id, key );
		return PushKey ( use_key );
	}

	bool KeyConfig::ReleKey_PL ( PLAYER_ID id, PLAYER_INPUT key ) const
	{
		GAME_USE_KEY use_key = InputFromPlayer ( id, key );
		return ReleKey ( use_key );
	}


	//----------------------------------------------------------------------------------
	//初期化
	void KeyConfig::SetInitial ()
	{
		m_deviceInput [ P1_UP   ].SetKeyboard ( SIK_UP );
		m_deviceInput [ P1_DOWN ].SetKeyboard ( SIK_DOWN );
		m_deviceInput [ P1_LEFT ].SetKeyboard ( SIK_LEFT );
		m_deviceInput [ P1_RIGHT].SetKeyboard ( SIK_RIGHT );
		m_deviceInput [ P1_BTN0 ].SetKeyboard ( SIK_Z );
		m_deviceInput [ P1_BTN1 ].SetKeyboard ( SIK_X );
		m_deviceInput [ P1_BTN2 ].SetKeyboard ( SIK_C );
		m_deviceInput [ P1_BTN3 ].SetKeyboard ( SIK_V );
		m_deviceInput [ P1_BTN4 ].SetKeyboard ( SIK_B );
		m_deviceInput [ P1_BTN5 ].SetKeyboard ( SIK_N );
		m_deviceInput [ P1_BTN6 ].SetKeyboard ( SIK_M );
		m_deviceInput [ P1_BTN7 ].SetKeyboard ( SIK_COMMA );

		m_deviceInput [ P2_UP   ].SetKeyboard ( SIK_HOME );
		m_deviceInput [ P2_DOWN ].SetKeyboard ( SIK_END );
		m_deviceInput [ P2_LEFT ].SetKeyboard ( SIK_DELETE );
		m_deviceInput [ P2_RIGHT].SetKeyboard ( SIK_PAGEDN );
		m_deviceInput [ P2_BTN0 ].SetKeyboard ( SIK_A );
		m_deviceInput [ P2_BTN1 ].SetKeyboard ( SIK_S );
		m_deviceInput [ P2_BTN2 ].SetKeyboard ( SIK_D );
		m_deviceInput [ P2_BTN3 ].SetKeyboard ( SIK_F );
		m_deviceInput [ P2_BTN4 ].SetKeyboard ( SIK_G );
		m_deviceInput [ P2_BTN5 ].SetKeyboard ( SIK_H );
		m_deviceInput [ P2_BTN6 ].SetKeyboard ( SIK_J );
		m_deviceInput [ P2_BTN7 ].SetKeyboard ( SIK_K );
	}


	//--------------------------------------------------
	//保存
	void KeyConfig::Save ()
	{
//		std::fstream fs ( _T ( "keyConfig.dat" ), std::ios::out, std::ios::binary );
		s3d::BinaryWriter bw { U"keyConfig.dat" };
			 
		for ( int i = 0; i < GAME_USE_KEY_NUM; ++ i )
		{
#if 0

			DeviceInput di = m_deviceInput [ i ];
			INPUT_DEVICE_TYPE type = di.GetType ();
			fs.write ( (char*)type, sizeof (INPUT_DEVICE_TYPE) );

			switch ( type )
			{
			case KEYBOARD:
				fs << (uint8)di.GetKey();
			break;
	
			case GAMEPAD:
				GamePadInput ji = di.GetPad ();
				fs << (uint8)ji.GetID ();
				fs << (uint8)ji.GetInputType ();
				fs << (uint8)ji.GetButtonID ();
				fs << (uint8)ji.GetLever ();
				fs << (uint8)ji.GetAxis ();
				fs << (uint8)ji.GetPov ();
			break;
			}
		}

#endif // 0
			m_deviceInput [ i ].Save ( bw );
		}
	}

	//--------------------------------------------------
	//読込
	void KeyConfig::Load ()
	{
#if 0
		//設定ファイル読込
		std::fstream fs ( _T("keyConfig.dat"), std::ios::in, std::ios::binary );

		//エラーのとき
		if ( fs.fail () )
		{
			//新規ファイルの作成
			SetInitial ();
//			Save ();
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
				di.SetKeyboard ( (KEY_NAME)key );
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
#endif // 0
		try
		{
			_Load ();
		}
		catch (...)
		{
			SetInitial ();
		}
	}

	//--------------------------------------------------
	//読込
	void KeyConfig::_Load ()
	{
		s3d::FilePath path = U"keyconfig.dat";
		s3d::BinaryReader br ( path );

		const uint32 NUM_STG = 24;

		for ( size_t i = 0; i < NUM_STG; ++ i )
		{
#if 0
			uint8 device_type = 0;
			br.read ( device_type );

			uint8 pad_id = 0;
			br.read ( pad_id );

			uint8 input_type = 0;
			br.read ( input_type );

			uint8 btn = 0;
			br.read ( btn );

			uint8 lever = 0;
			br.read ( lever );

			uint8 axis = 0;
			br.read ( axis );

			uint8 pov = 0;
			br.read ( pov );

			uint8 key = 0;
			br.read ( key );
#endif // 0

#if 0

			INPUT_DEVICE_TYPE idt = (INPUT_DEVICE_TYPE)ReadUInt8 ( br );
			uint32 pad_id = ReadUInt8 ( br );
			PAD_INPUT_TYPE input_type = (PAD_INPUT_TYPE)ReadUInt8 ( br );
			uint32 btn = ReadUInt8 ( br );
			LEVER_DIR lvr = (LEVER_DIR)ReadUInt8 ( br );
			AXIS_VALUE axis = (AXIS_VALUE)ReadUInt8 ( br );
			POV_VALUE pov = (POV_VALUE)ReadUInt8 ( br );
			KEY_NAME key = (KEY_NAME)ReadUInt8 ( br );

			GamePadInput gpi;

			switch ( idt )
			{
			case KEYBOARD:
				m_deviceInput [ i ].SetKeyboard ( key );
				break;

			case GAMEPAD:
				gpi.Set ( pad_id, input_type, btn, lvr, axis, pov );
				m_deviceInput [ i ].SetPad ( gpi );
				break;

			default:break;
			}

#endif // 0
			DeviceInput di;
			di.Load ( br );
			m_deviceInput [ i ] = di;
		}
	}


	s3d::String KeyConfig::ToString ()
	{
		s3d::String str { U"" };
		for ( DeviceInput di : m_deviceInput )
		{
			str.append ( di.ToString () );
			str.append ( U"\n" );
		}
		return str;
	}

	//----------------------------------------------------------------------------------
	//押された状態かどうか
	bool KeyConfig::Is_Joy ( GamePadInput gpi ) const
	{
		DWORD id = gpi.GetID ();
		PAD_INPUT_TYPE type = gpi.GetInputType ();
		switch ( type )
		{
		case PIT_AXIS: return Is_Axis_Vl ( id, gpi.GetAxis () ); break;
		case PIT_POINT_OF_VIEW: return Is_POV_Vl ( id, gpi.GetPov () ); break;
		case PIT_BUTTON: return SVINP->IsJoyButton ( id, gpi.GetButtonID () ); break;
		}
		return false;
	}

	bool KeyConfig::Is_Axis_Vl ( uint32 ID, AXIS_VALUE vl ) const
	{
		bool ret = false;
		switch ( vl )
		{
		case AXIS_VALUE::AXIS_X_P:	ret = SVINP->IsAxisX_Plus ( ID );	break;
		case AXIS_VALUE::AXIS_X_M:	ret = SVINP->IsAxisX_Minus ( ID );	break;
		case AXIS_VALUE::AXIS_Y_P:	ret = SVINP->IsAxisY_Plus ( ID );	break;
		case AXIS_VALUE::AXIS_Y_M:	ret = SVINP->IsAxisY_Minus ( ID );	break;
		case AXIS_VALUE::AXIS_Z_P:	ret = SVINP->IsAxisZ_Plus ( ID );	break;
		case AXIS_VALUE::AXIS_Z_M:	ret = SVINP->IsAxisZ_Minus ( ID );	break;
		}
		return ret;
	}
	
	bool KeyConfig::Is_POV_Vl ( uint32 ID, POV_VALUE vl ) const
	{
		bool ret = false;
		switch ( vl )
		{
		case POV_VALUE::POV_UP:		ret = SVINP->IsPovUp ( ID );	break;
		case POV_VALUE::POV_DOWN:	ret = SVINP->IsPovDown ( ID );	break;
		case POV_VALUE::POV_LEFT:	ret = SVINP->IsPovLeft ( ID );	break;
		case POV_VALUE::POV_RIGHT:	ret = SVINP->IsPovRight ( ID );	break;
		}
		return ret;
	}

	bool KeyConfig::Is_Keyboard ( KEY_NAME key ) const
	{
//		return DxInput::instance ()->IsOneKeyboard ( key );
		return SVINP->Is_Keyboard ( key );
	}

	//----------------------------------------------------------------------------------
	//押された瞬間かどうか
	bool KeyConfig::Push_Joy ( GamePadInput gpi ) const
	{
		DWORD id = gpi.GetID ();
		PAD_INPUT_TYPE type = gpi.GetInputType ();
		switch ( type )
		{
		case PIT_AXIS: return Push_Axis_Vl ( id, gpi.GetAxis () ); break;
		case PIT_POINT_OF_VIEW: return Push_POV_Vl ( id, gpi.GetPov () ); break;
		case PIT_BUTTON: return SVINP->PushJoyButton ( id, gpi.GetButtonID () ); break;
		}
		return false;
	}

	bool KeyConfig::Push_Axis_Vl ( uint32 ID, AXIS_VALUE vl ) const
	{
		bool ret = false;
		switch ( vl )
		{
		case AXIS_VALUE::AXIS_X_P:	ret = SVINP->PushAxisX_Plus ( ID );	break;
		case AXIS_VALUE::AXIS_X_M:	ret = SVINP->PushAxisX_Minus ( ID );	break;
		case AXIS_VALUE::AXIS_Y_P:	ret = SVINP->PushAxisY_Plus ( ID );	break;
		case AXIS_VALUE::AXIS_Y_M:	ret = SVINP->PushAxisY_Minus ( ID );	break;
		case AXIS_VALUE::AXIS_Z_P:	ret = SVINP->PushAxisZ_Plus ( ID );	break;
		case AXIS_VALUE::AXIS_Z_M:	ret = SVINP->PushAxisZ_Minus ( ID );	break;
		}
		return ret;
	}

	bool KeyConfig::Push_POV_Vl ( uint32 ID, POV_VALUE vl ) const
	{
		bool ret = false;
		switch ( vl )
		{
		case POV_VALUE::POV_UP:		ret = SVINP->PushPovUp ( ID );	break;
		case POV_VALUE::POV_DOWN:	ret = SVINP->PushPovDown ( ID );	break;
		case POV_VALUE::POV_LEFT:	ret = SVINP->PushPovLeft ( ID );	break;
		case POV_VALUE::POV_RIGHT:	ret = SVINP->PushPovRight ( ID );	break;
		}
		return ret;
	}

	bool KeyConfig::Push_Keyboard ( KEY_NAME key ) const
	{
		return SVINP->Push_Keyboard ( key );
	}

	//----------------------------------------------------------------------------------
	//離された瞬間かどうか
	bool KeyConfig::Rele_Joy ( GamePadInput gpi ) const
	{
		DWORD id = gpi.GetID ();
		PAD_INPUT_TYPE type = gpi.GetInputType ();
		switch ( type )
		{
		case PIT_AXIS: return Rele_Axis_Vl ( id, gpi.GetAxis () ); break;
		case PIT_POINT_OF_VIEW: return Rele_POV_Lvr ( id, gpi.GetPov () ); break;
		case PIT_BUTTON: return SVINP->ReleJoyButton ( id, gpi.GetButtonID () ); break;
		}
		return false;
	}

	bool KeyConfig::Rele_Axis_Vl ( uint32 ID, AXIS_VALUE vl ) const
	{
		bool ret = false;
		switch ( vl )
		{
		case AXIS_VALUE::AXIS_X_P:	ret = SVINP->ReleAxisX_Plus ( ID );	break;
		case AXIS_VALUE::AXIS_X_M:	ret = SVINP->ReleAxisX_Minus ( ID );	break;
		case AXIS_VALUE::AXIS_Y_P:	ret = SVINP->ReleAxisY_Plus ( ID );	break;
		case AXIS_VALUE::AXIS_Y_M:	ret = SVINP->ReleAxisY_Minus ( ID );	break;
		case AXIS_VALUE::AXIS_Z_P:	ret = SVINP->ReleAxisZ_Plus ( ID );	break;
		case AXIS_VALUE::AXIS_Z_M:	ret = SVINP->ReleAxisZ_Minus ( ID );	break;
		}
		return ret;
	}

	bool KeyConfig::Rele_POV_Lvr ( uint32 ID, POV_VALUE vl ) const
	{
		bool ret = false;
		switch ( vl )
		{
		case POV_VALUE::POV_UP:		ret = SVINP->RelePovUp ( ID );	break;
		case POV_VALUE::POV_DOWN:	ret = SVINP->RelePovDown ( ID );	break;
		case POV_VALUE::POV_LEFT:	ret = SVINP->RelePovLeft ( ID );	break;
		case POV_VALUE::POV_RIGHT:	ret = SVINP->RelePovRight ( ID );	break;
		}
		return ret;
	}

	bool KeyConfig::Rele_Keyboard ( KEY_NAME key ) const
	{
		return SVINP->Rele_Keyboard ( key );
	}

	//----------------------------------------------------------------------------------


	//static プレイヤーとキー種類から判定値を取得する
	GAME_USE_KEY KeyConfig::InputFromPlayer ( PLAYER_ID id, PLAYER_INPUT input )
	{
		GAME_USE_KEY ret = GAME_USE_KEY::GAME_USE_KEY_NUM;

		//プレイヤー側によって分岐
		bool b = ( PLAYER_ID_1 == id );

		switch ( input )
		{
		case PLY_UP:    ret = b ? P1_UP:    P2_UP;		break;
		case PLY_DOWN:  ret = b ? P1_DOWN:  P2_DOWN;	break;
		case PLY_LEFT:  ret = b ? P1_LEFT:  P2_LEFT;	break;
		case PLY_RIGHT: ret = b ? P1_RIGHT: P2_RIGHT;	break;
		case PLY_BTN0:  ret = b ? P1_BTN0:  P2_BTN0;	break;
		case PLY_BTN1:  ret = b ? P1_BTN1:  P2_BTN1;	break;
		case PLY_BTN2:  ret = b ? P1_BTN2:  P2_BTN2;	break;
		case PLY_BTN3:  ret = b ? P1_BTN3:  P2_BTN3;	break;
		case PLY_BTN4:  ret = b ? P1_BTN4:  P2_BTN4;	break;
		case PLY_BTN5:  ret = b ? P1_BTN5:  P2_BTN5;	break;
		case PLY_BTN6:  ret = b ? P1_BTN6:  P2_BTN6;	break;
		case PLY_BTN7:  ret = b ? P1_BTN7:  P2_BTN7;	break;
		};

		if ( ret == GAME_USE_KEY::GAME_USE_KEY_NUM ) { assert ( 0 ); }

		return ret;
	}


}	//namespace GAME

