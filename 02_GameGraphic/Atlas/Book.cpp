//=================================================================================================
//
//	Bookソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Atlas/Book.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	Book::Book ()
	{
		//最初の１つ
		m_pages.resize ( 1 );
		m_pages.back().SetID ( 0 );
	}


	Book::~Book ()
	{
	}

	void Book::Clear ()
	{
		m_pages.clear ();
		m_dic_pos.clear ();
	}


	void Book::AddCompress ( const Compress & cmprs, Canvas & canvas, MapHashTile & mht )
	{
		//Pageに追加
		bool bPage = m_pages.back().AddCompress ( cmprs, canvas, mht );

		//追加できなかったとき
		if ( ! bPage )
		{
			//新規に追加
			Page page;
			//IDは追加前のページ数と同じ
			page.SetID ( static_cast < uint32_t > ( m_pages.size() ) );
			m_pages.push_back ( std::move ( page ) );

			bool bExcept = m_pages.back().AddCompress ( cmprs, canvas, mht );

			//新規ページに追加できなかったら例外
			(void)bExcept;
		}

#if 0
		//※　ハッシュチェック時にはページを一括追加しない
		int32_t page_index = -1 + static_cast < int32_t > ( m_pages.size() );
		canvas.SetTilePage ( page_index );

#endif // 0
	}


	int32_t Book::N_Tip () const
	{
		int32_t count = 0;
		for ( const Page & pg : m_pages )
		{
			(void)pg;
		}
		return count;
	}

	void Book::CopyFromAryCanvas ( const AryCanvas & aryCnvs )
	{
		m_ary_canvas = aryCnvs;
	}

	void Book::HashCheck () const
	{
		for ( const Page & page : m_pages )
		{
			page.HashCheck ();
		}
	}

}	//namespace GAME
