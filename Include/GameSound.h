//=================================================================================================
//
// GameSound ヘッダファイル
//
//		Debugモード時にSoundディレクトリにあるwaveファイルをsound.datに書き出し、
//		Debugモード, Releaseモード時にsound.datからwaveを読み込む
// 
//		BGM, SE, VOICEに分割する
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Define.h"
#include "Define_Siv3D.h"
#include "_SoundArchiver.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class GameSound
	{
	//--------------------------------------------------
	//シングルトンパターン
	private:
		using P_GameSound = std::unique_ptr < GameSound >;
		static P_GameSound		m_inst;
		GameSound ();
		GameSound ( const GameSound& rhs ) = delete;
	public:
		~GameSound ();
		static void Create () { if ( ! m_inst ) { m_inst = P_GameSound ( new GameSound () ); } }
		static P_GameSound & Inst () { return m_inst; }
	//--------------------------------------------------

	private:
#pragma region CONST

	//ファイル名関連
		static CSIVSTR	ACV_FILENAME_BGM;	//作成するサウンドアーカイブファイル名
		static CSIVSTR	ACV_DIRNAME_BGM;	//アーカイブ作成のため読み込むディレクトリ名
		static CSIVSTR	ACV_CND_BGM;		//アーカイブ作成のため読み込むファイル名条件

		static CSIVSTR	ACV_FILENAME_SE;	//作成するサウンドアーカイブファイル名
		static CSIVSTR	ACV_DIRNAME_SE;		//アーカイブ作成のため読み込むディレクトリ名
		static CSIVSTR	ACV_CND_SE;			//アーカイブ作成のため読み込むファイル名条件

		static CSIVSTR	ACV_FILENAME_VC;	//作成するサウンドアーカイブファイル名
		static CSIVSTR	ACV_DIRNAME_VC;		//アーカイブ作成のため読み込むディレクトリ名
		static CSIVSTR	ACV_CND_VC;			//アーカイブ作成のため読み込むファイル名条件

#pragma endregion

	public:
		void Load ();
		void Make ();
		void Open ();


		//サウンドアーカイバ
		_SoundArchiver		m_bgm; //BGM
		_SoundArchiver		m_se; //SE
		_SoundArchiver		m_vc; //VC
	};

}	//namespace GAME

