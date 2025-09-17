//=================================================================================================
//
// �Q�[���V�X�e���@�w�b�_
//		�Q�[�����e�̑O�ɕK�v�ɂȂ�A�v���P�[�V�����⃉�C�u�����Ƃ̘A�����L�q����B
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
//	�w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "00_Common.h"
#include "GameMainBase.h"
using CLK = std::chrono::high_resolution_clock;


//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//-------------------------------------------------------------------------------------------------
	//	�Q�[�����̃��C�u�����g�p�Ȃ�
	//-------------------------------------------------------------------------------------------------
	class GameSystem
	{
		UP_GameMainBase		m_pGameMain;


		//���Ԍv��
		CLK::time_point start_time;
		CLK::time_point now_time;
		CLK::time_point end_time;
		uint32 frame { 0 };
		uint32 frame_ps { 0 };

		CLK::time_point fps_time;
		uint32 fps { 60 };
		double disp_fps { 0 };
		int64 sleep { 0 };
		double aveSleep { 0 };
		double dispSleep { 0 };

		//�ꎞ��~�p
		bool		m_bStop { F };

	public:
		GameSystem () {}
		GameSystem ( const GameSystem& rhs ) = delete;
		~GameSystem () {}

		void SystemLoad ();		//�V���O���g���̃N���G�C�g�ȂǏ�����

		void Move ();
		void Draw ();

		//���C���I�u�W�F�N�g�̐ݒ�
		void SetpGameMain ( UP_GameMainBase pGameMain );

		void SetbStop ( bool b ) { m_bStop = b; }

	private:
		static bool m_bMakeArchive;		//�A�[�J�C�u�쐬�t���O

		//�t���[������
		void Frame ();
		void _Frame ();
		void _Move ();

		double	m_frame { 0 };
		double	m_start_time { 0 };
		double	m_progress_time { 0 };

		//�f�o�b�O�\���ؑփg�O��
		bool m_bDispDebug { T };
		bool m_pre_bDispDebug { T };
		void FlipToggle ();

	public:
		//-----------------------------
		//	static ���ݒ�
		//-----------------------------

		//�f�o�b�O�\�������ׂ�ON
		//		static void FullDebugMode () { m_bDispTimer = T; }

		//�f�o�b�O�\�������ׂ�ON
		//		static void NoDebugMode () { m_bDispTimer = F; }

		//�A�[�J�C�u���쐬���ēǂݍ���
		static void SetFlag_MakeArchive ( bool b ) { m_bMakeArchive = b; }
	};

}

