//=================================================================================================
//
//	Compressソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Compress.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	Compress::Compress ()
	{
	}

	Compress::Compress ( const Compress & rhs )	//代入可能
	{
		this->m_tiles = rhs.m_tiles;
	}

	Compress::~Compress ()
	{
	}

	void Compress::Do ( const Image & img )
	{
		//Imageを受け取り、Tileに分ける

		//Tile個数を計算
		int32 img_w = img.width ();
		int32 img_h = img.height ();

		//Tile個数
		m_w = 1 + ( ( img_w - 1 ) / TIP_W );
		m_h = 1 + ( ( img_h - 1 ) / TIP_H );
		size_t tile_n = m_w * m_h;
		m_tiles.resize ( tile_n );


		size_t id = 0;	//配置ID
		size_t index = 0;	//記録ID

		//Tileの幅高で保存のループ
		for ( int32 y = 0; y < img_h; y += TIP_H )
		{
			for ( int32 x = 0; x < img_w; x += TIP_W )
			{
				//対象がすべて空白だったらIDだけはカウントして続行
				if ( IsBlank ( img, x, y ) )
				{
					++ id;
					continue;
				}

//				s3d::Logger << U"(" << y << U", " << x << U")" ;
				m_tiles [ index ].SetId ( (uint32)id );
				m_tiles [ index ].ToTile ( img, x, y );

				++ id;
				++ index;
			}
		}
		m_tiles.resize ( index );
	}


	bool Compress::IsBlank( const Image & img, int32 x, int32 y ) const
	{
		int32 img_w = img.width ();
		int32 img_h = img.height ();

		for ( int32 ny = y; ny < y + TIP_H; ++ ny )
		{
			//元画像位置を逸脱したら終了
			if ( ny >= img_h ) { break; }

			for ( int32 nx = x; nx < x + TIP_W; ++ nx )
			{
				//元画像位置を逸脱したら脱出
				if ( nx >= img_w ) { break; }

				//１つでもアルファ値が０以外ならFを返して終了
				uint32 ui = img [ ny ][ nx ].asUint32 ();
				if ( 0 != (ui & 0xff000000) )
				{
					//s3d::Logger << img [ ny ][ nx ].asUint32 ();
					return F;
				}

				//値が０なら続行
			}
		}

		//すべて０ならT
		return T;
	}


	void Compress::TestMakeTx ()
	{
		//サイズ
		size_t sz = m_tiles.size ();

		//平方根　整数チェック
		double sqrt = std::sqrt ( sz );
		int32 sqrt_i = static_cast < int32 > ( sqrt );
		int32 revise = ( sqrt == sqrt_i ) ? 0 : 1;

		int32 w = revise + static_cast < int32 > ( std::floor ( sqrt ) );
		int32 h = w;

		s3d::Image img { (size_t)(w * TIP_W), (size_t)(h * TIP_H) };

#if 0

		for ( int y = 0; y < h * TIP_H; ++ y )
		{
			for ( int x = 0; x < w * TIP_W; ++ x )
			{
				img [ y ] [ x ] = s3d::Color::FromABGR ( 0xff8080ff );
			}
		}

#endif // 0


		//すべて書き出す

		//Tip位置
		int32 pos_x = 0;
		int32 pos_y = 0;

		//イメージにおける座標
		int32 img_x = 0;
		int32 img_y = 0;

		for ( Tile tile : m_tiles )
		{
			img_x = pos_x * TIP_W;
			img_y = pos_y * TIP_H;
//			s3d::Logger << U"(" << img_y << U", " << img_x << U")" ;

			//値を取得
			for ( int32 y = 0; y < TIP_H; ++ y )
			{
				for ( int32 x = 0; x < TIP_W; ++ x )
				{
//					s3d::Logger << U"(" << y << U", " << x << U")" ;
					uint32 ui_tip = tile.GetUint ( x, y );

					//※ Color.asUint32() で保存した値はABGR
					//img [ y ] [ x ] = Color::FromRGBA ( 0x8080ff );
					//img [ y ] [ x ] = Color::FromRGBA ( ui_tip );
					img [ img_y + y ] [ img_x + x ] = Color::FromABGR ( ui_tip );

					//uint32 ui = 0xff800000u;
					//ui |= x ^ y;
					//img [ img_y + y ] [ img_x + x ] = Color::FromABGR ( ui );
				}
			}

			Color clr = img [ img_y ] [ img_x ];
			//s3d::Logger << U"Color = " << clr ;

			//改行
			if ( ++ pos_x >= w )
			{
				pos_x = 0;
				++ pos_y;
			}
		}

#if 0

		s3d::Image img { TIP_W, TIP_H };

		size_t center = m_tiles.size () / 2;
//		m_tiles [ center ].TestMakeImg ( img ) ;
		m_tiles [ 11 ].TestMakeImg ( img ) ;

#if 0
		for ( int32 y = 0; y < TIP_H; ++ y )
		{
			for ( int32 x = 0; x < TIP_W; ++ x )
			{
//				img [ y ][ x ].FromABGR ( m_tip [ x + y * TIP_W ] );
//				img [ y ][ x ].FromABGR ( 0xff00ff00 );
//				img [ y ][ x ].FromABGR ( (uint32)0xffff00ffUL );
//				img [ y ][ x ] = Color ( 0x00, 0xFF, 0xFF, 0xFF );
				img [ y ][ x ] = Color ( (uint32)x, 0xFF, 0xFF, 0xFF );

			}
		}

#endif // 0
#endif // 0

		m_tx = s3d::Texture ( img );
//		m_tx = s3d::Texture ( U"Image\\014_中攻撃_06.png" );

	}

	void Compress::TestDraw ()
	{
		m_tx.draw ( 720, 0 );
	}


	//テクスチャを生成してポインタを返す
	P_Tx Compress::Tx ()
	{
		//サイズ
		size_t sz = m_tiles.size ();

		//平方根　整数チェック
		double sqrt = std::sqrt ( sz );
		int32 sqrt_i = static_cast < int32 > ( sqrt );
		int32 revise = ( sqrt == sqrt_i ) ? 0 : 1;

		int32 w = revise + static_cast < int32 > ( std::floor ( sqrt ) );
		int32 h = w;

		s3d::Image img { (size_t)(w * TIP_W), (size_t)(h * TIP_H) };



		//すべて書き出す

		//Tip位置
		int32 pos_x = 0;
		int32 pos_y = 0;

		//イメージにおける座標
		int32 img_x = 0;
		int32 img_y = 0;

		for ( Tile tile : m_tiles )
		{
			img_x = pos_x * TIP_W;
			img_y = pos_y * TIP_H;
//			s3d::Logger << U"(" << img_y << U", " << img_x << U")" ;

			//値を取得
			for ( int32 y = 0; y < TIP_H; ++ y )
			{
				for ( int32 x = 0; x < TIP_W; ++ x )
				{
//					s3d::Logger << U"(" << y << U", " << x << U")" ;
					uint32 ui_tip = tile.GetUint ( x, y );

					//※ Color.asUint32() で保存した値はABGR
					img [ img_y + y ] [ img_x + x ] = Color::FromABGR ( ui_tip );
				}
			}

			Color clr = img [ img_y ] [ img_x ];

			//改行
			if ( ++ pos_x >= w )
			{
				pos_x = 0;
				++ pos_y;
			}
		}


		//テクスチャを生成してポインタを返す
		return std::make_shared < s3d::Texture > ( img );
	}



	//テクスチャを生成してポインタを返す
	//解凍して生成
	P_Tx Compress::Tx_Thawing ()
	{
		//サイズ
		//size_t sz = m_w * m_h;
		s3d::Image img { (size_t)(m_w * TIP_W), (size_t)(m_h * TIP_H) };

		//Tip位置
		int32 pos_x = 0;
		int32 pos_y = 0;

		//イメージにおける座標
		int32 img_x = 0;
		int32 img_y = 0;


		uint32 index = 0;

		for ( Tile tile : m_tiles )
		{
			//イメージ位置
			img_x = pos_x * TIP_W;
			img_y = pos_y * TIP_H;
//			s3d::Logger << U"(" << img_y << U", " << img_x << U")" ;

			//記録IDとインデックスが異なるとき
			while ( index != tile.GetId () )
			{
				//すべて空白にして次へ
				for ( int32 y = 0; y < TIP_H; ++ y )
				{
					for ( int32 x = 0; x < TIP_W; ++ x )
					{
						img [ img_y + y ] [ img_x + x ] = Color::FromABGR ( 0 );
					}
				}
				++ index;

				//改行
				if ( ++ pos_x >= m_w )
				{
					pos_x = 0;
					++ pos_y;
				}
				//イメージ位置
				img_x = pos_x * TIP_W;
				img_y = pos_y * TIP_H;

			}


			//tileから値を取得して設定
			for ( int32 y = 0; y < TIP_H; ++ y )
			{
				for ( int32 x = 0; x < TIP_W; ++ x )
				{
//					s3d::Logger << U"(" << y << U", " << x << U")" ;
					uint32 ui_tip = tile.GetUint ( x, y );

					//※ Color.asUint32() で保存した値はABGR
					img [ img_y + y ] [ img_x + x ] = Color::FromABGR ( ui_tip );
				}
			}

			++ index;

			//Color clr = img [ img_y ] [ img_x ];

			//改行
			if ( ++ pos_x >= m_w )
			{
				pos_x = 0;
				++ pos_y;
			}
		}


		//テクスチャを生成してポインタを返す
		return std::make_shared < s3d::Texture > ( img );
	}


}	//namespace GAME
