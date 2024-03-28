//=================================================================================================
//
// Direct Input �ɂ��W���C�X�e�B�b�N�̊Ǘ��@�N���X
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�̃C���N���[�h
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
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//------------------------------------------
	//�萔�錾
	//------------------------------------------
	const int INPUT_DEVICE_NUM = 16;	//�f�o�C�X�̍ő吔(Windows�ŃW���C�X�e�B�b�N�̈�����͈�)

	//--------------------------------------------------------
	// Direct Input �ɂ��W���C�X�e�B�b�N�̊Ǘ��@�N���X
	//--------------------------------------------------------
	class DxJoystick
	{
		LPDIRECTINPUT8			m_lpDI;			//DirectInput�I�u�W�F�N�g
		LPDIRECTINPUTDEVICE8	m_lpDIDevice[INPUT_DEVICE_NUM];		//�񋓂����f�o�C�X
		DIDEVCAPS				m_diDevCaps[INPUT_DEVICE_NUM];		//�W���C�X�e�B�b�N�̔\��

		DIJOYSTATE				m_dijs[INPUT_DEVICE_NUM];			//�W���C�X�e�B�b�N���
		DIJOYSTATE				m_preDijs[INPUT_DEVICE_NUM];		//���O�̃W���C�X�e�B�b�N���

		//DirectInput�ϐ�
		DWORD	m_dwJoyMaxCount;	//������W���C�X�e�B�b�N�̍ő吔
		DWORD	m_dwJoyCount;		//�W���C�X�e�B�b�N�̎���(��Ƀf�o�C�X�z��̓Y����)

		//DirectInput�R�[���o�b�N�֐�
		static BOOL CALLBACK EnumJoystickCallback ( const DIDEVICEINSTANCE* lpddi, LPVOID lpContext );
		static BOOL CALLBACK EnumAxisCallback ( LPCDIDEVICEOBJECTINSTANCE lpddi, LPVOID lpvRef );

	public:
		DxJoystick ();
		DxJoystick ( const DxJoystick& rhs ) = delete;
		~DxJoystick ();

		void Init( LPDIRECTINPUT8 lpDI );		//������
		void Rele();	//���


		//--------------------------------------------------------------
		//	���݃W���C�X�e�B�b�N����Ԃ��֐�
		DWORD GetJoyCount () const { return m_dwJoyCount; }

		//�Q�[�����p
		//��Ԃ̍X�V
		void Update ();


		//--------------------------------------------------------------
		//�{�^��

		//�w�肵���{�^����������Ă����Ԃ�
		bool IsButton( int id, int nButton ) const;
		//�w�肵���{�^���������ꂽ�u�Ԃ�
		bool PushButton( int id, int nButton ) const;
		//�w�肵���{�^���������ꂽ�u�Ԃ�
		bool ReleaseButton( int id, int nButton ) const;


		//--------------------------------------------------------------
		//���̏�Ԃ�Ԃ�
		LONG GetJoyAxisX( int id ) const { return m_dijs[id].lX; }
		LONG GetJoyAxisY( int id ) const { return m_dijs[id].lY; }

		//Axis:��������Ԃ̔���
		bool IsAxisUp	( int id ) const { return ( m_dijs[id].lY <= -500 ); }
		bool IsAxisDown	( int id ) const { return ( m_dijs[id].lY >=  500 ); }
		bool IsAxisLeft	( int id ) const { return ( m_dijs[id].lX <= -500 ); }
		bool IsAxisRight( int id ) const { return ( m_dijs[id].lX >=  500 ); }

		//�O�t���[���̏��
		bool IsPreAxisUp	( int id ) const { return ( m_preDijs [ id ].lY <= -500 ); }
		bool IsPreAxisDown	( int id ) const { return ( m_preDijs [ id ].lY >=  500 ); }
		bool IsPreAxisLeft	( int id ) const { return ( m_preDijs [ id ].lX <= -500 ); }
		bool IsPreAxisRight	( int id ) const { return ( m_preDijs [ id ].lX >=  500 ); }

		//�������u�Ԃ̔���(�O��off ����on)
		bool PushAxisUp		( int id ) const { return ( ! IsPreAxisUp(id)    && IsAxisUp(id)    ); }
		bool PushAxisDown	( int id ) const { return ( ! IsPreAxisDown(id)  && IsAxisDown(id)  ); }
		bool PushAxisLeft	( int id ) const { return ( ! IsPreAxisLeft(id)  && IsAxisLeft(id)  ); }
		bool PushAxisRight	( int id ) const { return ( ! IsPreAxisRight(id) && IsAxisRight(id) ); }

		//�������u�Ԃ̔���(�O��on ����off)
		bool ReleAxisUp   ( int id ) const { return ( IsPreAxisUp(id)    && ! IsAxisUp(id)    ); }
		bool ReleAxisDown ( int id ) const { return ( IsPreAxisDown(id)  && ! IsAxisDown(id)  ); }
		bool ReleAxisLeft ( int id ) const { return ( IsPreAxisLeft(id)  && ! IsAxisLeft(id)  ); }
		bool ReleAxisRight( int id ) const { return ( IsPreAxisRight(id) && ! IsAxisRight(id) ); }

		//--------------------------------------------------------------
		//POV�̏�Ԃ�Ԃ�( �ォ�� 0, 9000, 18000, 27000 )
		//���΂߂��P��̒l�����̂Ŕ͈͂Ŏw�肷��

		DWORD GetPov		( int id ) const;

		//���������
		bool IsPovUp		( int id ) const;
		bool IsPovRight		( int id ) const;
		bool IsPovDown		( int id ) const;
		bool IsPovLeft		( int id ) const;

		//�O�t���[���̏��
		bool IsPrePovUp		( int id ) const;
		bool IsPrePovRight	( int id ) const;
		bool IsPrePovDown	( int id ) const;
		bool IsPrePovLeft	( int id ) const;

		//�������u�Ԃ̔���(�O��off ����on)
		bool PushPovUp		( int id ) const { return ( ! IsPrePovUp ( id )		&& IsPovUp ( id ) ); }
		bool PushPovRight	( int id ) const { return ( ! IsPrePovRight ( id )	&& IsPovRight ( id ) ); }
		bool PushPovDown	( int id ) const { return ( ! IsPrePovDown ( id )	&& IsPovDown ( id ) ); }
		bool PushPovLeft	( int id ) const { return ( ! IsPrePovLeft ( id )	&& IsPovLeft ( id ) ); }

		//�������u�Ԃ̔���(�O��on ����off)
		bool RelePovUp		( int id ) const { return ( IsPrePovUp ( id ) && ! IsPovUp ( id ) ); }
		bool RelePovRight	( int id ) const { return ( IsPrePovRight ( id ) && ! IsPovRight ( id ) ); }
		bool RelePovDown	( int id ) const { return ( IsPrePovDown ( id ) && ! IsPovDown ( id ) ); }
		bool RelePovLeft	( int id ) const { return ( IsPrePovLeft ( id )	&& ! IsPovLeft ( id ) ); }

	};


}	//namespace GAME

