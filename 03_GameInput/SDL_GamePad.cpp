//=================================================================================================
//
//	SDL_GamePad
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "SDL_GamePad.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	SDL_GamePad::SDL_GamePad ()
	{
	}

	SDL_GamePad::~SDL_GamePad ()
	{
	}

	void SDL_GamePad::Load ()
	{
		// SDL3の初期化
		SDL_Init(SDL_INIT_GAMEPAD);
	}

	void SDL_GamePad::Update ()
	{
		SDL_Event event;

		//前回の値をコピー
		m_prev = m_store;

		//イベントがあったものだけ書き換える
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			//ゲームパッドの接続イベント
			case SDL_EVENT_GAMEPAD_ADDED:
			{
				SDL_Gamepad* pad = SDL_OpenGamepad ( event.gdevice.which );
				if ( pad )
				{
					SDL_JoystickID id = SDL_GetGamepadID(pad);
					m_pads [ id ] = pad;
					//保存データも確保
					m_store[id] = SDL_Input_Store();
					m_prev[id] = SDL_Input_Store();

					//ID保存
					mv_id.push_back ( id );
				}
			}
			break;

			//ゲームパッドの切断イベント
			case SDL_EVENT_GAMEPAD_REMOVED:
			{
				SDL_JoystickID id = event.gdevice.which;

				auto it = m_pads.find(id);
				if ( it != m_pads.end() )
				{
					SDL_CloseGamepad ( it->second );
					m_pads.erase ( it );
				}
				auto its = m_store.find(id);
				if ( its != m_store.end() )
				{
					m_store.erase ( its );
				}
				auto itp = m_prev.find(id);
				if ( itp != m_prev.end() )
				{
					m_prev.erase ( itp );
				}

				auto itv = std::find ( mv_id.begin(), mv_id.end(), id );
				mv_id.erase ( itv );
			}
			break;

			case SDL_EVENT_GAMEPAD_AXIS_MOTION:
			{
				//Sint16 value;       /**< The axis value (range: -32768 to 32767) */
				SDL_GamepadAxis ax = static_cast < SDL_GamepadAxis > ( event.gaxis.axis );
				m_store[event.gbutton.which].SetAxis ( ax, event.gaxis.value );
			}
			break;

			case SDL_EVENT_GAMEPAD_BUTTON_DOWN:
				m_store[event.gbutton.which].m_button [ event.gbutton.button ] = T;
			break;

			case SDL_EVENT_GAMEPAD_BUTTON_UP:
				m_store[event.gbutton.which].m_button [ event.gbutton.button ] = F;
			break;
			}

			SDL_UpdateGamepads();
		}
#if 0

		//有効なパッドのみ
		for ( auto& [id, p] : m_pads )
		{
			//軸の値を取得する
			for ( int i = 0; i < SDL_GAMEPAD_AXIS_COUNT; ++i )
			{
				float value = SDL_GetGamepadAxis ( p, static_cast<SDL_GamepadAxis>(i) );
				m_store[id].SetAxis ( static_cast<SDL_GamepadAxis>(i), value );
			}
		}

