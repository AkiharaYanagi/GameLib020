//=================================================================================================
//
// Siv3D ���p�f�t�@�C�� �w�b�_
//�@		GameLib�p���ʒ�`
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
//	�C���N���[�h�t�@�C��
//-------------------------------------------------------------------------------------------------
#include <Siv3D.hpp>
#include "Define.h"


//-------------------------------------------------------------------------------------------------
//	�錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	using P_Tx = std::shared_ptr < s3d::Texture >;
	using AP_Tx = s3d::Array < P_Tx >;
	using PAP_Tx = std::shared_ptr < AP_Tx >;


	class s3d_UTL
	{
	public:
		static s3d::Color DWORD_to_Color ( DWORD clr )
		{
			uint8 a = 0x000000ff & (clr >> 24);
			uint8 r = 0x000000ff & (clr >> 16);
			uint8 g = 0x000000ff & (clr >> 8);
			uint8 b = 0x000000ff & (clr >> 0);
			return Color { r, g, b, a };
		}
		static s3d::ColorF DWORD_to_ColorF ( DWORD clr )
		{
			return ColorF { DWORD_to_Color ( clr ) };
		}

		static VEC2 GetTxCenter ( const s3d::Texture & tx )
		{
			return VEC2 ( tx.size().x * 0.5f, tx.size().y * 0.5f );
		}

		static uint8 ReadUInt8 ( s3d::BinaryReader & br )
		{
			uint8 ret = 0;
			br.read ( ret );
			return ret;
		}
	};


	//�����񃊃e���� U""
	using LPCUSTR = const char32_t *;


}	//namespace GAME

