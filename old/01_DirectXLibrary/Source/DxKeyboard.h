//=================================================================================================
//
// Direct Input �ɂ��L�[�{�[�h�̊Ǘ��@�N���X
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Directx_common.h"
#include <dinput.h>		//DirectInput
#include "DebugManager.h"


//-------------------------------------------------------------------------------------------------
// ���C�u�����̃����N
//-------------------------------------------------------------------------------------------------
#pragma comment (lib, "dinput8.lib")


namespace GAME
{
	//------------------------------------------
	//�萔�錾
	//------------------------------------------
	const int DI_KEYBOARD = 256;			//�L�[�{�[�h�z��


	class DxKeyboard
	{
		LPDIRECTINPUTDEVICE8	m_lpDIKeyboard;		//�L�[�{�[�h�f�o�C�X

		//�L�[�{�[�h�̏�ԕۑ�
		BYTE	m_keyState[DI_KEYBOARD];
		BYTE	m_preKeyState[DI_KEYBOARD];

	public:
		DxKeyboard();
		DxKeyboard ( const DxKeyboard& rhs ) = delete;
		~DxKeyboard();

		void Init( LPDIRECTINPUT8 lpDI );		//������
		void Rele();	//���
		
		//�w�肵���L�[��������Ă��邩
		bool IsKey( int nKey );
		//�w�肵���L�[�������ꂽ�u�Ԃ�
		bool PushKey( int nKey );
		//�w�肵���L�[�������ꂽ�u�Ԃ�
		bool ReleaseKey( int nKey );

		//�Q�[�����p
		//��Ԃ̍X�V
		void Update();
	};


}	//namespace GAME

