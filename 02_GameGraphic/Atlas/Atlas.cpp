//=================================================================================================
//
//	Atlasソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Atlas/Atlas.h"

using namespace std;


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	void Atlas::DrawPos ( uint32_t indexTexture, float x, float y )
	{
		Canvas & cvs = m_id_canvas [ indexTexture ];

		//すべてのタイルを描画
		for ( const Tile & tl : cvs.GetTiles () )
		{
			s3d::Texture tx = m_txs [ tl.GetPage () ];
			s3d::RectF rect = s3d::RectF{ tl.U(), tl.V(), TIP_W, TIP_H };

			tx ( rect ).draw ( x + tl.X(), y + tl.Y() );

#if 0
			//hash test
			double s = 0.5;
			if (tl.GetHash())
			{
				tx ( rect ).scaled ( s ).draw ( x + tl.X() * s, y + tl.Y() * s, ColorF{ 1.0, 0.3, 0.3 } );
				//tx ( rect ).scaled ( s ).draw ( x + tl.X() * s, y + tl.Y() * s );
			}
			else
			{
				tx ( rect ).scaled ( s ).draw ( x + tl.X() * s, y + tl.Y() * s );
			}
#endif // 0

		}
	}

	void Atlas::DrawPosScl ( uint32_t indexTexture, VEC2 pos, VEC2 scl )
	{
		Canvas & cvs = m_id_canvas [ indexTexture ];
		double x = (double)pos.x;
		double y = (double)pos.y;

		//すべてのタイルを描画
		for ( const Tile & tl : cvs.GetTiles () )
		{
			s3d::Texture tx = m_txs [ tl.GetPage () ];
			s3d::RectF rect = s3d::RectF{ tl.U(), tl.V(), TIP_W, TIP_H };

			s3d::Vec2 s { (double)scl.x, (double)scl.y };
			s3d::Vec2 p { x + tl.X() * s.x, y + tl.Y() * s.y };

			tx ( rect ).scaled ( s ).draw ( p );

#if 0
			double sc = 0.5;
			s3d::Vec2 s { (double)sc, (double)sc };
			s3d::Vec2 p { x + tl.X() * s.x, y + tl.Y() * s.y };

			//hash test
			if (tl.GetHash())
			{
				//tx ( rect ).scaled ( s ).draw ( p, ColorF{ 1.0, 0.3, 0.3 } );
			}
			else
			{
				tx ( rect ).scaled ( s ).draw ( p );
			}
#endif // 0

		}
	}

	void Atlas::Draw ( uint32_t indexTexture, VEC2 pos, VEC2 scl, s3d::ColorF clrf )
	{
		Canvas & cvs = m_id_canvas [ indexTexture ];
		double x = (double)pos.x;
		double y = (double)pos.y;

		//すべてのタイルを描画
		for ( const Tile & tl : cvs.GetTiles () )
		{
			s3d::Texture tx = m_txs [ tl.GetPage () ];
			s3d::RectF rect = s3d::RectF{ tl.U(), tl.V(), TIP_W, TIP_H };

			s3d::Vec2 s { (double)scl.x, (double)scl.y };
			s3d::Vec2 p { x + tl.X() * s.x, y + tl.Y() * s.y };

			tx ( rect ).scaled ( s ).draw ( p, clrf );
		}
	}


	void Atlas::Clear ()
	{
		m_dic_pos.clear ();
		m_id_canvas.clear ();
	}

	s3d::Texture Atlas::Texture ()
	{
		s3d::Texture tx;

		if ( m_txs.size () < 1 ) { return tx; }

		return m_txs.front();
	}


	s3d::Texture Atlas::Texture ( size_t index )
	{
		s3d::Texture tx;

		if ( m_txs.size () <= index ) { return tx; }

		return m_txs[index];
	}


#if 0
	void Atlas::AddCompress(const Compress& cmprs, Canvas& canvas)
	{
		//Pageに追加
		bool bPage = m_pages.back().AddCompress ( cmprs, canvas );

		//追加できなかったとき
		if ( ! bPage )
		{
			cout << s3d::Unicode::ToUTF8 ( U"page_size = " ) << m_pages.size() << endl;

			Page page;

			//新規に追加
			m_pages.push_back ( std::move ( page ) );

			m_pages.back().AddCompress ( cmprs, canvas );
			//新規ページに追加できなかったら例外
		}

		canvas.SetTilePage ( static_cast < int32_t > ( m_pages.size() ) );


#if 0

		//辞書に登録
		m_dic_pos [ canvas.GetName() ] = canvas;



		const s3d::Array < Tile > & Tiles = canvas.GetTiles();
		size_t sz = Tiles.size ();
		size_t atlas_index = 0;
		for ( size_t tile_index = 0; tile_index < sz; ++ tile_index )
		{
			//配置
			m_pages [ atlas_index ] = Tiles [ tile_index ].GetTip ();
			++ atlas_index;
		}
		m_dic_pos [ pos_name ] = canvas;

#endif // 0
	}


	s3d::Texture Atlas::Texture ()
	{
		s3d::Texture tx;

		if ( m_pages.size () < 1 ) { return tx; }

		return m_pages.front().Texture();
	}


	s3d::Texture Atlas::Texture ( size_t index )
	{
		s3d::Texture tx;

		if ( m_pages.size () <= index ) { return tx; }

		return m_pages[index].Texture();
	}


	s3d::Image Atlas::Image ()
	{
		s3d::Image img;

		if ( m_pages.size () < 1 ) { return img; }

		return m_pages.front().Image();
	}


	s3d::Image Atlas::Image ( size_t index )
	{
		s3d::Image img;

		if ( m_pages.size () <= index ) { return img; }

		return m_pages[index].Image();
	}


	int32_t Atlas::N_Tip () const
	{
		int32_t count = 0;
		for ( const Page & pg : m_pages )
		{
			(void)pg;
		}
		return count;
	}
#endif // 0


	size_t Atlas::GetMetaSize () const
	{
		size_t size = 0;
		size += m_dic_pos.size() * sizeof ( Canvas );
		size += sizeof ( m_id_canvas );
		return size;
	}



}	//namespace GAME
