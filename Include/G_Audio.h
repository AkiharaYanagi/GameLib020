//=================================================================================================
//
// グローバル　オーディオ
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイル　インクルード
//-------------------------------------------------------------------------------------------------
#include "Define_Siv3D.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class G_Audio;
	using P_G_Audio = std::unique_ptr < G_Audio >;

	class G_Audio
	{
	//--------------------------------------------------
	//シングルトンパターン
	private:
		static P_G_Audio	m_inst;
		G_Audio ();
		G_Audio ( const G_Audio & rhs ) = delete;
	public:
		~G_Audio ();
		static void Create() { if ( ! m_inst ) { m_inst = P_G_Audio ( new G_Audio() ); } }
		static P_G_Audio & Inst() { return m_inst; }
	//--------------------------------------------------

	private:
		//一覧
		s3d::Array<s3d::String>	m_bgm_list;
		s3d::Array<s3d::String>	m_se_list;
		s3d::Array<s3d::String>	m_vc_list;

	public:

		void Load ();

		void HandLoad ();
		void CheckAudio ();

	private:
		void LoadDir ( const std::filesystem::path & dirPath, s3d::Array<s3d::String> & list );
	};



}	//namespace GAME

