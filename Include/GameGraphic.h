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
#include "Define_Siv3D.h"
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
		PAP_Tx		map_Texture;
		
//		s3d::String	m_filename { U"" };
//		std::shared_ptr < s3d::Texture >	m_tx { nullptr };

		//オブジェクト配列
		PAP_Ob		map_Object;

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
//		void SetTextureName ( s3d::String filename ) { m_filename = filename; }
		void AddTexture ();
		void AddTexture ( s3d::String filename );

		void AddpTexture ( P_Tx ptx );

		void SetpTexture ( P_Tx ptx );

		//---------------------------------------------------------------------
		//オブジェクト先頭の直接制御
		//単体で用いるときは、オブジェクトを指定しなくてよい
		void SetPos ( VEC2 v ) { map_Object->at ( 0 )->SetPos ( v ); }
		void SetPos ( float x, float y ) { map_Object->at ( 0 )->SetPos ( x, y ); }
		VEC2 GetPos () const { return map_Object->at ( 0 )->GetPos (); }
		void AddPos ( VEC2 v ) { map_Object->at ( 0 )->AddPos ( v ); }

		//---------------------------------------------------------------------
		//先頭のみ
		float GetZ () const;
		void SetZ ( float z );
	};

	using GrpBs = GameGraphicBase;
	using P_Grp = std::shared_ptr < GrpBs >;



}	//namespace GAME

