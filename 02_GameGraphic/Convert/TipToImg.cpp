//=================================================================================================
//
//	ImgToBookソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Convert/TipToImg.h"
#include <filesystem>

using namespace std;
namespace FS = std::filesystem;


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	Image TipToImg ( const Tip & tip )
	{
		s3d::Image img { (size_t)(TIP_W), (size_t)(TIP_H) };

		//イメージにおける座標
		int32 img_x = 0;
		int32 img_y = 0;

		//Tipスタート位置
		int32 tip_h = static_cast < int32 > ( TIP_H );
		int32 tip_w = static_cast < int32 > ( TIP_W );

		for ( int32 y = 0; y < tip_h; ++ y )
		{
			for ( int32 x = 0; x < tip_w; ++ x )
			{
				img[img_y][img_x] = tip.GetColor ( x, y );
				++ img_x;
			}
			img_x = 0;
			++ img_y;
		}

		return img;
	}

	Texture TipToTx(const Tip& tip)
	{
		return Texture { TipToImg ( tip ) };
	}

}	//namespace GAME
