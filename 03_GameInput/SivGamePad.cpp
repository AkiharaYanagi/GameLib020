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

	//コピーコンストラクタ
	GamePadInputStore::GamePadInputStore ( const GamePadInputStore & rhs )
	{
		for ( size_t i = 0; i < buttons.size (); ++ i )
		{
			buttons [ i ] = rhs.buttons [ i ];
		}

		axis_x = rhs.axis_x;
		axis_x = rhs.axis_x;
		axis_x = rhs.axis_x;

		povUp = rhs.povUp;
		povDown = rhs.povDown;
		povLeft = rhs.povLeft;
		povRight = rhs.povRight;
		povUp = rhs.povUp;povD8;
	}

	//s3d::detail::Gamepad_impl から変換
	void GamePadInputStore::Store ( const s3d::detail::Gamepad_impl & impl )
	{
		//ボタン
		int index = 0;
		size_t nBtn = impl.buttons.size ();
		buttons.resize ( nBtn );
		for ( s3d::Input inp : impl.buttons )
		{
			buttons [ index ++ ] = inp.pressed ();
		}

		//Axis
		size_t sizeAxis = impl.axes.size (); 
		if ( sizeAxis >= 1 )
		{
			axis_x = impl.axes [ AXIS_X ];
			if ( sizeAxis >= 2 )
			{
				axis_y = impl.axes [ AXIS_Y ];
				if ( sizeAxis >= 3 )
				{
					axis_z = impl.axes [ AXIS_Z ];
				}
			}
		}

		//POV
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

		//接続されているゲームパッドを列挙する
		s3d::Array < s3d::GamepadInfo > aryGamepads = s3d::System::EnumerateGamepads ();

		size_t MAX = detail::Gamepad_helper::MaxPlayerCount;
		for ( size_t i = 0; i < MAX; ++ i )
		{
			m_impl.push_back ( s3d::Gamepad ( i ) );
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
			if ( ! s3d::Gamepad ( i ) ) { continue; }

			//現在の状態を取得
			m_impl [ i ] = s3d::Gamepad ( i );
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
			if ( ! s3d::Gamepad ( i ) ) { continue; }

			//現在の状態を保存して次回に利用
			m_pre_store [ i ].Store ( m_impl [ i ] );
		}
	}


	const GMPD & SivGamePad::GetState () const 
	{
		return m_impl [ 0 ];
	}

	const GamePadInputStore & SivGamePad::GetStore () const 
	{
		return m_pre_store [ 0 ];
	}


	//---------------------------------------------------------------------------
	//キーコンフィグ用
	//いずれかが押された瞬間なら優先順で返す
	GamePadInput SivGamePad::PushInput ()
	{
		GamePadInput ret;	//戻値用

		//すべてのデバイスをチェック
		//１つでも該当すればその時点でreturn
		uint32 MAX = detail::Gamepad_helper::MaxPlayerCount;
		for ( uint32 i = 0; i < MAX; ++ i )
		{
			//接続されていなかったら何もしない
			if ( ! s3d::Gamepad ( i ) ) { continue; }

			GMPD gmpd = m_impl [ i ];

			//XYZ Axis
			if ( PushAxisX_Plus ( i ) )		{ SetGPI_Axis ( ret, i, AXIS_X_P ); return ret; }
			if ( PushAxisX_Minus ( i ) )	{ SetGPI_Axis ( ret, i, AXIS_X_M ); return ret; }
			if ( PushAxisY_Plus ( i ) )		{ SetGPI_Axis ( ret, i, AXIS_Y_P ); return ret; }
			if ( PushAxisY_Minus ( i ) )	{ SetGPI_Axis ( ret, i, AXIS_Y_M ); return ret; }
			if ( PushAxisZ_Plus ( i ) )		{ SetGPI_Axis ( ret, i, AXIS_Z_P ); return ret; }
			if ( PushAxisZ_Minus ( i ) )	{ SetGPI_Axis ( ret, i, AXIS_Z_M ); return ret; }

			//POV ( Point Of View )
#if 0
			if ( gmpd.povUp.down () )	 { SetGPI_Pov ( ret, i, POV_UP ); return ret;}
			if ( gmpd.povDown.down () )	 { SetGPI_Pov ( ret, i, POV_DOWN ); return ret;}
			if ( gmpd.povLeft.down () )	 { SetGPI_Pov ( ret, i, POV_LEFT ); return ret;}
			if ( gmpd.povRight.down () ) { SetGPI_Pov ( ret, i, POV_RIGHT ); return ret;}
#endif // 0
			if ( gmpd.povRight.down () ) { SetGPI_Pov ( ret, i, POV_RIGHT ); return ret;}
			if ( gmpd.povUp.down () )	 { SetGPI_Pov ( ret, i, POV_UP ); return ret;}
			if ( gmpd.povDown.down () )	 { SetGPI_Pov ( ret, i, POV_DOWN ); return ret;}
			if ( gmpd.povLeft.down () )	 { SetGPI_Pov ( ret, i, POV_LEFT ); return ret;}

			//ボタン
			uint32 nBtn = 0;
			for ( s3d::Input ipt : gmpd.buttons )
			{
				if ( ipt.down () )
				{
					ret.SetBtn ( i, nBtn );
					return ret;
				}
				++ nBtn;
			}
		}

		return ret;
	}

	void SivGamePad::SetGPI_Lvr ( GamePadInput & ret, uint32 pad_id, LEVER_DIR lvr )
	{
		ret.SetLvr ( pad_id, lvr );
	}

	void SivGamePad::SetGPI_Axis ( GamePadInput & ret, uint32 pad_id, AXIS_VALUE axis )
	{
		ret.SetAxis ( pad_id, axis );
	}

	void SivGamePad::SetGPI_Pov ( GamePadInput & ret, uint32 pad_id, POV_VALUE pov )
	{
		ret.SetPov ( pad_id, pov );
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
#if 0

	//軸の状態を返す ( -1.0 < double < 1.0 )
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

#endif // 0

	//Axis:状態の判定 ( -1.0 < double < 1.0 )
	bool SivGamePad::IsAxisX_Plus( size_t id ) const
	{
		if ( m_impl[id].axes.size () <= AXIS_X ) { return F; }
		return ( m_impl[id].axes[AXIS_X] >= +1.0 );
	}
	bool SivGamePad::IsAxisX_Minus	( size_t id ) const
	{
		if ( m_impl[id].axes.size () <= AXIS_X ) { return F; }
		return ( m_impl[id].axes[AXIS_X] <= -1.0 );
	}

	bool SivGamePad::IsAxisY_Plus	( size_t id ) const
	{
		if ( m_impl[id].axes.size () <= AXIS_Y ) { return F; }
		return (m_impl[id].axes[AXIS_Y] >= +1.0);
	}
	bool SivGamePad::IsAxisY_Minus	( size_t id ) const
	{
		if ( m_impl[id].axes.size () <= AXIS_Y ) { return F; }
		return (m_impl[id].axes[AXIS_Y] <= -1.0);
	}

	bool SivGamePad::IsAxisZ_Plus( size_t id ) const
	{
		if ( m_impl[id].axes.size () <= AXIS_Z ) { return F; }
		return ( m_impl[id].axes[AXIS_Z] >= +1.0 );
	}
	bool SivGamePad::IsAxisZ_Minus	( size_t id ) const
	{
		if ( m_impl[id].axes.size () <= AXIS_Z ) { return F; }
		return ( m_impl[id].axes[AXIS_Z] <= -1.0 );
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

	bool SivGamePad::WasAxisX_Plus	( size_t id ) const
	{
		return m_pre_store[id].WasAxisX_Plus ();
	}
	bool SivGamePad::WasAxisX_Minus	( size_t id ) const
	{
		return m_pre_store[id].WasAxisX_Minus ();
	}

	bool SivGamePad::WasAxisY_Plus	( size_t id ) const
	{
		return m_pre_store[id].WasAxisY_Plus ();
	}
	bool SivGamePad::WasAxisY_Minus	( size_t id ) const
	{
		return m_pre_store[id].WasAxisY_Minus ();
	}

	bool SivGamePad::WasAxisZ_Plus	( size_t id ) const
	{
		return m_pre_store[id].WasAxisZ_Plus ();
	}
	bool SivGamePad::WasAxisZ_Minus	( size_t id ) const
	{
		return m_pre_store[id].WasAxisZ_Minus ();
	}


	//押した瞬間の判定(前回off 今回on)
	bool SivGamePad::PushAxisX_Plus ( size_t id ) const
	{
		return ( ! WasAxisX_Plus(id) && IsAxisX_Plus(id) );
	}
	bool SivGamePad::PushAxisX_Minus ( size_t id ) const
	{
		return ( ! WasAxisX_Minus(id) && IsAxisX_Minus(id) );
	}

	bool SivGamePad::PushAxisY_Plus ( size_t id ) const
	{
		return ( ! WasAxisY_Plus(id) && IsAxisY_Plus(id) );
	}
	bool SivGamePad::PushAxisY_Minus ( size_t id ) const
	{
		return ( ! WasAxisY_Minus(id) && IsAxisY_Minus(id) );
	}

	bool SivGamePad::PushAxisZ_Plus ( size_t id ) const
	{
		return ( ! WasAxisZ_Plus(id) && IsAxisZ_Plus(id) );
	}
	bool SivGamePad::PushAxisZ_Minus ( size_t id ) const
	{
		return ( ! WasAxisZ_Minus(id) && IsAxisZ_Minus(id) );
	}


	//離した瞬間の判定(前回on 今回off)
	bool SivGamePad::ReleAxisX_Plus ( size_t id ) const
	{
		return ( WasAxisX_Plus(id) && ! IsAxisX_Plus(id) );
	}
	bool SivGamePad::ReleAxisX_Minus ( size_t id ) const
	{
		return ( WasAxisX_Minus(id) && ! IsAxisX_Minus(id) );
	}

	bool SivGamePad::ReleAxisY_Plus ( size_t id ) const
	{
		return ( WasAxisY_Plus(id) && ! IsAxisY_Plus(id) );
	}
	bool SivGamePad::ReleAxisY_Minus ( size_t id ) const
	{
		return ( WasAxisY_Minus(id) && ! IsAxisY_Minus(id) );
	}

	bool SivGamePad::ReleAxisZ_Plus ( size_t id ) const
	{
		return ( WasAxisZ_Plus(id) && ! IsAxisZ_Plus(id) );
	}
	bool SivGamePad::ReleAxisZ_Minus ( size_t id ) const
	{
		return ( WasAxisZ_Minus(id) && ! IsAxisZ_Minus(id) );
	}


	//--------------------------------------------------------------
	//POV

	Optional < int32 > SivGamePad::GetPov ( size_t id ) const
	{
		const auto & gamepad = Gamepad ( id );
		if ( ! gamepad ) { return 0; }

		return gamepad.povD8 ();
	}


	//POVの状態 ( 真上から時計回りに 0, 1, 2, 3, 4, 5, 6, 7 )
	//※単一の値なので範囲で指定する
	bool SivGamePad::IsPovUp ( size_t id ) const
	{
		const detail::Gamepad_impl & gamepad = Gamepad ( id );
		if ( ! gamepad ) { return F; }

		//オプショナル(null許容)型 チェック
		Optional < int32 > pov = gamepad.povD8 ();
		if ( ! pov.has_value () ) { return F; }
		return ( 0 == pov ) || ( 7 == pov ) || ( 1 == pov );
	}


	bool SivGamePad::IsPovRight ( size_t id ) const
	{
		Optional < int32 > pov = Gamepad ( id ).povD8 ();
		if ( ! pov.has_value () ) { return F; }
		return ( 2 == pov ) || ( 1 == pov ) || ( 3 == pov );
	}

	bool SivGamePad::IsPovDown ( size_t id ) const
	{
		Optional < int32 > pov = Gamepad ( id ).povD8 ();
		if ( ! pov.has_value () ) { return F; }
		return ( 4 == pov ) || ( 3 == pov ) || ( 5 == pov );
	}

	bool SivGamePad::IsPovLeft ( size_t id )  const
	{
		Optional < int32 > pov = Gamepad ( id ).povD8 ();
		if ( ! pov.has_value () ) { return F; }
		return ( 6 == pov ) || ( 5 == pov ) || ( 7 == pov );
	}

	//-----------------------------------------------
	bool SivGamePad::WasPovUp ( size_t id ) const
	{
		Optional < int32 > pov = m_pre_store[id].PovD8 ();
		if ( ! pov.has_value () ) { return F; }
		return ( 0 == pov ) || ( 7 == pov ) || ( 1 == pov );
	}

	bool SivGamePad::WasPovRight ( size_t id ) const
	{
		Optional < int32 > pov = m_pre_store[id].PovD8 ();
		if ( ! pov.has_value () ) { return F; }
		return ( 2 == pov ) || ( 1 == pov ) || ( 3 == pov );
	}

	bool SivGamePad::WasPovDown ( size_t id ) const
	{
		Optional < int32 > pov = m_pre_store[id].PovD8 ();
		if ( ! pov.has_value () ) { return F; }
		return ( 4 == pov ) || ( 3 == pov ) || ( 5 == pov );
	}

	bool SivGamePad::WasPovLeft ( size_t id )  const
	{
		Optional < int32 > pov = m_pre_store[id].PovD8 ();
		if ( ! pov.has_value () ) { return F; }
		return ( 6 == pov ) || ( 5 == pov ) || ( 7 == pov );
	}


}	//namespace GAME


