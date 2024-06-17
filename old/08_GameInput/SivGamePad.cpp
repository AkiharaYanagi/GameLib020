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

	SivGamePad::SivGamePad()
	{
		uint32 MAX = detail::Gamepad_helper::MaxPlayerCount;
		for ( uint32 i = 0; i < MAX; ++ i )
		{
			m_impl.push_back ( Gamepad ( i ) );
			m_pre_impl.push_back ( Gamepad ( i ) );
		}
	}

	SivGamePad::~SivGamePad()
	{
	}



	//--------------------------------------------------------------------------
	//ゲーム利用
	//--------------------------------------------------------------------------
	void SivGamePad::Update()
	{
		//以前の状態を記録
#if 0
		uint32 index = 0; 
		for ( bool b : ma_keyState )
		{
			ma_preKeyState [ index ++ ] = b;
		}
#endif // 0

		uint32 MAX = detail::Gamepad_helper::MaxPlayerCount;
		for ( uint32 i = 0; i < MAX; ++ i )
		{
			m_pre_impl [ i ] = m_impl [ i ];
			m_impl [ i ] = Gamepad ( i );
		}


#if 0
		//キー状態の取得

		//メインオブジェクトから取得
		Array < Input > keys = Keyboard::GetAllInputs ();


		Array < Input >::iterator it = keys.begin ();

		//先頭から検索してコードが該当する箇所をTとする
		for ( uint8 i = 0; i < SIV_KEYBOARD_NUM; ++ i )
		{
			if ( it->code() == i )
			{
				ma_keyState [ i ] = T;
				++ it;
			}
			else
			{
				ma_keyState [ i ] = F;
			}
		}
#endif // 0
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
		if ( m_pre_impl[id].buttons.size () <= nButton ) { return F; }

		//指定したボタンが押されている状態は T
		return m_pre_impl[id].buttons [ nButton ].pressed ();
	}

	//指定したボタンが押された瞬間か
	bool SivGamePad::PushButton( int id, int nButton ) const
	{
		bool bIs = IsButton ( id, nButton );
		bool bWs = WasButton ( id, nButton );
		return bIs && ! bWs;
	}

	//指定したボタンが離された瞬間か
	bool SivGamePad::ReleaseButton( int id, int nButton ) const
	{
		bool bIs = IsButton ( id, nButton );
		bool bWs = WasButton ( id, nButton );
		return ! bIs && bWs;
	}

	//--------------------------------------------------------------
	//軸
	//軸の状態を返す
	double SivGamePad::GetJoyAxisX( int id ) const
	{
		return  m_impl[id].axes[0];
	}

	double SivGamePad::GetJoyAxisY( int id ) const
	{
		return  m_impl[id].axes[1];
	}

	double SivGamePad::GetJoyAxisZ( int id ) const
	{
		return  m_impl[id].axes[2];
	}

	//Axis:押した状態の判定
	bool SivGamePad::IsAxisUp	( int id ) const { return ( m_impl[id].axes[1] <= -500 );}
	bool SivGamePad::IsAxisDown	( int id ) const { return ( m_impl[id].axes[1] >=  500 ); }
	bool SivGamePad::IsAxisLeft	( int id ) const { return ( m_impl[id].axes[0] <= -500 ); }
	bool SivGamePad::IsAxisRight( int id ) const { return ( m_impl[id].axes[0] >=  500 ); }

	//前フレームの状態
	bool SivGamePad::WasAxisUp		( int id ) const { return ( m_pre_impl[id].axes[1] <= -500 ); }
	bool SivGamePad::WasAxisDown	( int id ) const { return ( m_pre_impl[id].axes[1] >=  500 ); }
	bool SivGamePad::WasAxisLeft	( int id ) const { return ( m_pre_impl[id].axes[0] <= -500 ); }
	bool SivGamePad::WasAxisRight	( int id ) const { return ( m_pre_impl[id].axes[0] >=  500 ); }


	//--------------------------------------------------------------
	//POV

	Optional < int32 > SivGamePad::GetPov ( int id ) const
	{
		const auto & gamepad = Gamepad ( id );
		if ( ! gamepad ) { return 0; }

		return gamepad.povD8 ();
	}


	//POVの状態を返す( 上から 0, 9000, 18000, 27000 )
	//※単一の値なので範囲で指定する
	// (0,4500,9000,13500,18000,22500,27000,31500)
	bool SivGamePad::IsPovUp ( int id ) const
	{
		const detail::Gamepad_impl & gamepad = Gamepad ( id );
		if ( ! gamepad ) { return F; }

		//オプショナル(null許容)型 チェック
		Optional < int32 > pov = gamepad.povD8 ();
		if ( pov ) { return F; }

		return ( 0 <= pov && pov <= 4500 ) || ( 31500 <= pov && pov <= 35999 );
	}


	bool SivGamePad::IsPovRight ( int id ) const
	{
		Optional < int32 > pov = Gamepad ( id ).povD8 ();
		return ( 4500 <= pov && pov <= 13500 );
	}

	bool SivGamePad::IsPovDown ( int id ) const
	{
		Optional < int32 > pov = Gamepad ( id ).povD8 ();
		return ( 13500 <= pov && pov <= 22500 );
	}

	bool SivGamePad::IsPovLeft ( int id )  const
	{
		Optional < int32 > pov = Gamepad ( id ).povD8 ();
		return ( 22500 <= pov && pov <= 31500 );
	}

	//-----------------------------------------------
	bool SivGamePad::WasPovUp ( int id ) const
	{
		Optional < int32 > pov = m_pre_impl[id].povD8 ();
		return ( 0 <= pov && pov <= 4500 ) || ( 31500 <= pov && pov <= 35999 );
	}

	bool SivGamePad::WasPovRight ( int id ) const
	{
		Optional < int32 > pov = m_pre_impl[id].povD8 ();
		return ( 4500 <= pov && pov <= 13500 );
	}

	bool SivGamePad::WasPovDown ( int id ) const
	{
		Optional < int32 > pov = m_pre_impl[id].povD8 ();
		return ( 13500 <= pov && pov <= 22500 );
	}

	bool SivGamePad::WasPovLeft ( int id )  const
	{
		Optional < int32 > pov = m_pre_impl[id].povD8 ();
		return ( 22500 <= pov && pov <= 31500 );
	}



}	//namespace GAME


