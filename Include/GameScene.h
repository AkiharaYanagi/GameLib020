//=================================================================================================
//
// �Q�[���V�[���@�w�b�_
//		�J�ڎ��Ƀf�[�^�̐����Ɣj���������ԑJ��
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�̃C���N���[�h
//-------------------------------------------------------------------------------------------------
//#include "DebugManager.h"
#include "GameTask.h"
//#include "GameParam.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//------------------------------------------------------------------
	//�V�[�����z���Ĉ����p�����[�^
//	class GameParam {};
	class GameParam;
	using P_GameParam = std::shared_ptr < GameParam >;
	//------------------------------------------------------------------


	//------------------------------------------------------------------
	//	�Q�[���V�[��
	//		TaskArray���p�����A�ċA�I�Ƀ^�X�N�������ł���悤�ɂ���GameState
	//		�E���ʂ̃f�[�^�������Ĉڍ�����P��
	//		�E�V�[���̈ړ����ɃI�u�W�F�N�g�̑S����A�S�m�ہB������m_pParam�͎��̃V�[���ֈڏ�
	//		��this�̎擾�̂��߁Aenable_shared_from_this < GameScene >�𑽏d�p��
	//		shared_from_this��p����̂�std::unique_ptr�ɂ͂��Ȃ�
	//------------------------------------------------------------------
//	class GameScene : public GameTaskVector, public enable_shared_from_this < GameScene >
	class GameScene : public GameTaskVector
	{
		//�V�[�����ʃp�����[�^
		P_GameParam		m_pParam;

	public:
		GameScene () = default;
		GameScene ( const GameScene & rhs ) = delete;
		~GameScene () = default;

		//�p�����[�^��p�����������C���^�[�t�F�[�X
		//�p�����[�^�̎擾�̂��Ƃ̌ďo1��ۏ� ( ParamInit(), Load(), Init() �̏��� )
		//ParamInit()�Ƃ͈قȂ�f�o�C�X���Z�b�g�ł��Ă΂�Ȃ�
		//Load()�̓f�o�C�X���Z�b�g�̓x�ɌĂ΂��
		//Init()�͕�����Ă΂��\��������
		virtual void ParamInit () = 0;

		//�J�ڏ���
		//@info	this�����g�ɕۑ�����Əz�Q�ƂƂȂ�̂�weak_ptr��p����
		//��{�̖ߒl�� return shared_from_this();
		//�����ŏ������m�F���A�J�ڎ��͑J�ڐ�̃I�u�W�F�N�g��
		//	std::make_shared < GameScene > () ���ĕԂ�
		virtual std::shared_ptr < GameScene > Transit () = 0;

		//�V�[�����ʃp�����[�^
		void SetpParam ( P_GameParam && pParam ) { m_pParam = pParam; }
//		void SetpParam ( P_GameParam pParam ) { m_pParam = pParam; }
		P_GameParam GetpParam () { return m_pParam; }
	};

	using P_GameScene = std::shared_ptr < GameScene >;
	using WP_GameScene = std::weak_ptr < GameScene >;

	//------------------------------------------------------------------
	//	�Q�[���V�[���}�l�[�W��
	//------------------------------------------------------------------
	class GameSceneManager : public GameTaskVector
	{
		P_GameScene		m_pScene;

	public:
		GameSceneManager ();
		GameSceneManager ( const GameSceneManager & rhs ) = delete;
		virtual ~GameSceneManager ();

		void Move ();		//�t���[��������ƑJ�ڃ`�F�b�N

		//�V�[���̐ݒ�
		void SetScene ( P_GameScene p ) { m_pScene = p; AddpTask ( m_pScene ); }
		P_GameScene GetpScene () { return m_pScene; }

		//�J��
		virtual void Transit ();
	};

	using SCENE_MGR = GameSceneManager;


}	//namespace GAME

