﻿//=================================================================================================
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

		double axes_x { 0 };
		double axes_y { 0 };
		double axes_z { 0 };

		bool povUp { F };
		bool povDown { F };
		bool povLeft { F };
		bool povRight { F };
		s3d::Optional < int32 > povD8 { 0 };

	public :
		GamePadInputStore () {};
		GamePadInputStore ( const GamePadInputStore & rhs );	//コピー可(Array<T>)
		~GamePadInputStore () {};

		void Store ( const s3d::detail::Gamepad_impl & inp );

		bool WasBtn ( size_t nBtn ) const { return buttons [ nBtn ]; }
		size_t BtnSize () const { return buttons.size (); }

#if 0
		bool WasAxisUp () const { return axes_y <= -500; }
		bool WasAxisDown () const { return axes_y >= 500; }
		bool WasAxisLeft () const { return axes_x <= -500; }
		bool WasAxisRight () const { return axes_x >= 500; }
#endif // 0
		bool WasAxisY_Minus	() const { return axes_y <= -0.500; };
		bool WasAxisY_Plus  () const { return axes_y >= +0.500; };
		bool WasAxisX_Minus	() const { return axes_x <= -0.500; };
		bool WasAxisX_Plus	() const { return axes_x >= +0.500; };
		bool WasAxisZ_Minus	() const { return axes_z <= -0.500; };
		bool WasAxisZ_Plus	() const { return axes_z >= +0.500; };

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
		// 
		//軸の状態を返す ( -1.0 < double < 1.0 )
		double GetJoyAxisX( size_t id ) const;
		double GetJoyAxisY( size_t id ) const;
		double GetJoyAxisZ( size_t id ) const;

		//Axis:押した状態の判定
		bool IsAxisY_Minus	( size_t id ) const;	//上
		bool IsAxisY_Plus	( size_t id ) const;	//下
		bool IsAxisX_Minus	( size_t id ) const;	//左
		bool IsAxisX_Plus	( size_t id ) const;	//右
		bool IsAxisZ_Minus	( size_t id ) const;
		bool IsAxisZ_Plus	( size_t id ) const;


		//前フレームの状態
#if 0
		bool WasAxisUp		( size_t id ) const;
		bool WasAxisDown	( size_t id ) const;
		bool WasAxisLeft	( size_t id ) const;
		bool WasAxisRight	( size_t id ) const;
#endif // 0
		bool WasAxisY_Minus	( size_t id ) const;	//上
		bool WasAxisY_Plus	( size_t id ) const;	//下
		bool WasAxisX_Minus	( size_t id ) const;	//左
		bool WasAxisX_Plus	( size_t id ) const;	//右
		bool WasAxisZ_Minus	( size_t id ) const;
		bool WasAxisZ_Plus	( size_t id ) const;


		//押した瞬間の判定(前回off 今回on)
#if 0
		bool PushAxisUp		( size_t id ) const { return ( ! WasAxisUp(id)    && IsAxisUp(id)    ); }
		bool PushAxisDown	( size_t id ) const { return ( ! WasAxisDown(id)  && IsAxisDown(id)  ); }
		bool PushAxisLeft	( size_t id ) const { return ( ! WasAxisLeft(id)  && IsAxisLeft(id)  ); }
		bool PushAxisRight	( size_t id ) const { return ( ! WasAxisRight(id) && IsAxisRight(id) ); }
#endif // 0
		bool PushAxisY_Minus	( size_t id ) const;	//上
		bool PushAxisY_Plus		( size_t id ) const;	//下
		bool PushAxisX_Minus	( size_t id ) const;	//左
		bool PushAxisX_Plus		( size_t id ) const;	//右
		bool PushAxisZ_Minus	( size_t id ) const;
		bool PushAxisZ_Plus		( size_t id ) const;


		//離した瞬間の判定(前回on 今回off)
#if 0
		bool ReleAxisUp   ( size_t id ) const { return ( WasAxisUp(id)    && ! IsAxisUp(id)    ); }
		bool ReleAxisDown ( size_t id ) const { return ( WasAxisDown(id)  && ! IsAxisDown(id)  ); }
		bool ReleAxisLeft ( size_t id ) const { return ( WasAxisLeft(id)  && ! IsAxisLeft(id)  ); }
		bool ReleAxisRight( size_t id ) const { return ( WasAxisRight(id) && ! IsAxisRight(id) ); }
#endif // 0
		bool ReleAxisY_Minus	( size_t id ) const;	//上
		bool ReleAxisY_Plus		( size_t id ) const;	//下
		bool ReleAxisX_Minus	( size_t id ) const;	//左
		bool ReleAxisX_Plus		( size_t id ) const;	//右
		bool ReleAxisZ_Minus	( size_t id ) const;
		bool ReleAxisZ_Plus		( size_t id ) const;


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
		void SetGPI_POV ( GamePadInput& ret, uint32 pad_id, LEVER_DIR dir );
		void SetGPI_Axis ( GamePadInput& ret, uint32 pad_id, LEVER_DIR dir );

	};


}
