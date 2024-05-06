//------------------------------------------------------------------
//
// GameKeyCommand �w�b�_
//	�R�}���h����p�̂P�t���[�����̓��̓f�[�^
//		�Q�[����̋L�^�f�[�^(_GameKey)�ƈقȂ�_�́A
//		���o�[�͂P�ɂ܂Ƃ߁A����p��WILD��ے�̃t���O�Ȃǂ�����
//
//------------------------------------------------------------------
// �������7���
// 
//	[__] �������������
//	[--] �������������		
//	[-_] �������u��		
//	[_-] �������u��		
//	[**] �ǂ̏�Ԃł�	
//	[*_] ���݂̂݉��������
//	[*-] ���݂̂ݗ��������
// 
//------------------------------------------------------------------
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Define.h"
#include "GameKey.h"


//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class GameKeyCommand
	{
	public:
		//���͏��
		enum GAME_KEY_STATE
		{
			GAME_KEY_OFF,		// �������������
			GAME_KEY_ON,		// �������������
			GAME_KEY_PUSH,		// �������u��
			GAME_KEY_RELE,		// �������u��
			GAME_KEY_WILD,		// �ǂ̏�Ԃł�
			GAME_KEY_IS,		// ���݂̂݉��������
			GAME_KEY_NIS,		// ���݂̂ݗ��������
		};

		//���o�[����(10�L�[)��enum�ɒu��
		enum GAME_KEY_LVR_CMD
		{
			LVR_CMD_1 = 0,
			LVR_CMD_2 = 1,
			LVR_CMD_3 = 2,
			LVR_CMD_6 = 3,
			LVR_CMD_9 = 4,
			LVR_CMD_8 = 5,
			LVR_CMD_7 = 6,
			LVR_CMD_4 = 7,
		};

	private:
		GAME_KEY_STATE m_Lvr [ GameKey::LVR_NUM ];		//���o�[���
		GAME_KEY_STATE m_Btn [ GameKey::BTN_NUM ];		//�{�^�����
		bool	m_bNot;		//�ے�

	public:
		GameKeyCommand ();
		GameKeyCommand ( const GameKeyCommand & rhs );	//�R�s�[�\
		~GameKeyCommand ();

		//��r
		bool CompareTarget ( GameKey gameKeyData ) const;

		//�����w��̔�r
		//this�̏�Ԃ��`�F�b�N����R�}���h�����A�������v���C������
		//�����F�R�}���h���������ƂȂ�Q�[���L�[���, �L�����N�^����(�E��)
		//�ߒl�F�K��������true�A����ȊO��false
		bool CompareTarget ( GameKey gameKeyData, bool dirRight ) const;

		//-----------------------------------------------------------------
		//���o�[(�����w��)
		void SetLvr ( UINT index, GAME_KEY_STATE state ) { m_Lvr[index] = state; }
		void SetaLvr ( GAME_KEY_STATE state_ary [] );
		GAME_KEY_STATE GetLvr ( UINT index ) const { return m_Lvr[index]; }

#if 0
//		int IdLvr = 0;		//���݃��o�[�C���f�b�N�X
		//���o�[(1����)
//		GAME_KEY_LVR_CMD GetKeyLvrCmd () const;
		bool IsKeyLvrCmd ( GAME_KEY_LVR_CMD lvr_cmd ) const;
		bool PushKeyLvrCmd ( GAME_KEY_LVR_CMD lvr_cmd ) const;
#endif // 0

		//�{�^��
		void SetBtn ( UINT index, GAME_KEY_STATE state ) { m_Btn[index] = state; }
		void SetaBtn ( GAME_KEY_STATE state_ary [] );
		GAME_KEY_STATE GetButton ( UINT index ) const { return m_Btn[index]; }

		//�ے�̃t���O
		void SetNot ( bool b ) { m_bNot = b; }
		bool GetNot () const { return m_bNot; }
		//-----------------------------------------------------------------

#if 0
	private:
		//�������p�֐�
		//Is == ( ���݉�����Ă����� ( ON || PUSH ) )
		bool Is ( _GameKey::GAME_KEY_LEVER lvr ) const;
		bool IsNeutral () const;
		bool Is2E () const;
		bool Is6E () const;
		bool Is8E () const;
		bool Is4E () const;
#endif // 0
	};


	using V_GAME_KEY_CMD = std::vector < GameKeyCommand >;
	using KEY_ST = GameKeyCommand::GAME_KEY_STATE;


}	//namespace GAME

