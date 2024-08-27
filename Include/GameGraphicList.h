//=================================================================================================
//
// ��GameGraphicList
//		�O���t�B�b�N�\���̑O���S�̂œ��ꂷ��
//		Z�l��p���ă\�[�g����GameGpraphic�̃��X�g�̃|�C���^��ێ�����
//		�I�u�W�F�N�g�̏��L�𒴂��ēo�^����O���t�B�b�N�̃��X�g
//		�y�V���O���g���z��p���ăO���[�o������A�N�Z�X����
//		GameSystem�����̂������A�e�ʃQ�[���^�X�N��o�^����
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "GameTask.h"
#include "GameGraphicCore.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	using LP_GrpCr = std::list < P_GrpCr >;
	using UPLP_GrpCr = std::unique_ptr < LP_GrpCr >;
	using UP_RndrTx = std::unique_ptr < s3d::RenderTexture >;


	class GameGraphicList
	{
	//---------------------------------------------------------------------
	//�V���O���g���p�^�[��
	private:
		using _GrpLst = GameGraphicList;
		using _P_GrpLst = std::unique_ptr < _GrpLst >;
		static _P_GrpLst	m_inst;		//�V���O���g���C���X�^���X
		GameGraphicList ();		//private �R���X�g���N�^�Œʏ�̎��̉��͋֎~
	public:
		~GameGraphicList ();	//�f�X�g���N�^��std::unique_ptr�̂���public
		static void Create() { if ( ! m_inst ) { m_inst = _P_GrpLst ( new _GrpLst () ); } }
		static _P_GrpLst & Inst () { return m_inst; }	//�C���X�^���X�擾
	//---------------------------------------------------------------------
	
	private:
		UPLP_GrpCr		mplp_GrpMain;		//�O���t�B�b�N ���C�� ���X�g

		//test
		UP_RndrTx		m_renderTx;			//�����_�[�e�N�X�`��

	public:

		//@info ����̓^�X�N���X�g���ōs��

		//�S����
		void Clear ();

		//�`��
		void Draw ();

		//Z�l�ō~���\�[�g���ꂽ�ʒu�ɑ}��
		//�`��Z�ʒu(��:1.f �` 0.0f:�O) "GameGraphicConst.h"�� Z_BG �ȂǂŒ萔���錾���Ă���
		void InsertByZ ( P_GrpCr pGrpCr );

		//�Ώۃ^�X�N����O
		void Remove ( P_GrpCr p ) { mplp_GrpMain->remove ( p ); }

		//��
		size_t GetNumList () const { return mplp_GrpMain->size (); }


		//�����_�[�e�N�X�`���ڏ�
		UP_RndrTx Handover_RndrTx () { return std::move ( m_renderTx ); }
		//�����_�[�e�N�X�`���Ԋ�
		void Refund_RndrTx ( UP_RndrTx&& up ) { m_renderTx = std::move ( up ); }


	private:
		bool m_startMv { F };
		std::unique_ptr < s3d::VideoTexture > mp_vtx;

	public:
		void SetupVtx ( std::unique_ptr < s3d::VideoTexture > p_vtx )
		{
			mp_vtx = std::move ( p_vtx );
		}
		void StartVtx () { m_startMv = T; }
	};

	using GrpLst = GameGraphicList;
	using UP_GrpLst = std::unique_ptr < GrpLst >;


#define		GRPLST_CREATE	GrpLst::Create
#define		GRPLST_DRAW		GrpLst::Inst()->Draw
#define		GRPLST_INSERT	GrpLst::Inst()->InsertByZ
#define		GRPLST_REMOVE	GrpLst::Inst()->Remove
#define		GRPLST_CLEAR	GrpLst::Inst()->Clear


}	//namespace GAME


