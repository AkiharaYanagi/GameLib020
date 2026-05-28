//=================================================================================================
//
//	Atlas ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "../Define_Siv3D.h"
#include "Define_Atlas.h"
#include "Compress.h"
#include "Canvas.h"
#include "Page.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	using MapNameCanvas = std::unordered_map < String, Canvas >;
	using AryCanvas = s3d::Array < Canvas >;


	//Pageを変換したテクスチャを持つ
	class Atlas
	{
		//テクスチャ
		s3d::Array < s3d::Texture > m_txs;	//自動コピー不可、ムーブ可能

		//元画像の位置を保存する辞書
		MapNameCanvas	m_dic_pos;
		AryCanvas		m_id_canvas;

	public:

		//--------------------------------------------------------
		Atlas () = default;
		~Atlas () = default;

		//E1776　のためにコピーコンストラクタを削除
		//Atlas ( const Atlas & rhs ) = default;	//コピー可能->不可
		Atlas ( const Atlas& rhs ) = delete;
		Atlas& operator = ( const Atlas& rhs ) = delete;

		//ムーブコンストラクタ (戻値生成のため)
		Atlas ( Atlas && p ) noexcept = default;
		Atlas & operator = ( Atlas && p ) noexcept = default;

		//--------------------------------------------------------


		void Draw ( uint32_t indexTexture, float x, float y );

		void Clear ();

		void AddTexture ( const s3d::Texture & tx ) { m_txs.push_back ( tx ); }

		void AddCanvas ( const Canvas & cvs ) { m_id_canvas.push_back ( cvs ); }

		s3d::Texture Texture ();
		s3d::Texture Texture ( size_t index );

		const s3d::Array < s3d::Texture > & GetTxs() const { return m_txs; }

#if 0

		void AddCompress ( const Compress & cmprs, Canvas & canvas );
		void AddMap(const String & pos_name, const Canvas & canvas) { m_dic_pos[pos_name] = canvas; }


		s3d::Image Image ();
		s3d::Image Image ( size_t index );

		int32_t N_Tip () const;

		//const s3d::Array < Page > & GetPages () const { return m_pages; }


		Canvas GetCanvas ( const String & name ) const
		{
			auto it = m_dic_pos.find ( name );
			if ( it != m_dic_pos.end () )
			{
				return it->second;
			}
			return Canvas ();
		}

#endif // 0

		//ディープコピー
		void DeepCopyFrom ( const MapNameCanvas & map ) { m_dic_pos = map; }
		void SetIdCanvas ( const AryCanvas & map ) { m_id_canvas = map; }
	};


	using P_Atlas = std::shared_ptr < Atlas >;


}	//namespace GAME


