//=================================================================================================
//
//	Compressソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Atlas/Compress.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	Compress::Compress ()
	{
	}

	Compress::~Compress ()
	{
	}

	void Compress::Do ( const Image & img, Canvas & cnvs  )
	{
		//Imageを受け取り、Tipに圧縮

		//Tip個数を計算
		int32_t img_w = img.width ();
		int32_t img_h = img.height ();
		cnvs.SetTxWH ( img_w, img_h );

		//Tile個数
		int32_t m_w = 1 + ( ( img_w - 1 ) / TIP_W );
		int32_t m_h = 1 + ( ( img_h - 1 ) / TIP_H );
		size_t tile_n = static_cast < size_t > ( m_w * m_h );

		//空白フラグ
		s3d::Array < bool > blank ( tile_n, F );	//最大タイル数


		//事前空白チェック
		size_t ActiveCount = 0;		//有効数	
		size_t index = 0;	//全体インデックス
		for ( int32 y = 0; y < img_h; y += TIP_H )
		{
			for ( int32 x = 0; x < img_w; x += TIP_W )
			{
				//対象がすべて空白だったらチェック
				if ( IsBlank ( img, x, y ) )
				{
					blank [ index ] = T;
				}
				else
				{
					++ ActiveCount;		//有効数
				}

				++ index;	//全体インデックス
			}
		}
		m_tips.resize ( ActiveCount );	//有効Tip数で確保
		cnvs.SetTileSize ( static_cast < int32_t > ( ActiveCount ) );	//有効Tip数で確保
		cnvs.SetTileWH ( m_w, m_h );


		//保存のループ
		size_t activeIndex = 0;	//有効インデックス
		index = 0;	//全体インデックス
		for ( int32 y = 0; y < img_h; y += TIP_H )
		{
			for ( int32 x = 0; x < img_w; x += TIP_W )
			{
				//空白ならスキップ
				if ( blank [ index ] )
				{
				}
				else
				{
					//Tipに保存
					m_tips [ activeIndex ].ToTip ( img, x, y );

					//Canvasに保存
					int32_t i = static_cast < int32_t > ( activeIndex );
					cnvs.SetTilePos ( i, x, y );

					++ activeIndex;	//有効インデックス
				}

				++ index;	//全体インデックス
			}
		}
	}


	bool Compress::IsBlank( const Image & img, int32 x, int32 y ) const
	{
		int32 img_w = img.width ();
		int32 img_h = img.height ();
		int32 tip_h = static_cast < int32 > ( TIP_H );
		int32 tip_w = static_cast < int32 > ( TIP_W );

		for ( int32 ny = y; ny < y + tip_h; ++ ny )
		{
			//元画像位置を逸脱したら終了
			if ( ny >= img_h ) { break; }

			for ( int32 nx = x; nx < x + tip_w; ++ nx )
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


	s3d::Texture Compress::Texture () const
	{
		//サイズ
		const size_t tipCount = m_tips.size ();
		if ( 0 == tipCount )
		{
			return s3d::Texture ();
		}

		//保存は１次配列なので、平方根で幅高を決定
		//平方根　整数チェック
		// ceil ( x ) はx以上の最小の整数を返す
		double sqrt = std::sqrt ( tipCount );
		size_t ceiling = static_cast < size_t > ( std::ceil ( sqrt ) );
		const size_t IMG_W = ceiling * TIP_W;
		const size_t IMG_H = ceiling * TIP_H;


		//書出イメージ作成 C6262 ヒープ
		//s3d::Image img { (size_t)(w * TIP_W), (size_t)(h * TIP_H) };
		std::unique_ptr < s3d::Image > img = std::make_unique < s3d::Image > ( IMG_W, IMG_H );


		//Tip位置
		uint32 pos_x = 0;
		uint32 pos_y = 0;

		for ( const Tip & tip : m_tips )
		{
			//書出イメージにおける基準座標
			const uint32 img_x = pos_x * TIP_W;
			const uint32 img_y = pos_y * TIP_H;
//			s3d::Logger << U"(" << img_y << U", " << img_x << U")" ;

			//値を取得
			for ( uint32 y = 0; y < TIP_H; ++ y )
			{
				for ( uint32 x = 0; x < TIP_W; ++ x )
				{
					//分割線
					if ( x == 0 || y == 0 || x + 1 == TIP_W || y + 1 == TIP_H )
					{
						(*img) [ img_y + y ] [ img_x + x ] = Color::FromABGR ( 0xff0000ff );
						continue;
					}

					// s3d::Logger << U"(" << y << U", " << x << U")" ;

					//※ Color.asUint32() で保存した値はABGR
					(*img) [ img_y + y ] [ img_x + x ] = tip.GetColor ( x, y );
				}
			}

			//改行
			if ( ++ pos_x >= ceiling )
			{
				pos_x = 0;
				++ pos_y;
			}
		}

		//テクスチャを生成して返す
		return s3d::Texture ( *img );
	}


}	//namespace GAME
