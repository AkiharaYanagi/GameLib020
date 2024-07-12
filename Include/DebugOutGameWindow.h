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
#if 0
#include "DebugLibrary.h"
#include "Dx3D.h"
#include "DxVertex.h"
#include "GameTexture.h"
#endif // 0


//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME 
{
#if 0
	//=====================================================
	//�Œ�\�� ASCII�����ʃe�N�X�`��
	class ConstDebugOut_ASCII
	{
		bool		m_valid;

		VEC2		m_pos;		//��ʒu
		VP_VxRct	mvp_vx;		//���_�W��(��`)
		static const UINT	SIZE;
		tstring		m_tstr;		//�\��������
		std::string		m_str;		//char�`���ŕۑ�

	public:
		ConstDebugOut_ASCII ();
		ConstDebugOut_ASCII ( const ConstDebugOut_ASCII & rhs ) = delete;
		~ConstDebugOut_ASCII ();

		void Load ();
		void Rele ();
		void Reset ();
		void Move ();
		void Draw ();

		void SetPos ( VEC2 v );
		void SetStr ( UP_TSTR upctstr );
		void SetStr ( LPCTSTR lpctstr );
		void SetValid ( bool b ) { m_valid = b; }

		void ToggleValid () { m_valid = ! m_valid; }
		void Off () { m_valid = F; }
		void On () { m_valid = T; }
	};
	//=====================================================
#endif // 0

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

		//Siv3D ������`��@�t�H���g
		s3d::Font		m_font;

		s3d::String		m_str { U"Test" };


		s3d::Array < Font >		ma_font;


	public:

		void Draw ();


		void DebugOutf ( s3d::String str );

		void AddDbgOutWndf ( s3d::String str );


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
		void Move ();
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


