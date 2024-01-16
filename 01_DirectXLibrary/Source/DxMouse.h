//=================================================================================================
//
// Direct Input �ɂ��}�E�X�̊Ǘ��@�N���X
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Directx_common.h"
#include <dinput.h>		//DirectInput
#include "DebugManager.h"
#include "HWnd.h"


//-------------------------------------------------------------------------------------------------
// ���C�u�����̃����N
//-------------------------------------------------------------------------------------------------
#pragma comment (lib, "dinput8.lib")


//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class DxMouse
	{
		LPDIRECTINPUTDEVICE8	m_lpDIMouse;		//�}�E�X�f�o�C�X

		//���ڃf�[�^
		DIMOUSESTATE			m_mouseState;
		DIMOUSESTATE			m_preMouseState;	//��O�̃f�[�^

	public:
		DxMouse();
		DxMouse( const DxMouse& rhs ) = delete;
		~DxMouse();

		void Init( LPDIRECTINPUT8 lpDI );		//������
		void Rele();	//���

		//�����ꂩ�̃L�[��������Ă����Ԃ��ǂ���
		//	0: LBUTTON, 1: RBUTTON, 2: �z�C�[���N���b�N
		bool IsButton ( UINT n ) const
		{
			assert ( n < 4 );
			return ( m_mouseState.rgbButtons[n] & 0x80 ) ? true: false; 
		}

		//�����ꂩ�̃L�[��������Ă����Ԃ��痣���ꂽ���ǂ���
		//	0: LBUTTON, 1: RBUTTON, 2: �z�C�[���N���b�N
		bool UpButton ( UINT n ) const
		{
			assert ( n < 4 );
			return (	! (m_mouseState.rgbButtons[n] & 0x80)
					&&	(m_preMouseState.rgbButtons[n] & 0x80) ) ? true: false; 
		}

		//�}�E�X�̈ړ��ʂ��擾
		POINT GetMouseDelta () const 
		{
			return { m_mouseState.lX, m_mouseState.lY };
		}

		//�Q�[�����p
		//��Ԃ̍X�V
		void Update();
	};


}	//namespace GAME

