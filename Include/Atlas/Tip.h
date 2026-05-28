//=================================================================================================
//
//	Tip ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "../Define_Siv3D.h"
#include "../Define.h"
#include "Define_Atlas.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//固定サイズのピクセルデータ
	class Tip
	{
		//std::array < PIXEL, TIP_N >	m_pixels { 0 };
		std::unique_ptr < PIXEL [] >	m_pixels;

	public:
		Tip ();
		Tip ( const Tip & rhs );	//コピー可能
		~Tip ();

		Tip & operator = ( const Tip & rhs );	//代入演算子も定義が必要

		//参照元イメージと開始位置からデータ作成
		void ToTip ( const Image & img, const int32 x, const int32 y );

		//値を取得
		PIXEL GetPixel ( int32 x, int32 y ) const;
		s3d::Color GetColor(int32 x, int32 y) const { return Color::FromABGR(GetPixel(x, y)); }

		//メモリストリーム上に書込
		void ToMemStrm ( s3d::MemoryWriter & mw ) const;

		//メモリストリーム上から読込
		void FromMemStrm ( s3d::BinaryReader & br );


		//ハッシュ値 FNV-1a
		uint32_t HasFNV1a () const;

		//完全一致
		bool operator == ( const Tip & rhs ) const ;

		int32_t equal ( const Tip & rhs ) const;

		//0
		bool IsZero () const;

	};


}	//namespace GAME


