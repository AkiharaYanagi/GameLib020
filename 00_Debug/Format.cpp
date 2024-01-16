//=================================================================================================
//
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Format.h"

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	TOSS Format::m_toss;

	UP_TSTR Format::GetFormatStr ( LPCTSTR format, ... )
	{
		va_list args;	//�ϒ����X�g
		va_start ( args, format );	//������̐擪�|�C���^���Z�b�g
		UP_TSTR out = Printf_Args ( format, args );
		va_end ( args );	//�ϒ����X�g�̉��

		return std::move ( out );
	}

	UP_TSTR Format::Printf_Args ( LPCTSTR format, va_list args )
	{
		//Unicode�i���C�h�����j�Ή��@_vsc w printf() / �}���`�o�C�g�����Ή� _vsc printf()
		int size = _vsctprintf ( format, args ) + 1;		//'\0'���Ō�ɂ����T�C�Y�𓾂�
		UP_TSTR buf = std::make_unique < TCHAR[] > ( size );		//�o�b�t�@���m��
		//Unicode�i���C�h�����j�Ή��@vs w printf_s() / �}���`�o�C�g�����Ή� vs printf_s()
		_vstprintf_s ( buf.get (), size, format, args );	//�o�b�t�@�ɏ�������
		return std::move ( buf );
	}

}	//namespace GAME

