//=================================================================================================
//
//	Menu
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Menu.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//=================================================
	//MenuItem

	//=================================================
	//MenuString

	MenuString::MenuString ()
	{
#if 0
		SetFontParam ( 100, 1, 2 );
		SetFontFace ( _T ( "メイリオ" ) );
//		SetFontFace ( _T ( "MSゴシック" ) );
		SetFontColor ( 0xffffffff, 0xff202080 );
#endif // 0
		SetbMenu ( T );
		SetZ ( Z_MENU );
		SetStr ( U"MenuStr" );
	}

	MenuString::~MenuString ()
	{
	}

	//=================================================

	MenuItem::MenuItem ()
	{
		m_str = std::make_shared < MenuString > ();
		m_str->SetPos ( 100, 20 );
//		GRPLST_INSERT ( m_str );
	}

	MenuItem::~MenuItem ()
	{
	}

	void MenuItem::UpdatePos ( VEC2 v )
	{
		m_str->SetPos ( v + m_str->GetPos () );
	}


	//=================================================
	Menu::Menu ()
	{
		m_itItem = mvp_MenuItem.begin ();

		m_str = std::make_shared < MenuString > ();

		m_bg = std::make_shared < PrmRect > ();
		m_bg->SetSize ( s3d::Point { 500, 300 } );
		m_bg->SetColor ( s3d::ColorF { 0, 0, 0, 0.5 } );
		m_bg->SetZ ( Z_MENU );
		GRPLST_INSERT ( m_bg );
	}

	Menu::~Menu ()
	{
	}

	void Menu::Init ()
	{
		m_itItem = mvp_MenuItem.begin ();
		
		MenuItem::Init ();
	}
	
	void Menu::SetpMenuItem ( P_MenuItem mi )
	{
		mi->SetwpParent ( shared_from_this () );
		mvp_MenuItem.push_back ( mi );
	}


	void Menu::PushMenuItem ()
	{
		P_MenuItem mi = std::make_shared < MenuItem > ();
		mi->SetwpParent ( shared_from_this () );
		mvp_MenuItem.push_back ( mi );
	}


	void Menu::Next ()
	{
//		TRACE_F ( _T ( "Menu::Next()\n" ) );


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

	void Menu::Prev ()
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
	
	void Menu::Do ()
	{
		//BG切替
		m_bg->SetValid ( m_bBg );

		( * m_itItem )->Do ();
	}

	void Menu::Decide ()
	{
		( * m_itItem )->Decide ();
	}

	DWORD Menu::GetIdItem () const
	{
		size_t size = mvp_MenuItem.size ();
		if ( 0 == size ) { return 0; }


		VP_MenuItem::const_iterator	it = mvp_MenuItem.begin ();
		for ( DWORD i = 0; i < size; ++ i )
		{
			if ( it == m_itItem ) { return i; }
			++ it;
		}

		return 0;
	}

	void Menu::Top ()
	{
		if ( mvp_MenuItem.size () == 0 ) { return; }
		m_itItem = mvp_MenuItem.begin ();
	}

	void Menu::Last ()
	{
		if ( mvp_MenuItem.size () == 0 ) { return; }
		m_itItem = mvp_MenuItem.end ();
		-- m_itItem;
	}

	void Menu::Select ( UINT n )
	{
		if ( mvp_MenuItem.size () < n ) { return; }

		m_itItem = mvp_MenuItem.begin ();
		m_itItem += n;
	}


	//On/Off
	void Menu::Off ()
	{
		m_bg->SetValid ( F );
		MenuItem::Off ();
	}

	void Menu::On ()
	{
		m_bg->SetValid ( T );
		MenuItem::On ();
	}

	void Menu::AllOff ()
	{
		for ( P_MenuItem p : mvp_MenuItem )
		{
			p->Off ();
		}
		Off ();	//自身もOff();
	}

	void Menu::AllOn ()
	{
		for ( P_MenuItem p : mvp_MenuItem )
		{
			p->On ();
		}
		On ();	//自身もOn();
	}

	void Menu::ItemOff ()
	{
		for ( P_MenuItem p : mvp_MenuItem )
		{
			p->Off ();
		}
		//		Off ();	//自身はOff();しない
	}

	void Menu::ItemOn ()
	{
		for ( P_MenuItem p : mvp_MenuItem )
		{
			p->On ();
		}
		//		On ();	//自身はOn();しない
	}


	void Menu::UpdatePos ()
	{
		int32 x = m_bg->GetPos ().x;
		int32 y = m_bg->GetPos ().y;
		UpdatePos ( VEC2 ( (float)x, (float)y ) );
	}


	void Menu::UpdatePos ( VEC2 v )
	{
		m_bg->SetPos ( (int32)v.x, (int32)v.y );

		for ( P_MenuItem p : mvp_MenuItem )
		{
			p->UpdatePos ( v );
		}
	}

	void Menu::SetBG_use ( bool b )
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


}	//namespace GAME

