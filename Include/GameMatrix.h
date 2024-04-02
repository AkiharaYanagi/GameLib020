//=================================================================================================
//
//	�Q�[���}�g���N�X�@�w�b�_
//		�P�̕ϊ��s��Ƃ��̃p�����[�^������
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���@�C���N���[�h
//-------------------------------------------------------------------------------------------------
//#include "DebugManager.h"
//#include "Dx3D.h"
#include "Define.h"


//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class GameMatrix
	{
//		D3DXMATRIX		m_matrix;				//�ϊ��s��̈ꎞ�ۑ�

		VEC2			m_vecPos { 0, 0 };			//���I�u�W�F�N�g�ʒu
//		VEC2			m_vecDisp;					//�X�N���[���\���ʒu
		VEC2			m_scalingCenter { 0, 0 };	//�X�P�[�����O�̒��S���W
		VEC2			m_scaling { 0, 0 };			//�X�P�[�����O
		float			m_scalingRotation { 0 };	//�g���]�̗v�f
		VEC2			m_rotationCenter { 0, 0 };	//��]���̒��S���W
//		INT				m_nDegree { 0 };			//�p�x
		float			m_radian { 0 };				//�p�x[rad]

	public:
		GameMatrix();
		GameMatrix ( const GameMatrix& rhs );	//�����\
		~GameMatrix(){}

		//�ϊ��s��̍쐬
		void Move();

		//�ϊ��s��̎擾
//		D3DXMATRIX* GetpMatrix() { return & m_matrix; }
//		const D3DXMATRIX* GetcpMatrix() const { return & m_matrix; }

		//�l�̐ݒ�
		VEC2 GetPos() const			{ return m_vecPos; }
		void SetPos ( VEC2 vecPos )	{ m_vecPos = vecPos; }
		void SetPos ( float x, float y )	{ m_vecPos.x = x; m_vecPos.y = y; }
		void SetPosX ( float x )			{ m_vecPos.x = x; }
		void SetPosY ( float y )			{ m_vecPos.y = y; }
		void AddPos ( VEC2 vecPos )	{ m_vecPos += vecPos; }
		void AddPos ( float x, float y )	{ m_vecPos.x += x; m_vecPos.y += y; }
		void AddPosX ( float x )			{ m_vecPos.x += x; }
		void AddPosY ( float y )			{ m_vecPos.y += y; }

		VEC2 GetScaling() const			{ return m_scaling; }
		void SetScaling ( VEC2 vec )		{ m_scaling = vec; }
		void SetScaling ( float x, float y )	{ m_scaling.x = x; m_scaling.y = y; }

		void SetScalingRotation ( float f )			{ m_scalingRotation = f; }
		void SetScalingCenter ( VEC2 vec )	{ m_scalingCenter = vec; }
		void SetRotationCenter ( VEC2 vec )	{ m_rotationCenter = vec; }
//		void SetDegree ( int n )					{ m_nDegree = n; }
		void SetRadian ( float f )					{ m_radian = f; }
	};


}	//namespace GAME

