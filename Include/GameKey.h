//------------------------------------------------------------------
//	�Q�[�����̓L�[
//------------------------------------------------------------------
// ���Q�[�����C���ɂ�����1�t���[�����̃L�[���͏��(���o�[, �{�^��)
// ��8�������o�[(Lever)�A�{�^���S��(Button)��\��
// �����o�[�ʕ��������������ɑΉ�����
//
//------------------------------------------------------------------
//	�yLever�z
// [7] [8] [9]
//
// [4] [_] [6]
//				�yButton�z
// [1] [2] [3]	,[0], [1], [2], [3]
//------------------------------------------------------------------
//
// ���f�[�^�Ƃ��Č��݃t���[���A�O�t���[����������
// (..., -2, [-1, 0], 2, 3, ...)[F]
//
//------------------------------------------------------------------
//
// ���o�[�A�C�R���\������12369874(�e���L�[�\���łP���甽���v���)
// ���o�[�ɂ��u�Ԃ̏�Ԃ��L�q
//
// �w���͏�Ԃ����N���X�x�Ɓw�R�}���h�̂P�t���[�������̃N���X�x�𕪊�����
// �R�}���h�Ƃ��āu�ے�v�t���O���u�w��̃Q�[���L�[��ԂłȂ��Ȃ����Ƃ��v
//-------------------------------------------------------------------
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Define.h"


//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class GameKey
	{
	public:
		//�����L�[
		enum GAME_KEY_LEVER
		{
			LVR_1 = 0,
			LVR_2 = 1,
			LVR_3 = 2,
			LVR_6 = 3,
			LVR_9 = 4,
			LVR_8 = 5,
			LVR_7 = 6,
			LVR_4 = 7,
		};
		static const int LVR_NUM = 8;

		//�{�^��
		enum GAME_KEY_BUTTON
		{
			BTN_0 = 0,
			BTN_1 = 1,
			BTN_2 = 2,
			BTN_3 = 3,
			BTN_4 = 4,
			BTN_5 = 5,
			BTN_6 = 6,
			BTN_7 = 7,
		};
		static const int BTN_NUM = 8;

	private:
		bool Lvr [ LVR_NUM ]	 = { false };	//���o�[���
		bool PreLvr [ LVR_NUM ] = { false };	//�O���o�[���
		bool Btn [ BTN_NUM ]	 = { false };	//�{�^�����
		bool PreBtn [ BTN_NUM ] = { false };	//�O�{�^�����

	public:
		GameKey ();
		GameKey ( const GameKey & rhs );
		~GameKey ();

		//�X�V(����̃L�[��O��ɕۑ�����)
//		void Update ();
		//�O��̃L�[������ɕۑ�����)
		void ReservePrevious ( const GameKey gkPrev );

		bool GetLvr ( UINT index ) const { return Lvr[index]; }
		void SetLvr ( UINT index, bool b ) { Lvr[index] = b; }
		void SetLvrOff ();
		bool GetPreLvr ( UINT index ) const { return PreLvr[index]; }
		void SetPreLvr ( UINT index, bool b ) { PreLvr[index] = b; }

		bool GetBtn ( UINT index ) const { return Btn[index]; }
		void SetBtn ( UINT index, bool b ) { Btn[index] = b; }
		bool GetPreBtn ( UINT index ) const { return PreBtn[index]; }
		void SetPreBtn ( UINT index, bool b ) { PreBtn[index] = b; }
	};

	using V_GAME_KEY = std::vector < GameKey >;


}	//namespace GAME

