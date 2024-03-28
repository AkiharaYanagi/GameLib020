//=================================================================================================
//
// DirectInput �W���C�X�e�B�b�N �̎���
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "DxJoystick.h"

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	DxJoystick::DxJoystick() : m_lpDI ( nullptr )
	{
	}

	DxJoystick::~DxJoystick()
	{
		Rele();
	}

	void DxJoystick::Init( LPDIRECTINPUT8 lpDI )
	{
		assert( lpDI );

		HRESULT hr;
		m_lpDI = lpDI;	//DirectInput�I�u�W�F�N�g�̕ۑ�

		//�����o�̏�����
		m_dwJoyMaxCount = INPUT_DEVICE_NUM;		//�f�o�C�X�̍ő吔���擾
		m_dwJoyCount = 0;						//���݃f�o�C�X�ԍ���������


		//�������p
		DIJOYSTATE dijs = {0};

		for ( DWORD dw = 0; dw < INPUT_DEVICE_NUM; dw++ )
		{
			m_lpDIDevice[dw] = nullptr;	//�W���C�X�e�B�b�N�f�o�C�X�̏�����
			memcpy( &m_dijs[dw], &dijs, sizeof(DIJOYSTATE) );
			memcpy( &m_preDijs[dw], &dijs, sizeof(DIJOYSTATE) );
		}


		//�f�o�C�X��񋓂��č쐬
		hr = lpDI->EnumDevices( DI8DEVCLASS_GAMECTRL, EnumJoystickCallback, (LPVOID)this, DIEDFL_ATTACHEDONLY );
		if ( FAILED(hr) )
		{
			DXTRACE_ERR( TEXT("DirectInputDevice8�I�u�W�F�N�g�̍쐬�Ɏ��s"), hr);
			return;
		}

		//�v���p�e�B�����l��ݒ�i���ƃo�b�t�@�T�C�Y�Ŏg�p����j
		DIPROPDWORD diprop;
		ZeroMemory( &diprop, sizeof(diprop) );
		diprop.diph.dwSize			= sizeof(diprop);
		diprop.diph.dwHeaderSize	= sizeof(diprop.diph);
		diprop.diph.dwObj			= 0;
		diprop.diph.dwHow			= DIPH_DEVICE;

		//�W���C�X�e�B�b�N�ʐݒ�
		//(�R�[���o�b�N�֐�EnumJoystickCallback�ɂ�����m_dwJoyCount�̓f�o�C�X�̐��ɂȂ��Ă���)
		for ( DWORD dw = 0; dw < m_dwJoyCount; dw++ )
		{
			//�f�[�^�`����ݒ�
			hr = m_lpDIDevice[dw]->SetDataFormat( &c_dfDIJoystick );
			if ( FAILED(hr) )
			{
				DXTRACE_ERR(  TEXT("c_dfDIJoystick2�`���̐ݒ�Ɏ��s"), hr);
				return;
			}

			//���[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
			hr = m_lpDIDevice[dw]->SetCooperativeLevel( HWnd::Get(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE );
			if( FAILED(hr) )
			{
				DXTRACE_ERR(  TEXT("�t�H�A�O���E���h����r�����[�h�̐ݒ�Ɏ��s"), hr);
				return;
			}

			//�R�[���o�b�N�֐����g���Ċe���̃��[�h��ݒ�
			//�����[�h�����l
			diprop.dwData = DIPROPAXISMODE_ABS;		//��Βl���[�h
//			diprop.dwData = DIPROPAXISMODE_REL;		//���Βl���[�h
			hr = m_lpDIDevice[dw]->EnumObjects( EnumAxisCallback, (LPVOID)m_lpDIDevice[dw], DIDFT_AXIS );
			if( FAILED(hr) )
			{
				DXTRACE_ERR(  TEXT("�����[�h�̐ݒ�Ɏ��s"), hr );
				return;
			}

			//�v���p�e�B�̐ݒ�
			hr = m_lpDIDevice[dw]->SetProperty( DIPROP_BUFFERSIZE, &diprop.diph );
			if( FAILED(hr) )
			{
				DXTRACE_ERR(  TEXT("�o�b�t�@�T�C�Y�̐ݒ�Ɏ��s"), hr );
				return;
			}

//			DXTRACE_MSG( TEXT("DirectInput: �W���C�X�e�B�b�N�@�ݒ萬��") );

			//���͐���J�n
			m_lpDIDevice[dw]->Acquire();
		}
	}

	//�W���C�X�e�B�b�N�@�R�[���o�b�N�֐�
	//�������F�f�o�C�X�n���h��
	//�������F(�ėp�|�C���^)�����I�u�W�F�N�g�̃|�C���^
	//�ߒl�F���s�c�cDIENUM_CONTINUE�C�I���c�cDIENUM_STOP
	BOOL CALLBACK DxJoystick::EnumJoystickCallback( const DIDEVICEINSTANCE* lpddi, LPVOID lpContext )
	{
		//�������玩�g��this�|�C���^�𓾂�
		DxJoystick* pDxJoystick = (DxJoystick*)lpContext;

		HRESULT hr;	//�C���^�[�t�F�[�X�ߒl

		//�񋓂��ꂽ�W���C�X�e�B�b�N�ւ̃C���^�[�t�F�[�X���擾����
		hr = pDxJoystick->m_lpDI->CreateDevice(
				lpddi->guidInstance, 
				&pDxJoystick->m_lpDIDevice[pDxJoystick->m_dwJoyCount], 
				nullptr
		);
		if ( FAILED(hr) )
		{
			DXTRACE_ERR( TEXT("�W���C�X�e�B�b�N�̗񋓂Ɏ��s"), hr );
			return DIENUM_CONTINUE;		//���s�����瑱�s
		}
		
		//�W���C�X�e�B�b�N�\�͂𒲂ׂ�
		DWORD index = pDxJoystick->GetJoyCount();		//���݃W���C�X�e�B�b�N�����擾

		pDxJoystick->m_diDevCaps[index].dwSize = sizeof(DIDEVCAPS);
		hr = pDxJoystick->m_lpDIDevice[index]->GetCapabilities( &pDxJoystick->m_diDevCaps[index] );
		if ( FAILED(hr) )
		{
			DXTRACE_ERR( TEXT("�W���C�X�e�B�b�N�̐ݒ�Ɏ��s"), hr);
			RELEASE( pDxJoystick->m_lpDIDevice[index] );
			return DIENUM_CONTINUE;
		}

		//�W���C�X�e�B�b�N�����C���N�������g���A�ő�l�ɂȂ��Ă�����X�g�b�v����
		if ( ++(pDxJoystick->m_dwJoyCount) == pDxJoystick->m_dwJoyMaxCount )
		{
			return DIENUM_STOP;
		}
		return DIENUM_CONTINUE;		//����ȊO�͑��s
	}


	//�W���C�X�e�B�b�N�̎���񋓂���֐�
	//�������F�f�o�C�X�n���h��
	//�������F�񋓂��ꂽ�f�o�C�X�I�u�W�F�N�g�̃|�C���^
	//�ߒl�F���s�c�cDIENUM_CONTINUE�C�I���c�cDIENUM_STOP
	BOOL CALLBACK DxJoystick::EnumAxisCallback( LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID lpRef )
	{
		//���͈̔͂�ݒ�(-1000�`+1000)
		DIPROPRANGE diprg;
		ZeroMemory( &diprg, sizeof(diprg) );
		diprg.diph.dwSize		= sizeof(diprg);
		diprg.diph.dwHeaderSize	= sizeof(diprg.diph);
		diprg.diph.dwObj		= lpddoi->dwType;
		diprg.diph.dwHow		= DIPH_BYID;
		diprg.lMin				= -1000;
		diprg.lMax				= +1000;

		//�f�o�C�X�̐ݒ�
		LPDIRECTINPUTDEVICE8 lpDevice = (LPDIRECTINPUTDEVICE8)lpRef;
		HRESULT hr;

		hr = lpDevice->SetProperty( DIPROP_RANGE, &diprg.diph );
		if( FAILED(hr) )
		{
			DXTRACE_ERR( TEXT("�W���C�X�e�B�b�N�̎��̐ݒ�Ɏ��s"), hr);		
			return DIENUM_STOP;
		}

		return DIENUM_CONTINUE;
	}

	//���
	void DxJoystick::Rele()
	{
		for( DWORD dw = 0; dw < m_dwJoyCount; dw++ )
		{
			if( m_lpDIDevice[dw] ) m_lpDIDevice[dw]->Unacquire();	//�v��������
			RELEASE( m_lpDIDevice[dw] );	//���
		}
	}

	//--------------------------------------------------------------------------
	//�Q�[�����p
	//--------------------------------------------------------------------------

	//��Ԃ̍X�V
	void DxJoystick::Update()
	{
		//�l�̕ۑ�
		memcpy( &m_preDijs, &m_dijs, sizeof(DIJOYSTATE) * INPUT_DEVICE_NUM );

		for ( DWORD dw = 0; dw < m_dwJoyCount; dw++ )
		{
			if ( m_lpDIDevice[dw] != nullptr )
			{
				HRESULT hr = m_lpDIDevice[dw]->Poll();
				if ( FAILED(hr) )
				{
					if ( hr == DIERR_INPUTLOST )
					{
						m_lpDIDevice[dw]->Acquire();
					}
				}
				hr = m_lpDIDevice[dw]->GetDeviceState( sizeof(DIJOYSTATE), &m_dijs[dw] );
			}
		}
	}

	//--------------------------------------------------------------------------
	//	�{�^��
	//--------------------------------------------------------------------------
	//�w�肵���{�^����������Ă��邩
	//�����F nDevice �f�o�C�X�ԍ�, nButton �{�^���ԍ�
	bool DxJoystick::IsButton( int nDevice, int nButton ) const
	{
		//�w��f�o�C�X�����݂��Ȃ��Ƃ�false��Ԃ�
		if ( ! m_lpDIDevice[nDevice] ) return false;

		return ( m_dijs[nDevice].rgbButtons[ nButton ] & 0x80 ) ? true: false;
	}

	//�w�肵���{�^���������ꂽ�u�Ԃ�
	//�����F nDevice �f�o�C�X�ԍ�, nButton �{�^���ԍ�
	bool DxJoystick::PushButton( int nDevice, int nButton ) const
	{
		//�w��f�o�C�X�����݂��Ȃ��Ƃ�false��Ԃ�
		if ( ! m_lpDIDevice[nDevice] ) return false;

		//���݂̏�Ԃ�������Ă���@���@�O�̏�Ԃ�������Ă��Ȃ�
		return ( (m_dijs[nDevice].rgbButtons[ nButton ] & 0x80) && ! (m_preDijs[nDevice].rgbButtons[ nButton ] & 0x80) ) ? true: false;
	}

	//�w�肵���{�^���������ꂽ�u�Ԃ�
	//�����F nDevice �f�o�C�X�ԍ�, nButton �{�^���ԍ�
	bool DxJoystick::ReleaseButton( int nDevice, int nButton ) const
	{
		//�w��f�o�C�X�����݂��Ȃ��Ƃ�false��Ԃ�
		if ( ! m_lpDIDevice[nDevice] ) return false;

		//���݂̏�Ԃ�������Ă��Ȃ��@���@�O�̏�Ԃ�������Ă���
		return ( ! (m_dijs[nDevice].rgbButtons[ nButton ] & 0x80) && (m_preDijs[nDevice].rgbButtons[ nButton ] & 0x80) ) ? true: false;
	}


	//--------------------------------------------------------------------------
	//POV
	//--------------------------------------------------------------------------
	
	//POV�̏�Ԃ�Ԃ�( �ォ�� 0, 9000, 18000, 27000 )
	//���΂߂��P��̒l�����̂Ŕ͈͂Ŏw�肷��(0,4500,9000,13500,18000,22500,27000,31500)
	DWORD DxJoystick::GetPov ( int id ) const
	{ 
		return m_dijs [ id ].rgdwPOV [ 0 ]; 
	}

	//-----------------------------------------------
	bool DxJoystick::IsPovUp ( int id ) const
	{
		DWORD th = m_dijs [ id ].rgdwPOV [ 0 ];
		bool ret = ( 0 <= th && th <= 4500 ) || ( 31500 <= th && th <= 35999 );
		return ret;
	}

	bool DxJoystick::IsPovRight ( int id ) const
	{
		DWORD th = m_dijs [ id ].rgdwPOV [ 0 ];
		return ( 4500 <= th && th <= 13500 );
	}

	bool DxJoystick::IsPovDown ( int id ) const
	{
		DWORD th = m_dijs [ id ].rgdwPOV [ 0 ];
		return ( 13500 <= th && th <= 22500 );
	}

	bool DxJoystick::IsPovLeft ( int id )  const
	{
		DWORD th = m_dijs [ id ].rgdwPOV [ 0 ];
		return ( 22500 <= th && th <= 31500 );
	}

	//-----------------------------------------------
	bool DxJoystick::IsPrePovUp ( int id ) const
	{
		DWORD th = m_preDijs [ id ].rgdwPOV [ 0 ];
		bool ret = ( 0 <= th && th <= 4500 ) || ( 31500 <= th && th <= 35999 );
		return ret;
	}

	bool DxJoystick::IsPrePovRight ( int id ) const
	{
		DWORD th = m_preDijs [ id ].rgdwPOV [ 0 ];
		return ( 4500 <= th && th <= 13500 );
	}

	bool DxJoystick::IsPrePovDown ( int id ) const
	{
		DWORD th = m_preDijs [ id ].rgdwPOV [ 0 ];
		return ( 13500 <= th && th <= 22500 );
	}

	bool DxJoystick::IsPrePovLeft ( int id )  const
	{
		DWORD th = m_preDijs [ id ].rgdwPOV [ 0 ];
		return ( 22500 <= th && th <= 31500 );
	}


}	//namespace GAME


