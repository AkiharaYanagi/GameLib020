//=================================================================================================
//
// Siv ゲームパッド の実装
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "SivGamePad.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//-----------------------------------------------------------
	//1[F]のゲームパッドの入力を保存する
	GamePadInputStore::GamePadInputStore ( const GamePadInputStore & rhs )
	{
		axes_x = rhs.axes_x;
		axes_x = rhs.axes_x;
		axes_x = rhs.axes_x;
		for ( size_t i = 0; i < buttons.size (); ++ i )
		{
			buttons [ i ] = rhs.buttons [ i ];
		}
		povUp = rhs.povUp;
		povDown = rhs.povDown;
		povLeft = rhs.povLeft;
		povRight = rhs.povRight;
		povUp = rhs.povUp;povD8;
	}


	void GamePadInputStore::Store ( const s3d::detail::Gamepad_impl & impl )
	{
		axes_x = impl.axes [ AXIS_X ];
		axes_y = impl.axes [ AXIS_Y ];
		axes_z = impl.axes [ AXIS_Z ];

		int index = 0;
		size_t nBtn = impl.buttons.size ();
		buttons.resize ( nBtn );
		for ( s3d::Input inp : impl.buttons )
		{
			buttons [ index ++ ] = inp.pressed ();
		}

		povUp = impl.povUp.pressed ();
		povDown = impl.povDown.pressed ();
		povLeft = impl.povLeft.pressed ();
		povRight = impl.povRight.pressed ();
		povD8 = impl.povD8 ();
	}




	//-----------------------------------------------------------
	SivGamePad::SivGamePad()
	{
		m_impl.clear ();
//		m_pre_impl.clear ();


		size_t MAX = detail::Gamepad_helper::MaxPlayerCount;
		for ( size_t i = 0; i < MAX; ++ i )
		{
			m_impl.push_back ( Gamepad ( i ) );
//			m_pre_impl.push_back ( Gamepad ( i ) );
			m_pre_store.push_back ( GamePadInputStore () );
		}


		//@info デフォルトコンストラクタが指定されていないため、引数ありのコンストラクタしか利用できない
		// Array < T > では コピーコンストラクタ  T ( const T & rhs ){} の定義が必要
#if 0
		m_impl.resize ( MAX );
		m_pre_impl.resize ( MAX );
		m_pre_store.resize ( MAX );
#endif // 0


	}

	SivGamePad::~SivGamePad()
	{
	}



	//--------------------------------------------------------------------------
	//ゲーム利用
	//--------------------------------------------------------------------------

	//状態の更新
	void SivGamePad::Update()
	{
		//プレイヤーカウントでループ
		size_t MAX = detail::Gamepad_helper::MaxPlayerCount;
		for ( size_t i = 0; i < MAX; ++ i )
		{
			//接続されていなかったら何もしない
			if ( ! Gamepad ( i ) ) { continue; }

			//現在の状態を取得
			m_impl [ i ] = Gamepad ( i );
		}
	}

	//状態の更新
	void SivGamePad::Store ()
	{
		//プレイヤーカウントでループ
		size_t MAX = detail::Gamepad_helper::MaxPlayerCount;
		for ( size_t i = 0; i < MAX; ++ i )
		{
			//接続されていなかったら何もしない
			if ( ! Gamepad ( i ) ) { continue; }

			//現在の状態を保存して次回に利用
			m_pre_store [ i ].Store ( m_impl [ i ] );
		}
	}


	const GMPD & SivGamePad::GetState () const 
	{
		return m_impl [ 0 ];
	}


	//---------------------------------------------------------------------------
	//キーコンフィグ用
	//いずれかが押されていたら優先順で返す
	GamePadInput SivGamePad::PushInput ()
	{
		GamePadInput ret;	//戻値用

		//すべてのデバイスをチェック
		//１つでも該当すればその時点でreturn
		uint32 MAX = detail::Gamepad_helper::MaxPlayerCount;
		for ( uint32 i = 0; i < MAX; ++ i )
		{
			//接続されていなかったら何もしない
			if ( ! Gamepad ( i ) ) { continue; }

			GMPD gmpd = m_impl [ i ];

			//ボタン
			uint32 nBtn = 0;
			for ( s3d::Input ipt : gmpd.buttons )
			{
				if ( ipt.down () )
				{
					ret.Set ( i, PIT_BUTTON, nBtn, LVR_UP );
					return ret;
				}
				++ nBtn;
			}

			//POV ( Point Of View )
			if ( gmpd.povUp.down () )	 { SetGPI_POV ( ret, i, LVR_UP ); return ret;}
			if ( gmpd.povDown.down () )	 { SetGPI_POV ( ret, i, LVR_DOWN ); return ret;}
			if ( gmpd.povLeft.down () )	 { SetGPI_POV ( ret, i, LVR_LEFT ); return ret;}
			if ( gmpd.povRight.down () ) { SetGPI_POV ( ret, i, LVR_RIGHT ); return ret;}

			//XY Axis
			if ( PushAxisUp ( i ) )		{ SetGPI_Axis ( ret, i, LVR_UP ); return ret; }
			if ( PushAxisDown ( i ) )	{ SetGPI_Axis ( ret, i, LVR_DOWN ); return ret; }
			if ( PushAxisLeft ( i ) )	{ SetGPI_Axis ( ret, i, LVR_LEFT ); return ret; }
			if ( PushAxisRight ( i ) )	{ SetGPI_Axis ( ret, i, LVR_RIGHT ); return ret; }
		}

		return ret;
	}

	void SivGamePad::SetGPI_POV ( GamePadInput & ret, uint32 pad_id, LEVER_DIR dir )
	{
		ret.Set ( pad_id, PIT_POINT_OF_VIEW, 0, dir );
	}

	void SivGamePad::SetGPI_Axis ( GamePadInput & ret, uint32 pad_id, LEVER_DIR dir )
	{
		ret.Set ( pad_id, PIT_AXIS, 0, dir );
	}

	//--------------------------------------------------------------
	//ボタン

	//指定したボタンが押されている状態か
	bool SivGamePad::IsButton( int id, int nButton ) const
	{
		//接続されているか
		const detail::Gamepad_impl & gamepad = Gamepad ( id );

		//ボタン個数のチェック
		if ( gamepad.buttons.size () <= nButton ) { return F; }

		//指定したボタンが押されている状態は T
		return gamepad.buttons [ nButton ].pressed ();
	}

	//ひとつ前のフレームで指定したボタンが押されている状態か
	bool SivGamePad::WasButton( int id, int nButton ) const
	{
		//ボタン個数のチェック
//		if ( m_pre_impl[id].buttons.size () <= nButton ) { return F; }
		if ( m_pre_store[id].BtnSize () <= nButton ) { return F; }

		//指定したボタンが押されている状態は T
//		return m_pre_impl[id].buttons [ nButton ].pressed ();
		return m_pre_store [ id ].WasBtn ( (size_t)nButton );
	}

	//指定したボタンが押された瞬間か
	bool SivGamePad::PushButton( int id, int nButton ) const
	{
		bool bIs = IsButton ( id, nButton );
		bool bWs = WasButton ( id, nButton );
		return bIs && ! bWs;
	}

	//指定したボタンが離された瞬間か
	bool SivGamePad::ReleButton( int id, int nButton ) const
	{
		bool bIs = IsButton ( id, nButton );
		bool bWs = WasButton ( id, nButton );
		return ! bIs && bWs;
	}

	//--------------------------------------------------------------
	//軸
	//軸の状態を返す
	double SivGamePad::GetJoyAxisX( size_t id ) const
	{
		return  m_impl[id].axes[AXIS_X];
	}

	double SivGamePad::GetJoyAxisY( size_t id ) const
	{
		return  m_impl[id].axes[AXIS_Y];
	}

	double SivGamePad::GetJoyAxisZ( size_t id ) const
	{
		return  m_impl[id].axes[AXIS_Z];
	}

	//Axis:押した状態の判定 ( -1 < double < 1 )
	bool SivGamePad::IsAxisY_Plus	( size_t id ) const
	{
		return ( m_impl[id].axes[AXIS_Y] <= -0.500 );
	}
	bool SivGamePad::IsAxisY_Minus	( size_t id ) const
	{
		return ( m_impl[id].axes[AXIS_Y] >= +0.500 );
	}
	bool SivGamePad::IsAxisX_Minus	( size_t id ) const
	{
		return ( m_impl[id].axes[AXIS_X] <= -0.500 );
	}
	bool SivGamePad::IsAxisX_Plus( size_t id ) const
	{
		return ( m_impl[id].axes[AXIS_X] >= +0.500 );
	}
	bool SivGamePad::IsAxisZ_Minus	( size_t id ) const
	{
		return ( m_impl[id].axes[AXIS_Z] <= -0.500 );
	}
	bool SivGamePad::IsAxisZ_Plus( size_t id ) const
	{
		return ( m_impl[id].axes[AXIS_Z] >= +0.500 );
	}

	//前フレームの状態
