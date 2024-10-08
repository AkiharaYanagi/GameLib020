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
#include "02_GameGraphic.h"


//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class GrpDemo : public GameGraphic
	{
		UINT		m_timer { 0 };		//�^�C�}���ݒl
		UINT		m_endTime { 10 };	//�^�C�}�I��
		bool		m_end { F };		//�I���t���O

		VEC2		m_startScaling { 1.f, 1.f };	//�J�n
		VEC2		m_targetScaling { 1.f, 1.f };	//�ڕW
		VEC2		m_mag { 1.f, 1.f };		//�{��
		VEC2		m_vel { 0, 0 };			//�{���ω����x
		VEC2		m_acc { 0, 0 };			//�{���ω������x
		VEC2		m_secondVel { 0, 0 };	//��2���x

	public:
		GrpDemo ();
		GrpDemo ( const GrpDemo& rhs ) = delete;
		~GrpDemo ();

		void DemoInit ();	//���삷�鏉���l
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


