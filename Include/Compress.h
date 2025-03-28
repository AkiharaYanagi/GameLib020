﻿//=================================================================================================
//
//	Compress ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Define_Siv3D.h"
#include "Tile.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class Compress
	{
		s3d::Array < Tile >			m_tiles;

		//保存元の記録
		//タイル個数
		int32	m_w { 0 };
		int32	m_h { 0 };

		//test
		s3d::Texture		m_tx;


	public:
		Compress ();
		Compress ( const Compress & rhs );	//代入可能
		~Compress ();

		void Do ( const Image & img );


		//対象Tile位置がすべて空白かどうか
		bool IsBlank ( const Image & img, int32 x, int32 y ) const;

		void TestMakeTx ();
		void TestDraw ();

		//テクスチャを生成してポインタを返す
		P_Tx Tx ();
		P_Tx Tx_Thawing ();	//解凍して生成

		bool Compare ( const Compress & rhs ) const;

		//-------------------------------------------
		//シリアライズ可能にするためのテンプレート関数定義
		template < class T >
		void SIV3D_SERIALIZE ( T & t )
		{
			t ( m_tiles, m_w, m_h );
		}

		//-------------------------------------------
		//MemoryStream上に展開
		void WriteMemoryStream ( s3d::MemoryWriter & mw );

		//MemoryStreamから読込
		void LoadMemoryStream ( s3d::MemoryReader & mr );
	};

	using P_Compress = std::shared_ptr < Compress >;


}	//namespace GAME


