//=================================================================================================
//
//	ImgToTip ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Convert/ImgToTip.h"
#include <filesystem>
//#include "Utl/G_Log.h"


using namespace std;
namespace FS = std::filesystem;


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	Compress ImgToCompress ( const String & filename )
	{
		Canvas canvas;
		canvas.SetName ( filename );

		Image img ( filename );

		Compress cmpr;
		cmpr.Do ( img, canvas );

		return cmpr;
	}

	void TestCompress ( const Compress & cmpr )
	{
		const Array < Tip > ary_tip = cmpr.GetrTips ();
		cout << "tip size:" << ary_tip.size () << endl;

#if 0

		for ( const Tip & tip : ary_tip )
		{
			G::ARY_TIP.push_back ( tip );

			Array < int32_t > ary_eq;

			for ( const Tip & tip_rhs : ary_tip )
			{

				if ( tip == tip_rhs )
				{
					++ G::HASH_HIT;
					G::ARY_TIP_HUSH.push_back ( tip ); 
				}

#if 0
				int32_t eq = tip.equal ( tip_rhs );
				ary_eq.push_back ( eq );
#endif // 0
			}


#if 0

			ary_eq.rsort ();

			ostringstream oss;
			for ( int i = 0; i < 10; ++ i )
			{
				oss << setfill ( '0' ) << setw ( 4 ) << ary_eq [ i ] << ",";
			}
			cout << oss.str() << endl;

#endif // 0
		}


#endif // 0
	}


}	//namespace GAME
