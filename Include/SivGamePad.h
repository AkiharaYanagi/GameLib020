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

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	using GMPD = detail::Gamepad_impl;
	using A_GMPD = Array < GMPD >;


	class SivGamePad
	{
		//状態の保存
		A_GMPD	m_impl { 0 };
		A_GMPD	m_pre_impl { 0 };

	public:
		SivGamePad ();
		SivGamePad ( const SivGamePad & rhs ) = delete;
		~SivGamePad ();

		//--------------------------------------------------------------
		//ゲーム利用
		//状態の更新
		void Update();

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
		//軸の状態を返す
		double GetJoyAxisX( int id ) const;
		double GetJoyAxisY( int id ) const;
		double GetJoyAxisZ( int id ) const;

		//Axis:押した状態の判定
		bool IsAxisUp	( int id ) const;
		bool IsAxisDown	( int id ) const;
		bool IsAxisLeft	( int id ) const;
		bool IsAxisRight( int id ) const;

		//前フレームの状態
		bool WasAxisUp		( int id ) const;
		bool WasAxisDown	( int id ) const;
		bool WasAxisLeft	( int id ) const;
		bool WasAxisRight	( int id ) const;

		//押した瞬間の判定(前回off 今回on)
		bool PushAxisUp		( int id ) const { return ( ! WasAxisUp(id)    && IsAxisUp(id)    ); }
		bool PushAxisDown	( int id ) const { return ( ! WasAxisDown(id)  && IsAxisDown(id)  ); }
		bool PushAxisLeft	( int id ) const { return ( ! WasAxisLeft(id)  && IsAxisLeft(id)  ); }
		bool PushAxisRight	( int id ) const { return ( ! WasAxisRight(id) && IsAxisRight(id) ); }

		//離した瞬間の判定(前回on 今回off)
		bool ReleAxisUp   ( int id ) const { return ( WasAxisUp(id)    && ! IsAxisUp(id)    ); }
		bool ReleAxisDown ( int id ) const { return ( WasAxisDown(id)  && ! IsAxisDown(id)  ); }
		bool ReleAxisLeft ( int id ) const { return ( WasAxisLeft(id)  && ! IsAxisLeft(id)  ); }
		bool ReleAxisRight( int id ) const { return ( WasAxisRight(id) && ! IsAxisRight(id) ); }

		//--------------------------------------------------------------
		//POVの状態を返す( 上方向から 左回りに 0, 9000, 18000, 27000 )
		//※斜めも単一の値を持つので範囲で指定する
		// (0,4500,9000,13500,18000,22500,27000,31500)

		Optional < int32 >	GetPov		( int id ) const;

		//押した状態
		bool IsPovUp	( int id ) const;
		bool IsPovRight	( int id ) const;
		bool IsPovDown	( int id ) const;
		bool IsPovLeft	( int id ) const;

		//前フレームの状態
		bool WasPovUp	( int id ) const;
		bool WasPovRight( int id ) const;
		bool WasPovDown	( int id ) const;
		bool WasPovLeft	( int id ) const;

		//押した瞬間の判定(前回off 今回on)
		bool PushPovUp		( int id ) const { return ( ! WasPovUp ( id )	&& IsPovUp ( id ) ); }
		bool PushPovRight	( int id ) const { return ( ! WasPovRight ( id )&& IsPovRight ( id ) ); }
		bool PushPovDown	( int id ) const { return ( ! WasPovDown ( id )	&& IsPovDown ( id ) ); }
		bool PushPovLeft	( int id ) const { return ( ! WasPovLeft ( id )	&& IsPovLeft ( id ) ); }

		//離した瞬間の判定(前回on 今回off)
		bool RelePovUp		( int id ) const { return ( WasPovUp ( id )		&& ! IsPovUp ( id ) ); }
		bool RelePovRight	( int id ) const { return ( WasPovRight ( id )	&& ! IsPovRight ( id ) ); }
		bool RelePovDown	( int id ) const { return ( WasPovDown ( id )	&& ! IsPovDown ( id ) ); }
		bool RelePovLeft	( int id ) const { return ( WasPovLeft ( id )	&& ! IsPovLeft ( id ) ); }
	};
}
