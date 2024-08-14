//=================================================================================================
//
// アスキーフォント　固定保持
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Base_DebugOut.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//=====================================================
	//	基本情報表示
	//=====================================================

	Base_DebugOut::Base_DebugOut ()
	{
	}

	Base_DebugOut::~Base_DebugOut ()
	{
	}

	void Base_DebugOut::Draw ()
	{
		if ( ! m_valid ) { return; }

		m_font ( m_str ).draw ( m_pos.x, m_pos.y, s3d::ColorF { 1.0, 0.0, 1.0 } );
	}

	void Base_DebugOut::SetPos ( VEC2 v )
	{
		m_pos = v;
	}

	void Base_DebugOut::SetStr ( s3d::String str )
	{
		m_str = str;
	}

#if 0
	void ConstDebugOut_ASCII::SetStr ( LPCTSTR lpctstr )
	{
		m_tstr.assign ( lpctstr );

		//文字列変換
		size_t str_size = m_tstr.size ();
		std::unique_ptr < char[] > ary_ch = std::make_unique < char[] > ( str_size );

		vector < char > v_ch;
		v_ch.resize ( str_size );

		int converted = 0;
		UINT i = 0;
		for ( TCHAR tch : m_tstr )
		{
			wctomb_s ( & converted, & v_ch [ i ], 1, m_tstr [ i ] );
			wctomb_s ( & converted, & ary_ch [ i ], 1, m_tstr [ i ] );
			++ i;
		}
		m_str.assign ( ary_ch.get (), str_size );


		//テクスチャを指定して	サイズ取得
		float dx = 0;	//補正位置
		for ( UINT i_c = 0; i_c < str_size; ++ i_c )
		{
			P_VxRct p = mvp_vx [ i_c ];
			TX tx = GameText::Inst ()->GetAsciiTx ( ary_ch [ i_c ] );
			USIZE us = Dx_UTL::TxSize ( tx );
			LONG w = GameText::Inst ()->GetAsciiW ( ary_ch [ i_c ] );

			p->SetSize ( 1.f * us.w, 1.f * us.h );
			p->SetPos ( m_pos.x + dx, m_pos.y );
			p->ApplyPos ();
			p->WriteVertexBuffer ();

			dx += w;	//次の頂点位置はテクスチャではなく文字から取得する
		}
	}


#endif // 0

}	//namespace GAME

