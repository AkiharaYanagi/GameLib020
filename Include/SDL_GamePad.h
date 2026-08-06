//=================================================================================================
//
//	SDL_GamePad
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
# include <Siv3D.hpp> // Siv3D v0.6.16
#include <SDL3/SDL.h>
#include "00_Common.h"
#include "03_GameInput.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	struct SDL_Input_Store
	{
		bool m_button [ SDL_SCANCODE_COUNT ];
		Sint16 m_axis [ SDL_GAMEPAD_AXIS_COUNT ];

	public:
		SDL_Input_Store ()
		{
			for ( int i = 0; i < SDL_SCANCODE_COUNT; ++i )
			{
				m_button[i] = false;
			}
			for ( int i = 0; i < SDL_GAMEPAD_AXIS_COUNT; ++i )
			{
				m_axis[i] = 0;
			}
		}

		void SetAxis ( SDL_GamepadAxis axis, Sint16 value )
		{
			uint32_t index = static_cast < uint32_t > ( axis );
			m_axis[index] = value;
		}
	};

	using A_SDLI = s3d::Array < SDL_Input_Store >;
	using UOMP_SDLI = std::unordered_map < SDL_JoystickID, SDL_Input_Store >;

	//外部指定IDと内部ID
	using V_ID = std::vector < SDL_JoystickID >;


	class SDL_GamePad
	{
		//ゲームパッドの保存
		std::unordered_map < SDL_JoystickID, SDL_Gamepad * >  m_pads;

		//入力状態の保存(ゲームパッドに対応)
		UOMP_SDLI	m_store;	//今回の保存
		UOMP_SDLI	m_prev;		//前回の保存

		//SDL_JoystickIDの保存
		V_ID		mv_id;

	public:
		SDL_GamePad ();
		SDL_GamePad ( const SDL_GamePad & rhs ) = delete;
		~SDL_GamePad ();

		void Load();
		void Update ();

		//---------------------------------------------------------------------------
		//キーコンフィグ用
		//いずれかが押されていたら優先順で返す
		GamePadInput PushInput ();

		//--------------------------------------------------------------
		//ボタン

		//指定したボタンが押されている状態か
		bool IsButton( int32_t id, int32_t nBtn ) const;
		//指定したボタンが離されている状態か
		bool NisButton( int32_t id, int32_t nBtn ) const;

		//指定したボタンの1つ前が押されている状態か
		bool WasButton( int32_t id, int32_t nBtn ) const;
		//指定したボタンの１つ前が離されている状態か
		bool NwasButton( int32_t id, int32_t nBtn ) const;

		//指定したボタンが押された瞬間か
		bool PushButton( int32_t id, int32_t nBtn ) const;
		//指定したボタンが離された瞬間か
		bool ReleButton( int32_t id, int32_t nBtn ) const;


		//--------------------------------------------------------------
		//軸
		float GetAxisLX ( int32_t id ) const;
		float GetAxisLY ( int32_t id ) const;
		float GetAxisRX ( int32_t id ) const;
		float GetAxisRY ( int32_t id ) const;
		float GetAxisLT ( int32_t id ) const;
		float GetAxisRT ( int32_t id ) const;

		//Axis:状態の判定  ( -32768 < SInt16 < 32768 )
		bool IsAxisLX_Plus	( int32_t id ) const;
		bool IsAxisLX_Minus	( int32_t id ) const;
		bool IsAxisLY_Plus	( int32_t id ) const;
		bool IsAxisLY_Minus	( int32_t id ) const;

		bool IsAxisRX_Plus	( int32_t id ) const;
		bool IsAxisRX_Minus	( int32_t id ) const;
		bool IsAxisRY_Plus	( int32_t id ) const;
		bool IsAxisRY_Minus	( int32_t id ) const;

		bool IsAxisLT	( int32_t id ) const;
		bool IsAxisRT	( int32_t id ) const;


	private:
		bool NotExist(int32_t id) const { return ! Exist ( id ); }
		bool Exist ( int32_t id ) const;

		bool Check_Id_and_Btn (int32_t id, int32_t nBtn) const;


		void SetAxis(int32_t id, SDL_GamepadAxis axis, Sint16 value);
	};

	using P_SDL_GamePad = std::shared_ptr < SDL_GamePad >;


}	//namespace GAME

