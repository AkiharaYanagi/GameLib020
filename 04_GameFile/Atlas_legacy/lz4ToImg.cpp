//=================================================================================================
//
//	lz4ToImgソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "lz4ToImg.h"
#include "Atlas_legacy.h"
#include <filesystem>

using namespace std;
namespace FS = std::filesystem;


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	void lz4ToImg(const s3d::String& filepath)
	{
		//ファイル読込
		s3d::BinaryReader br { filepath };

		//圧縮サイズ
		size_t cmprsdSz = br.size();

		//元サイズを読取
		size_t originSz = 0;
		br.read ( originSz );

		//圧縮データを読取
		s3d::Blob cmprsBlob { cmprsdSz };
		br.read ( cmprsBlob.data(), sizeof ( originSz ), cmprsdSz );

		//解凍サイズ
		int dcmprsSz = (int)originSz;
		//std::vector < char > dcmprsBuf ( dcmprsSz );
		s3d::Blob dcmprsBuf ( originSz );

		//解凍
		LZ4_decompress_safe ( (const char *)cmprsBlob.data(), (char*)dcmprsBuf.data(), (int)cmprsdSz, dcmprsSz );

//		size_t szDmprsBuf = dcmprsBuf.size ();
		s3d::MemoryReader mr { dcmprsBuf };

		//レガシーアトラスに変換
		legacy::Atlas atlas;
		atlas.LoadMemoryStream ( mr );

		//Imageをpng形式で書き出し
		atlas.ToImg ( FileSystem::ParentPath ( filepath ) );
	}

}	//namespace GAME
