//=================================================================================================
//
// �f�t�@�C���w�b�_
//�@		GameLib�p���ʒ�`
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//-------------------------------------------------------------------------------------------------
#include <WinSock2.h>	//<windows.h>�����O�ɐ錾����
#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")
#include <Windows.h>
#include <iostream>
#include <tchar.h>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <memory>

#define WIN32_LEAN_AND_MEAN		// Windows �w�b�_�[����قƂ�ǎg�p����Ă��Ȃ����������O����


//=============================================
//
//using namespace std;
//
//@info	using namespace std; ���~�߁A	std::�錾��t����
//	��ނ𓾂�using�Ƃ��� �w�b�_.h �ł͂Ȃ� �\�[�X.cpp�Ő錾����
//
//=============================================

//-------------------------------------------------------------------------------------------------
//	�錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//-------------------------------------------------------------------------------------------------
	//	�ʒu
	//-------------------------------------------------------------------------------------------------
	using VEC2 = D3DXVECTOR2;
	using P_VEC2 = std::shared_ptr < VEC2 >;
	using V_VEC2 = std:: vector < VEC2 >;
	using L_VEC2 = std:: list < VEC2 >;

	using VEC3 = D3DXVECTOR3;
	using P_VEC3 = std::shared_ptr < VEC3 >;
	using V_VEC3 = std::vector < VEC3 >;
	using L_VEC3 = std::list < VEC3 >;

	//-------------------------------------------------------------------------------------------------
	// unsigned int
	//-------------------------------------------------------------------------------------------------
	using UINT = unsigned __int32;
	using UINT64 = unsigned __int64;

	typedef struct USIZE
	{
	public:
		USIZE () { w = 0; h = 0; }
		USIZE ( UINT w0, UINT h0 ) { w = w0; h = h0; }
		UINT w;
		UINT h;
	} USIZE;

	using V_UINT = std::vector < UINT >;

	//-------------------------------------------------------------------------------------------------
	// TCAHR�Ή�
	//-------------------------------------------------------------------------------------------------
	using tstring =			std::basic_string< TCHAR >;
	using tistream =		std::basic_istream< TCHAR >;
	using tostream =		std::basic_ostream< TCHAR >;
	using tfstream =		std::basic_fstream< TCHAR >;
	using tifstream =		std::basic_ifstream< TCHAR >;
	using tofstream =		std::basic_ofstream< TCHAR >;
	using tistringstream =	std::basic_istringstream< TCHAR >;
	using tostringstream =	std::basic_ostringstream< TCHAR >;

	using V_STR = std::vector < tstring >;
	using P_STR = std::shared_ptr < tstring >;
	using VP_STR = std::vector < P_STR >;
	using PVP_STR = std::shared_ptr < tstring >;


	typedef tostringstream TOSS;
	typedef std::shared_ptr < TOSS > P_TOSS;


	using UP_CTSTR = std::unique_ptr < TCHAR >;
	using UP_TSTR = std::unique_ptr < TCHAR[] >;	//�z��Ƃ��� < TCHAR[] > �Ő錾����


	//-------------------------------------------------------------------------------------------------
	// TRUE, FALSE
	//-------------------------------------------------------------------------------------------------
	constexpr bool T = true;
	constexpr bool F = false;

	//-------------------------------------------------------------------------------------------------
	//	�����ɂ����ϐ�����A�ϐ��������������񃊃e�����Ƃ��ĕԂ�((#)�������񉻉��Z�q)
	//-------------------------------------------------------------------------------------------------
	#define	STR(var) #var


}	//namespace GAME

