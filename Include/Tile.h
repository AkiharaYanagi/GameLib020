//=================================================================================================
//
//	Tile ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Define_Siv3D.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//画像の切り出した部分
	using Tip = s3d::Array < uint32 >;

	//切り出しサイズ
	const int32 TIP_W = 64;
	const int32 TIP_H = 64;
	const size_t TIP_N = TIP_W * TIP_H;



	//Tipまとめ
	class Tile
	{
		uint32	m_id { 0 };	//配置ID
		Tip		m_tip { 0 };

	public:
		Tile ();
		Tile ( const Tile & rhs );	//コピー可能
		~Tile ();

		void SetId ( uint32 id ) { m_id = id; }
		uint32 GetId () const { return m_id; }

		//参照元イメージと開始位置
		void ToTile ( const Image & img, int32 x, int32 y );

		//test
		void TestMakeImg ( Image & img );

		//値を取得
		uint32 GetUint ( int32 x, int32 y ) const;

		bool Compare ( const Tile & rhs ) const;

		//-------------------------------------------
		//シリアライズ可能にするためのテンプレート関数定義
		template < class T >
		void SIV3D_SERIALIZE ( T & t )
		{
			t ( m_id, m_tip );
		}

		//-------------------------------------------
		//MemoryStream上に展開
		void WriteMemoryStream ( s3d::MemoryWriter & mw );

		//MemoryStreamから読込
		void LoadMemoryStream ( s3d::MemoryReader & mr );
	};

	using P_Tile = std::shared_ptr < Tile >;


}	//namespace GAME


