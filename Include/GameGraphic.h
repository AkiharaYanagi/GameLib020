//=================================================================================================
//
// ゲームグラフィック　クラス　ヘッダ
//		グラフィックを扱うオブジェクトを定義する
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイル　インクルード
//-------------------------------------------------------------------------------------------------
#include "00_Common.h"
#include "GameTask.h"
#include "GameObject.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//■=======================================================================
	// ゲームグラフィック　ベース
	//		・複数テクスチャと複数オブジェクトを持つゲームタスク
	//		・テクスチャが指定されていないときは何もしない
	//		・オブジェクトは自動で１つ生成する。指定個数使用する場合は０にクリアしてから追加する
	//■=======================================================================
	class GameGraphicBase : public GameTask
	{
		//テクスチャ配列(インデックスはオブジェクトが持つ)
		PAP_Tx		mpap_Texture;

		//オブジェクト配列
		PAP_Ob		mpap_Object;

	public:
		GameGraphicBase ();
		GameGraphicBase ( const GameGraphicBase & rhs ) = delete;
		~GameGraphicBase ();

		//---------------------------------------------------------------------
		void Load ();
		void Move ();
		void Draw ();

		//---------------------------------------------------------------------
		//テクスチャ
		PAP_Tx Getpap_tx () const { return mpap_Texture; }

		void ClearTexture () { mpap_Texture->clear (); }
		void AddTexture ();
		void AddTexture ( s3d::String filename );
		void AddTexture_FromArchive ( s3d::String filename );
		void AddpTexture ( P_Tx ptx );
		void SetpTexture ( P_Tx ptx );

		//---------------------------------------------------------------------
		// オブジェクト
		PAP_Ob Getpap_ob () const { return mpap_Object; }

		//オブジェクト先頭の直接制御
		//単体で用いるときは、オブジェクトを指定しなくてよい
		void SetPos ( VEC2 v ) { mpap_Object->at ( 0 )->SetPos ( v ); }
		void SetPos ( float x, float y ) { mpap_Object->at ( 0 )->SetPos ( x, y ); }
		VEC2 GetPos () const { return mpap_Object->at ( 0 )->GetPos (); }
		void AddPos ( VEC2 v ) { mpap_Object->at ( 0 )->AddPos ( v ); }

		void SetScaling ( float x, float y ) { mpap_Object->at(0)->SetScaling ( x, y ); }
		void SetScaling ( VEC2 v ) { mpap_Object->at(0)->SetScaling ( v ); }

		float GetZ () const;
		void SetZ ( float z );

		void SetIndexTexture ( uint32 index ) { mpap_Object->at(0)->SetIndexTexture ( index ); }
		void SetColor ( uint32 clr ) { mpap_Object->at(0)->SetColor ( clr ); }

		//---------------------------------------------------------------------
	};

	using GrpBs = GameGraphicBase;
	using P_Grp = std::shared_ptr < GrpBs >;



}	//namespace GAME

