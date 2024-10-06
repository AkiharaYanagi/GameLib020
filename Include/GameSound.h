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

		//�T�E���h�A�[�J�C�o
		_SoundArchiver		m_bgm; //BGM
		_SoundArchiver		m_se; //SE
		_SoundArchiver		m_vc; //VC
	};

}	//namespace GAME

