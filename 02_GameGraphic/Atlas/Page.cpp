//=================================================================================================
//
//	Pageソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Atlas/Page.h"
//#include "Utl/Utl.h"
//#include "Utl/G_Log.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	Page::Page() : m_page ( std::make_unique < Tip[] > ( ATLAS_TIP_N ) )
	{
	}


	Page::~Page ()
	{
	}

	bool Page::AddCompress ( const Compress & cmprs, Canvas & canvas, MapHashTile & mht )
	{
		const s3d::Array < Tip > & Tips = cmprs.GetrTips();
		const int32_t tip_sz = static_cast < int32_t > ( Tips.size () );
		const int32_t tip_n = static_cast < int32_t > ( ATLAS_TIP_N );

		//std::cout << Prt(U"Pageに追加") << tip_sz << std::endl;

		//１回で最大サイズより大きいときは例外
		if ( tip_n < tip_sz ) { throw; }
	
		//はみ出すとき終了
		if ( m_nTip + tip_sz > tip_n )
		{
			return F;
		}

		//保存
		s3d::Array < Tile > & tiles = canvas.GetrTiles ();

		size_t index = 0;
		for ( const Tip & tip : Tips )
		{

#define SAME_TIP 0
#if SAME_TIP
			//引数でハッシュチェック用mapを受け取る

			//ハッシュの確認
			uint32_t hash = tip.HasFNV1a();
			auto it = mht.find ( hash );

			if ( it == mht.end() )
			{
				//ハッシュがないときは追加
				
				//Pageにおける位置
				tiles [ index ].SetUV ( U ( m_nTip ), V ( m_nTip ) );
				tiles [ index ].SetPage ( m_id );	//自ページ

				//ハッシュ記録
				mht[hash] = tiles[index];

				//Tipを記録
				m_page [ m_nTip ] = tip;

				++ m_nTip;
				++ index;
			}
			else
			{
				//ハッシュがあるときは指定位置とページを再利用して保存
				tiles [ index ].SetUV ( it->second.U(), it->second.V() );
				tiles [ index ].SetPage ( it->second.GetPage() );
				tiles [ index ].SetHash ( T );

				++ G::HASH_HIT;
				G::ARY_TIP.push_back(tip);

				++ index;
			}
#if 0

			auto it = map_hash_index.find ( hash );
			//ない場合it.end();

			if ( it == map_hash_index.end() )
			{
				//ハッシュがないときは追加
				//Pageにおける位置
				tiles [ index ].SetUV ( U ( m_nTip ), V ( m_nTip ) );
				m_page [ m_nTip ] = tip;

				//ハッシュ記録
				map_hash_index[tip.HasFNV1a()] = m_nTip;
				++ m_nTip;
				++ index;
			}
			else
			{
				//ハッシュがあるときは位置のみ再利用して保存
			}

#endif // 0


#if 0

			//Page内で同じTipが既にあるとき、位置のみ保存
			int32_t index_same = 0;
			if ( SameTip ( tip, index_same ) )
			{
				//Pageにおける位置
				float u = static_cast < float > ( TIP_W * ( index_same % ATLAS_X ) );
				float v = static_cast < float > ( TIP_H * ( index_same / ATLAS_X ) );
				tiles [ index ].SetUV ( u, v );
				++ index;
			}
			else
			{
				//Pageにおける位置
				float u = static_cast < float > ( TIP_W * ( m_nTip % ATLAS_X ) );
				float v = static_cast < float > ( TIP_H * ( m_nTip / ATLAS_X ) );
				tiles [ index ].SetUV ( u, v );

				m_page [ m_nTip ] = tip;

				//ハッシュ記録
				map_hash_index[tip.HasFNV1a()] = m_nTip;

				++ m_nTip;
				++ index;
			}

#endif // 0


#else 	//SAME_TIP

			//通常時
			(void)mht;

			//Pageにおける位置
			float u = U ( m_nTip );
			float v = V ( m_nTip );
			tiles [ index ].SetUV ( u, v );

			m_page [ m_nTip ] = tip;

			++ m_nTip;
			++ index;

#endif // SAME_TIP

		}

		return T;

#if 0

		int32 tip_index = 0;
		const int32 SIZE = static_cast < int32 > ( ary_cmprs.size() );

		for ( int32 cmprs_index = 0; cmprs_index < SIZE; ++ cmprs_index )
		{
			const Compress & cmprs = ary_cmprs [ cmprs_index ];

			const s3d::Array < Tip > & Tips = cmprs.GetrTips();
			const int32 sz = static_cast < int32 > ( Tips.size () );
			const int32 tip_n = static_cast < int32 > ( ATLAS_TIP_N );

			//はみ出すとき終了
			if ( tip_index + sz > tip_n )
			{
				break;
			}

			for ( const Tip & tip : Tips )
			{
				m_page [ tip_index ] = tip;

				if ( ++ tip_index >= tip_n ) { break; }
			}
		}

#endif // 0
	}


	s3d::Texture Page::Texture () const
	{
		//テクスチャを生成して返す
		return s3d::Texture ( Image () );
	}


	s3d::Image Page::Image () const
	{
		s3d::Image img { (size_t)(ATLAS_X), (size_t)(ATLAS_Y) };

		//イメージにおける座標
		int32 img_x = 0;
		int32 img_y = 0;

		//Tipスタート位置
		int32 img_x0 = 0;
		int32 img_y0 = 0;
		int32 tip_h = static_cast < int32 > ( TIP_H );
		int32 tip_w = static_cast < int32 > ( TIP_W );
		int32 atlas_x = static_cast < int32 > ( ATLAS_X );

		//Tipを書出
		for ( int32 i = 0; i < ATLAS_TIP_N; ++ i )
		{
			for ( int32 y = 0; y < tip_h; ++ y )
			{
				for ( int32 x = 0; x < tip_w; ++ x )
				{
					img[img_y][img_x] = m_page [ i ].GetColor ( x, y );
					++ img_x;
				}
				img_x = img_x0;
				++ img_y;
			}

			img_x0 += tip_w;

			//Tip改行
			if ( img_x0 >= atlas_x )
			{
				img_x0 = 0;
				img_y0 += tip_h;
			}

			img_x = img_x0;
			img_y = img_y0;
		}	

		//イメージを返す
		return img;
	}

	//メモリストリームに書出
	void Page::ToMemStrm ( s3d::MemoryWriter & mw ) const
	{
		//Tip個数
		mw.write ( static_cast < uint32 > ( m_nTip ) );
		//std::cout << "m_nTip = " << m_nTip << std::endl;

		for ( int32_t i = 0; i < m_nTip; ++ i )
		{
			m_page [ i ] .ToMemStrm ( mw );
		}
	}

	//メモリストリームから読込
	void Page::FromMemStrm ( s3d::BinaryReader & br )
	{
		//Tip個数
		uint32 nTip = 0;
		br.read ( & nTip, sizeof ( uint32 ) );
		m_nTip = static_cast < int32_t > ( nTip );

		//std::cout << "m_nTip = " << m_nTip << std::endl;

		for ( int32_t i = 0; i < m_nTip; ++ i )
		{
			m_page [ i ] .FromMemStrm ( br );
		}
	}


	bool Page::SameTip ( const Tip & tip, int32_t & index ) const
	{
		//std::cout << Prt (U"同値チェック: ") << m_nTip << std::endl;

		for ( int32_t i = 0; i < m_nTip; ++ i )
		{
			//ハッシュチェック
			if ( SameTipHash ( tip ) )
			{
				//完全同一かチェック
				if ( m_page[i] == tip )
				{
					index = i;
					return T;	//インデックスを記録して終了
				}
			}
		}
		return F;
	}

	bool Page::SameTipHash ( const Tip & tip ) const
	{
		uint32_t hash = tip.HasFNV1a();

//		std::cout << "ハッシュチェック: " << hash << std::endl;

		for ( int32_t i = 0; i < m_nTip; ++ i )
		{
			uint32_t hash_i = m_page[i].HasFNV1a();
			if ( hash_i == hash )
			{
				//std::cout << hash_i << Prt(U" == ") << hash << std::endl;
				return T;
			}
//			std::cout << hash_i << Prt(U" != ") << hash << std::endl;
		}
		return F;
	}


	float Page::U ( int32_t index ) const
	{
		return static_cast < float > ( TIP_W * ( index % ATLAS_TIP_X ) );
	}

	float Page::V ( int32_t index ) const
	{
		return static_cast < float > ( TIP_H * ( index / ATLAS_TIP_X ) );
	}


	void Page::HashCheck() const
	{
		s3d::Array < uint32_t > aryHash;

		for ( int32_t i = 0; i < m_nTip; ++ i )
		{
			uint32_t hash =  m_page[i].HasFNV1a();

			for (uint32_t h : aryHash)
			{
				if (h == hash)
				{
					return;
				}
			}
			aryHash.push_back(hash);

			//std::cout << "index = " << i << ", hash = " << hash << std::endl;
		}
	}

}	//namespace GAME
