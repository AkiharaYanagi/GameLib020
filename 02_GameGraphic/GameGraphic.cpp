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
		map_Texture = std::make_shared < AP_Tx > ();

		map_Object = std::make_shared < AP_Ob > ();
		map_Object->push_back ( std::make_shared < GameObject > () );
	}

	GameGraphicBase::~GameGraphicBase ()
	{
		map_Object->clear ();
	}


	//---------------------------------------------------------------------
	void GameGraphicBase::Load ()
	{
	}

	void GameGraphicBase::Move ()
	{
		for ( P_Ob pob : *map_Object ) { pob->PreMove (); }
		for ( P_Ob pob : *map_Object ) { pob->Move (); }
	}

	void GameGraphicBase::Draw ()
	{
		//オブジェクトの数だけ描画
		for ( P_Ob pob : *map_Object )
		{
			if ( ! pob->GetValid () ) { continue; }

			//テクスチャの指定
			uint32 indexTexture = pob->GetIndexTexture ();
			map_Texture->at ( indexTexture )->draw ( pob->GetPos().x, pob->GetPos().y );
			//m_tx->draw ( pob->GetPos().x, pob->GetPos().y );
		}
	}

	//---------------------------------------------------------------------
	void GameGraphicBase::AddpTexture ( P_Tx ptx )
	{
		map_Texture->push_back ( ptx );
	}

	void GameGraphicBase::AddTexture ()
	{
		P_Tx ptx = std::make_shared < s3d::Texture > ();
		map_Texture->push_back ( ptx );
	}

	void GameGraphicBase::AddTexture ( s3d::String filename )
	{
		P_Tx ptx = std::make_shared < s3d::Texture > ( filename );
		map_Texture->push_back ( ptx );
	}

	void GameGraphicBase::SetpTexture ( P_Tx ptx )
	{
		map_Texture->at ( 0 ) = ptx;
	}


	//---------------------------------------------------------------------
	float GameGraphicBase::GetZ () const
	{
		if ( map_Object->size() > 0 )
		{
			return map_Object->at ( 0 )->GetZ ();
		}
		return 0;
	}

	void GameGraphicBase::SetZ ( float z )
	{
		if ( map_Object->size() > 0 )
		{
			map_Object->at ( 0 )->SetZ ( z );
		}
	}


}	//namespace GAME

