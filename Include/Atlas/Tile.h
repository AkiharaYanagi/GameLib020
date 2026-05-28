//=================================================================================================
//
//	Tile ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Define_Atlas.h"
#include "../Define.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//Tipのpageとuv位置
	class Tile
	{
		int32_t		x{ 0 };	//元画像の座標X
		int32_t		y{ 0 };	//元画像の座標y

		uint32_t	page { 0 };	//配置ページ
		float		u{ 0 };	//page内UV座標　左上X
		float		v{ 0 };	//page内UV座標　左上Y

		//test
		bool		m_hash { F };	//ハッシュヒット時

	public:
		Tile ();
		Tile ( const Tile & rhs ) = default;	//コピー可能
		~Tile ();

		void SetPos ( int32_t px, int32_t py ) { x = px; y = py; }
		void SetPage ( int32_t n ) { page = n; }
		void SetUV ( float pu, float pv ) { u = pu; v = pv; }

		uint32_t GetPage() const { return page; }

		int32_t X() const { return x; }
		int32_t Y() const { return y; }

		float U() const { return u; }
		float V() const { return v; }

		//test
		bool GetHash() const { return m_hash; }
		void SetHash(bool b) { m_hash = b; }
	};

	//ハッシュからTileへのマップ
	using MapHashTile = std::unordered_map < uint32_t, Tile >;


}	//namespace GAME


