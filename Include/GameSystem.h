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

	public:
		GameSystem () {}
		GameSystem ( const GameSystem& rhs ) = delete;
		~GameSystem () {}

		void SystemLoad ();		//�V���O���g���̃N���G�C�g�ȂǏ�����

		void Move ();
		void Draw ();

		//���C���I�u�W�F�N�g�̐ݒ�
		void SetpGameMain ( UP_GameMainBase pGameMain );

	private:
		static bool m_bMakeArchive;		//�A�[�J�C�u�쐬�t���O

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