#if 0
	bool SivGamePad::WasAxisUp		( size_t id ) const
	{
		if ( id < 0 || detail::Gamepad_helper::MaxPlayerCount <= id ) { return F; }
		return m_pre_store[id].WasAxisUp ();
	}
	bool SivGamePad::WasAxisDown	( size_t id ) const
	{
		if ( id < 0 || detail::Gamepad_helper::MaxPlayerCount <= id ) { return F; }
		return m_pre_store[id].WasAxisDown ();
	}
	bool SivGamePad::WasAxisLeft	( size_t id ) const
	{
		if ( id < 0 || detail::Gamepad_helper::MaxPlayerCount <= id ) { return F; }
		return m_pre_store[id].WasAxisLeft ();
	}
	bool SivGamePad::WasAxisRight	( size_t id ) const
	{
		if ( id < 0 || detail::Gamepad_helper::MaxPlayerCount <= id ) { return F; }
		return m_pre_store[id].WasAxisRight ();
	}
#endif // 0
		bool SivGamePad::WasAxisY_Minus	( size_t id ) const
		{
			return m_pre_store[id].WasAxisY_Minus ();
		}
		bool SivGamePad::WasAxisY_Plus	( size_t id ) const
		{
			return m_pre_store[id].WasAxisY_Plus ();
		}
		bool SivGamePad::WasAxisX_Minus	( size_t id ) const
		{
			return m_pre_store[id].WasAxisX_Minus ();
		}
		bool SivGamePad::WasAxisX_Plus	( size_t id ) const
		{
			return m_pre_store[id].WasAxisX_Plus ();
		}
		bool SivGamePad::WasAxisZ_Minus	( size_t id ) const
		{
			return m_pre_store[id].WasAxisZ_Minus ();
		}
		bool SivGamePad::WasAxisZ_Plus	( size_t id ) const
		{
			return m_pre_store[id].WasAxisZ_Plus ();
		}


	//--------------------------------------------------------------
	//POV

	Optional < int32 > SivGamePad::GetPov ( size_t id ) const
	{
		const auto & gamepad = Gamepad ( id );
		if ( ! gamepad ) { return 0; }

		return gamepad.povD8 ();
	}


	//POVの状態を返す( 上から 0, 9000, 18000, 27000 )
	//※単一の値なので範囲で指定する
	// (0,4500,9000,13500,18000,22500,27000,31500)
	bool SivGamePad::IsPovUp ( size_t id ) const
	{
		const detail::Gamepad_impl & gamepad = Gamepad ( id );
		if ( ! gamepad ) { return F; }

		//オプショナル(null許容)型 チェック
		Optional < int32 > pov = gamepad.povD8 ();
		if ( pov ) { return F; }

		return ( 0 <= pov && pov <= 4500 ) || ( 31500 <= pov && pov <= 35999 );
	}


	bool SivGamePad::IsPovRight ( size_t id ) const
	{
		Optional < int32 > pov = Gamepad ( id ).povD8 ();
		return ( 4500 <= pov && pov <= 13500 );
	}

	bool SivGamePad::IsPovDown ( size_t id ) const
	{
		Optional < int32 > pov = Gamepad ( id ).povD8 ();
		return ( 13500 <= pov && pov <= 22500 );
	}

	bool SivGamePad::IsPovLeft ( size_t id )  const
	{
		Optional < int32 > pov = Gamepad ( id ).povD8 ();
		return ( 22500 <= pov && pov <= 31500 );
	}

	//-----------------------------------------------
	bool SivGamePad::WasPovUp ( size_t id ) const
	{
		Optional < int32 > pov = m_pre_store[id].PovD8 ();
		return ( 0 <= pov && pov <= 4500 ) || ( 31500 <= pov && pov <= 35999 );
	}

	bool SivGamePad::WasPovRight ( size_t id ) const
	{
		Optional < int32 > pov = m_pre_store[id].PovD8 ();
		return ( 4500 <= pov && pov <= 13500 );
	}

	bool SivGamePad::WasPovDown ( size_t id ) const
	{
		Optional < int32 > pov = m_pre_store[id].PovD8 ();
		return ( 13500 <= pov && pov <= 22500 );
	}

	bool SivGamePad::WasPovLeft ( size_t id )  const
	{
		Optional < int32 > pov = m_pre_store[id].PovD8 ();
		return ( 22500 <= pov && pov <= 31500 );
	}


}	//namespace GAME


