//=================================================================================================
//
// GrpEf �w�b�_�t�@�C��
//	Pos��Base��Revised�Ōv�Z����
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "GameGraphic.h"
#include "Timer.h"


//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class GrpEf : public GameGraphic
	{
		VEC2	m_base { 0, 0 };		//��ʒu
		VEC2	m_revised { 0, 0 };		//�␳�ʒu	//GrpAcv�Ƃ̍����ɒ���
//		V_VEC2	m_vPosMatrix;			//�����I�u�W�F�N�g�g�p���̌ʕ␳�ʒu
		VEC2	m_dispBase { 0, 0 };	//�O���␳�ʒu(�L�������m�ɂ���ʕ␳)

		VEC2	m_startScaling { 1.f, 1.f };	//�J�n
		VEC2	m_targetScaling { 1.f, 1.f };	//�ڕW
		VEC2	m_vec { 0, 0 };
		VEC2	m_vel { 0, 0 };
		VEC2	m_acc { 0, 0 };

		Timer	m_tmr;

		//�\�����e�N�X�`�����S�ʒu�ɂ���(��F�w��)
		bool	m_bCenterOfTx { F };


	public:
		GrpEf ();
		GrpEf ( const GrpEf & rhs ) = delete;
		~GrpEf ();

		void Load ();
		void Init ();
		void Move ();

		void On ();
		void Off ();

		void Advance ();		//�e�N�X�`�������ɐi�߂�@�Ō�܂ōs������Off()
		void Advance_Loop ();	//�e�N�X�`�������ɐi�߂�@�Ō�܂ōs������ŏ��ɖ߂�

		//�v���Z�b�g
		void Preset_Ef_Action ();

		//�L�����ʒu�ɂ��Q�[����ʕ␳
		void SetDispBase ( VEC2 v ) { m_dispBase = v; }

		//�x�[�X�ɃQ�[���ʒu��������
		void SetBase ( VEC2 vec ) { m_base = vec; }

		//���o�C�Y�h���\���ʒu���C������(�e�N�X�`���̒��S�Ȃ�)
		VEC2 GetRevised () const { return m_revised; }
		void SetRevised ( VEC2 vec ) { m_revised = vec; }

//		void SetTimer ( UINT n ) { m_timer = n; }
		void SetStartScaling ( VEC2 vec ) { m_startScaling = vec; }
		void SetTargetScaling ( VEC2 vec ) { m_targetScaling = vec; }

		void SetVel ( VEC2 vec ) { m_vel = vec; }
		void SetAcc ( VEC2 vec ) { m_acc = vec; }

		//�����I�u�W�F�N�g�̏����ݒ�
//		void ResetObjectNUm ( UINT n ) {}

#if 0

		void AddObject () 
		{
			m_vPosMatrix.push_back ( VEC2 ( 0, 0 ) );
//			GameGraphic::AddObject ();
		}

		void AddObject ( UINT n )
		{
			for ( UINT i = 0; i < n; ++i ) { AddObject (); }
		}
		
		void AddpObject ( P_Ob p )
		{
			m_vPosMatrix.push_back ( VEC2 ( 0, 0 ) );
			GameGraphic::AddpObject ( p );
		}
		
		void SetPosMatrix ( UINT i, VEC2 pos )
		{
			m_vPosMatrix[i] = pos;
		}

#endif // 0

		//�v�Z��̍ŏI�ʒu���擾
		VEC2 GetCalcPos ( UINT i )
		{
			(void)i;

			//��ʒu + �␳�ʒu + �O���␳�ʒu + �ʈʒu
//			return m_base + m_revised + m_dispBase + m_vPosMatrix[i];
			return m_base + m_revised + m_dispBase;

		}

		//�C���f�b�N�X�Ŏw�肵���e�N�X�`���Œ��S��ݒ肷��
		void SetCenterOfTexture ();


		//�ʒu�w��J�n
		void Start ( VEC2 v, uint32 t );

		//�e�N�X�`�����S�ʒu�ŕ\��
		void SetbCenterOfTx ( bool b ) { m_bCenterOfTx = b; }
	};

	using P_GrpEf = std::shared_ptr < GrpEf >;


}	//namespace GAME


