//=================================================================================================
//
// GrpDemo �w�b�_�t�@�C��
//	�L�����ʒu�ɂ�炸���̈ʒu�ŕ\��
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Game.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class GrpDemo : public GameGraphic
	{
		UINT		m_timer;	//�����^�C�}
		VEC2		m_startScaling;		//�J�n
		VEC2		m_targetScaling;	//�ڕW
		VEC2		m_mag;		//�{��
		VEC2		m_vel;		//�{���ω����x
		VEC2		m_acc;		//�{���ω������x

		VEC2		m_secondVel;	//��2���x

		bool		m_end;	//�I���t���O
		UINT		m_endTime;

	public:
		GrpDemo ();
		GrpDemo ( const GrpDemo& rhs ) = delete;
		~GrpDemo ();

		void Init ();
		void Move ();

		void Start ();

		void SetTimer ( UINT n ) { m_timer = n; }
		void SetStartScaling ( VEC2 vec ) { m_startScaling = vec; }
		void SetTargetScaling ( VEC2 vec ) { m_targetScaling = vec; }

		void SetVel ( VEC2 vec ) { m_vel = vec; }
		void SetAcc ( VEC2 vec ) { m_acc = vec; }
		void SetSecondVel ( VEC2 vec ) { m_secondVel = vec; }

		void SetEnd ( UINT n ) { m_end = false; m_endTime = n; }
		void ResetEnd () { m_end = false; }
	};

	using P_GrpDemo = std::shared_ptr < GrpDemo >;


}	//namespace GAME


