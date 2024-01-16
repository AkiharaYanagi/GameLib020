//=================================================================================================
//
// DirectInput �̎���
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "DxInput.h"

//-------------------------------------------------------------------------------------------------
// ���C�u���������݂̂ŎQ�Ƃ���w�b�_�t�@�C��
//-------------------------------------------------------------------------------------------------
#include "DxJoystick.h"			//�W���C�X�e�B�b�N
#include "DxKeyboard.h"			//�L�[�{�[�h
#include "DxMouse.h"			//�}�E�X

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//-------------------------------------------------------------------------------------------------
	//	�V���O���g���@�C���X�^���X
	//-------------------------------------------------------------------------------------------------
	DxInput::P_DxInput		DxInput::m_inst = nullptr;

	//-------------------------------------------------------------------------------------------------
	//	�V���O���g���@�C���X�^���X����
	//-------------------------------------------------------------------------------------------------
	void DxInput::Create ()
	{
		assert ( ! m_inst );
		if ( ! m_inst ) { m_inst = P_DxInput ( new DxInput () ); }
	}

	//-------------------------------------------------------------------------------------------------
	//	�R���X�g���N�^
	//-------------------------------------------------------------------------------------------------
	DxInput::DxInput ()
		: m_lpDI ( nullptr ), m_joystick ( nullptr ), m_keyboard ( nullptr ), m_mouse ( nullptr )
	{
		m_joystick = std::make_unique < DxJoystick > ();
		m_keyboard = std::make_unique < DxKeyboard > ();
		m_mouse = std::make_unique < DxMouse > ();

		Init ();		//������
	}

	//-------------------------------------------------------------------------------------------------
	//	�f�X�g���N�^
	//-------------------------------------------------------------------------------------------------
	DxInput::~DxInput ()
	{
		Rele ();	//���
	}


	//-------------------------------------------------------------------------------------------------
	//	DirectInput ������
	//-------------------------------------------------------------------------------------------------
	void DxInput::Init()
	{
		HRESULT hr;
		HINSTANCE hInstance = GetModuleHandle(nullptr);

		//DirectInput�I�u�W�F�N�g�̍쐬
#if	0
		hr = DirectInput8Create (	hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, 
									reinterpret_cast<LPVOID*>(&m_lpDI), nullptr );
		DXTRACE_RETURN_FLASE( hr, TEXT("DirectInput�I�u�W�F�N�g�̍쐬�Ɏ��s") );
#else
		::CoInitialize(nullptr);		//COM�̏�����
		//COM�I�u�W�F�N�g�Ƃ��Đ�������Ƃ�CoInitialize(nullptr)���ĂԕK�v������B�I�����ɂ�CoUninitialize()�B
		hr = ::CoCreateInstance( CLSID_DirectInput8, nullptr, CLSCTX_ALL, IID_IDirectInput8,
									reinterpret_cast<LPVOID*>(&m_lpDI) );
		if ( FAILED(hr) ) DXTRACE( hr, TEXT("COM�ɂ��DirectInput�I�u�W�F�N�g�̍쐬�Ɏ��s") );

		hr = m_lpDI->Initialize( hInstance, DIRECTINPUT_VERSION );
		if ( FAILED(hr) ) DXTRACE( hr, TEXT("DirectInput�I�u�W�F�N�g�̏������Ɏ��s") );
#endif	//0

		m_joystick->Init ( m_lpDI );	//	�W���C�X�e�B�b�N
		m_keyboard->Init ( m_lpDI );	//	�L�[�{�[�h
		m_mouse->Init ( m_lpDI );		//	�}�E�X
	}

	//-------------------------------------------------------------------------------------------------
	//	DirectInput ���
	//-------------------------------------------------------------------------------------------------
	void DxInput::Rele()
	{
		m_keyboard->Rele ();	//�L�[�{�[�h
		m_joystick->Rele ();	//�W���C�X�e�B�b�N
		m_mouse->Rele ();		//�}�E�X
		RELEASE ( m_lpDI );		//DirectInput�̉��
		::CoUninitialize ();	//COM�̉��
	}

	//-------------------------------------------------------------------------------------------------
	//	DirectInput �Đݒ�
	//-------------------------------------------------------------------------------------------------
	void DxInput::Reset()
	{
		Rele();
		Init();
	}

	//-------------------------------------------------------------------------------------------------
	//	�t���[�����̍X�V
	//-------------------------------------------------------------------------------------------------
	void DxInput::Update()
	{
		m_keyboard->Update();		//�L�[�{�[�h�f�o�C�X
		m_joystick->Update();		//�W���C�X�e�B�b�N
		m_mouse->Update();			//�}�E�X
	}


	//---------------------------------------------------------------------------
	//	�L�[�{�[�h
	//---------------------------------------------------------------------------
	//-------------------------------------------------------------------------------------------------
	//	�L�[�{�[�h�ŉ�����Ă����Ԃ��ǂ������擾����
	//	�����Fkey �L�[�{�[�h�̔z��萔
	//	�ߒl�F�Ώۂ̃L�[��������Ă����ԂȂ�true, �����łȂ����false
	//-------------------------------------------------------------------------------------------------
	bool DxInput::IsOneKeyboard ( int key ) const
	{
		return m_keyboard->IsKey( key );
	}

	//-------------------------------------------------------------------------------------------------
	//	�L�[�{�[�h�������ꂽ�u�Ԃ��ǂ������擾���� (1�t���[���O��false ���� ���݃t���[����true)
	//	�����Fkey �L�[�{�[�h�̔z��萔
	//	�ߒl�F�Ώۂ̃L�[�������ꂽ�u�ԂȂ�true, �����łȂ����false
	//-------------------------------------------------------------------------------------------------
	bool DxInput::PushOneKeyboard ( int key ) const
	{
		return m_keyboard->PushKey( key );
	}

	//-------------------------------------------------------------------------------------------------
	//	�L�[�{�[�h�������ꂽ�u�Ԃ��ǂ������擾���� (1�t���[���O��true ���� ���݃t���[����false)
	//	�����Fkey �L�[�{�[�h�̔z��萔
	//	�ߒl�F�Ώۂ̃L�[�������ꂽ�u�ԂȂ�true, �����łȂ����false
	//-------------------------------------------------------------------------------------------------
	bool DxInput::ReleaseOneKeyboard ( int key ) const
	{
		return m_keyboard->ReleaseKey( key );
	}


	//---------------------------------------------------------------------------
	//	�W���C�X�e�B�b�N
	//---------------------------------------------------------------------------
	//-------------------------------------------------------------------------------------------------
	//	�W���C�X�e�B�b�N(�L�[)�ŉ�����Ă����Ԃ��ǂ������擾����
	//	�����Fnum �f�o�C�X�ԍ�, key �L�[�ԍ�
	//-------------------------------------------------------------------------------------------------
	bool DxInput::IsJoyButton( int num, int btn ) const
	{
		return m_joystick->IsButton( num, btn );
	}
	//�W���C�X�e�B�b�N(Axis)�ŉ�����Ă����Ԃ��ǂ������擾����
	bool DxInput::IsAxisUp( int nDevice ) const { return m_joystick->IsAxisUp(nDevice); }
	bool DxInput::IsAxisDown( int nDevice ) const { return m_joystick->IsAxisDown(nDevice); }
	bool DxInput::IsAxisLeft( int nDevice ) const { return m_joystick->IsAxisLeft(nDevice); }
	bool DxInput::IsAxisRight( int nDevice ) const { return m_joystick->IsAxisRight(nDevice); }

	//�W���C�X�e�B�b�N(POV)�̏�Ԃ�Ԃ�
	DWORD DxInput::GetPov ( int id ) const { return m_joystick->GetPov ( id ); }
	bool DxInput::IsPovUp ( int nDevice ) const { return m_joystick->IsPovUp ( nDevice ); }
	bool DxInput::IsPovRight ( int nDevice ) const { return m_joystick->IsPovRight ( nDevice ); }
	bool DxInput::IsPovDown ( int nDevice ) const { return m_joystick->IsPovDown ( nDevice ); }
	bool DxInput::IsPovLeft ( int nDevice ) const { return m_joystick->IsPovLeft ( nDevice ); }


	//-------------------------------------------------------------------------------------------------
	//	�W���C�X�e�B�b�N(�L�[)�ŉ����ꂽ�u�Ԃ��ǂ������擾����
	//	�����Fnum �f�o�C�X�ԍ�, key �L�[�ԍ�
	//-------------------------------------------------------------------------------------------------
	bool DxInput::PushJoyButton( int num, int btn ) const
	{
		return m_joystick->PushButton( num, btn );
	}
	//�W���C�X�e�B�b�N(Axis)�ŉ����ꂽ�u�Ԃ��ǂ������擾����
	bool DxInput::PushAxisUp( int nDevice ) const { return m_joystick->PushAxisUp(nDevice); }
	bool DxInput::PushAxisDown( int nDevice ) const { return m_joystick->PushAxisDown(nDevice); }
	bool DxInput::PushAxisLeft( int nDevice ) const { return m_joystick->PushAxisLeft(nDevice); }
	bool DxInput::PushAxisRight( int nDevice ) const { return m_joystick->PushAxisRight(nDevice); }

	//�W���C�X�e�B�b�N(POV)�ŉ����ꂽ�u�Ԃ��ǂ������擾����
	bool DxInput::PushPovUp ( int nDevice ) const { return m_joystick->PushPovUp ( nDevice ); }
	bool DxInput::PushPovRight ( int nDevice ) const { return m_joystick->PushPovRight ( nDevice ); }
	bool DxInput::PushPovDown ( int nDevice ) const { return m_joystick->PushPovDown ( nDevice ); }
	bool DxInput::PushPovLeft ( int nDevice ) const { return m_joystick->PushPovLeft ( nDevice ); }


	//-------------------------------------------------------------------------------------------------
	//	�W���C�X�e�B�b�N(�L�[)�ŗ����ꂽ�u�Ԃ��ǂ������擾����
	//	�����Fnum �f�o�C�X�ԍ�, key �L�[�ԍ�
	//-------------------------------------------------------------------------------------------------
	bool DxInput::ReleaseJoyButton( int num, int btn ) const
	{
		return m_joystick->ReleaseButton( num, btn );
	}
	//	�W���C�X�e�B�b�N(Axis)�ŗ����ꂽ�u�Ԃ��ǂ������擾����
	bool DxInput::ReleaseAxisUp( int nDevice ) const { return m_joystick->ReleAxisUp(nDevice); }
	bool DxInput::ReleaseAxisDown( int nDevice ) const { return m_joystick->ReleAxisDown(nDevice); }
	bool DxInput::ReleaseAxisLeft( int nDevice ) const { return m_joystick->ReleAxisLeft(nDevice); }
	bool DxInput::ReleaseAxisRight( int nDevice ) const { return m_joystick->ReleAxisRight(nDevice); }

	//�W���C�X�e�B�b�N(POV)�ŗ����ꂽ�u�Ԃ��ǂ������擾����
	bool DxInput::RelePovUp ( int nDevice ) const { return m_joystick->RelePovUp ( nDevice ); }
	bool DxInput::RelePovRight ( int nDevice ) const { return m_joystick->RelePovRight ( nDevice ); }
	bool DxInput::RelePovDown ( int nDevice ) const { return m_joystick->RelePovDown ( nDevice ); }
	bool DxInput::RelePovLeft ( int nDevice ) const { return m_joystick->RelePovLeft ( nDevice ); }


	//���̏�Ԃ�Ԃ�
	LONG DxInput::GetJoyAxisX( int nDevice ) const { return m_joystick->GetJoyAxisX( nDevice ); }
	LONG DxInput::GetJoyAxisY( int nDevice ) const { return m_joystick->GetJoyAxisY( nDevice ); }


	//---------------------------------------------------------------------------
	//	�}�E�X
	//---------------------------------------------------------------------------
	bool DxInput::IsMouseButton ( MOUSE_BUTTON n ) const
	{
		return m_mouse->IsButton ( n ); 
	}

	bool DxInput::UpMouseButton ( MOUSE_BUTTON n ) const
	{
		return m_mouse->UpButton ( n ); 
	}

	POINT DxInput::GetMouseDelta () const
	{
		return m_mouse->GetMouseDelta (); 
	}

	POINT DxInput::GetMousePoint () const
	{
		//�}�E�X�ʒu�̎擾
		POINT cursorPt;
		::GetCursorPos ( &cursorPt );
		::ScreenToClient ( HWnd::Get(), &cursorPt );
		return cursorPt; 
	}

	bool DxInput::IsMouseInside ( LONG x, LONG y, LONG w, LONG h ) const
	{
		//�}�E�X�ʒu�̎擾
		POINT cursorPt = GetMousePoint ();
		if (	x <= cursorPt.x 
			&&	cursorPt.x <= x + w
			&&	y <= cursorPt.y 
			&&	cursorPt.y <= y + h )
		{
			return true;
		}
		return false; 
	}


}	//namespace GAME

