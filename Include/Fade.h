//=================================================================================================
//
// �t�F�[�h
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "DebugLibrary.h"
#include "DxDefine.h"			//DirectX���O����

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//------------------------------------------------------------
	//�t�F�[�h�I�u�W�F�N�g
	//	�O���t�B�b�N���ۗL����^�X�N
	//	���ԂƐF���w�肵�A�t���[�����ɑJ�ڂ���(���ݐF��Ԃ�)
	//------------------------------------------------------------
	class Fade
	{
		UINT	m_timer;	//���ݎ���
		UINT	m_time;		//�ڍs����

		_CLR	m_color_present;//���ݐF

		_CLR	m_color_start;	//�����F
		_CLR	m_color_end;	//�ڕW�F

	public:
		Fade ();
		Fade ( const Fade & rhs );	//�R�s�[�\
		~Fade ();

		//���t���[������(Move()���擪�ŌĂ�)
		void PreMove ();

		//�F�ۑ�
		void SetColor ( _CLR clr) { m_color_present = clr; }

		//�F�擾
		_CLR GetColor () const { return m_color_present; }

		//�t�F�[�h���Ԑݒ�
		void SetTime ( UINT time );

		//���ݎ��ԁi�ғ���ԁj���擾
		UINT GetTimer () const { return m_timer; }

		//�F�ݒ�
		void SetFadeColor ( _CLR clr_start, _CLR clr_end )
		{
			m_color_start = clr_start; 
			m_color_end = clr_end; 
		}

		//�t�F�[�h�ݒ�
		void SetFade ( UINT time, _CLR clr_start, _CLR clr_end )
		{
			SetTime ( time );
			SetFadeColor ( clr_start, clr_end );
			m_color_present = clr_start;
		}

		//�I��
		void End ( _CLR clr );

	private:

		//������
		void _Fade_Do ();
	};


}	//namespace GAME


