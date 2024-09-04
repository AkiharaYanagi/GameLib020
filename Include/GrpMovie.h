//=================================================================================================
//
// ゲームグラフィック　ムービ　ヘッダ
//		動画を扱うオブジェクトを定義する
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイル　インクルード
//-------------------------------------------------------------------------------------------------
#include "00_Common.h"
#include "GameGraphic.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	using UP_Mov = std::unique_ptr < s3d::VideoTexture >;


	class GrpMovie : public GameGraphicBase
	{
		UP_Mov		mp_vtx;				//ビデオテクスチャ
		s3d::String		m_filename { U"" };		//対象ファイル名
		bool		m_startMv { F };	//開始フラグ
		bool		m_loop { F };		//ループフラグ

	public:
		GrpMovie ();
		GrpMovie ( const GrpMovie & rhs ) = delete;
		~GrpMovie ();

		void Load ();
		void Draw ();
		void _Draw ();

		void SetMovName ( s3d::String filename );

		void Start () { m_startMv = T; }
		void Loop ( bool b ) { m_loop = b; }
	};

	using GrpMov = GrpMovie;
	using P_GrpMovie = std::shared_ptr < GrpMov >;


}	//namespace GAME

