//=================================================================================================
//
//	Sivインプット
//		入力記録を毎フレームで記録し、押されている状態かどうかを取得する
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Define.h"
#include "SivKeyboard.h"
#include "SivGamePad.h"
#include "DeviceInput.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class SivInput
	{
	//---------------------------------------------------------------------
	//シングルトン　パターン
	private:
		using P_SivInput = std::unique_ptr < SivInput >;	//ポインタ型定義
		static P_SivInput	m_inst;		//シングルトンインスタンス(実体は.cppで定義)
		SivInput () {}		//private コンストラクタで通常の実体化は禁止
	public:
		~SivInput (){}		//デストラクタはstd::unique_ptrのためpublic
		static void Create () { if ( ! m_inst ) { m_inst = P_SivInput ( new SivInput () ); } }
		static P_SivInput & Inst () { return m_inst; }
	//---------------------------------------------------------------------

		//キーボード
		SivKeyboard		m_keyboard;

		//ゲームパッド
		SivGamePad		m_gamepad;

	public:

		//---------------------------------------------------------------------------
		//毎回の更新
//		void Update ( const Array < s3d::Input > & keys );
		void Update ();

		//---------------------------------------------------------------------------
		//キーコンフィグ用
		//いずれかが押されていたら優先順で返す
		DeviceInput PushInput ();

		//---------------------------------------------------------------------------
		//キーボード
		//---------------------------------------------------------------------------
		bool Is_Keyboard ( KEY_NAME k ) { return m_keyboard.IsKey(k); }
		bool Push_Keyboard ( KEY_NAME k ) { return m_keyboard.PushKey(k); }
		bool Rele_Keyboard(KEY_NAME k) { return m_keyboard.ReleaseKey(k); }

		//---------------------------------------------------------------------------
		//ゲームパッド
		//---------------------------------------------------------------------------
		//	ジョイスティックで押されている状態かどうかを取得する
		//	引数：num デバイス番号, btn キー番号
		bool IsJoyButton ( int id, int btn ) const;

		bool IsAxisUp(int nDevice) const;
		bool IsAxisDown(int nDevice) const;
		bool IsAxisLeft(int nDevice) const;
		bool IsAxisRight(int nDevice) const;

		bool IsPovUp(int nDevice) const;
		bool IsPovRight(int nDevice) const;
		bool IsPovDown(int nDevice) const;
		bool IsPovLeft(int nDevice) const;

		//	ジョイスティックで押された瞬間かどうかを取得する
		//	引数：num デバイス番号, btn キー番号
		bool PushJoyButton(int num, int btn) const;

		bool PushAxisUp(int id) const;
		bool PushAxisDown(int id) const;
		bool PushAxisLeft(int id) const;
		bool PushAxisRight(int id) const;

		bool PushPovUp(int id) const;
		bool PushPovRight(int id) const;
		bool PushPovDown(int id) const;
		bool PushPovLeft(int id) const;

		//	ジョイスティックで離された瞬間かどうかを取得する
		//	引数：num デバイス番号, btn キー番号
		bool ReleJoyButton(int num, int btn) const;

		bool ReleAxisUp(int id) const;
		bool ReleAxisDown(int id) const;
		bool ReleAxisLeft(int id) const;
		bool ReleAxisRight(int id) const;

		bool RelePovUp(int id) const;
		bool RelePovRight(int id) const;
		bool RelePovDown(int id) const;
		bool RelePovLeft(int id) const;

		//軸の状態を返す
		double GetJoyAxisX(int id) const;
		double GetJoyAxisY(int id) const;
		double GetJoyAxisZ(int id) const;

		//POVの状態を返す
		Optional < int32 > GetPov(int id) const;


#if 0
		//---------------------------------------------------------------------------
		//	マウス
		//---------------------------------------------------------------------------
		//マウスボタン定数
		enum MOUSE_BUTTON
		{
			MOUSE_LEFT = 0,
			MOUSE_RIGHT = 1,
			MOUSE_CENTER = 2,
		};
		//ボタンを押した状態かどうか
		//	0: LBUTTON, 1: RBUTTON, 2: ホイールクリック
		bool IsMouseButton(MOUSE_BUTTON n) const;

		//いずれかのキーが押されている状態から離されたかどうか
		//	0: LBUTTON, 1: RBUTTON, 2: ホイールクリック
		bool UpMouseButton(MOUSE_BUTTON n) const;
		bool UpMouseLeft() { return UpMouseButton(MOUSE_LEFT); }
		bool UpMouseRight() { return UpMouseButton(MOUSE_RIGHT); }
		bool UpMouseCenter() { return UpMouseButton(MOUSE_CENTER); }

		//マウスの移動量を取得
		POINT GetMouseDelta() const;

		//マウスのクライアントウィンドウ内の位置を取得
		POINT GetMousePoint() const;

		//対象の枠内にマウス位置があるかどうか
		bool IsMouseInside(LONG x, LONG y, LONG w, LONG h) const;
#endif // 0

	};


#define	SVINP	SivInput::Inst()


}

