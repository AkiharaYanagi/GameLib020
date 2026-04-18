//=================================================================================================
//
//	GameMenu
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "GameMenu.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//=================================================
	//GameMenuString

	GameMenuString::GameMenuString ()
	{
#if 0
		SetFontParam ( 100, 1, 2 );
		SetFontFace ( _T ( "メイリオ" ) );
//		SetFontFace ( _T ( "MSゴシック" ) );
		SetFontColor ( 0xffffffff, 0xff202080 );
#endif // 0
		SetbMenu ( T );
		SetZ ( Z_MENU - 0.002f );
		SetStr ( U"MenuStr" );
		SetValid ( F );
	}

	GameMenuString::~GameMenuString ()
	{
	}

	//=================================================


	//=================================================
	//MenuItem

	GameMenuItem::GameMenuItem ()
	{
		m_str = std::make_shared < GameMenuString > ();
		AddpTask ( m_str );
		GRPLST_INSERT ( m_str );

		Off();
	}

	void GameMenuItem::Off ()
	{
		m_str->SetValid ( F );
	}

	void GameMenuItem::On ()
	{
		m_str->SetValid ( T );
	}

	void GameMenuItem::SetPosStr ( VEC2 v )
	{
		m_str->SetPos ( v + m_str->GetPos () );
	}

	void GameMenuItem::SetStr ( const s3d::String & str )
	{
		m_str->SetStr ( str );
	}


	//=================================================
	GameMenu::GameMenu ()
	{
		m_itItem = mvp_MenuItem.begin ();

		m_bg = std::make_shared < PrmRect > ();
		m_bg->SetSize ( s3d::Point { 500, 300 } );
		m_bg->SetColor ( s3d::ColorF { 0, 0, 0, 0.5 } );
		m_bg->SetZ ( Z_MENU );
		m_bg->SetValid ( F );
		GRPLST_INSERT ( m_bg );
	}

	void GameMenu::Init ()
	{
		m_itItem = mvp_MenuItem.begin ();
		
		GameMenuItem::Init ();
	}
	
	void GameMenu::SetpMenuItem ( P_GameMenuItem mi )
	{
		mi->SetwpParentMenu ( shared_from_this () );
		mvp_MenuItem.push_back ( mi );
	}

	void GameMenu::SetwpParentMenu ( WP_GameMenu wp )
	{
		GameMenuItem::SetwpParentMenu ( wp );
		for ( P_GameMenuItem mi : mvp_MenuItem )
		{
			mi->SetwpParentMenu ( wp );
		}
	}

	void GameMenu::SetpParam ( P_GameParam p )
	{
		GameMenuItem::SetpParam ( p );
		for ( P_GameMenuItem mi : mvp_MenuItem )
		{
			mi->SetpParam ( p );
		}
	}


	void GameMenu::PushMenuItem ()
	{
		P_GameMenuItem mi = std::make_shared < GameMenuItem > ();
		mi->SetwpParentMenu ( shared_from_this () );
		mvp_MenuItem.push_back ( mi );
	}


	void GameMenu::Next ()
	{
		//個数が1,または0のとき何もしない
		if ( mvp_MenuItem.size () < 2 ) { return; }

		if ( mvp_MenuItem.end () == m_itItem + 1 )
		{
			m_itItem = mvp_MenuItem.begin ();
		}
		else
		{
			++ m_itItem;
		}
	}

	void GameMenu::Prev ()
	{
		//個数が1,または0のとき何もしない
		if ( mvp_MenuItem.size () < 2 ) { return; }

		if ( mvp_MenuItem.begin () == m_itItem )
		{
			m_itItem = mvp_MenuItem.end () - 1;
		}
		else
		{
			-- m_itItem;
		}
	}
	
	void GameMenu::Do ()
	{
		( * m_itItem )->Do ();
	}

	void GameMenu::Decide ()
	{
		( * m_itItem )->Decide ();
	}

	DWORD GameMenu::GetIdItem () const
	{
		size_t size = mvp_MenuItem.size ();
		if ( 0 == size ) { return 0; }


		VP_GameMenuItem::const_iterator	it = mvp_MenuItem.begin ();
		for ( DWORD i = 0; i < size; ++ i )
		{
			if ( it == m_itItem ) { return i; }
			++ it;
		}

		return 0;
	}


	void GameMenu::ForEachMenuItem_Do(std::function < void(P_GameMenuItem) > func)
	{
		for ( P_GameMenuItem p : mvp_MenuItem )
		{
			func ( p );
		}
	}

	void GameMenu::SelectTop ()
	{
		if ( mvp_MenuItem.size () == 0 ) { return; }
		m_itItem = mvp_MenuItem.begin ();
	}

	void GameMenu::SelectLast ()
	{
		if ( mvp_MenuItem.size () == 0 ) { return; }
		m_itItem = mvp_MenuItem.end ();
		-- m_itItem;
	}

	void GameMenu::Select ( UINT n )
	{
		if ( mvp_MenuItem.size () < n ) { return; }

		m_itItem = mvp_MenuItem.begin ();
		m_itItem += n;
	}


	//On/Off
	void GameMenu::Off ()
	{
		m_bg->SetValid ( F );
		GameMenuItem::Off ();
	}

	void GameMenu::On ()
	{
		m_bg->SetValid ( T );
		GameMenuItem::On ();
	}

	void GameMenu::AllOff ()
	{
		for ( P_GameMenuItem p : mvp_MenuItem )
		{
			p->Off ();
		}
		Off ();	//自身もOff();
	}

	void GameMenu::AllOn ()
	{
		for ( P_GameMenuItem p : mvp_MenuItem )
		{
			p->On ();
		}
		On ();	//自身もOn();
	}

	void GameMenu::ItemOff ()
	{
		for ( P_GameMenuItem p : mvp_MenuItem )
		{
			p->Off ();
		}
		//		Off ();	//自身はOff();しない
	}

	void GameMenu::ItemOn ()
	{
		for ( P_GameMenuItem p : mvp_MenuItem )
		{
			p->On ();
		}
		//		On ();	//自身はOn();しない
	}


	void GameMenu::UpdatePos ()
	{
		int32 x = m_bg->GetPos ().x;
		int32 y = m_bg->GetPos ().y;
		GameMenuItem::SetPosStr ( VEC2 ( (float)x, (float)y ) );
	}


	void GameMenu::UpdatePos ( VEC2 v )
	{
		m_bg->SetPos ( (int32)v.x, (int32)v.y );

		for ( P_GameMenuItem p : mvp_MenuItem )
		{
			p->SetPosStr ( v );
		}
	}

	void GameMenu::SetBG_use ( bool b )
	{
		m_bg->SetValid ( b );
		m_bBg = b;

		if ( ! b )
		{
			m_bg->SetColor  ( _CLR ( 0x00000000 ) );
			m_bg->SetSize ( 0, 0 );
			m_bg->SetPos ( 0, 0 );
		}
	}

	void GameMenu::SetBG_Z ( float z )
	{
		m_bg->SetZ ( z );

		//Z値変更のため、再度グラフィックリストで位置を調整する
		//Zが同値で順番を指定しているときに再指定のために位置がずれることに注意
		GRPLST_REMOVE ( m_bg );
		GRPLST_INSERT ( m_bg );
	}


}	//namespace GAME

