//=================================================================================================
//
// �Q�[����ʂւ̃f�o�b�O�e�L�X�g�\��
//		�Q�[����ʂւ̒��_��p�����e�L�X�g�\��
//		DebugTextNum = 15�܂ł̃C���f�b�N�X���w��
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Define.h"
#include "02_GameGraphic.h"


//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME 
{

	constexpr size_t DBGOUT_WND_N = 10;		//�\���s��


	class DebugOutGameWindow;
	using DBGO_WND = DebugOutGameWindow;
	using P_DBG_WND = std::unique_ptr < DBGO_WND >;


	// �Q�[����ʂւ̃f�o�b�O�e�L�X�g�\��
	class DebugOutGameWindow
	{
	//--------------------------------------------------
	//�V���O���g���p�^�[��
	private:
		static P_DBG_WND	m_inst;
		DebugOutGameWindow ();
		DebugOutGameWindow ( const DBGO_WND & rhs ) = delete;
	public:
		~DebugOutGameWindow ();
		static void Create() { if ( ! m_inst ) { m_inst = P_DBG_WND ( new DBGO_WND () ); } }
		static P_DBG_WND & Inst() { return m_inst; }
	//--------------------------------------------------

	private:
		s3d::Array < P_GrpStr >		ma_str { DBGOUT_WND_N };

	public:
		void Load ();
		void Draw ();

		void DebugOutf ( uint32 index, s3d::String str );


		void On ();
		void Off ();

		//====================================================
		//��{���
	private:
		//Base_DebugOut		m_frame;
		P_GrpStr		m_frame;

	public:
		//�Œ�\�� : �ғ�����[F]
		void DebugOutWnd_Frame ( UINT frame );
#if 0

	private:

	public:
		//�萔
		enum Const_DebugOutGameWindow
		{
			DebugTextNum = 15,
			DebugVertexNum = 32,
		};
	private:
		//�f�o�b�O�\���z��
		TX			m_texture[DebugTextNum];	//�e�N�X�`��
		Vx_Rect		m_vertex[DebugTextNum];		//���_�����I�u�W�F�N�g
		tstring		m_tstr[DebugTextNum];		//������

		//�f�o�b�O�p�Œ�\��
		ConstDebugOut_ASCII		m_frame;
		ConstDebugOut_ASCII		m_FPS;
		ConstDebugOut_ASCII		m_moveTime;
		ConstDebugOut_ASCII		m_drawTime;
		ConstDebugOut_ASCII		m_sleepTime;

	public:
		void Load ();
		void Rele ();
		void Reset ( D3DDEV d3dDevice );	//�Đݒ�
		void DrawVertex ();		//���_�ɂ��`��


		//-----------------------------------------------------

		//�\��������w��
		void SetStr ( UINT index, LPCTSTR lpctstr );
		void SetStr ( UINT index, tstring& tstr );
		void SetStr ( UINT index, UP_TSTR pstr );

		//�ʒu�w��
		void SetPos ( UINT index, float x, float y ) { m_vertex[index].SetPos ( x, y ); }

		//��ʂɃe�L�X�g�`�悷�镶����t�H�[�}�b�g��ݒ�
		void DebugOutf ( UINT index, LPCTSTR format, ... );

		//-----------------------------------------------------
		//�Œ�\�� : �ғ�����[F]
		void DebugOutWnd_Frame ( UINT frame );
		//�Œ�\�� : FPS
		void DebugOutWnd_FPS ( UINT FPS );
		//�Œ�\�� : �x������[ms]
		void DebugOutWnd_SleepTime ( float sleepTile );
		//�Œ�\�� : ���쎞��[ms]
		void DebugOutWnd_MoveTime ( float moveTime );
		//�Œ�\�� : �`�掞��[ms]
		void DebugOutWnd_DrawTime ( float drawTime );

		//-----------------------------------------------------
		//��\��
//		void Off ();

		void Off ();
		void On ();

	private:
		void DebugOutWnd ( UP_TSTR up_tstr, VP_VxRct& vpVpRct );
#endif // 0

	};


//�V���O���g���A�N�Z�X�p
#define DBGOUT_WND		DBGO_WND::Inst
#define DBGOUT_WND_F	DBGO_WND::Inst()->DebugOutf
#define DBGOUT_WND_OFF	DBGO_WND::Inst()->Off
#define DBGOUT_WND_ON	DBGO_WND::Inst()->On



}	//namespace GAME


