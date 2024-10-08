//=================================================================================================
//
// FadeRect �w�b�_�t�@�C��
//		�őO�ʂɔz�u������ʃT�C�Y�̔������O���t�B�b�N�ŁA�t�F�[�h�C���E�A�E�g���s��
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "02_GameGraphic.h"
#include "Define_Siv3D.h"
#include "Timer.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class FadeRect : public PrmRect
	{
		P_Timer	m_timer;
		//_CLR	m_color0;	//�����F
		//_CLR	m_color1;	//�ڕW�F
		s3d::ColorF		m_color0;	//�����F
		s3d::ColorF		m_color1;	//�ڕW�F

		bool	m_after_clear { F };	//�I�����ɔ�\���ɂ��邩�ǂ���

	public:
		FadeRect ();
		FadeRect ( UINT time ) { SetTime ( time ); };
		FadeRect ( const FadeRect & rhs ) = delete;
		~FadeRect ();

		void Move ();

		//�F�ݒ�
		//void SetColor ( _CLR clr0, _CLR clr1 ) { m_color0 = clr0; m_color1 = clr1; }
		void SetColor ( s3d::ColorF clr0, s3d::ColorF clr1 ) { m_color0 = clr0; m_color1 = clr1; }
		void SetTime ( UINT t )
		{ 
			m_timer->SetTargetTime ( t ); 
		}

		void Start ()
		{
			m_timer->Start ();
			PrmRect::SetValid ( true );
		}

		void Start ( UINT time )
		{
			m_timer->SetTargetTime ( time );
			m_timer->Start ();
			PrmRect::SetValid ( true );
		}

		void Off ()
		{
			m_timer->Clear ();
			PrmRect::SetColor ( m_color1 );
			PrmRect::SetValid ( F );
		}

		bool IsActive () const { return m_timer->IsActive (); }
		bool IsLast () const { return m_timer->IsLast (); }

		//�I�����ɔ�\���ɂ��邩�ǂ���
		void SetAfterClear ( bool b ) { m_after_clear = b; }

		//-----------------------------------
		//��̐ݒ�
		//@info 0x00000000 ���w�肷��Ƃ�D3DXCOLOR�̏������̂��ߐ������e���� UL ��t����
		
		//�z���C�g�C��( 0xffffffff �� 0x00ffffff )
		void SetWhiteIn ( UINT time );
		void StartWhiteIn ( UINT time ) { SetWhiteIn ( time ); Start (); }

		//�z���C�g�A�E�g( 0x00ffffff �� 0xffffffff )
		void SetWhiteOut ( UINT time );
		void StartWhiteOut ( UINT time ) { SetWhiteOut ( time ); Start (); }

		//�u���b�N�C�� ( 0xff000000 �� 0x00000000 )
		void SetBlackIn ( UINT time );
		void StartBlackIn ( UINT time ) { SetBlackIn ( time ); Start (); }

		//�u���b�N�A�E�g( 0x00000000 �� 0xff000000 )
		void SetBlackOut ( UINT time );
		void StartBlackOut ( UINT time ) { SetBlackOut ( time ); Start (); }
	};

	using P_FadeRect = std::shared_ptr < FadeRect >;


}	//namespace GAME


