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
#include <map>
#include <memory>
#include <fstream>

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
#if 0
	typedef struct D3DXVECTOR2
	{
#ifdef __cplusplus
	public:
		D3DXVECTOR2() {};
		D3DXVECTOR2( CONST FLOAT * );
		D3DXVECTOR2( CONST D3DXFLOAT16 * );
		D3DXVECTOR2( FLOAT x, FLOAT y );

		// casting
		operator FLOAT* ();
		operator CONST FLOAT* () const;

		// assignment operators
		D3DXVECTOR2& operator += ( CONST D3DXVECTOR2& );
		D3DXVECTOR2& operator -= ( CONST D3DXVECTOR2& );
		D3DXVECTOR2& operator *= ( FLOAT );
		D3DXVECTOR2& operator /= ( FLOAT );

		// unary operators
		D3DXVECTOR2 operator + () const;
		D3DXVECTOR2 operator - () const;

		// binary operators
		D3DXVECTOR2 operator + ( CONST D3DXVECTOR2& ) const;
		D3DXVECTOR2 operator - ( CONST D3DXVECTOR2& ) const;
		D3DXVECTOR2 operator * ( FLOAT ) const;
		D3DXVECTOR2 operator / ( FLOAT ) const;

		friend D3DXVECTOR2 operator * ( FLOAT, CONST D3DXVECTOR2& );

		BOOL operator == ( CONST D3DXVECTOR2& ) const;
		BOOL operator != ( CONST D3DXVECTOR2& ) const;


	public:
#endif //__cplusplus
		FLOAT x, y;
	} D3DXVECTOR2, *LPD3DXVECTOR2;

#endif // 0

	struct VEC2
	{
		float x { 0 };	float y { 0 };
	public:
		VEC2 ();
		VEC2 ( const VEC2& rhs );
		VEC2 ( float x, float y );
		~VEC2 ();

		VEC2 operator += ( const VEC2 & rhs );
		VEC2 operator -= ( const VEC2 & rhs );
		VEC2 operator *= ( float f ) const;
		VEC2 operator /= ( float f ) const;

		VEC2 operator + () const;
		VEC2 operator - () const;

		VEC2 operator + ( const VEC2& rhs ) const;
		VEC2 operator - ( const VEC2& rhs ) const;
		VEC2 operator * ( float f ) const;
		VEC2 operator / ( float f ) const;

		bool operator == ( const VEC2& rhs ) const;
		bool operator != ( const VEC2& rhs ) const;

	};
	using P_VEC2 = std::shared_ptr < VEC2 >;
	using V_VEC2 = std::vector < VEC2 >;
	using L_VEC2 = std::list < VEC2 >;

	//------------------------------------
	struct VEC3
	{
		float x { 0 };	float y { 0 }; float z { 0 };
	public:
		VEC3 ();
		VEC3 ( const VEC3& rhs );
		VEC3 ( float x, float y, float z );
		~VEC3 ();

		VEC3 operator += ( const VEC3& rhs );
		VEC3 operator -= ( const VEC3& rhs );
		VEC3 operator *= ( float f ) const;
		VEC3 operator /= ( float f ) const;

		VEC3 operator + () const;
		VEC3 operator - () const;

		VEC3 operator + ( const VEC3& rhs ) const;
		VEC3 operator - ( const VEC3& rhs ) const;
		VEC3 operator * ( float f ) const;
		VEC3 operator / ( float f ) const;

		bool operator == ( const VEC3& rhs ) const;
		bool operator != ( const VEC3& rhs ) const;

	};
	using P_VEC3 = std::shared_ptr < VEC3 >;
	using V_VEC3 = std::vector < VEC3 >;
	using L_VEC3 = std::list < VEC3 >;

	//-------------------------------------------------------------------------------------------------
	//	�F
	//-------------------------------------------------------------------------------------------------
#if 0
	typedef struct D3DXCOLOR
	{
#ifdef __cplusplus
	public:
		D3DXCOLOR() {}
		D3DXCOLOR( DWORD argb );
		D3DXCOLOR( CONST FLOAT * );
		D3DXCOLOR( CONST D3DXFLOAT16 * );
		D3DXCOLOR( CONST D3DCOLORVALUE& );
		D3DXCOLOR( FLOAT r, FLOAT g, FLOAT b, FLOAT a );

		// casting
		operator DWORD () const;

		operator FLOAT* ();
		operator CONST FLOAT* () const;

		operator D3DCOLORVALUE* ();
		operator CONST D3DCOLORVALUE* () const;

		operator D3DCOLORVALUE& ();
		operator CONST D3DCOLORVALUE& () const;

		// assignment operators
		D3DXCOLOR& operator += ( CONST D3DXCOLOR& );
		D3DXCOLOR& operator -= ( CONST D3DXCOLOR& );
		D3DXCOLOR& operator *= ( FLOAT );
		D3DXCOLOR& operator /= ( FLOAT );

		// unary operators
		D3DXCOLOR operator + () const;
		D3DXCOLOR operator - () const;

		// binary operators
		D3DXCOLOR operator + ( CONST D3DXCOLOR& ) const;
		D3DXCOLOR operator - ( CONST D3DXCOLOR& ) const;
		D3DXCOLOR operator * ( FLOAT ) const;
		D3DXCOLOR operator / ( FLOAT ) const;

		friend D3DXCOLOR operator * ( FLOAT, CONST D3DXCOLOR& );

		BOOL operator == ( CONST D3DXCOLOR& ) const;
		BOOL operator != ( CONST D3DXCOLOR& ) const;

#endif //__cplusplus
		FLOAT r, g, b, a;
	} D3DXCOLOR, *LPD3DXCOLOR;
#endif // 0

	struct _CLR
	{
	public:
		_CLR ();
		_CLR ( const _CLR& rhs );
		_CLR ( float r, float g, float b, float a );
		_CLR ( UINT32 argb ); 
		~_CLR ();

		_CLR& operator += ( const _CLR& rhs );
		_CLR& operator -= ( const _CLR& rhs );
		_CLR& operator *= ( float f );
		_CLR& operator /= ( float f );

		float r, b, g, a;
	};


	//-------------------------------------------------------------------------------------------------
	// unsigned int
	//-------------------------------------------------------------------------------------------------
	typedef struct USIZE
	{
	public:
		USIZE () { w = 0; h = 0; }
		USIZE ( UINT w0, UINT h0 ) { w = w0; h = h0; }
		UINT32 w;
		UINT32 h;
	} USIZE;

	using V_UINT = std::vector < UINT32 >;

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

