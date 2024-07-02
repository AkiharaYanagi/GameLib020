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
	//	ジョイスティックで押されている状態かどうかを取得する
	bool SivInput::IsJoyButton ( int id, int btn ) const { return m_gamepad.IsButton ( id, btn ); }

	bool SivInput::IsAxisUp(int id) const { return m_gamepad.IsAxisUp ( id ); }
	bool SivInput::IsAxisDown(int id) const { return m_gamepad.IsAxisDown ( id ); }
	bool SivInput::IsAxisLeft(int id) const { return m_gamepad.IsAxisLeft ( id ); }
	bool SivInput::IsAxisRight(int id) const { return m_gamepad.IsAxisRight ( id ); }

	bool SivInput::IsPovUp(int id) const { return m_gamepad.IsPovUp ( id ); }
	bool SivInput::IsPovDown(int id) const { return m_gamepad.IsPovDown ( id ); }
	bool SivInput::IsPovLeft(int id) const { return m_gamepad.IsPovLeft ( id ); }
	bool SivInput::IsPovRight(int id) const { return m_gamepad.IsPovRight ( id ); }

	//	ジョイスティックで押された瞬間かどうかを取得する
	bool SivInput::PushJoyButton ( int id, int btn ) const { return m_gamepad.PushButton ( id, btn ); }

	bool SivInput::PushAxisUp(int id) const { return m_gamepad.PushAxisUp ( id ); }
	bool SivInput::PushAxisDown(int id) const { return m_gamepad.PushAxisDown ( id ); }
	bool SivInput::PushAxisLeft(int id) const { return m_gamepad.PushAxisLeft ( id ); }
	bool SivInput::PushAxisRight(int id) const { return m_gamepad.PushAxisRight ( id ); }

	bool SivInput::PushPovUp(int id) const { return m_gamepad.PushPovUp ( id ); }
	bool SivInput::PushPovDown(int id) const { return m_gamepad.PushPovDown ( id ); }
	bool SivInput::PushPovLeft(int id) const { return m_gamepad.PushPovLeft ( id ); }
	bool SivInput::PushPovRight(int id) const { return m_gamepad.PushPovRight ( id ); }

	//	ジョイスティックで離された瞬間かどうかを取得する
	bool SivInput::ReleJoyButton ( int id, int btn ) const { return m_gamepad.ReleButton ( id, btn ); }

	bool SivInput::ReleAxisUp(int id) const { return m_gamepad.ReleAxisUp ( id ); }
	bool SivInput::ReleAxisDown(int id) const { return m_gamepad.ReleAxisDown ( id ); }
	bool SivInput::ReleAxisLeft(int id) const { return m_gamepad.ReleAxisLeft ( id ); }
	bool SivInput::ReleAxisRight(int id) const { return m_gamepad.ReleAxisRight ( id ); }

	bool SivInput::RelePovUp(int id) const { return m_gamepad.RelePovUp ( id ); }
	bool SivInput::RelePovDown(int id) const { return m_gamepad.RelePovDown ( id ); }
	bool SivInput::RelePovLeft(int id) const { return m_gamepad.RelePovLeft ( id ); }
	bool SivInput::RelePovRight(int id) const { return m_gamepad.RelePovRight ( id ); }


	//軸の状態を返す
	double SivInput::GetJoyAxisX(int id) const { return m_gamepad.GetJoyAxisX ( id ); }
	double SivInput::GetJoyAxisY(int id) const { return m_gamepad.GetJoyAxisY ( id ); }
	double SivInput::GetJoyAxisZ(int id) const { return m_gamepad.GetJoyAxisZ ( id ); }


	//POVの状態を返す
	Optional < int32 > SivInput::GetPov(int id) const { return m_gamepad.GetPov ( id ); }
}

