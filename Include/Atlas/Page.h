//=================================================================================================
//
//	Page ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "../Define_Siv3D.h"
#include "Define_Atlas.h"
#include "Compress.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//Compressまとめ
	class Page
	{
		//Image
		//std::array < Tip, ATLAS_TIP_N > m_page;
		std::unique_ptr < Tip[] > m_page;

		int32_t		m_nTip { 0 };

		//ハッシュ記録(ハッシュ値、元データインデックス)
//		std::unordered_map < uint32_t, size_t > map_hash_index;

		//ページID
		uint32_t	m_id { 0 };

	public:
		Page ();
		Page ( const Page & rhs ) = default;	//コピー可能
		~Page ();

		//ムーブコンストラクタ(unique_ptrのため)
		Page ( Page && p ) = default;
		Page & operator = ( Page && p ) = default;

		//追加
		bool AddCompress ( const Compress & cmprs, Canvas & canvas, MapHashTile & mht );

		//テクスチャ
		s3d::Texture Texture () const;

		//イメージ
		s3d::Image Image () const;
		const s3d::Image Image_c () const { return Image (); }

		//メモリストリームに書出
		void ToMemStrm ( s3d::MemoryWriter & mw ) const;

		//バイナリリーダから読込
		void FromMemStrm ( s3d::BinaryReader & br );

		//同じTipがあるかどうか
		//戻値：一致したインデックス
		bool SameTip ( const Tip & tip, int32_t & index ) const;
		bool SameTipHash ( const Tip & tip ) const;

		//対応するUV位置
		float U ( int32_t index ) const;
		float V ( int32_t index ) const;

		void HashCheck() const;

		//ページID
		uint32_t ID () const { return m_id; }
		void SetID ( uint32_t id ) { m_id = id; }
	};


}	//namespace GAME


