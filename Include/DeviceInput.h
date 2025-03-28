//=================================================================================================
//
//	デバイスインプット
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Define.h"
#include "KeyDefine.h"
#include "SivKeyboardDefine.h"
#include "SivKeyboard_Name.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//============================================================
	//ゲームパッドの入力定義
	class GamePadInput
	{
		uint32			m_gamepadID { 0 };		//ゲームパッドID
		PAD_INPUT_TYPE	m_type { PIT_NO_DATA };	//入力種類
		uint32			m_buttonID { 0 };		//ボタン
		LEVER_DIR		m_lever { LVR_UP };		//レバー
		AXIS_VALUE		m_axis { AXIS_X_P };	//軸
		POV_VALUE		m_pov { POV_UP };		//POV

	public:
		GamePadInput ();
		GamePadInput ( const GamePadInput & rhs )	//コピー可能
		{
			m_gamepadID = rhs.m_gamepadID;
			m_type = rhs.m_type;
			m_buttonID = rhs.m_buttonID;
			m_lever = rhs.m_lever;
			m_axis = rhs.m_axis;
			m_pov = rhs.m_pov;
		}
		~GamePadInput () {}

		void Set ( uint32 pad_id, PAD_INPUT_TYPE type, uint32 btn, LEVER_DIR lvr, AXIS_VALUE axis, POV_VALUE pov );
//		void Set ( uint32 pad_id, PAD_INPUT_TYPE type, uint32 btn_id, LEVER_DIR lvr );
//		void Set ( uint32 pad_id, PAD_INPUT_TYPE type, uint32 btn_id, AXIS_VALUE axv );
		void SetBtn		( uint32 pad_id, uint32 btn_id );
		void SetLvr		( uint32 pad_id, LEVER_DIR lvr );
		void SetAxis	( uint32 pad_id, AXIS_VALUE axis );
		void SetPov		( uint32 pad_id, POV_VALUE pov );

		uint32 GetID () const { return m_gamepadID; }
		PAD_INPUT_TYPE GetInputType () const { return m_type; }
		uint32 GetButtonID () const { return m_buttonID; }
		LEVER_DIR GetLever () const { return m_lever; }
		AXIS_VALUE GetAxis () const { return m_axis; }
		s3d::String GetStrAxis ( AXIS_VALUE axis ) const;
		s3d::String GetStrAxis () const;
		POV_VALUE GetPov () const { return m_pov; }
		s3d::String GetStrPov () const;

		s3d::String ToString () const;
	};



	//============================================================
	//ゲーム内におけるデバイスの入力定義
	class DeviceInput
	{
		//デバイスタイプ
		INPUT_DEVICE_TYPE	m_dvc_type { NODEVICE };

		//各デバイス入力
		KEY_NAME			m_keyboardInput { SIK_NODATA };	//キーボード (キーID)
		GamePadInput		m_gamepadInput;				//ゲームパッド

	public:
		DeviceInput ();
		DeviceInput ( const DeviceInput & rhs );	//コピー可能
		~DeviceInput ();

		void SetKey ( INPUT_DEVICE_TYPE	dvc_type, KEY_NAME key );
		void SetKeyboard ( KEY_NAME key );
		void SetPad ( GamePadInput gamePadInput );

		INPUT_DEVICE_TYPE GetType () const { return m_dvc_type; }
		KEY_NAME GetKey () const { return m_keyboardInput; }
		s3d::String GetKeyName () { return KEYBOARD_STR [ m_keyboardInput ]; }
		GamePadInput GetPad () const { return m_gamepadInput; }

		s3d::String ToString ();

		//IO
		void Save ( s3d::BinaryWriter & bw );
		void Load ( s3d::BinaryReader & br );
	};




}	//namespace GAME

