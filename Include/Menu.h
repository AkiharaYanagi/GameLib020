//=================================================================================================
//
//	Menu
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "02_GameGraphic.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//=================================================
	class Menu; using WP_Menu = std::weak_ptr < Menu >;

	//=================================================
	//メニュ内文字列
	class MenuString : public GrpStr
	{
	public:
		MenuString ();
		MenuString ( const MenuString & rhs ) = delete;
		~MenuString ();
	};

	using P_MenuString = std::shared_ptr < MenuString >;


	//=================================================
	//メニュ 項目
	class MenuItem : public TASK_VEC
	{
	protected:
		WP_Menu		mwp_Parent;	//直接の親メニュ

		P_MenuString	m_str;	//文字列

	public:
		MenuItem ();
		MenuItem ( const MenuItem & rhs ) = delete;
		~MenuItem ();

		virtual void Do () {}
		virtual void Decide () {}
		virtual void Off () {}
		virtual void On () {}

		void SetwpParent ( WP_Menu wp ) { mwp_Parent = wp; }

		void UpdatePos ( VEC2 v );
	};

	using P_MenuItem = std::shared_ptr < MenuItem >;
	using VP_MenuItem = std::vector < P_MenuItem >;


	//=================================================
	//メニュ 動作主体
	class Menu : public MenuItem, public std::enable_shared_from_this < Menu >
	{
		bool			m_active { F };		//全体稼働フラグ

		P_PrmRect		m_bg;				//背景
		bool			m_bBg { F };		//背景利用

		VP_MenuItem		mvp_MenuItem;
		VP_MenuItem::iterator		m_itItem;

	public:
		Menu ();
		Menu ( const Menu & rhs ) = delete;
		~Menu ();

		void Init ();

		void SetActive ( bool b ) { m_active = b; }
		bool GetActive () const { return m_active; }

		//shared_from_this () を含むのでコンストラクタで用いない
		void SetpMenuItem ( P_MenuItem mi );
		P_MenuItem GetpMenuItem () { return *m_itItem; }

		//メニュアイテムを生成
		void PushMenuItem ();

		void Next ();
		void Prev ();
		void Do ();
		void Decide ();

		DWORD GetIdItem () const;

		//選択
		void Top ();
		void Last ();
		void Select ( UINT n );	//IDで選択、範囲外は何もしない

		//切替
		void Off ();
		void On ();

		//全体 オン / オフ
		void AllOff ();
		void AllOn ();

		//Itemのみ オン / オフ
		void ItemOff ();
		void ItemOn ();

		//階層メニュ込みの位置更新
		void UpdatePos ();
		void UpdatePos ( VEC2 v );

		//背景の設定
		void SetBG_use ( bool b );
		P_PrmRect GetBG () const { return m_bg; }
		
		void SetBG_Z ( float z );

		void SetBG_Size ( float x, float y ) { m_bg->SetSize ( VEC2 ( x, y ) ); };
		void SetBG_Size ( VEC2 v ) { m_bg->SetSize ( v ); };

		void SetBG_Pos ( float x, float y ) { m_bg->SetPos ( VEC2 ( x, y ) ); };
		void SetBG_Pos ( VEC2 v ) { m_bg->SetPos ( v ); };

		void SetBG_Color ( s3d::Color clr ) { m_bg->SetColor ( clr ); };
		void SetBG_Color ( _CLR clr ) { m_bg->SetColor ( clr ); };
	};

	using P_Menu = std::shared_ptr < Menu >;


}	//namespace GAME

