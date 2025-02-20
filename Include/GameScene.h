//=================================================================================================
//
// ゲームシーン　ヘッダ
//		遷移時にデータの生成と破棄をする状態遷移
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダのインクルード
//-------------------------------------------------------------------------------------------------
//#include "DebugManager.h"
#include "GameTask.h"
//#include "GameParam.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//------------------------------------------------------------------
	//シーンを越えて扱うパラメータ
//	class GameParam {};
	class GameParam;
	using P_GameParam = std::shared_ptr < GameParam >;
	//------------------------------------------------------------------


	//------------------------------------------------------------------
	//	ゲームシーン
	//		TaskArrayを継承し、再帰的にタスク処理ができるようにしたGameState
	//		・多量のデータを持って移項する単位
	//		・シーンの移動時にオブジェクトの全解放、全確保。ただしm_pParamは次のシーンへ移譲
	//		※thisの取得のため、enable_shared_from_this < GameScene >を多重継承
	//		shared_from_thisを用いるのでstd::unique_ptrにはしない
	//------------------------------------------------------------------
//	class GameScene : public GameTaskVector, public enable_shared_from_this < GameScene >
	class GameScene : public GameTaskVector
	{
		//シーン共通パラメータ
		P_GameParam		m_pParam;

	public:
		GameScene () = default;
		GameScene ( const GameScene & rhs ) = delete;
		~GameScene () = default;

		//パラメータを用いた初期化インターフェース
		//パラメータの取得のあとの呼出1回保証 ( ParamInit(), Load(), Init() の順番 )
		//ParamInit()とは異なりデバイスリセットでも呼ばれない
		//Load()はデバイスリセットの度に呼ばれる
		//Init()は複数回呼ばれる可能性がある
		virtual void ParamInit () = 0;

		//遷移条件
		//@info	thisを自身に保存すると循環参照となるのでweak_ptrを用いる
		//基本の戻値は return shared_from_this();
		//内部で条件を確認し、遷移時は遷移先のオブジェクトを
		//	std::make_shared < GameScene > () して返す
		virtual std::shared_ptr < GameScene > Transit () = 0;

		//シーン共通パラメータ
		void SetpParam ( P_GameParam && pParam ) { m_pParam = pParam; }
//		void SetpParam ( P_GameParam pParam ) { m_pParam = pParam; }
		P_GameParam GetpParam () { return m_pParam; }
	};

	using P_GameScene = std::shared_ptr < GameScene >;
	using WP_GameScene = std::weak_ptr < GameScene >;

	//------------------------------------------------------------------
	//	ゲームシーンマネージャ
	//------------------------------------------------------------------
	class GameSceneManager : public GameTaskVector
	{
		P_GameScene		m_pScene;

	public:
		GameSceneManager ();
		GameSceneManager ( const GameSceneManager & rhs ) = delete;
		virtual ~GameSceneManager ();

		void Move ();		//フレーム毎動作と遷移チェック

		//シーンの設定
		void SetScene ( P_GameScene p ) { m_pScene = p; AddpTask ( m_pScene ); }
		P_GameScene GetpScene () { return m_pScene; }

		//遷移
		virtual void Transit ();
	};

	using SCENE_MGR = GameSceneManager;


}	//namespace GAME

