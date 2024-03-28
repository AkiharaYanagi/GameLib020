//=================================================================================================
//
// �Q�[���V�[�� �\�[�X�t�@�C��
//		�J�ڎ��Ƀf�[�^�̔j���������ԑJ��
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "GameScene.h"


//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//------------------------------------------------------------------
	//	�Q�[���V�[��
	//------------------------------------------------------------------
	//�w�b�_�̂�


	//------------------------------------------------------------------
	//	�Q�[���V�[���}�l�[�W��
	//------------------------------------------------------------------
	GameSceneManager::GameSceneManager ()
	{
	}

	GameSceneManager::~GameSceneManager ()
	{
	}

	//�t���[��������ƑJ�ڃ`�F�b�N
	void GameSceneManager::Move ()
	{
		Transit ();	//�J�ڏ����m�F
		GameTaskVector::Move ();
	}

	void GameSceneManager::Transit ()
	{
		//Transit()���Ŏw�肵���J�ڐ�A�܂���this���Ԃ�
		P_GameScene next = m_pScene->Transit ();

		if ( next != m_pScene )	//�ȑO�ƈقȂ�ꍇ
		{
//			TRACE_F ( _T ( "m_pScene = %x, next = %x\n" ), m_pScene, next );

			//�p�����[�^�̈ڏ�
			next->SetpParam ( m_pScene->GetpParam () );

			//�����I���
#if 0
			TRACE_F ( _T ( "�� GameSceneManager : next.use_count = %d\n" ), next.use_count() );
			TRACE_F ( _T ( "�� GameSceneManager : m_pScene.use_count = %d" ), m_pScene.use_count() );
			EraseTask ( m_pScene );
			TRACE_F ( _T ( "-> %d " ), m_pScene.use_count() );
			m_pScene.reset ();
			TRACE_F ( _T ( "-> %d\n" ), m_pScene.use_count() );
			TRACE_F ( _T ( "�� GameSceneManager : next.use_count = %d\n" ), next.use_count() );

			//�V�K�V�[����ݒ�
			m_pScene = next;
			AddpTask ( m_pScene );
			TRACE_F ( _T ( "m_pScene = %x, next = %x\n" ), m_pScene, next );
			TRACE_F ( _T ( "�� GameSceneManager : m_pScene.use_count = %d\n" ), m_pScene.use_count () );
			TRACE_F ( _T ( "�� GameSceneManager : next.use_count = %d\n" ), next.use_count () );
			m_pScene->ParamInit ();
			m_pScene->Load ();
			m_pScene->Init ();

			next.reset ();
			TRACE_F ( _T ( "next.reset (); \n" ), m_pScene.use_count () );
			TRACE_F ( _T ( "�� GameSceneManager : m_pScene.use_count = %d\n" ), m_pScene.use_count () );
			TRACE_F ( _T ( "�� GameSceneManager : next.use_count = %d\n" ), next.use_count () );
#endif // 0
			//�����I���
			EraseTask ( m_pScene );
			m_pScene.reset ();
			//�V�K�V�[����ݒ�
			m_pScene = next;
			AddpTask ( m_pScene );
			m_pScene->ParamInit ();
			m_pScene->Load ();
			m_pScene->Init ();
			next.reset ();
		}
	}


}	//namespace GAME

