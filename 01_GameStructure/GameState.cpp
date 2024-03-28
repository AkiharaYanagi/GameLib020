//=================================================================================================
//
// �Q�[���X�e�[�g
//		��ԑJ��
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "GameState.h"

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	GameState::GameState () : m_next(nullptr), m_change(false)
	{
	}

	GameState::~GameState ()
	{
	}

//-------------------------------------------------------------------------------
	GameStateManager::GameStateManager() : m_state(nullptr)
	{
	}

	GameStateManager::~GameStateManager()
	{
//		if ( m_state ) delete m_state;		//�Ō�̃I�u�W�F�N�g�̉��
		m_state = nullptr;
	}

	void GameStateManager::Init()
	{
		if ( m_state ) m_state->Init();
		GameTaskVector::Init ();
	}

	void GameStateManager::Rele()
	{
		if ( m_state ) m_state->Rele();
		GameTaskVector::Rele ();
	}

	void GameStateManager::Load()
	{
		if ( m_state ) m_state->Load();
		GameTaskVector::Load ();
	}

	void GameStateManager::Reset()
	{
		if ( m_state ) m_state->Reset();
		GameTaskVector::Reset ();
	}

	void GameStateManager::Move()
	{
		if ( m_state ) m_state->Move();
		GameTaskVector::Move ();
	}

#if 0
	void GameStateManager::Draw()
	{
		if ( m_state ) m_state->Draw();
		GameTaskVector::Draw ();
	}

	void GameStateManager::DrawVertex()
	{
		if ( m_state ) { m_state->DrawVertex(); }
		GameTaskVector::DrawVertex ();
	}
#endif // 0

	void GameStateManager::Transit()
	{
		if ( ! m_state ) return;

		//�J�ڏ�Ԃ̃`�F�b�N
		GameState* next = m_state->Transit();		//Transit()����new�����I�u�W�F�N�g�܂���this���Ԃ�
		if ( next != m_state )	//�ȑO�ƈقȂ�ꍇ
		{
			m_state->Rele();
//			if ( m_state ) delete m_state;	//�O�̃I�u�W�F�N�g��j��
			m_state = next;		//�V�K�I�u�W�F�N�g��ݒ�
			m_state->Load();
			m_state->Init();
		}
	}


//======================================================================================

	void _GameStateManager::Transit ()
	{
		if ( m_state )
		{
			_GameState* next = m_state->Transit ();		//Transit()���Ŏw�肵���J�ڐ�A�܂���this���Ԃ�
			if ( next != m_state )	//�ȑO�ƈقȂ�ꍇ
			{
				m_state = next;		//�V�K�X�e�[�g��ݒ�
			}
		}
	}


}	//namespace GAME

