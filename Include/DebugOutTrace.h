//=================================================================================================
//
// �f�o�b�O�o�� IDE
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

	//IDE�f�o�b�O�E�B���h�E�o�� [ TRACE() ]
	class DebugOutTrace
	{
		DebugOutTrace () = delete;	//static�N���X�Ƃ��Ď��̉��֎~

	public:

		//������t�H�[�}�b�g��\��(TCHAR)
		static void DebugOutf ( LPCTSTR format, ... );

		//������t�H�[�}�b�g��\��(char*)
		static void DebugOutchf ( LPCSTR format, ... );

		//GetLastError()�����WIN32API�̃G���[���b�Z�[�W�\��
		//�����F�ďo����__FILE__, __LINE__���w��
		static void OutputLastError ( LPCSTR file, DWORD line );
	};

//�V���O���g���A�N�Z�X�p
#define TRACE_F		DebugOutTrace::DebugOutf
#define TRACE_CHF	DebugOutTrace::DebugOutchf


}	//namespace GAME

