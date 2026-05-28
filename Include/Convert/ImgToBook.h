//=================================================================================================
//
//	ImgToBook ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "../Define_Siv3D.h"
#include "../Atlas/Define_Atlas.h"
#include "../Atlas/Book.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//名前空間内の自由関数

	//---------------------------------------------------------
	//.png画像.imgフォルダから作成
	Book CreateBookFromDir ( const s3d::String & dirpath );

	//Bookから.atlsの保存 Tip単位
	void SaveAtlas ( const s3d::String & filepath, const Book & book );


	//Bookから.atlsの保存 Image形式
	void SaveAtlasImg ( const s3d::String & filepath, const Book & book );

	//Bookから.atlsの保存 Image+lz4形式
	void SaveAtlasImgLz4 ( const s3d::String & filepath, const Book & book );


	//Bookから.atlsの保存 png形式
	void SaveAtlasPng ( const s3d::String & filepath, const Book & book );

	//Bookから.atlsの保存 png+lz4形式
	void SaveAtlasPngLz4 ( const s3d::String & filepath, const Book & book );


	//キャンバス辞書部分の共通化
	void SaveCanvasDic ( BinaryWriter & bw, const Book & book );

	//キャンバス辞書部分の共通化
	void SaveCanvasDic ( IWriter & writer, const Book & book );


	//---------------------------------------------------------
	//s3d::Textureはデバイス依存のため中身はpng形式で保存する
	//拡張子は.atls
	//void SaveAtlasPng ( const s3d::String & filepath, const Book & book );


	//C#からバイナリで.png形式をまとめた.imgファイルから作成
	Book CreateBookImg ( const s3d::String & filepath );

	//.Imgファイルを.atlsファイルに変換
	void ImgToAtlasFile ( const s3d::String & filepath );


}	//namespace GAME


