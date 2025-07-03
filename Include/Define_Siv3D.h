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
	//�e�N�X�`���@�G�C���A�X
	using P_Tx = std::shared_ptr < s3d::Texture >;
	using AP_Tx = s3d::Array < P_Tx >;
	using PAP_Tx = std::shared_ptr < AP_Tx >;

	//�|���S�� �G�C���A�X
	using P_Plgn = std::shared_ptr < s3d::Polygon >;

	//������ �G�C���A�X
	using CSIVSTR = const s3d::String;

	//�I�[�f�B�I �G�C���A�X
	using P_Adi = std::shared_ptr < s3d::Audio >;
	using AP_Adi = s3d::Array < P_Adi >;
	using PAP_Adi = std::shared_ptr < AP_Adi >;


	//���[�e�B���e�B
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

	//�z��@�G�C���A�X
	using A_UINT32 = s3d::Array < uint32 >;
	using A_INT32 = s3d::Array < int32 >;

	using UPA_UINT32 = std::unique_ptr < A_UINT32 >;

	//������@�G�C���A�X
	using Prp_Str = Property < s3d::String >;


}	//namespace GAME

