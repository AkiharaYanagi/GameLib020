//=================================================================================================
//
//	Book ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "../Define_Siv3D.h"
#include "Define_Atlas.h"
#include "Page.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	using MapNameCanvas = std::unordered_map < String, Canvas >;
	using AryCanvas = s3d::Array < Canvas >;


	//Pageまとめ
	class Book
	{
		//Page
		s3d::Array < Page > m_pages;

		//元画像の位置を保存する辞書
		MapNameCanvas	m_dic_pos;
		AryCanvas		m_ary_canvas;

		MapHashTile		m_hash_tile;

	public:
		Book ();
		Book ( const Book & rhs ) = default;	//コピー可能

		//ムーブコンストラクタ (戻値生成のため)
		Book ( Book && p ) noexcept = default;
		Book & operator = ( Book && p ) noexcept = default;

		~Book ();

		void Clear ();

		//CompressをPageに追加してBookに保存
		// cmprs: Tipにまとめたビットデータ
		// canvas: アトラステクスチャにおけるuv位置を保存するCanvas
		// mht: ハッシュチェック用のマップ
		void AddCompress ( const Compress & cmprs, Canvas & canvas, MapHashTile & mht );
		void AddMap(const String & pos_name, const Canvas & canvas) { m_dic_pos[pos_name] = canvas; }
		void AddCanvas(const Canvas& canvas) { m_ary_canvas.push_back(canvas); }


		int32_t N_Tip () const;

		const s3d::Array < Page > & GetPages () const { return m_pages; }
		s3d::Array < Page > & GetvPages () { return m_pages; }


		Canvas GetCanvas ( const String & name ) const
		{
			auto it = m_dic_pos.find ( name );
			if ( it != m_dic_pos.end () )
			{
				return it->second;
			}
			return Canvas ();
		}


		const MapNameCanvas & GetMap () const { return m_dic_pos; }
		const AryCanvas & GetAryCanvas () const { return m_ary_canvas; }

		void CopyFromAryCanvas ( const AryCanvas & aryCnvs );

		void HashCheck() const;
	};


}	//namespace GAME


