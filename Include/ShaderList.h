//=================================================================================================
//
// �� ShaderList
//		�V�F�[�_��p�����O���t�B�b�N���X�g
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "GameTask.h"
#include "GameGraphic.h"

//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	using RndrTx = s3d::RenderTexture;
	using UP_RndrTx = std::unique_ptr < RndrTx >;



	class ShaderList
	{
	//---------------------------------------------------------------------
	//�V���O���g���p�^�[��
	private:
		using _SdrLst = ShaderList;
		using UP_SdrLst = std::unique_ptr < _SdrLst >;
		static UP_SdrLst	m_inst;		//�V���O���g���C���X�^���X
		ShaderList ();		//private �R���X�g���N�^�Œʏ�̎��̉��͋֎~
	public:
		~ShaderList ();		//�f�X�g���N�^��std::unique_ptr�̂���public
		static void Create() { if ( ! m_inst ) { m_inst = UP_SdrLst ( new _SdrLst () ); } }
		static UP_SdrLst & Inst () { return m_inst; }	//�C���X�^���X�擾
	//---------------------------------------------------------------------
	
	private:
		UPAP_Grp		mpap_GrpMain;		//�O���t�B�b�N ���C�� ���X�g

		//�s�N�Z���V�F�[�_
		PixelShader		m_ps;
		PixelShader		m_ps_screen;

		s3d::Texture	m_emoji;
		s3d::Texture	m_windmill;

		RndrTx			m_rndrTx { 1280, 960 };		//�ʒu���킹�p�����_�[�e�N�X�`��

	public:

		void Load ();
		void Draw ();
		void Clear ();

		void InsertByZ ( P_Grp	pGrp );

		//�Ώۃ^�X�N����O
		void Remove ( P_Grp p ) { mpap_GrpMain->remove ( p ); }
	};

	using SdrLst = ShaderList;
	using UP_SrdLst = std::unique_ptr < SdrLst >;


#define		SDRLST_CREATE	SdrLst::Create
#define		SDRLST_LOAD		SdrLst::Inst()->Load
#define		SDRLST_DRAW		SdrLst::Inst()->Draw
#define		SDRLST_INSERT	SdrLst::Inst()->InsertByZ
#define		SDRLST_REMOVE	SdrLst::Inst()->Remove
#define		SDRLST_CLEAR	SdrLst::Inst()->Clear


}	//namespace GAME


