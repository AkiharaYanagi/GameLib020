//=================================================================================================
//
//	Compress ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "../Define_Siv3D.h"
#include "Tip.h"
#include "Canvas.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class Compress
	{
		s3d::Array < Tip >	m_tips;

	public:
		Compress ();
		Compress ( const Compress & rhs ) = default;	//代入可能
		~Compress ();

		void Do ( const Image & img, Canvas & cnvs );

		//Tip参照取得
		const s3d::Array < Tip > & GetrTips () const { return m_tips; }

		//対象Tip位置がすべて空白かどうか
		bool IsBlank ( const Image & img, int32 x, int32 y ) const;

		//個数
		size_t GetTipCount() const { return m_tips.size(); }

		//テクスチャ
		s3d::Texture Texture() const;
	};


}	//namespace GAME


