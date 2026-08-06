//=================================================================================================
//
//	Canvas ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "../Define_Siv3D.h"
#include "Tile.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//１枚の画像単位でTileまとめ
	class Canvas
	{
		s3d::String m_name;	//画像名
		s3d::Array < Tile > m_tiles;

		//保存元の記録
		//タイル個数
		int32_t		m_w { 0 };
		int32_t		m_h { 0 };

		//元テクスチャサイズ
		int32_t		m_tx_w { 0 };
		int32_t		m_tx_h { 0 };

	public:
		Canvas ();
		Canvas ( const Canvas & rhs ) = default;	//コピー可能
		~Canvas ();

		void SetName(const s3d::String& name) { m_name = name; }
		const s3d::String & GetName() const { return m_name; }

		void SetTileSize (int32_t size ) { m_tiles.resize ( size ); }
		void SetTile(int32_t index, const Tile& tile) { m_tiles[index] = tile; }
		void SetTilePos(int32_t index, int32_t x, int32_t y) { m_tiles[index].SetPos(x, y); }
		void SetTilePage ( int32_t nPage );
		void SetTileWH(int32_t w, int32_t h) { m_w = w; m_h = h; }
		void SetTxWH ( int32_t w, int32_t h ) { m_tx_w = w; m_tx_h = h; }

		const s3d::Array < Tile > & GetTiles () const { return m_tiles; }
		s3d::Array < Tile > & GetrTiles () { return m_tiles; }

		int32_t W() const { return m_w; }
		int32_t H() const { return m_h; }

		int32_t TxW () const { return m_tx_w; }
		int32_t TxH () const { return m_tx_h; }
	};


}	//namespace GAME


