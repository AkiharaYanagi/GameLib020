﻿//=================================================================================================
//
// ゲームタスク　ヘッダ
//		ゲームに用いる基本オブジェクト構造の定義
//
//		ゲームタスク		：ゲームメインに用いるオブジェクトの基本型で最小単位。
//		ゲームタスクベクタ	：タスクを再帰的に保持し、フレーム毎でゲームタスクの基本インターフェースを一括して行う配列
//		ゲームタスクリスト	：生成、削除が多いときに用いる
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイル　インクルード
//-------------------------------------------------------------------------------------------------
#include "Define.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//=========================================================================
	// ゲームタスク
	//=========================================================================
	class GameTask
	{
	public:
		GameTask () = default;
		GameTask ( const GameTask& rhs ) = delete;
		virtual ~GameTask () = default;

		//共通動作
		//定義無しでも用いるため純粋仮想関数にはしない
		virtual void Load () {}		//読込(初回、または再設定時などの解放後１回のみ)
		virtual void Rele () {}		//動的な一時領域の解放(恒常的なメモリ確保はコンストラクタ～デストラクタで行う)
		virtual void Reset () {}	//再設定( Rele(); Load(); Init(); )

		virtual void Init () {}		//初期化(繰り返してもよい)
		virtual void Move () {}		//フレーム毎動作

		//->描画はGraphicListに移項
		//	ただし、テクスチャはグラフィックタスク以外でも読み込むため
		//	Load(),Rele(),Reset()は定義しておく
	};

	//型定義
	using P_Task = std::shared_ptr < GameTask >;
	using VP_Task = std::vector < P_Task >;
	using PVP_Task = std::shared_ptr < VP_Task >;
	using LP_Task = std::list < P_Task >;
	using PLP_Task = std::shared_ptr < LP_Task >;


	//=========================================================================
	// ゲームタスクベクタ
	//	ゲームタスクの基本インターフェースを一括して行う
	//=========================================================================
	class GameTaskVector : public GameTask
	{
		PVP_Task		m_pvpTask;

	public:
		GameTaskVector ();
		GameTaskVector ( const GameTaskVector & rhs ) = delete;
		virtual ~GameTaskVector ();

		virtual void Load();		//読込(初回、または再設定時などの解放後１回のみ)
		virtual void Rele();		//動的な一時領域の解放(恒常的なメモリ確保はコンストラクタ～デストラクタで行う)
		virtual void Reset();		//再設定( Rele(); Load(); Init(); )

		virtual void Init();		//初期化(繰り返してもよい)※再設定時(フォーカスの変更など)に毎回行う
		virtual void Move();		//フレーム毎動作

		//初期化
		void Clear();
		
		//配列サイズの取得
		size_t GetSize () { return m_pvpTask->size (); }

		//配列ポインタの取得
		PVP_Task GetpvpTask () { return m_pvpTask; }

		//タスクの追加（サイズの変更も自動的に行う）
		//	※実体のある変数から&でスマートポインタを直接扱わない
		void AddpTask ( P_Task pTask );

		//タスクの取得（サイズの変更も自動的に行う）
		P_Task GetpTask ( UINT index );

		//アクセサ		
		P_Task operator [] ( UINT index );

		//タスクの挿入
		void InsertTask ( P_Task pTask, UINT index );

		//タスクの取外
		void EraseTask ( P_Task pTask );
		void EraseTask ( const VP_Task::iterator it );

		//指定オブジェクトを最前列描画にする
		//	指定したオブジェクトが無い場合なにもしない
		void Top ( P_Task pTask );

		//指定オブジェクトを最背列描画にする
		//	指定したオブジェクトが無い場合なにもしない
		void End ( P_Task pTask );
	};

	using TASK_VEC = GameTaskVector;
	using P_TASK_VEC = std::shared_ptr < TASK_VEC >;


	//=========================================================================
	// ゲームタスクリスト
	//	ゲームタスクの基本インターフェースを一括して行う
	//	生成・削除が多いときに用いる
	//=========================================================================
	class GameTaskList : public GameTask
	{
		PLP_Task	m_plpTask;

	public:
		GameTaskList ();
		GameTaskList ( const GameTaskList & rhs ) = delete;
		virtual ~GameTaskList ();

		virtual void Load ();		//読込(初回、または再設定時などの解放後１回のみ)
		virtual void Rele ();		//動的な一時領域の解放(恒常的なメモリ確保はコンストラクタ～デストラクタで行う)
		virtual void Reset ();		//再設定( Rele(); Load(); Init(); )

		virtual void Init ();		//初期化(繰り返してもよい)※再設定時(フォーカスの変更など)に毎回行う
		virtual void Move ();		//フレーム毎動作

		//初期化
		void Clear ();

		//配列サイズの取得
		size_t GetSize () { return m_plpTask->size (); }

		//配列ポインタの取得
		PLP_Task GetplpTask () { return m_plpTask; }

		//タスクの追加
		void AddpTask ( P_Task pTask );

		//タスクの挿入
		void InsertTask ( LP_Task::iterator it, P_Task pTask );

		//タスクの取外
		void EraseTask ( P_Task pTask );
		void EraseTask ( const LP_Task::iterator it );

		//指定オブジェクトを最前列描画にする
		//	指定したオブジェクトが無い場合なにもしない
		void TopTask ( P_Task pTask );

		//指定オブジェクトを最背列描画にする
		//	指定したオブジェクトが無い場合なにもしない
		void EndTask ( P_Task pTask );
	};

	using TASK_LST = GameTaskList;
	using P_TASK_LST = std::shared_ptr < TASK_LST >;

}	//namespace GAME


