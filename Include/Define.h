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
		VEC2 () {};
		VEC2 ( const VEC2& rhs ) { x = rhs.x; y = rhs.y; }
		VEC2 ( float x, float y ) { this->x = x; this->y = y; }
		~VEC2 () {};

		VEC2 operator += ( const VEC2 & rhs ) { this->x + rhs.x; this->y + rhs.y; return *this; }
		VEC2 operator -= ( const VEC2 & rhs ) { this->x - rhs.x; this->y - rhs.y; return *this; }
		VEC2 operator *= ( float f ) const { return VEC2 ( this->x * f, this->y * f ); }
		VEC2 operator /= ( float f ) const { return VEC2 ( this->x / f, this->y / f ); }

		VEC2 operator + () const { return *this; }
		VEC2 operator - () const { return VEC2 ( -this->x, -this->y ); }

		VEC2 operator + ( const VEC2 & rhs ) const { return VEC2 ( this->x + rhs.x, this->y + rhs.y ); }
		VEC2 operator - ( const VEC2 & rhs ) const { return VEC2 ( this->x - rhs.x, this->y - rhs.y ); }
		VEC2 operator * ( float f ) const { return VEC2 ( this->x * f, this->y * f ); }
		VEC2 operator / ( float f ) const { return VEC2 ( this->x / f, this->y / f ); }

		bool operator == ( const VEC2& rhs ) const { return this->x == rhs.x && this->y == rhs.y; }
		bool operator != ( const VEC2& rhs ) const { return this->x != rhs.x || this->y != rhs.y; }

	};
	using P_VEC2 = std::shared_ptr < VEC2 >;
	using V_VEC2 = std::vector < VEC2 >;
	using L_VEC2 = std::list < VEC2 >;

	//------------------------------------
	struct VEC3
	{
		float x { 0 };	float y { 0 }; float z { 0 };
	public:
		VEC3 () {};
		VEC3 ( const VEC3& rhs ) { this->x = rhs.x; this->y = rhs.y; this->z = rhs.z; }
		VEC3 ( float x, float y, float z ) { this->x = x; this->y = y; this->z = z; }
		~VEC3 () {};

		VEC3 operator += ( const VEC3& rhs ) { this->x + rhs.x; this->y + rhs.y; this->z + rhs.z; return *this; }
		VEC3 operator -= ( const VEC3& rhs ) { this->x - rhs.x; this->y - rhs.y; this->z + rhs.z; return *this; }
		VEC3 operator *= ( float f ) const { return VEC3 ( this->x * f, this->y * f, this->z * f ); }
		VEC3 operator /= ( float f ) const { return VEC3 ( this->x / f, this->y / f, this->z / z ); }

		VEC3 operator + () const { return *this; }
		VEC3 operator - () const { return VEC3 ( -this->x, -this->y, -this->z ); }

		VEC3 operator + ( const VEC3 & rhs ) const { return VEC3 ( this->x + rhs.x, this->y + rhs.y, this->z + rhs.z ); }
		VEC3 operator - ( const VEC3 & rhs ) const { return VEC3 ( this->x - rhs.x, this->y - rhs.y, this->z - rhs.z ); }
		VEC3 operator * ( float f ) const { return VEC3 ( this->x * f, this->y * f, this->z * f ); }
		VEC3 operator / ( float f ) const { return VEC3 ( this->x / f, this->y / f, this->z / f ); }

		bool operator == ( const VEC3& rhs ) const { return this->x == rhs.x && this->y == rhs.y && this->z == rhs.z; }
		bool operator != ( const VEC3& rhs ) const { return this->x != rhs.x || this->y != rhs.y || this->z != rhs.z; }

	};
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

