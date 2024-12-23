//=================================================================================================
//
// Sivインプット 実装
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "SivInput.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//------------------------------------------
	//	Static実体
	//------------------------------------------
	//	シングルトン　インスタンス
	SivInput::P_SivInput	SivInput::m_inst;



	//-------------------------------------------------------------------------------------------------
	//	フレーム毎の更新
	//-------------------------------------------------------------------------------------------------
	//毎回の更新
	void SivInput::Update ()
	{
		m_keyboard.Update ();		//キーボードデバイス
		m_gamepad.Update ();			//ゲームパッド
	}

	//状態の記録
	void SivInput::Store ()
	{
		//キーボードはUpdateで状態の記録も行う
		m_gamepad.Store ();			//ゲームパッド
	}

	//---------------------------------------------------------------------------
	//キーコンフィグ用
	//いずれかが押されていたら優先順で返す
	DeviceInput SivInput::PushInput ()
	{
		DeviceInput di;

		//ゲームパッド
		GamePadInput gpi = m_gamepad.PushInput ();
		if ( gpi.GetInputType () != PIT_NO_DATA )
		{
			di.SetPad ( gpi );
		}

		//キーボード
		KEY_NAME key = m_keyboard.WhichInput ();
		if ( key != SIK_NODATA )
		{
			di.SetKeyboard ( key );
		}

		return di;
	}


	//-------------------------------------------------------------------------------------------------
	//	ゲームパッドで押されている状態かどうかを取得する
	bool SivInput::IsJoyButton ( int id, int btn ) const { return m_gamepad.IsButton ( id, btn ); }

#if 0
	bool SivInput::IsAxisUp(int id) const { return m_gamepad.IsAxisUp ( id ); }
	bool SivInput::IsAxisDown(int id) const { return m_gamepad.IsAxisDown ( id ); }
	bool SivInput::IsAxisLeft(int id) const { return m_gamepad.IsAxisLeft ( id ); }
	bool SivInput::IsAxisRight(int id) const { return m_gamepad.IsAxisRight ( id ); }
#endif // 0

	bool SivInput::IsAxisX_Plus ( int id ) const { return m_gamepad.IsAxisX_Plus ( id ); }
	bool SivInput::IsAxisX_Minus ( int id ) const { return m_gamepad.IsAxisX_Minus ( id ); }
	bool SivInput::IsAxisY_Plus ( int id ) const { return m_gamepad.IsAxisY_Plus ( id ); }
	bool SivInput::IsAxisY_Minus ( int id ) const { return m_gamepad.IsAxisY_Minus ( id ); }
	bool SivInput::IsAxisZ_Plus ( int id ) const { return m_gamepad.IsAxisZ_Plus ( id ); }
	bool SivInput::IsAxisZ_Minus ( int id ) const { return m_gamepad.IsAxisZ_Minus ( id ); }

	bool SivInput::IsPovUp(int id) const { return m_gamepad.IsPovUp ( id ); }
	bool SivInput::IsPovDown(int id) const { return m_gamepad.IsPovDown ( id ); }
	bool SivInput::IsPovLeft(int id) const { return m_gamepad.IsPovLeft ( id ); }
	bool SivInput::IsPovRight(int id) const { return m_gamepad.IsPovRight ( id ); }

	//	ゲームパッドで押された瞬間かどうかを取得する
	bool SivInput::PushJoyButton ( int id, int btn ) const { return m_gamepad.PushButton ( id, btn ); }

#if 0
	bool SivInput::PushAxisUp(int id) const { return m_gamepad.PushAxisUp ( id ); }
	bool SivInput::PushAxisDown(int id) const { return m_gamepad.PushAxisDown ( id ); }
	bool SivInput::PushAxisLeft(int id) const { return m_gamepad.PushAxisLeft ( id ); }
	bool SivInput::PushAxisRight(int id) const { return m_gamepad.PushAxisRight ( id ); }
#endif // 0

	bool SivInput::PushAxisX_Plus ( int id ) const { return m_gamepad.PushAxisX_Plus ( id ); }
	bool SivInput::PushAxisX_Minus ( int id ) const { return m_gamepad.PushAxisX_Minus ( id ); }
	bool SivInput::PushAxisY_Plus ( int id ) const { return m_gamepad.PushAxisY_Plus ( id ); }
	bool SivInput::PushAxisY_Minus ( int id ) const { return m_gamepad.PushAxisY_Minus ( id ); }
	bool SivInput::PushAxisZ_Plus ( int id ) const { return m_gamepad.PushAxisZ_Plus ( id ); }
	bool SivInput::PushAxisZ_Minus ( int id ) const { return m_gamepad.PushAxisZ_Minus ( id ); }

	bool SivInput::PushPovUp(int id) const { return m_gamepad.PushPovUp ( id ); }
	bool SivInput::PushPovDown(int id) const { return m_gamepad.PushPovDown ( id ); }
	bool SivInput::PushPovLeft(int id) const { return m_gamepad.PushPovLeft ( id ); }
	bool SivInput::PushPovRight(int id) const { return m_gamepad.PushPovRight ( id ); }

	//	ゲームパッドで離された瞬間かどうかを取得する
	bool SivInput::ReleJoyButton ( int id, int btn ) const { return m_gamepad.ReleButton ( id, btn ); }

#if 0
	bool SivInput::ReleAxisUp(int id) const { return m_gamepad.ReleAxisUp ( id ); }
	bool SivInput::ReleAxisDown(int id) const { return m_gamepad.ReleAxisDown ( id ); }
	bool SivInput::ReleAxisLeft(int id) const { return m_gamepad.ReleAxisLeft ( id ); }
	bool SivInput::ReleAxisRight(int id) const { return m_gamepad.ReleAxisRight ( id ); }
#endif // 0

	bool SivInput::ReleAxisX_Plus ( int id ) const { return m_gamepad.ReleAxisX_Plus ( id ); }
	bool SivInput::ReleAxisX_Minus ( int id ) const { return m_gamepad.ReleAxisX_Minus ( id ); }
	bool SivInput::ReleAxisY_Plus ( int id ) const { return m_gamepad.ReleAxisY_Plus ( id ); }
	bool SivInput::ReleAxisY_Minus ( int id ) const { return m_gamepad.ReleAxisY_Minus ( id ); }
	bool SivInput::ReleAxisZ_Plus ( int id ) const { return m_gamepad.ReleAxisZ_Plus ( id ); }
	bool SivInput::ReleAxisZ_Minus ( int id ) const { return m_gamepad.ReleAxisZ_Minus ( id ); }

	bool SivInput::RelePovUp(int id) const { return m_gamepad.RelePovUp ( id ); }
	bool SivInput::RelePovDown(int id) const { return m_gamepad.RelePovDown ( id ); }
	bool SivInput::RelePovLeft(int id) const { return m_gamepad.RelePovLeft ( id ); }
	bool SivInput::RelePovRight(int id) const { return m_gamepad.RelePovRight ( id ); }

#if 0

	//軸の状態を返す
	double SivInput::GetJoyAxisX(int id) const { return m_gamepad.GetJoyAxisX ( id ); }
	double SivInput::GetJoyAxisY(int id) const { return m_gamepad.GetJoyAxisY ( id ); }
	double SivInput::GetJoyAxisZ(int id) const { return m_gamepad.GetJoyAxisZ ( id ); }

#endif // 0


	//POVの状態を返す
	Optional < int32 > SivInput::GetPov(int id) const { return m_gamepad.GetPov ( id ); }
}

