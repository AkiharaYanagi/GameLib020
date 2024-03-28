//=================================================================================================
//
// DirectInput �L�[�{�[�h �̎���
//
//=================================================================================================

#include "DxKeyboard.h"


namespace GAME
{

	DxKeyboard::DxKeyboard() : m_lpDIKeyboard(nullptr)
	{
		for ( DWORD dw = 0; dw < DI_KEYBOARD; dw++ )
		{
			m_keyState[dw] = 0x00;
			m_preKeyState[dw] = 0x00;
		}
	}

	DxKeyboard::~DxKeyboard()
	{
		Rele ();
	}

	void DxKeyboard::Init( LPDIRECTINPUT8 lpDI )
	{
		assert ( lpDI );
		HRESULT hr;

		//�f�o�C�X�̏�����
		hr = lpDI->CreateDevice ( GUID_SysKeyboard, &m_lpDIKeyboard, nullptr );
		if ( FAILED(hr) )
		{
			DXTRACE( hr, TEXT("�L�[�{�[�h�f�o�C�X�̍쐬�Ɏ��s") );
			return;
		}

		//�f�[�^�`����ݒ�
		hr = m_lpDIKeyboard->SetDataFormat ( &c_dfDIKeyboard );
		if ( FAILED(hr) )
		{
			DXTRACE( hr, TEXT("�L�[�{�[�h:�f�[�^�`���̐ݒ�Ɏ��s") );
			return;
		}

//		DXTRACE_MSG ( TEXT("DirectInput: �L�[�{�[�h�ݒ萬��") );

		//���͐���J�n
		m_lpDIKeyboard->Acquire ();
	}

	void DxKeyboard::Rele()
	{
		if ( m_lpDIKeyboard )
		{
			m_lpDIKeyboard->Unacquire();	//�v��������
			RELEASE( m_lpDIKeyboard );		//���
		}
	}

	//�w�肵���L�[��������Ă��邩
	bool DxKeyboard::IsKey( int nKey )
	{
		if ( m_lpDIKeyboard == nullptr ) return false;	//�L�[�{�[�h�̂Ȃ���Ԃ�false��Ԃ�

		//�f�o�C�X�̒��ڃf�[�^���擾����
		BYTE byKeyState[DI_KEYBOARD];
		HRESULT hr = m_lpDIKeyboard->GetDeviceState ( DI_KEYBOARD, byKeyState );

		if ( SUCCEEDED ( hr ) )
		{
			//�L�[��������Ă��邩���ׂ�
			if ( m_keyState[nKey] & 0x80 )	//key�Ԗڂ̃L�[��������Ă��邩�ǂ���
			{
				return true;
			}
		}
		else if ( hr == DIERR_INPUTLOST )		//�A�N�Z�X�����������ꍇ
		{
			m_lpDIKeyboard->Acquire ();		//�A�N�Z�X���̍Ď擾
		}

		return false;	//�Ώۂ̃L�[�������ꂽ��ԂłȂ��Ƃ���false��Ԃ�
	}


	//�w�肵���L�[�������ꂽ�u�Ԃ�
	bool DxKeyboard::PushKey( int nKey )
	{
		if ( m_lpDIKeyboard == nullptr ) return false;	//�L�[�{�[�h�̂Ȃ���Ԃ�false��Ԃ�

		//�f�o�C�X�̒��ڃf�[�^���擾����
		BYTE byKeyState[DI_KEYBOARD];
		HRESULT hr = m_lpDIKeyboard->GetDeviceState ( DI_KEYBOARD, byKeyState );

		if ( SUCCEEDED ( hr ) )
		{
			//�L�[��������Ă��邩���ׂ�
			if ( (m_keyState[nKey] & 0x80) && ( ! (m_preKeyState[nKey] & 0x80) ) )	//key�Ԗڂ̃L�[�������ꂽ�u�Ԃ��ǂ���
			{
				return true;
			}
		}
		else if ( hr == DIERR_INPUTLOST )		//�A�N�Z�X�����������ꍇ
		{
			m_lpDIKeyboard->Acquire ();		//�A�N�Z�X���̍Ď擾
		}

		return false;	//�Ώۂ̃L�[�������ꂽ��ԂłȂ��Ƃ���false��Ԃ�
	}

	//�w�肵���L�[�������ꂽ�u�Ԃ�
	bool DxKeyboard::ReleaseKey( int nKey )
	{
		if ( m_lpDIKeyboard == nullptr ) return false;	//�L�[�{�[�h�̂Ȃ���Ԃ�false��Ԃ�

		//�f�o�C�X�̒��ڃf�[�^���擾����
		BYTE byKeyState[DI_KEYBOARD];
		HRESULT hr = m_lpDIKeyboard->GetDeviceState ( DI_KEYBOARD, byKeyState );

		if ( SUCCEEDED ( hr ) )
		{
			//�L�[��������Ă��邩���ׂ�
			if ( ( ! (m_keyState[nKey] & 0x80) ) && (m_preKeyState[nKey] & 0x80) )	//key�Ԗڂ̃L�[�������ꂽ�u�Ԃ��ǂ���
			{
				return true;
			}
		}
		else if ( hr == DIERR_INPUTLOST )		//�A�N�Z�X�����������ꍇ
		{
			m_lpDIKeyboard->Acquire ();		//�A�N�Z�X���̍Ď擾
		}

		return false;	//�Ώۂ̃L�[�������ꂽ��ԂłȂ��Ƃ���false��Ԃ�
	}


	//--------------------------------------------------------------------------
	//�Q�[�����p
	//--------------------------------------------------------------------------
	void DxKeyboard::Update()
	{
		if ( m_lpDIKeyboard )
		{
			for ( DWORD dw = 0; dw < DI_KEYBOARD; dw++ )
			{
				m_preKeyState[dw] = m_keyState[dw];	//�ȑO�̏�Ԃ̋L�^
			}

			HRESULT hr = m_lpDIKeyboard->GetDeviceState ( DI_KEYBOARD, m_keyState );
			if ( hr == DIERR_INPUTLOST )	//�A�N�Z�X�����������ꍇ
			{
				m_lpDIKeyboard->Acquire();	//�Ď擾
			}
		}
	}


}	//namespace GAME


