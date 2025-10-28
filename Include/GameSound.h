//=================================================================================================
//
// GameSound �w�b�_�t�@�C��
//
//		Debug���[�h����Sound�f�B���N�g���ɂ���wave�t�@�C����sound.dat�ɏ����o���A
//		Debug���[�h, Release���[�h����sound.dat����wave��ǂݍ���
// 
//		BGM, SE, VOICE�ɕ�������
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Define.h"
#include "Define_Siv3D.h"
#include "_SoundArchiver.h"


//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class GameSound
	{
	//--------------------------------------------------
	//�V���O���g���p�^�[��
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

	//�t�@�C�����֘A
		static CSIVSTR	ACV_FILENAME_BGM;	//�쐬����T�E���h�A�[�J�C�u�t�@�C����
		static CSIVSTR	ACV_DIRNAME_BGM;	//�A�[�J�C�u�쐬�̂��ߓǂݍ��ރf�B���N�g����
		static CSIVSTR	ACV_CND_BGM;		//�A�[�J�C�u�쐬�̂��ߓǂݍ��ރt�@�C��������

		static CSIVSTR	ACV_FILENAME_SE;	//�쐬����T�E���h�A�[�J�C�u�t�@�C����
		static CSIVSTR	ACV_DIRNAME_SE;		//�A�[�J�C�u�쐬�̂��ߓǂݍ��ރf�B���N�g����
		static CSIVSTR	ACV_CND_SE;			//�A�[�J�C�u�쐬�̂��ߓǂݍ��ރt�@�C��������

		static CSIVSTR	ACV_FILENAME_VC;	//�쐬����T�E���h�A�[�J�C�u�t�@�C����
		static CSIVSTR	ACV_DIRNAME_VC;		//�A�[�J�C�u�쐬�̂��ߓǂݍ��ރf�B���N�g����
		static CSIVSTR	ACV_CND_VC;			//�A�[�J�C�u�쐬�̂��ߓǂݍ��ރt�@�C��������

#pragma endregion

		//�T�E���h�A�[�J�C�o
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
		void SetVolume_BGM ( double vol );
		bool IsPlayBGM ( uint32 id ) { return m_bgm.IsPlaying ( id ); }
		bool IsPlayBGM ( const s3d::String & filename ) { return m_bgm.IsPlaying ( filename ); }


		void PlaySE ( uint32 id ) { m_se.Play ( id ); }
		void PlaySE ( const s3d::String & filename ) { m_se.Play ( filename ); }
		void Play_OneShotSE ( uint32 id ) { m_se.Play_OneShot ( id ); }
		void Play_OneShotSE ( const s3d::String & filename ) { m_se.Play_OneShot ( filename ); }
		void StopSE ( uint32 id ) { m_se.Stop ( id ); }
		void StopSE ( const s3d::String & filename ) { m_se.Stop ( filename ); }
		void Stop_All_SE () { m_se.Stop_All (); }
		void SetVolume_SE ( double vol );

		void PlayVC ( uint32 id ) { m_vc.Play ( id ); }
		void PlayVC ( const s3d::String & filename ) { m_vc.Play ( filename ); }
		void Play_OneShotVC ( uint32 id ) { m_vc.Play_OneShot ( id ); }
		void Play_OneShotVC ( const s3d::String & filename ) { m_vc.Play_OneShot ( filename ); }
		void StopVC ( uint32 id ) { m_vc.Stop ( id ); }
		void StopVC ( const s3d::String & filename ) { m_vc.Stop ( filename ); }
		void Stop_All_VC () { m_vc.Stop_All (); }
		void SetVolume_VC ( double vol );


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
#define	SND_STOP_SE			GameSound::Inst()->StopSE
#define	SND_STOP_ALL_SE		GameSound::Inst()->Stop_All_SE

#define	SND_PLAY_VC			GameSound::Inst()->PlayVC
#define	SND_PLAY_ONESHOT_VC	GameSound::Inst()->Play_OneShotVC
#define	SND_STOP_VC			GameSound::Inst()->StopVC
#define	SND_STOP_ALL_VC		GameSound::Inst()->Stop_All_VC


}	//namespace GAME

