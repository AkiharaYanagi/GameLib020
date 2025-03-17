//=================================================================================================
//
//	Atlas ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Define.h"
#include "Define_Siv3D.h"
#include "Compress.h"




//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//Atlas
	//Cmpressをまとめる
	class Atlas
	{
		//Atlas
		//	┣[] Compress
		//		┣[] Tile
		//		  ┣ Tip :  Array < uint32 >;
		s3d::Array < P_Compress >			m_aryCmprs;

	public:

		Atlas ();
		Atlas ( const Atlas & rhs );
		~Atlas ();

		void Copy ( const Atlas & rhs );

		void Do ();

		//IO
		void Make ( std::filesystem::path dir );
		void Write ();
		PAP_Tx Read ();
	
		//C#からバイナリで.png形式をまとめた.imgファイルから作成
		void Conversion ( s3d::String filepath );

		P_Tx GetpTx ();
		PAP_Tx GetpapTx ();

		bool Compare ( const Atlas & rhs ) const;


		//取得
		//Image Get ();

		//シリアライズ可能にするためのテンプレート関数定義
		template < class T >
		void SIV3D_SERIALIZE ( T & t )
		{
			t ( m_aryCmprs );
		}


		//MemoryStream上に展開
		void WriteMemoryStream ( s3d::MemoryWriter & mw );

		//MemoryStreamから読込
		void LoadMemoryStream ( s3d::MemoryReader & mr );
	};

	using P_Atlas = std::shared_ptr < Atlas >;



	//シリアライズ用
	class Srl_Atlas
	{
	public:

		const s3d::String FILE_NAME { U"img.atls" };

		void Save ( const Atlas & atls );
		void Load ( Atlas & atls );
	};


}	//namespace GAME


