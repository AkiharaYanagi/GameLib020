//=================================================================================================
//
// GrpBlink �w�b�_�t�@�C��
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "GameGraphic.h"


//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class GrpBlink : public GameGraphic
	{
		bool	m_blink { T };		//�_�ŕ���(T:�S�F, F:����)
		uint32	m_timer { 0 };		//���ݎ���
		uint32	m_blinkTime { 30 };	//�_�Ŏ���
		bool	m_active { T };		//�ғ��t���O
		bool	m_half { F };		//�����܂łŐ܂�Ԃ�

		void Blink ();

	public:
		GrpBlink ();
		GrpBlink ( const GrpBlink & rhs ) = delete;
		~GrpBlink ();

		void Move ();

		void SetTimer ( uint32 n ) { m_timer = n; }
		void SetBlinkTime ( uint32 n ) { m_blinkTime = n; }
		void Stop ();
		void Start ();
		void SetHalf ( bool b ) { m_half = b; }
	};

	using P_GrpBlink = std::shared_ptr < GrpBlink >;


}	//namespace GAME


