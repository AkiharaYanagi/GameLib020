//=================================================================================================
//
//	ImgToAtlas ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "../Define.h"
#include "../Atlas/Define_Atlas.h"
#include "../Atlas/Atlas.h"
#include "../Atlas/Book.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//名前空間内の自由関数

	//----------------------------------------------
	//Atlasファイルの読込

	//Atlasの読込(メモリ上でTip単位)
	Atlas LoadAtlas ( const s3d::String & filename );

	//Atlasの読込(メモリ上でImage単位)
	Atlas LoadAtlasImg ( const s3d::String & filename );

	//Atlasの読込(メモリ上でpng形式)
	Atlas LoadAtlasPng ( const s3d::String & filename );

	//Atlasの読込(メモリ上でpng+lz4形式)
	Atlas LoadAtlasPngLz4 ( const s3d::String & filename );


	//Canvas辞書部分の共通化
	void LoadCanvasDic ( BinaryReader & br, Atlas & atlas );


	//----------------------------------------------
	//Book to Atlas
	Atlas BookToAtlas ( const Book & book );
	P_Atlas BookToP_Atlas(const Book& book);


	//----------------------------------------------
	//C#からバイナリで.png形式をまとめた.imgファイルから作成
	//.imgファイルからBookを経由してP_Atlasを作成
	P_Atlas CreateAtlasImg ( const s3d::String & filepath );

	//.atlasファイルからP_Atlasを作成
	P_Atlas LoadpAtlasImg ( const s3d::String & filepath );

	//imgディレクトリからBookを経由してP_Atlasを作成
	P_Atlas CreateAtlasImgDir ( const s3d::String & dirpath );


}	//namespace GAME


