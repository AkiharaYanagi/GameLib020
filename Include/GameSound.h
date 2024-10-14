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

		//サウンドアーカイバ
		_SoundArchiver		m_bgm; //BGM
		_SoundArchiver		m_se; //SE
		_SoundArchiver		m_vc; //VC

	public:
		void Load ();
		void Make ();
		void Open ();


		void PlayBGM ( uint32 id ) { m_bgm.Play ( id ); }
		void PlayBGM ( const s3d::String & filename ) { m_bgm.Play ( filename ); }
		void PlayLoopBGM ( uint32 id ) { m_bgm.Play_Loop ( id ); }
		void PlayLoopBGM ( const s3d::String & filename ) { m_bgm.Play_Loop ( filename ); }
		void StopBGM ( uint32 id ) { m_bgm.Stop ( id ); }
		void StopBGM ( const s3d::String & filename ) { m_bgm.Stop ( filename ); }
		void Stop_All_BGM () { m_bgm.Stop_All (); }


		void PlaySE ( uint32 id ) { m_se.Play ( id ); }
		void PlaySE ( const s3d::String & filename ) { m_se.Play ( filename ); }
		void Play_OneShotSE ( uint32 id ) { m_se.Play_OneShot ( id ); }
		void Play_OneShotSE ( const s3d::String & filename ) { m_se.Play_OneShot ( filename ); }
		void StopSE ( uint32 id ) { m_se.Stop ( id ); }

		void PlayVC ( uint32 id ) { m_vc.Play ( id ); }
		void PlayVC ( const s3d::String & filename ) { m_vc.Play ( filename ); }
		void Play_OneShotVC ( uint32 id ) { m_vc.Play_OneShot ( id ); }
		void Play_OneShotVC ( const s3d::String & filename ) { m_vc.Play_OneShot ( filename ); }
		void StopVC ( uint32 id ) { m_vc.Stop ( id ); }


		void SetVolume ( double vol );


		void Test ();
	};


#define	SND			GameSound::Inst

#define	SND_PLAY_BGM		GameSound::Inst()->PlayBGM
#define	SND_PLAY_LOOP_BGM	GameSound::Inst()->PlayLoopBGM
#define	SND_STOP_BGM		GameSound::Inst()->StopBGM
#define	SND_STOP_ALL_BGM	GameSound::Inst()->Stop_All_BGM

#define	SND_PLAY_SE			GameSound::Inst()->PlaySE
#define	SND_PLAY_ONESHOT_SE	GameSound::Inst()->Play_OneShotSE

#define	SND_PLAY_VC			GameSound::Inst()->PlayVC
#define	SND_PLAY_ONESHOT_VC	GameSound::Inst()->Play_OneShotVC


}	//namespace GAME

