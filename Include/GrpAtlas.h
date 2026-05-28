//=================================================================================================
//
//	GrpAtlas ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Define_Siv3D.h"
#include "GameGraphic.h"
#include "Atlas/Define_Atlas.h"
#include "Atlas/Atlas.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//アトラスを持ち、描画するクラス
	class GrpAtlas : public GameGraphicBase
	{
		P_Atlas atlas { nullptr };

	public:
		GrpAtlas ();
		GrpAtlas ( const GrpAtlas & rhs ) = delete;	//コピー不可
		~GrpAtlas ();


		void Load ();


		bool IsLoaded () const { return atlas != nullptr; }

		void SetpAtlas(const P_Atlas& p) { atlas = p; }


		//描画：画像ID、位置x, y
		void Draw ( uint32_t txid, float x, float y );

	};


}	//namespace GAME


