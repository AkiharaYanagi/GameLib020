//=================================================================================================
//
// ゲームグラフィック　クラス　
//		ゲームで用いる画像を扱うオブジェクトを定義する。
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイル　インクルード
//-------------------------------------------------------------------------------------------------
#include "GameGraphic.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//■=======================================================================
	// ゲームグラフィック　ベース
	//■=======================================================================
	GameGraphicBase::GameGraphicBase ()
	{
		mpap_Texture = std::make_shared < AP_Tx > ();

		mpap_Object = std::make_shared < AP_Ob > ();
		mpap_Object->push_back ( std::make_shared < GameObject > () );
	}

	GameGraphicBase::~GameGraphicBase ()
	{
		mpap_Object->clear ();
	}


	//---------------------------------------------------------------------
	void GameGraphicBase::Load ()
	{
	}

	void GameGraphicBase::Move ()
	{
		for ( P_Ob pob : *mpap_Object ) { pob->PreMove (); }
	}

	void GameGraphicBase::Draw ()
	{
		//オブジェクトの数だけ描画
		for ( P_Ob pob : *mpap_Object )
		{
			if ( ! pob->GetValid () ) { continue; }

			//拡大縮小
			VEC2 v = pob->GetScaling();
			s3d::Vec2 vScaling { v.x, v.y };

			//描画テクスチャの指定
			uint32 indexTexture = pob->GetIndexTexture ();
			P_Tx ptx = mpap_Texture->at ( indexTexture );
			ptx->scaled ( vScaling ).draw ( pob->GetPos().x, pob->GetPos().y );
		}
	}

	//---------------------------------------------------------------------
	void GameGraphicBase::AddpTexture ( P_Tx ptx )
	{
		mpap_Texture->push_back ( ptx );
	}

	void GameGraphicBase::AddTexture ()
	{
		P_Tx ptx = std::make_shared < s3d::Texture > ();
		mpap_Texture->push_back ( ptx );
	}

	void GameGraphicBase::AddTexture ( s3d::String filename )
	{
		P_Tx ptx = std::make_shared < s3d::Texture > ( filename );
		mpap_Texture->push_back ( ptx );
	}

	void GameGraphicBase::SetpTexture ( P_Tx ptx )
	{
		//0の位置にテクスチャを設定します
		//map_Texture->at ( 0 ) = ptx;
		mpap_Texture->remove_at ( 0 );
		mpap_Texture->push_back ( ptx );
	}


	//---------------------------------------------------------------------
	float GameGraphicBase::GetZ () const
	{
		if ( mpap_Object->size() > 0 )
		{
			return mpap_Object->at ( 0 )->GetZ ();
		}
		return 0;
	}

	void GameGraphicBase::SetZ ( float z )
	{
		if ( mpap_Object->size() > 0 )
		{
			mpap_Object->at ( 0 )->SetZ ( z );
		}
	}


}	//namespace GAME

