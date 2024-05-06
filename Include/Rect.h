//=================================================================================================
//
// Rect�@�w�b�_�t�@�C��
//		��`���ʏ������`
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Define.h"


//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//-------------------------------------------------------------------------------------------------
	// RECT�^ �錾
	//-------------------------------------------------------------------------------------------------
	using V_RECT = std::vector < RECT >;
	using PV_RECT = std::shared_ptr < V_RECT >;

	using P_RECT = std::shared_ptr < RECT >;
	using VP_RECT = std::vector < P_RECT >;
	using PVP_RECT = std::shared_ptr < VP_RECT >;

	//-------------------------------------------------------------------------------------------------
	//	�O���[�o���֐��v���g�^�C�v�錾
	//-------------------------------------------------------------------------------------------------

	//�[���ŏ���������
	void ZeroRect ( RECT & rect );

	//��g(���ׂ�0)���ǂ���
	bool IsZeroRect ( const RECT & rect );

	//��`�̒l��ݒ肷��
	void SetRect ( RECT & rect, LONG left, LONG top, LONG right, LONG bottom );

	//��`��rhs����lhs�ɃR�s�[����
	void CopyRect ( RECT & lhs, const RECT & rhs );

	//�g�z��̒l���[������������(�z��T�C�Y�͌Œ�)
	void ZeroVecRect ( PV_RECT pvRect );

	//-------------------------------------
	//�d�Ȃ蔻��

	//�_�Ƌ�`�̏d�Ȃ蔻��
	bool OverlapPoint ( const VEC2 & pt, const RECT & rect );

	//��`�Q�ŏd�Ȃ蔻��
	bool OverlapRect ( const RECT & rect1, const RECT & rect2 );

	//�g�z��ɍs���d�Ȃ蔻��
	bool OverlapAryRect ( PV_RECT pvRect1, PV_RECT pvRect2 );

	//�g�d�Ȃ蕔���̒��S�ʒu���擾
	VEC2 GetOverlayCenterRects ( const RECT & rect1, const RECT & rect2 );

	//�g�z��ɍs���d�Ȃ蔻��(�d�Ȃ�̒��S�t��)
	bool OverlapAryRect_Center ( PV_RECT pvRect1, PV_RECT pvRect2, VEC2 & center );	//���S�����߂�


}	//namespace GAME


