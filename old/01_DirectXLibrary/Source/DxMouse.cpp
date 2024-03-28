//=================================================================================================
//
// DirectInput	�}�E�X
//
//=================================================================================================


//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "DxMouse.h"


//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	DxMouse::DxMouse() : m_lpDIMouse(nullptr)
	{
	}

	DxMouse::~DxMouse()
	{
		Rele ();
	}

	void DxMouse::Init( LPDIRECTINPUT8 lpDI )
	{
		assert ( lpDI );
		HRESULT hr;

		//�f�o�C�X�̏�����
		hr = lpDI->CreateDevice ( GUID_SysMouse, &m_lpDIMouse, nullptr );
		if ( FAILED(hr) )
		{
			DXTRACE( hr, TEXT("�}�E�X�f�o�C�X�̍쐬�Ɏ��s") );
			return;
		}

		//�f�[�^�`����ݒ�
		hr = m_lpDIMouse->SetDataFormat ( &c_dfDIMouse );
		if ( FAILED(hr) )
		{
			DXTRACE( hr, TEXT("�}�E�X:�f�[�^�`���̐ݒ�Ɏ��s") );
			return;
		}

		//�������x����ݒ�
		hr = m_lpDIMouse->SetCooperativeLevel ( HWnd::Get(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE );
		if ( FAILED(hr) )
		{
			DXTRACE( hr, TEXT("�}�E�X:�t�H�A�O���E���h�A��r�����[�h�̐ݒ�Ɏ��s") );
			return;
		}

		//�o�b�t�@�����O�f�[�^�̐ݒ�
		DIPROPDWORD diprop;
		diprop.diph.dwSize			= sizeof ( diprop );
		diprop.diph.dwHeaderSize	= sizeof ( diprop.diph );
		diprop.diph.dwObj			= 0;
		diprop.diph.dwHow			= DIPH_DEVICE;
		diprop.dwData				= 100;
		hr = m_lpDIMouse->SetProperty ( DIPROP_BUFFERSIZE, &diprop.diph );
		if ( FAILED ( hr ) )
		{
			DXTRACE( hr, TEXT("�o�b�t�@�����O�f�[�^�̐ݒ�Ɏ��s") );
			return;
		}

//		DXTRACE_MSG ( TEXT("DirectInput: �}�E�X�ݒ萬��") );

		//���͐���J�n
		m_lpDIMouse->Acquire ();
	}

	void DxMouse::Rele()
	{
		if ( m_lpDIMouse )
		{
			m_lpDIMouse->Unacquire();	//�v��������
			RELEASE( m_lpDIMouse );		//���
		}
	}

	//--------------------------------------------------------------------------
	//�Q�[�����p
	//--------------------------------------------------------------------------
	void DxMouse::Update()
	{
		if ( m_lpDIMouse == nullptr ) { return; }

		//�O�f�[�^�̕ۑ�
		m_preMouseState.lX = m_mouseState.lX;
		m_preMouseState.lY = m_mouseState.lY;
		m_preMouseState.lZ = m_mouseState.lZ;
		m_preMouseState.rgbButtons[0] = m_mouseState.rgbButtons[0];
		m_preMouseState.rgbButtons[1] = m_mouseState.rgbButtons[1];
		m_preMouseState.rgbButtons[2] = m_mouseState.rgbButtons[2];
		m_preMouseState.rgbButtons[3] = m_mouseState.rgbButtons[3];

		//�}�E�X�̒��ڃf�[�^���擾����
		HRESULT hr = m_lpDIMouse->GetDeviceState ( sizeof ( DIMOUSESTATE ), &m_mouseState );
		if ( hr == DIERR_INPUTLOST )	//�A�N�Z�X�����������ꍇ
		{
			m_lpDIMouse->Acquire();	//�Ď擾
		}
	}


}	//namespace GAME


