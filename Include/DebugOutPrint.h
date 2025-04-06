//=================================================================================================
//
// �f�o�b�O�o�� �R�}���h�v�����v�g Print
//�@		
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//-------------------------------------------------------------------------------------------------
#include "Define.h"


//-------------------------------------------------------------------------------------------------
//	�錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//--------------------------------------------------
	//�V���O���g���p�^�[��
	class DebugOutPrint;
	using DBG_PRNT = DebugOutPrint;
	using P_DBG_PRNT = std::unique_ptr < DBG_PRNT >;
	//--------------------------------------------------


	//IDE�f�o�b�O�E�B���h�E�o�� [ PRINT () ]
	class DebugOutPrint
	{
	//--------------------------------------------------
	//�V���O���g���p�^�[��
	private:
		static P_DBG_PRNT	m_inst;
		DebugOutPrint ();
		DebugOutPrint ( const P_DBG_PRNT & rhs ) = delete;
	public:
		~DebugOutPrint ();
		static void Create() { if ( ! m_inst ) { m_inst = P_DBG_PRNT ( new DBG_PRNT () ); } }
		static P_DBG_PRNT & Inst() { return m_inst; }
	//--------------------------------------------------

	public:
#if 0

		//������t�H�[�}�b�g��\��(TCHAR)
		static void DebugOutf ( LPCTSTR format, ... );

		//������t�H�[�}�b�g��\��(char*)
		static void DebugOutchf ( LPCSTR format, ... );

		//GetLastError()�����WIN32API�̃G���[���b�Z�[�W�\��
		//�����F�ďo����__FILE__, __LINE__���w��
		static void OutputLastError ( LPCSTR file, DWORD line );

#endif // 0


		//Siv3D�Ή��f�o�b�O�o�͕\��
		static void DebugOutf_s3d ( s3d::String str );
		static void DebugOutf_s3d ( s3d::Error err );

	};

//�V���O���g���A�N�Z�X�p
//#define PRINT_F		DebugOutPrint::DebugOutf
//#define PRINT_CHF	DebugOutPrint::DebugOutchf
#define PRINT_F_S	DebugOutPrint::DebugOutf_s3d


}	//namespace GAME

