﻿//=================================================================================================
//
// GameKeyCommand ソース
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "GameKeyCommand.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	GameKeyCommand::GameKeyCommand ()
	{
		for ( UINT i = 0; i < GameKey::LVR_NUM; ++ i )
		{
			m_Lvr[i] = GAME_KEY_WILD;
		}
		for ( UINT i = 0; i < GameKey::BTN_NUM; ++ i )
		{
			m_Btn[i] = GAME_KEY_WILD;
		}
	}

	GameKeyCommand::GameKeyCommand ( const GameKeyCommand & rhs )
	{
		for ( UINT i = 0; i < GameKey::LVR_NUM; ++ i )
		{
			m_Lvr[i] = rhs.m_Lvr[i];
		}
		for ( UINT i = 0; i < GameKey::BTN_NUM; ++ i )
		{
			m_Btn[i] = rhs.m_Btn[i];
		}
	}

	GameKeyCommand::~GameKeyCommand ()
	{

	}


	bool GameKeyCommand::CompareTarget ( const GameKey & gameKeyData ) const
	{
		//条件がワイルドのときは比較しない
		bool bWildLvr[GameKey::LVR_NUM] = { false };
		bool bWildBtn[GameKey::BTN_NUM] = { false };

		//比較結果
		bool bLvr[GameKey::LVR_NUM] = { false };
		bool bBtn[GameKey::BTN_NUM] = { false };

		//レバー比較
		for ( UINT i = 0; i < GameKey::LVR_NUM; ++ i )
		{
			bool b = gameKeyData.GetLvr ( i );
			bool pb = gameKeyData.GetPreLvr ( i );

			switch ( m_Lvr[i] )
			{
			case GAME_KEY_OFF:	bLvr[i] = ! pb && ! b; break;
			case GAME_KEY_ON:	bLvr[i] =   pb &&   b; break;
			case GAME_KEY_PUSH:	bLvr[i] = ! pb &&   b; break;
			case GAME_KEY_RELE:	bLvr[i] =   pb && ! b; break;
			case GAME_KEY_IS:	bLvr[i] =   b; break;
			case GAME_KEY_NIS:	bLvr[i] = ! b; break;
			case GAME_KEY_WILD:	bWildLvr[i] = true; break;
			}
		}

		//ボタン比較
		for ( UINT i = 0; i < GameKey::BTN_NUM; ++ i )
		{
			bool b = gameKeyData.GetBtn ( i );
			bool pb = gameKeyData.GetPreBtn ( i );

			switch ( m_Btn[i] )
			{
			case GAME_KEY_OFF:	bBtn[i] = ! pb && ! b; break;
			case GAME_KEY_ON:	bBtn[i] =   pb &&   b; break;
			case GAME_KEY_PUSH:	bBtn[i] = ! pb &&   b; break;
			case GAME_KEY_RELE:	bBtn[i] =   pb && !   b; break;
			case GAME_KEY_IS:	bBtn[i] =   b; break;
			case GAME_KEY_NIS:	bBtn[i] = ! b; break;
			case GAME_KEY_WILD:	bWildBtn[i] = true; break;
			}
		}

		//すべてを走査し１つでも ワイルドでない かつ 該当しない 場合falseを返す
		for ( UINT i = 0; i < GameKey::LVR_NUM; ++ i )
		{
			if ( ! bWildLvr[i] && ! bLvr[i] ) { return false; }
		}
		for ( UINT i = 0; i < GameKey::BTN_NUM; ++ i )
		{
			if ( ! bWildBtn[i] && ! bBtn[i] ) { return false; }
		}

		//すべて適合だったらtrue
		return true;
	}


	//向き指定の比較
	bool GameKeyCommand::CompareTarget ( const GameKey & gameKeyData, bool dirRight ) const
	{
		//比較するかどうか ( 条件がワイルドのときは比較しない )
		bool bWildLvr[GameKey::LVR_NUM] = { false };
		bool bWildBtn[GameKey::BTN_NUM] = { false };

		//比較結果
		bool bLvr[GameKey::LVR_NUM] = { false };
		bool bBtn[GameKey::BTN_NUM] = { false };

		//左右によるレバーインデックス
		//	6 5 4				//	4 5 6
		//	7   3	右→		←左	//	3   7
		//	0 1 2				//	2 1 0
		const int lever_dir_R[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
		const int lever_dir_L[] = { 2, 1, 0, 7, 6, 5, 4, 3 };


		//レバー比較
		for ( UINT i = 0; i < GameKey::LVR_NUM; ++ i )
		{
			int lr_index = dirRight ? lever_dir_R[i] : lever_dir_R[i];
			bool b =  gameKeyData.GetLvr ( lr_index );
			bool pb = gameKeyData.GetPreLvr ( lr_index );

			switch ( m_Lvr[i] )
			{
			case GAME_KEY_OFF:	bLvr[i] = ! pb && ! b; break;
			case GAME_KEY_ON:	bLvr[i] =   pb && b; break;
			case GAME_KEY_PUSH:	bLvr[i] = ! pb &&   b; break;
			case GAME_KEY_RELE:	bLvr[i] =   pb && ! b; break;
			case GAME_KEY_IS:	bLvr[i] =   b; break;
			case GAME_KEY_NIS:	bLvr[i] = ! b; break;
			case GAME_KEY_WILD:	bWildLvr[i] = true; break;
			}
		}

		//ボタン比較
		for ( UINT i = 0; i < GameKey::BTN_NUM; ++ i )
		{
			bool b = gameKeyData.GetBtn ( i );
			bool pb = gameKeyData.GetPreBtn ( i );

			switch ( m_Btn[i] )
			{
			case GAME_KEY_OFF:	bBtn[i] = ! pb && ! b; break;
			case GAME_KEY_ON:	bBtn[i] =   pb && b; break;
			case GAME_KEY_PUSH:	bBtn[i] = ! pb &&   b; break;
			case GAME_KEY_RELE:	bBtn[i] =   pb && !   b; break;
			case GAME_KEY_IS:	bBtn[i] =   b; break;
			case GAME_KEY_NIS:	bBtn[i] = ! b; break;
			case GAME_KEY_WILD:	bWildBtn[i] = true; break;
			}
		}

		//すべてを走査し１つでも ワイルドでない かつ 該当しない 場合falseを返す
		for ( UINT i = 0; i < GameKey::LVR_NUM; ++ i )
		{
			if ( ! bWildLvr[i] && ! bLvr[i] ) { return false; }
		}
		for ( UINT i = 0; i < GameKey::BTN_NUM; ++ i )
		{
			if ( ! bWildBtn[i] && ! bBtn[i] ) { return false; }
		}

		//すべて適合だったらtrue
		return true;
	}


	void GameKeyCommand::SetaLvr ( GAME_KEY_STATE state_ary [] )
	{
		for ( UINT i = 0; i < GameKey::BTN_NUM; ++ i )
		{
			m_Lvr [ i ] = state_ary [ i ];
		}
	}

	void GameKeyCommand::SetaBtn ( GAME_KEY_STATE state_ary [] )
	{
		for ( UINT i = 0; i < GameKey::BTN_NUM; ++ i )
		{
			m_Btn [ i ] = state_ary [ i ];
		}
	}


#if 0

	bool _GameKeyCommand::IsKeyLvrCmd ( GAME_KEY_LVR_CMD lvr_cmd ) const
	{
		switch ( lvr_cmd )
		{
		case LVR_CMD_1: return Is ( GameKey::LVR_1 );
		case LVR_CMD_2: return Is ( GameKey::LVR_2 );
		case LVR_CMD_3: return Is ( GameKey::LVR_3 );
		case LVR_CMD_6: return Is ( GameKey::LVR_6 );
		case LVR_CMD_9: return Is ( GameKey::LVR_9 );
		case LVR_CMD_8: return Is ( GameKey::LVR_8 );
		case LVR_CMD_7: return Is ( GameKey::LVR_7 );
		case LVR_CMD_4: return Is ( GameKey::LVR_4 );
#if 0

		case LVR_CMD_2E: return Is2E ();
		case LVR_CMD_6E: return Is6E ();
		case LVR_CMD_8E: return Is8E ();
		case LVR_CMD_4E: return Is4E ();

#endif // 0
		}
		return false;
	}

	bool _GameKeyCommand::Is ( GameKey::GAME_KEY_LEVER lvr ) const
	{
		return (GAME_KEY_ON == m_Lvr[lvr]) || (GAME_KEY_PUSH == m_Lvr[lvr]);
	}

	//レバーニュートラルかどうか
	bool _GameKeyCommand::IsNeutral () const
	{
		//すべてのレバーを走査して、１つでもOFFかRELEでなかったらfalse
		for ( UINT i = 0; i < GameKey::LVR_NUM; ++ i )
		{
			if ( GAME_KEY_OFF != m_Lvr [ i ] || GAME_KEY_RELE != m_Lvr [ i ] ) { return false; }
		}
		return true;
	}

	bool _GameKeyCommand::Is2E () const
	{
		return Is ( GameKey::LVR_1 ) || Is ( GameKey::LVR_2 ) || Is ( GameKey::LVR_3 );
	}
	bool _GameKeyCommand::Is6E () const
	{
		return Is ( GameKey::LVR_3 ) || Is ( GameKey::LVR_6 ) || Is ( GameKey::LVR_9 );
	}
	bool _GameKeyCommand::Is8E () const
	{
		return Is ( GameKey::LVR_7 ) || Is ( GameKey::LVR_8 ) || Is ( GameKey::LVR_9 );
	}
	bool _GameKeyCommand::Is4E () const
	{
		return Is ( GameKey::LVR_1 ) || Is ( GameKey::LVR_4 ) || Is ( GameKey::LVR_7 );
	}
#endif // 0


}	//namespace GAME

