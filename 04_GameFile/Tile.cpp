//=================================================================================================
//
//	Tileソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Tile.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	Tile::Tile ()
	{
		m_tip.resize ( TIP_N );
	}

	Tile::Tile ( const Tile & rhs )
	{
		this->m_id = rhs.m_id;
		this->m_tip = rhs.m_tip;	//即値代入
	}

	Tile::~Tile ()
	{
	}


	//参照元イメージと開始位置
	void Tile::ToTile ( const Image & img, int32 x, int32 y )
	{
		int32 img_w = img.width ();
		int32 img_h = img.height ();
		
		int32 ix = 0;
		int32 iy = 0;

		//元画像をはみ出すとき、透明で記録する(初期値は０)
		for ( int32 ny = y; ny < y + TIP_H; ++ ny )
		{
			//元画像位置を逸脱したら終了
			if ( ny >= img_h ) { break; }

			for ( int32 nx = x; nx < x + TIP_W; ++ nx )
			{
				//元画像位置を逸脱したら脱出
				if ( nx >= img_w ) { break; }

				m_tip [ ix + iy * TIP_W ] = img [ ny ][ nx ].asUint32 ();
				++ ix;
			}
			ix = 0;
			++ iy;
		}

#if 0

		for ( int32 ny = y; ny < y + TIP_H; ++ ny )
		{
			for ( int32 nx = x; nx < x + TIP_W; ++ nx )
			{
				//通常記録
				if ( ny < img_h && nx < img_w )
				{
//					Logger << U"iy = " << iy << U", ix = " << ix << U", ny = " << ny << U", nx = " << nx;
					m_tip [ ix + iy * TIP_W ] = img [ ny ][ nx ].asUint32 ();
				}
				else
				{
					//元画像をはみ出すとき、透明で記録する
//					Logger << U"iy = " << iy << U", ix = " << ix << U", ny = " << ny << U", nx = " << nx;
					m_tip [ ix + iy * TIP_W ] = 0x00000000u;
				}

				++ ix;

				//はみ出し時、tip側の位置でループ終了
				if ( ix >= TIP_W ) { break; }
			}
			ix = 0;
			++ iy;

			//はみ出し時、tip側の位置でループ終了
			if ( iy >= TIP_H ) { break; }
		}

#endif // 0
	}

	void Tile::TestMakeImg ( Image & img )
	{
		for ( int32 y = 0; y < TIP_H; ++ y )
		{
			for ( int32 x = 0; x < TIP_W; ++ x )
			{

//				img [ y ][ x ].FromABGR ( m_tip [ x + y * TIP_W ] );
//				img [ y ][ x ] = Color ( 0xFF, 0xFF, 0xFF, 0xFF );

				//※ Color.asUint32() で保存した値はABGR
//				img [ y ][ x ] = Color::FromRGBA ( m_tip [ x + y * TIP_W ] );
				img [ y ][ x ] = Color::FromABGR ( m_tip [ x + y * TIP_W ] );
			}
		}
	}


	uint32 Tile::GetUint ( int32 x, int32 y ) const
	{
		if ( 0 <= x && x < TIP_W && 0 <= y && y < TIP_H )
		{
			size_t index = x + y * TIP_W; 
//			s3d::Logger << U"index = " << index << U", x = " << x << U", y = " << y;
			return m_tip [ index ];
		}
		return 0xff0000ff;
	}

	bool Tile::Compare ( const Tile & rhs ) const
	{
		if ( m_id != rhs.m_id ) { return F; }

		size_t index = 0;
		for	( uint32 i : m_tip )
		{
			if ( i != rhs.m_tip [ index ] )
			{
//				uint32 tip = rhs.m_tip [ index ];
				return F;
			}
			++ index;
		}
		return T;
	}

	//MemoryStream上に展開
	void Tile::WriteMemoryStream ( s3d::MemoryWriter & mw )
	{
		//ID [4byte]
		mw.write ( m_id );

		//個数は固定 TIP_N

		//データ
		for ( uint32 i : m_tip )
		{
			mw.write ( i );
		}
	}

	//MemoryStreamから読込
	void Tile::LoadMemoryStream ( s3d::MemoryReader & mr )
	{
		//ID [4byte]
		mr.read ( m_id );

		//個数は固定 TIP_N

		//データ
		m_tip.clear ();
		m_tip.resize ( TIP_N );
		
		for ( size_t index = 0; index < TIP_N; ++ index )
		{
			mr.read ( m_tip [ index ] );
		}
	}


}	//namespace GAME
