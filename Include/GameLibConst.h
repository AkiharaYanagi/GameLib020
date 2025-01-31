//=================================================================================================
//
// GameLibConst ファイル
//		ライブラリ内共通定義
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
//	インクルードファイル
//-------------------------------------------------------------------------------------------------
# include <Siv3D.hpp> // Siv3D v0.6.13


//-------------------------------------------------------------------------------------------------
//	定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//------------------------------------------
	// 定数宣言
	//------------------------------------------
	
	//ウィンドウサイズ(表示上・変更可能)
	const s3d::uint32 WINDOW_WIDTH = 1280;
	const s3d::uint32 WINDOW_HEIGHT = 960;

	//ゲームシーンサイズ(原寸・書込対象)
	const s3d::uint32 GAME_WINDOW_WIDTH = 1280;
	const s3d::uint32 GAME_WINDOW_HEIGHT = 960;

	//プレイヤーID
	enum PLAYER_ID
	{
		PLAYER_ID_1 = 1,
		PLAYER_ID_2 = 2,
		_PLAYER_NUM = 3,	//人数+1
	};

	//プレイヤ種類
	enum PLAYER_MODE
	{
		MODE_PLAYER,
		MODE_CPU,
		MODE_NETWORK,
	};

	//対戦 組み合わせ 種類
	enum MUTCH_MODE
	{
		MODE_PLAYER_PLAYER,
		MODE_PLAYER_CPU,
		MODE_CPU_PLAYER,
		MODE_CPU_CPU,
		MODE_PLAYER_NETWORK,
	};

	//ゲームモード
	enum GAME_MODE
	{
		MODE_MAIN,		//対人(メイン)
		MODE_TRAINING,	//トレーニング
	};

}

