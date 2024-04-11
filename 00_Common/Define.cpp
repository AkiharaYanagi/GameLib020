//=================================================================================================
//
// デファイン 実装
//　		GameLib用共通定義
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
//	インクルードファイル
//-------------------------------------------------------------------------------------------------
#include "Define.h"


//-------------------------------------------------------------------------------------------------
//	宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//-------------------------------------------------------------------------------------------------
	//	位置
	//-------------------------------------------------------------------------------------------------
	VEC2::VEC2 () {};
	VEC2::VEC2 ( const VEC2& rhs ) { x = rhs.x; y = rhs.y; }
	VEC2::VEC2 ( float x, float y ) { this->x = x; this->y = y; }
	VEC2::~VEC2 () {};

	VEC2 VEC2::operator += ( const VEC2 & rhs )
	{
		this->x += rhs.x;
		this->y += rhs.y;
		return *this;
	}

	VEC2 VEC2::operator -= ( const VEC2 & rhs )
	{
		this->x -= rhs.x; this->y -= rhs.y; return *this;
	}

	VEC2 VEC2::operator *= ( float f ) const
	{
		return VEC2 ( this->x * f, this->y * f );
	}
	VEC2 VEC2::operator /= ( float f ) const
	{
		return VEC2 ( this->x / f, this->y / f );
	}

	VEC2 VEC2::operator + () const { return *this; }
	VEC2 VEC2::operator - () const
	{
		return VEC2 ( -this->x, -this->y );
	}

	VEC2 VEC2::operator + ( const VEC2 & rhs ) const
	{
		return VEC2 ( this->x + rhs.x, this->y + rhs.y );
	}
	VEC2 VEC2::operator - ( const VEC2 & rhs ) const
	{
		return VEC2 ( this->x - rhs.x, this->y - rhs.y );
	}
	VEC2 VEC2::operator * ( float f ) const
	{
		return VEC2 ( this->x * f, this->y * f );
	}
	VEC2 VEC2::operator / ( float f ) const
	{
		return VEC2 ( this->x / f, this->y / f );
	}

	bool VEC2::operator == ( const VEC2& rhs ) const
	{
		return this->x == rhs.x && this->y == rhs.y;
	}
	bool VEC2::operator != ( const VEC2& rhs ) const
	{
		return this->x != rhs.x || this->y != rhs.y;
	}


	//------------------------------------
	VEC3::VEC3 () {};
	VEC3::VEC3 ( const VEC3& rhs ) { this->x = rhs.x; this->y = rhs.y; this->z = rhs.z; }
	VEC3::VEC3 ( float x, float y, float z ) { this->x = x; this->y = y; this->z = z; }
	VEC3::~VEC3 () {};
	
	VEC3 VEC3::operator += ( const VEC3& rhs ) { this->x += rhs.x; this->y += rhs.y; this->z += rhs.z; return *this; }
	VEC3 VEC3::operator -= ( const VEC3& rhs ) { this->x -= rhs.x; this->y -= rhs.y; this->z += rhs.z; return *this; }
	VEC3 VEC3::operator *= ( float f ) const { return VEC3 ( this->x * f, this->y * f, this->z * f ); }
	VEC3 VEC3::operator /= ( float f ) const { return VEC3 ( this->x / f, this->y / f, this->z / z ); }

	VEC3 VEC3::operator + () const { return *this; }
	VEC3 VEC3::operator - () const { return VEC3 ( -this->x, -this->y, -this->z ); }

	VEC3 VEC3::operator + ( const VEC3 & rhs ) const { return VEC3 ( this->x + rhs.x, this->y + rhs.y, this->z + rhs.z ); }
	VEC3 VEC3::operator - ( const VEC3 & rhs ) const { return VEC3 ( this->x - rhs.x, this->y - rhs.y, this->z - rhs.z ); }
	VEC3 VEC3::operator * ( float f ) const { return VEC3 ( this->x * f, this->y * f, this->z * f ); }
	VEC3 VEC3::operator / ( float f ) const { return VEC3 ( this->x / f, this->y / f, this->z / f ); }

	bool VEC3::operator == ( const VEC3& rhs ) const { return this->x == rhs.x && this->y == rhs.y && this->z == rhs.z; }
	bool VEC3::operator != ( const VEC3& rhs ) const { return this->x != rhs.x || this->y != rhs.y || this->z != rhs.z; }


	//-------------------------------------------------------------------------------------------------
	//	色
	//-------------------------------------------------------------------------------------------------
	_CLR::_CLR () {}
	_CLR::_CLR ( const _CLR& rhs )
	{
		this->r = rhs.r;
		this->g = rhs.g;
		this->b = rhs.b;
		this->a = rhs.a;
	}
	_CLR::_CLR ( float r, float g, float b, float a )
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}
	_CLR::_CLR ( UINT32 argb )
	{
		this->a = (float)((argb & 0xff000000) >> 24) / 255.f;
		this->r = (float)((argb & 0x00ff0000) >> 16) / 255.f;
		this->g = (float)((argb & 0x0000ff00) >> 8)	 / 255.f;
		this->b = (float)((argb & 0x000000ff) )		 / 255.f;
	}
	_CLR::~_CLR () {}

	_CLR& _CLR::operator += ( const _CLR& rhs )
	{
		this->r += rhs.r; 
		this->g += rhs.g; 
		this->b += rhs.b; 
		this->a += rhs.a; 
		return *this;
	}
	_CLR& _CLR::operator -= ( const _CLR& rhs )
	{
		this->r -= rhs.r; 
		this->g -= rhs.g; 
		this->b -= rhs.b; 
		this->a -= rhs.a; 
		return *this;
	}
	_CLR& _CLR::operator *= ( float f )
	{
		this->r *= f; 
		this->g *= f; 
		this->b *= f; 
		this->a *= f; 
		return *this;
	}
	_CLR& _CLR::operator /= ( float f )
	{
		this->r /= f; 
		this->g /= f; 
		this->b /= f; 
		this->a /= f; 
		return *this;
	}


}	//namespace GAME