#endif // 0

	}


	//---------------------------------------------------------------------------
	//キーコンフィグ用
	//いずれかが押されていたら優先順で返す
	GamePadInput SDL_GamePad::PushInput()
	{
		GamePadInput ret;

		//すべてのデバイスをチェック
		//１つでも該当すればその時点でreturn
		for ( auto& [id, p] : m_pads )
		{
			//ボタン
			for ( int i = 0; i < SDL_SCANCODE_COUNT; ++i )
			{
				if ( IsButton ( id, i ) )
				{
					ret.SetBtn ( id, i );
					return ret;
				}
			}
			//軸
			for ( int i = 0; i < SDL_GAMEPAD_AXIS_COUNT; ++i )
			{
			}
		}

		return ret;
	}


	//--------------------------------------------------------------
	//ボタン

	//指定したボタンが押されている状態か
	bool SDL_GamePad::IsButton ( int32_t id, int32_t nBtn ) const
	{
		//IDとボタンのチェック
		if ( Check_Id_and_Btn ( id, nBtn ) ) { return F; }

		//指定したボタンが押されている状態は T
		return m_store.at ( mv_id[ id ] ).m_button[ nBtn ];
	}

	//指定したボタンが離されている状態か
	bool SDL_GamePad::NisButton( int32_t id, int32_t nBtn ) const
	{
		//IDとボタンのチェック
		if ( Check_Id_and_Btn ( id, nBtn ) ) { return F; }

		//指定したボタンが離されている状態は T
		return ! m_store.at ( mv_id[ id ] ).m_button[ nBtn ];
	}


	//指定したボタンの1つ前が押されている状態か
	bool SDL_GamePad::WasButton( int32_t id, int32_t nBtn ) const
	{
		//IDとボタンのチェック
		if ( Check_Id_and_Btn ( id, nBtn ) ) { return F; }

		//指定したボタンが押されている状態は T
		return m_prev.at( mv_id[ id ] ).m_button [ nBtn ];
	}

	//指定したボタンの１つ前が離されている状態か
	bool SDL_GamePad::NwasButton( int32_t id, int32_t nBtn ) const
	{
		//IDとボタンのチェック
		if ( Check_Id_and_Btn ( id, nBtn ) ) { return F; }

		//指定したボタンが離されている状態は T
		return ! m_prev.at( mv_id[ id ] ).m_button [ nBtn ];
	}


	//指定したボタンが押された瞬間か
	bool SDL_GamePad::PushButton( int32_t id, int32_t nBtn ) const
	{
		bool bIs = IsButton ( id, nBtn );
		bool bWs = WasButton ( id, nBtn );
		return bIs && ! bWs;
	}

	//指定したボタンが離された瞬間か
	bool SDL_GamePad::ReleButton( int32_t id, int32_t nBtn ) const
	{
		bool bIs = IsButton ( id, nBtn );
		bool bWs = WasButton ( id, nBtn );
		return ! bIs && bWs;
	}

	//--------------------------------------------------------------
	//軸
	float SDL_GamePad::GetAxisLX ( int32_t id ) const
	{
		if ( NotExist ( id ) ) { return 0; }

		uint32_t index = static_cast < uint32_t > ( SDL_GAMEPAD_AXIS_LEFTX );
		return m_store.at ( mv_id[ id ] ).m_axis [ index ];
	}
	
	float SDL_GamePad::GetAxisLY( int32_t id ) const
	{
		if ( NotExist ( id ) ) { return 0; }

		uint32_t index = static_cast < uint32_t > ( SDL_GAMEPAD_AXIS_LEFTY );
		return m_store.at ( mv_id[ id ] ).m_axis [ index ];
	}
	
	float SDL_GamePad::GetAxisRX ( int32_t id ) const
	{
		if ( NotExist ( id ) ) { return 0; }

		uint32_t index = static_cast < uint32_t > ( SDL_GAMEPAD_AXIS_RIGHTX );
		return m_store.at ( mv_id[ id ] ).m_axis [ index ];
	}
	
	float SDL_GamePad::GetAxisRY( int32_t id ) const
	{
		if ( NotExist ( id ) ) { return 0; }

		uint32_t index = static_cast < uint32_t > ( SDL_GAMEPAD_AXIS_RIGHTY );
		return m_store.at ( mv_id[ id ] ).m_axis [ index ];
	}
	
	float SDL_GamePad::GetAxisLT ( int32_t id ) const
	{
		if ( NotExist ( id ) ) { return 0; }

		uint32_t index = static_cast < uint32_t > ( SDL_GAMEPAD_AXIS_LEFT_TRIGGER );
		return m_store.at ( mv_id[ id ] ).m_axis [ index ];
	}
	
	float SDL_GamePad::GetAxisRT( int32_t id ) const
	{
		if ( NotExist ( id ) ) { return 0; }

		uint32_t index = static_cast < uint32_t > ( SDL_GAMEPAD_AXIS_RIGHT_TRIGGER );
		return m_store.at ( mv_id[ id ] ).m_axis [ index ];
	}


	//--------------------------------------------------------------
	//Axis:状態の判定  ( -32768 < SInt16 < 32768 )
	bool SDL_GamePad::IsAxisLX_Plus( int32_t id ) const
	{
		if ( NotExist ( id ) ) { return F; }

		uint32_t index = static_cast < uint32_t > ( SDL_GAMEPAD_AXIS_LEFTX );
		return ( m_store.at ( mv_id[ id ] ).m_axis [ index ] > 16384 );
	}

	bool SDL_GamePad::IsAxisLX_Minus( int32_t id ) const
	{
		if ( NotExist ( id ) ) { return F; }

		uint32_t index = static_cast < uint32_t > ( SDL_GAMEPAD_AXIS_LEFTX );
		return ( m_store.at ( mv_id[ id ] ).m_axis [ index ] < -16384 );
	}

	bool SDL_GamePad::IsAxisLY_Plus( int32_t id ) const
	{
		if ( NotExist ( id ) ) { return F; }

		uint32_t index = static_cast < uint32_t > ( SDL_GAMEPAD_AXIS_LEFTY );
		return ( m_store.at ( mv_id[ id ] ).m_axis [ index ] > 16384 );
	}

	bool SDL_GamePad::IsAxisLY_Minus( int32_t id ) const
	{
		if ( NotExist ( id ) ) { return F; }

		uint32_t index = static_cast < uint32_t > ( SDL_GAMEPAD_AXIS_LEFTY );
		return ( m_store.at ( mv_id[ id ] ).m_axis [ index ] < -16384 );
	}


	bool SDL_GamePad::IsAxisRX_Plus( int32_t id ) const
	{
		if ( NotExist ( id ) ) { return F; }

		uint32_t index = static_cast < uint32_t > ( SDL_GAMEPAD_AXIS_RIGHTX );
		return ( m_store.at ( mv_id[ id ] ).m_axis [ index ] > 16384 );
	}

	bool SDL_GamePad::IsAxisRX_Minus( int32_t id ) const
	{
		if ( NotExist ( id ) ) { return F; }

		uint32_t index = static_cast < uint32_t > ( SDL_GAMEPAD_AXIS_RIGHTX );
		return ( m_store.at ( mv_id[ id ] ).m_axis [ index ] < -16384 );
	}

	bool SDL_GamePad::IsAxisRY_Plus( int32_t id ) const
	{
		if ( NotExist ( id ) ) { return F; }

		uint32_t index = static_cast < uint32_t > ( SDL_GAMEPAD_AXIS_RIGHTY );
		return ( m_store.at ( mv_id[ id ] ).m_axis [ index ] > 16384 );
	}

	bool SDL_GamePad::IsAxisRY_Minus( int32_t id ) const
	{
		if ( NotExist ( id ) ) { return F; }

		uint32_t index = static_cast < uint32_t > ( SDL_GAMEPAD_AXIS_RIGHTY );
		return ( m_store.at ( mv_id[ id ] ).m_axis [ index ] < -16384 );
	}



	bool SDL_GamePad::IsAxisLT( int32_t id ) const
	{
		if ( NotExist ( id ) ) { return F; }

		uint32_t index = static_cast < uint32_t > ( SDL_GAMEPAD_AXIS_LEFT_TRIGGER );
		return ( m_store.at ( mv_id[ id ] ).m_axis [ index ] > 16384 );
	}

	bool SDL_GamePad::IsAxisRT( int32_t id ) const
	{
		if ( NotExist ( id ) ) { return F; }

		uint32_t index = static_cast < uint32_t > ( SDL_GAMEPAD_AXIS_RIGHT_TRIGGER );
		return ( m_store.at ( mv_id[ id ] ).m_axis [ index ] > 16384 );
	}


	//--------------------------------------------------------------
	//内部関数

	//パッドが存在しているか
	bool SDL_GamePad::Exist ( int32_t id ) const
	{
		//接続されているか
		if (id >= mv_id.size()) { return F; }
		SDL_JoystickID jid = mv_id[id];

		auto it = m_pads.find ( jid );
		if ( it == m_pads.end() ) { return F; }

		return T;
	}

	//パッドとボタンのチェック
	bool SDL_GamePad::Check_Id_and_Btn ( int32_t id, int32_t nBtn ) const
	{
		//パッドIDの存在
		if ( ! Exist(id) ) { return T; }

		//ボタン個数のチェック
		if ( SDL_SCANCODE_COUNT <= nBtn ) { return T; }

		//両方OKのときFを返す（問題があったらTで呼び出し側がif(T){return F;}）
		return F;
	}

	//軸の保存
	void SDL_GamePad::SetAxis ( int32_t id, SDL_GamepadAxis axis, Sint16 value )
	{
		//接続されているか
		SDL_JoystickID jid = static_cast<SDL_JoystickID>(id);
		auto it = m_pads.find ( jid );
		if ( it == m_pads.end() ) { return; }
		m_store[id].SetAxis ( axis, value );
	}


}	//namespace GAME

