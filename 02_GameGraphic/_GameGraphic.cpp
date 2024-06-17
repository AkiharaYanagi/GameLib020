//=================================================================================================
//
// ゲームグラフィック　クラス　
//		ゲームで用いる画像を扱うオブジェクトを定義する。
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイル　インクルード
//-------------------------------------------------------------------------------------------------
#include "_GameGraphic.h"

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
		map_Object = std::make_shared < AP_Ob > ();
		map_Object->push_back ( std::make_shared < GameObject > () );
	}

	GameGraphicBase::~GameGraphicBase ()
	{
		map_Object->clear ();
	}

	void GameGraphicBase::Load ()
	{
		m_tx = std::make_shared < s3d::Texture > ( m_filename );
	}

	void GameGraphicBase::Move ()
	{
		for ( P_Ob pob : *map_Object ) { pob->PreMove (); }
		for ( P_Ob pob : *map_Object ) { pob->Move (); }
	}

	void GameGraphicBase::Draw ()
	{

		for ( P_Ob pob : *map_Object )
		{
			if ( ! pob->GetValid () ) { continue; }

			m_tx->draw ( pob->GetPos().x, pob->GetPos().y );
		}
	}

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

