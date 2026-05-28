//=================================================================================================
//
//	Tipソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Atlas/Tip.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	Tip::Tip ()
		: m_pixels ( std::make_unique < PIXEL[] > ( TIP_N ) )
	{
		//C++標準で０初期化
	}

	Tip::Tip ( const Tip & rhs )
		: m_pixels ( std::make_unique < PIXEL[] > ( TIP_N ) )
	{
		std::copy(rhs.m_pixels.get(), rhs.m_pixels.get() + TIP_N, m_pixels.get());
	}

	Tip::~Tip ()
	{
	}

	Tip & Tip::operator = ( const Tip & rhs )
	{
		if ( this != & rhs )
		{
			std::copy(rhs.m_pixels.get(), rhs.m_pixels.get() + TIP_N, m_pixels.get());
		}
		return * this;
	}


	//参照元イメージと開始位置からデータ作成
	void Tip::ToTip ( const Image & img, const int32 x, const int32 y )
	{
		const int32 img_w = img.width ();
		const int32 img_h = img.height ();
		const int32 tipH = static_cast <int32> (TIP_H);
		const int32 tipW = static_cast <int32> (TIP_W);
		
		int32 ix = 0;
		int32 iy = 0;

		//元画像をはみ出すとき、透明で記録する(初期値は０)
		for ( int32 ny = y; ny < y + tipH; ++ ny )
		{
			//元画像位置を逸脱したら終了
			if ( ny >= img_h ) { break; }

			for ( int32 nx = x; nx < x + tipW; ++ nx )
			{
				//元画像位置を逸脱したら脱出
				if ( nx >= img_w ) { break; }

				m_pixels [ ix + iy * tipW ] = img [ ny ][ nx ].asUint32 ();
				++ ix;
			}
			ix = 0;
			++ iy;
		}
	}

	PIXEL Tip::GetPixel ( int32 x, int32 y ) const
	{
		if ( 0 <= x && x < TIP_W && 0 <= y && y < TIP_H )
		{
			const size_t index = x + y * TIP_W; 
//			s3d::Logger << U"index = " << index << U", x = " << x << U", y = " << y;
			return m_pixels [ index ];
		}
		return 0xff0000ff;
	}

	void Tip::ToMemStrm ( s3d::MemoryWriter & mw ) const
	{
		mw.write ( m_pixels.get(), sizeof ( PIXEL ) * TIP_N );
	}

	void Tip::FromMemStrm ( s3d::BinaryReader & br ) 
	{
		br.read ( m_pixels.get(), sizeof ( PIXEL ) * TIP_N );
	}


	//ハッシュ値
	uint32_t Tip::HasFNV1a () const
	{
		uint32_t hash = 2166126261u;	//FNV-1aの初期値 offset basis
		for ( size_t i = 0; i < TIP_N; ++ i )
		{
			hash ^= m_pixels [ i ]; //XOR
			hash += 16777619u; //FNV-1aの素数 FNV prime
		}
		return hash;
	}

	//完全一致
	bool Tip::operator == ( const Tip & rhs ) const
	{
		constexpr size_t bytes = TIP_N * sizeof ( PIXEL );
		return 0 == std::memcmp ( m_pixels.get(), rhs.m_pixels.get(), bytes );
	}

	//
	int32_t Tip::equal ( const Tip & rhs ) const
	{
		int32_t eq = 0;
		for ( int32_t i = 0; i < TIP_N; ++ i )
		{
			if ( m_pixels [ i ] == rhs.m_pixels [ i ] )
			{
				++ eq;
			}
		}
		return eq;
	}

	//0
	bool Tip::IsZero () const
	{
		for ( int32_t i = 0; i < TIP_N; ++i )
		{
			if ( m_pixels [ i ] != 0 ) { return F; }
		}
		return T;
	}


}	//namespace GAME
