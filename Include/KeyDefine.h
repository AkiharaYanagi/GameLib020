//=================================================================================================
//
//	入力キー定義
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//プレイヤごとの入力種類
	enum PLAYER_INPUT
	{
		PLY_UP,
		PLY_DOWN,
		PLY_LEFT,
		PLY_RIGHT,
		PLY_BTN0,
		PLY_BTN1,
		PLY_BTN2,
		PLY_BTN3,
		PLY_BTN4,
		PLY_BTN5,
		PLY_BTN6,
		PLY_BTN7,

		PLY_INPUT_NUM,	//プレイヤの入力種類数
	};

	//ゲーム使用キー
	enum GAME_USE_KEY
	{
		P1_UP,
		P1_DOWN,
		P1_LEFT,
		P1_RIGHT,
		P1_BTN0,
		P1_BTN1,
		P1_BTN2,
		P1_BTN3,
		P1_BTN4,
		P1_BTN5,
		P1_BTN6,
		P1_BTN7,

		P2_UP,
		P2_DOWN,
		P2_LEFT,
		P2_RIGHT,
		P2_BTN0,
		P2_BTN1,
		P2_BTN2,
		P2_BTN3,
		P2_BTN4,
		P2_BTN5,
		P2_BTN6,
		P2_BTN7,

		GAME_USE_KEY_NUM,	//ゲーム使用キーの数
	};


	//デバイス種類
	enum INPUT_DEVICE_TYPE
	{
		KEYBOARD,
		GAMEPAD,
		MOUSE, 
		NODEVICE,
	};


	//ゲームパッド内の入力種類
	enum PAD_INPUT_TYPE
	{
		PIT_BUTTON,
		PIT_LEVER,
		PIT_AXIS,
		PIT_POINT_OF_VIEW,
		PIT_NO_DATA,
	};


	//レバー方向
	enum LEVER_DIR
	{
		LVR_UP,
		LVR_DOWN,
		LVR_LEFT,
		LVR_RIGHT,
	};

	//XYZ アクシズ方向
	enum AXIS_DIR
	{
		AXIS_X = 0,
		AXIS_Y = 1,
		AXIS_Z = 2,
	};

	enum AXIS_VALUE
	{
		AXIS_X_P,	//Plus
		AXIS_X_M,	//Minus
		AXIS_Y_P,	//Plus
		AXIS_Y_M,	//Minus
		AXIS_Z_P,	//Plus
		AXIS_Z_M,	//Minus
	};

	//POV : Point Of View 方向
	enum POV_VALUE
	{
		POV_UP,
		POV_DOWN,
		POV_LEFT,
		POV_RIGHT,
	};


}	//namespace GAME

