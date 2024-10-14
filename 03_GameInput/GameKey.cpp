//=================================================================================================
//
// GameKey ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "GameKey.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	GameKey::GameKey ()
	{
		for ( UINT i = 0; i < LVR_NUM; ++ i )
		{
			Lvr[i] = false;
			PreLvr[i] = false;
		}
		for ( UINT i = 0; i < BTN_NUM; ++ i )
		{
			Btn[i] = false;
			PreBtn[i] = false;
		}
	}

	GameKey::GameKey ( const GameKey & rhs )
	{
		for ( UINT i = 0; i < LVR_NUM; ++ i )
		{
			Lvr[i] = rhs.Lvr[i];
			PreLvr[i] = rhs.PreLvr[i];
		}
		for ( UINT i = 0; i < BTN_NUM; ++ i )
		{
			Btn[i] = rhs.Btn[i];
			PreBtn[i] = rhs.PreBtn[i];
		}
	}

	GameKey::~GameKey ()
	{

	}

	void GameKey::ClearKey ()
	{
		for ( UINT i = 0; i < LVR_NUM; ++ i )
		{
			Lvr[i] = false;
			PreLvr[i] = false;
		}
		for ( UINT i = 0; i < BTN_NUM; ++ i )
		{
			Btn[i] = false;
			PreBtn[i] = false;
		}
	}

#if 0

	void GameKey::Update ()
	{
		//末尾から先頭に向けて上書きしていく
		for ( UINT i = _LVR_NUM - 1; i > 0; -- i )
		{
			PreLvr [ i ] = Lvr [ i - 1 ];
		}
		//先頭は手動で初期化
		Lvr[0] = false;
	}

#endif // 0

	void GameKey::ReservePrevious ( const GameKey gkPrev )
	{
		for ( UINT i = 0; i < LVR_NUM; ++ i )
		{
			PreLvr[i] = gkPrev.Lvr[i];
		}
		for ( UINT i = 0; i < BTN_NUM; ++ i )
		{
			PreBtn[i] = gkPrev.Btn[i];
		}
	}

	void GameKey::SetLvrOff ()
	{
		for ( UINT i = 0; i < LVR_NUM; ++ i )
		{
			Lvr[i] = false;
		}
	}


}	//namespace GAME

