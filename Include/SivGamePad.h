//=================================================================================================
//
//	Siv ゲームパッド
//		入力記録を毎フレームで記録し、押されている状態かどうかを取得する
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Define.h"
#include "DeviceInput.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//-----------------------------------------------------------
	//1[F]のゲームパッドの入力を保存する
	class GamePadInputStore
	{
		Array < bool > buttons;

		double axis_x { 0 };	//値の範囲は -1 <= n <= +1
		double axis_y { 0 };	//レバー遊びを除く確定値は -1.0, +1.0で判定
		double axis_z { 0 };

		bool povUp { F };
		bool povDown { F };
		bool povLeft { F };
		bool povRight { F };

		//POVの状態 ( 真上から時計回りに 0, 1, 2, 3, 4, 5, 6, 7 )
		s3d::Optional < int32 > povD8 { 0 };

	public :
		GamePadInputStore () {};
		GamePadInputStore ( const GamePadInputStore & rhs );	//コピー可(Array<T>)
		~GamePadInputStore () {};

		void Store ( const s3d::detail::Gamepad_impl & inp );


		double GetAxisX () const { return axis_x; }
		double GetAxisY () const { return axis_y; }
		double GetAxisZ () const { return axis_z; }

		bool WasBtn ( size_t nBtn ) const { return buttons [ nBtn ]; }
		size_t BtnSize () const { return buttons.size (); }

#if 0
		bool WasAxisUp () const { return axes_y <= -500; }
		bool WasAxisDown () const { return axes_y >= 500; }
		bool WasAxisLeft () const { return axes_x <= -500; }
		bool WasAxisRight () const { return axes_x >= 500; }
#endif // 0
		bool WasAxisX_Plus	() const { return axis_x >= +1.0; };
		bool WasAxisX_Minus	() const { return axis_x <= -1.0; };
		bool WasAxisY_Plus  () const { return axis_y >= +1.0; };
		bool WasAxisY_Minus	() const { return axis_y <= -1.0; };
		bool WasAxisZ_Plus	() const { return axis_z >= +1.0; };
		bool WasAxisZ_Minus	() const { return axis_z <= -1.0; };

		bool WasPovUp () const { return povUp; }
		bool WasPovDown () const { return povDown; }
		bool WasPovLeft () const { return povLeft; }
		bool WasPovRight () const { return povRight; }

		s3d::Optional < int32 > PovD8 () const { return povD8; }
	};
	//-----------------------------------------------------------

	using A_GMPD_S = s3d::Array < GamePadInputStore >;


	//@info Gamepad_implがSiv3Dの直接データ保存型
	//		前フレームの値を自前で保存し直すときにGamePadInputStoreを用いる


	using GMPD = s3d::detail::Gamepad_impl;
	using A_GMPD = s3d::Array < GMPD >;


	class SivGamePad
	{
		//状態の保存
		A_GMPD	m_impl { 0 };
//		A_GMPD	m_pre_impl { 0 };

		A_GMPD_S	m_pre_store { detail::Gamepad_helper::MaxPlayerCount }; 

	public:
		SivGamePad ();
		SivGamePad ( const SivGamePad & rhs ) = delete;
		~SivGamePad ();

		//--------------------------------------------------------------
		//ゲーム利用
		//状態の更新
		void Update();

		//状態の記録
		void Store();

		//状態の取得
		const GMPD &	GetState () const ;
		const GamePadInputStore & GetStore () const;

		//---------------------------------------------------------------------------
		//キーコンフィグ用
		//いずれかが押されていたら優先順で返す
		GamePadInput PushInput ();

		//--------------------------------------------------------------
		//ボタン

		//指定したボタンが押されている状態か
		bool IsButton( int id, int nButton ) const;
		//ひとつ前のフレームで指定したボタンが押されている状態か
		bool WasButton( int id, int nButton ) const;
		//指定したボタンが押された瞬間か
		bool PushButton( int id, int nButton ) const;
		//指定したボタンが離された瞬間か
		bool ReleButton( int id, int nButton ) const;


		//--------------------------------------------------------------
		//軸
#if 0
		//軸の状態を返す ( -1.0 < double < 1.0 )
		double GetJoyAxisX( size_t id ) const;
		double GetJoyAxisY( size_t id ) const;
		double GetJoyAxisZ( size_t id ) const;
#endif // 0

		//Axis:状態の判定  ( -1.0 < double < 1.0 )
		bool IsAxisX_Plus	( size_t id ) const;
		bool IsAxisX_Minus	( size_t id ) const;
		bool IsAxisY_Plus	( size_t id ) const;
		bool IsAxisY_Minus	( size_t id ) const;
		bool IsAxisZ_Plus	( size_t id ) const;
		bool IsAxisZ_Minus	( size_t id ) const;


		//前フレームの状態
#if 0
		bool WasAxisUp		( size_t id ) const;
		bool WasAxisDown	( size_t id ) const;
		bool WasAxisLeft	( size_t id ) const;
		bool WasAxisRight	( size_t id ) const;
#endif // 0
		bool WasAxisX_Plus	( size_t id ) const;
		bool WasAxisX_Minus	( size_t id ) const;
		bool WasAxisY_Plus	( size_t id ) const;
		bool WasAxisY_Minus	( size_t id ) const;
		bool WasAxisZ_Plus	( size_t id ) const;
		bool WasAxisZ_Minus	( size_t id ) const;


		//押した瞬間の判定(前回off 今回on)
		bool PushAxisX_Plus		( size_t id ) const;
		bool PushAxisX_Minus	( size_t id ) const;
		bool PushAxisY_Plus		( size_t id ) const;
		bool PushAxisY_Minus	( size_t id ) const;
		bool PushAxisZ_Plus		( size_t id ) const;
		bool PushAxisZ_Minus	( size_t id ) const;


		//離した瞬間の判定(前回on 今回off)
		bool ReleAxisX_Plus		( size_t id ) const;
		bool ReleAxisX_Minus	( size_t id ) const;
		bool ReleAxisY_Plus		( size_t id ) const;
		bool ReleAxisY_Minus	( size_t id ) const;
		bool ReleAxisZ_Plus		( size_t id ) const;
		bool ReleAxisZ_Minus	( size_t id ) const;


		//--------------------------------------------------------------
		//POVの状態を返す( 上方向から 左回りに 0, 9000, 18000, 27000 )
		//※斜めも単一の値を持つので範囲で指定する
		// (0,4500,9000,13500,18000,22500,27000,31500)

		Optional < int32 >	GetPov		( size_t id ) const;

		//押した状態
		bool IsPovUp	( size_t id ) const;
		bool IsPovRight	( size_t id ) const;
		bool IsPovDown	( size_t id ) const;
		bool IsPovLeft	( size_t id ) const;

		//前フレームの状態
		bool WasPovUp	( size_t id ) const;
		bool WasPovRight( size_t id ) const;
		bool WasPovDown	( size_t id ) const;
		bool WasPovLeft	( size_t id ) const;

		//押した瞬間の判定(前回off 今回on)
		bool PushPovUp		( size_t id ) const { return ( ! WasPovUp ( id )	&& IsPovUp ( id ) ); }
		bool PushPovRight	( size_t id ) const { return ( ! WasPovRight ( id )&& IsPovRight ( id ) ); }
		bool PushPovDown	( size_t id ) const { return ( ! WasPovDown ( id )	&& IsPovDown ( id ) ); }
		bool PushPovLeft	( size_t id ) const { return ( ! WasPovLeft ( id )	&& IsPovLeft ( id ) ); }

		//離した瞬間の判定(前回on 今回off)
		bool RelePovUp		( size_t id ) const { return ( WasPovUp ( id )		&& ! IsPovUp ( id ) ); }
		bool RelePovRight	( size_t id ) const { return ( WasPovRight ( id )	&& ! IsPovRight ( id ) ); }
		bool RelePovDown	( size_t id ) const { return ( WasPovDown ( id )	&& ! IsPovDown ( id ) ); }
		bool RelePovLeft	( size_t id ) const { return ( WasPovLeft ( id )	&& ! IsPovLeft ( id ) ); }


	private:
		//内部関数
		void SetGPI_Lvr ( GamePadInput& ret, uint32 pad_id, LEVER_DIR lvr );
		void SetGPI_Axis ( GamePadInput& ret, uint32 pad_id, AXIS_VALUE axis );
		void SetGPI_Pov ( GamePadInput& ret, uint32 pad_id, POV_VALUE pov );

	};


}
