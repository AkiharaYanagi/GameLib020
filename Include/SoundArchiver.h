//=================================================================================================
//
// SoundArchiver �w�b�_�t�@�C��
//
//		Debug���[�h����Sound�f�B���N�g���ɂ���wave�t�@�C����sound.dat�ɏ����o���A
//		Debug���[�h, Release���[�h����sound.dat����wave��ǂݍ���
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Define.h"
//#include "SivSound.h"


//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//========================================================
	//	�� �T�E���h�A�[�J�C�u �t�H�[�}�b�g
	//	----
	//	UINT	4byte	//�T�C�Y
	//	BYTE	...		//�o�C�i���f�[�^
	//	----
	//	n�̗�
	//	��������Ƃ��͒萔�Y��
	//========================================================

	class SoundArchiver
	{
	//--------------------------------------------------
	//�V���O���g���p�^�[��
	private:
		using P_SoundArchiver = std::unique_ptr < SoundArchiver >;
		static P_SoundArchiver		m_inst;
		SoundArchiver ();
		SoundArchiver ( const SoundArchiver& rhs ) = delete;
	public:
		~SoundArchiver ();
		static void Create () { if ( ! m_inst ) { m_inst = P_SoundArchiver ( new SoundArchiver () ); } }
		static P_SoundArchiver & Inst () { return m_inst; }
	//--------------------------------------------------

	private:
		//--------------------------------------------------
		//���O �萔
		static LPCTSTR	m_archiveFileName;	//�쐬����T�E���h�A�[�J�C�u�t�@�C����
		static LPCTSTR	m_archiveDirName;	//�A�[�J�C�u�쐬�̂��ߓǂݍ��ރf�B���N�g����
		static LPCTSTR	m_searchCondition;	//�A�[�J�C�u�쐬�̂��ߓǂݍ��ރt�@�C��������
		static LPCTSTR	m_archiveDirName_SE;	//�A�[�J�C�u�쐬�̂��ߓǂݍ��ރf�B���N�g����
		static LPCTSTR	m_searchCondition_SE;	//�A�[�J�C�u�쐬�̂��ߓǂݍ��ރt�@�C��������
		//--------------------------------------------------


		//�T�E���h�f�[�^
		s3d::Array < s3d::Audio >	ma_sound;


		DWORD		m_nBGM { 0 };	//BGM�Ǎ���
		DWORD		m_nSE { 0 };	//SE�Ǎ���

		// DSBVOLUME_MAX : ��������(0), DSBVOLUME_MIN : �ŏ��l(-10000) [1/100dB]
		LONG		m_volume { 0 };		//�S�̃{�����[��

		bool		m_bPlay { F };	//���łɃv���C�����ǂ���

	public:
		void Make ();
		void Open ();

		//------------------------------------------------------------------
		void Play_BGM ( UINT BGM_ID );
		void Play_Loop_BGM ( UINT BGM_ID );
		void Stop_BGM ( UINT BGM_ID );
		void All_Stop ();

		//���łɃv���C���łȂ���΍Đ�
		//�����I��Stop_BGM()�����s����΍Đ������
		void If_Play_Loop_BGM ( UINT BGM_ID );

		void Play_SE ( UINT SE_ID );

		//���ʐݒ�
		// DSBVOLUME_MAX : ��������(0), DSBVOLUME_MIN : �ŏ��l(-10000) [1/100dB]
		void SetVolume ( LONG volume ) { m_volume = volume; }

	private:

		//�����̃t�@�C�������グ
		UINT CountFileNum ( LPCTSTR condition );

		//�쐬
		void _Make ( HANDLE hWriteFile, LPCTSTR dirname, LPCTSTR condition );
	};

	//�O�����p��`
	#define		SOUND	SoundArchiver::Inst()


}	//namespace GAME

