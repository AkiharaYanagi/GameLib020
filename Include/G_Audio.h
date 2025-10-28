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

		double	m_bgmVolume { 1.0 };
		double	m_seVolume { 1.0 };
		double	m_vcVolume { 1.0 };

	public:

		void Load ();

		void HandLoad ();
		void CheckAudio ();
		void AllWait ();

		void SetVolume ( double vol );

		void PlayBGM ( LPCUSTR BGM_NAME );
		void PlayBGM ( const s3d::String & filename ) { PlayBGM ( filename.c_str() ); }
		void PlayLoopBGM ( LPCUSTR BGM_NAME );
		void PlayLoopBGM ( const s3d::String & filename ) { PlayLoopBGM ( filename.c_str() ); }
		void StopBGM ( LPCUSTR BGM_NAME );
		void StopBGM ( const s3d::String & filename ) { StopBGM ( filename.c_str() ); }
		void Stop_All_BGM ();
		bool IsPlayBGM ( LPCUSTR BGM_NAME );
		bool IsPlayBGM ( const s3d::String & filename ) { return IsPlayBGM ( filename.c_str() ); }

		void PlaySE ( LPCUSTR SE_NAME );
		void PlaySE ( const s3d::String & filename ) { PlaySE ( filename.c_str() ); }
		void Play_OneShotSE ( LPCUSTR SE_NAME );
		void Play_OneShotSE ( const s3d::String & filename ) { Play_OneShotSE ( filename.c_str() ); }
		void StopSE ( LPCUSTR SE_NAME );
		void StopSE ( const s3d::String & filename ) { StopSE ( filename.c_str() ); }
		void Stop_All_SE ();
		
		void PlayVC ( LPCUSTR VC_NAME );
		void PlayVC ( const s3d::String & filename ) { PlayVC ( filename.c_str() ); }
		void Play_OneShotVC ( LPCUSTR VC_NAME );
		void Play_OneShotVC ( const s3d::String & filename ) { Play_OneShotVC ( filename.c_str() ); }
		void StopVC ( LPCUSTR VC_NAME );
		void StopVC ( const s3d::String & filename ) { StopVC ( filename.c_str() ); }
		void Stop_All_VC ();


	private:
		void LoadDir ( const std::filesystem::path & dirPath, s3d::Array<s3d::String> & list );
	};


#define	AUDIO			G_Audio::Inst

#define	AUD_PLAY_BGM		G_Audio::Inst()->PlayBGM
#define	AUD_PLAY_LOOP_BGM	G_Audio::Inst()->PlayLoopBGM
#define	AUD_STOP_BGM		G_Audio::Inst()->StopBGM
#define	AUD_STOP_ALL_BGM	G_Audio::Inst()->Stop_All_BGM

#define	AUD_PLAY_SE			G_Audio::Inst()->PlaySE
#define	AUD_PLAY_ONESHOT_SE	G_Audio::Inst()->Play_OneShotSE
#define	AUD_STOP_SE			G_Audio::Inst()->StopSE
#define	AUD_STOP_ALL_SE		G_Audio::Inst()->Stop_All_SE

#define	AUD_PLAY_VC			G_Audio::Inst()->PlayVC
#define	AUD_PLAY_ONESHOT_VC	G_Audio::Inst()->Play_OneShotVC
#define	AUD_STOP_VC			G_Audio::Inst()->StopVC
#define	AUD_STOP_ALL_VC		G_Audio::Inst()->Stop_All_VC


}	//namespace GAME

