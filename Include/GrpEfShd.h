//=================================================================================================
//
// GrpEfShd �w�b�_�t�@�C��
// �V�F�[�_
//	�L�������m�ɂ��ʒu�␳��p����G�t�F�N�g
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
	class GrpEfShd : public GrpShd
	{
		VEC2	m_base { 0, 0 };		//��ʒu
		VEC2	m_revised { 0, 0 };		//�␳�ʒu	//GrpAcv�Ƃ̍����ɒ���
		V_VEC2	m_vPosMatrix;			//�����}�g���b�N�X�g�p���̕␳�ʒu
		VEC2	m_dispBase { 0, 0 };	//�O���␳�ʒu

		UINT	m_timer { 0 };
		VEC2	m_startScaling { 1.f, 1.f };	//�J�n
		VEC2	m_targetScaling { 1.f, 1.f };	//�ڕW
		VEC2	m_vec { 0, 0 };
		VEC2	m_vel { 0, 0 };
		VEC2	m_acc { 0, 0 };


	public:
		GrpEfShd ();
		GrpEfShd ( const GrpEfShd & rhs ) = delete;
		~GrpEfShd ();

		void Load ();
		void Init ();
		void Move ();

		void On ();
		void Off ();

		void Advance ();	//���ɐi�߂�

		//�v���Z�b�g
		void Preset_Ef_Action ();

		//�L�����ʒu�ɂ���ʕ␳
		void SetDispBase ( VEC2 v ) { m_dispBase = v; }

		void SetBase ( VEC2 vec ) { m_base = vec; }
		VEC2 GetRevised () const { return m_revised; }
		void SetRevised ( VEC2 vec ) { m_revised = vec; }

		void SetTimer ( UINT n ) { m_timer = n; }
		void SetStartScaling ( VEC2 vec ) { m_startScaling = vec; }
		void SetTargetScaling ( VEC2 vec ) { m_targetScaling = vec; }

		void SetVel ( VEC2 vec ) { m_vel = vec; }
		void SetAcc ( VEC2 vec ) { m_acc = vec; }

		//�����I�u�W�F�N�g�̏����ݒ�
//		void ResetObjectNUm ( UINT n ) {}

		void AddObject () 
		{
			m_vPosMatrix.push_back ( VEC2 ( 0, 0 ) );
//			GrpShd::AddObject ();
		}

		void AddObject ( UINT n )
		{
			for ( UINT i = 0; i < n; ++i ) { AddObject (); }
		}
		
		void AddpObject ( P_Ob p )
		{
			m_vPosMatrix.push_back ( VEC2 ( 0, 0 ) );
			GrpShd::AddpObject ( p );
		}
		
		void SetPosMatrix ( UINT i, VEC2 pos )
		{
			m_vPosMatrix[i] = pos;
		}

		//�v�Z��̍ŏI�ʒu���擾
		VEC2 GetCalcPos ( UINT i )
		{
			//��ʒu + �␳�ʒu + �O���␳�ʒu + �ʈʒu
			return m_base + m_revised + m_dispBase + m_vPosMatrix[i];

		}

		//�C���f�b�N�X�Ŏw�肵���e�N�X�`���Œ��S��ݒ肷��
		void SetCenterOfTexture ();
	};

	using P_GrpEfShd = std::shared_ptr < GrpEfShd >;


}	//namespace GAME


