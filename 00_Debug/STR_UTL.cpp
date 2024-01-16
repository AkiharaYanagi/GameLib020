//=================================================================================================
//
//	�����񃆁[�e�B���e�B
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "STR_UTL.h"

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//������T�C�Y�̎擾
	UINT STR_UTL::Size ( LPCTSTR lpctstr )
	{
		UINT ret = 0;
		TCHAR t = *lpctstr;

		try
		{
			while ( t != '\0' )
			{
				t = *( lpctstr + ( ret ++ ) );
			}
		}
		catch ( ... )
		{
			return 0;
		}

		return ret;
	}


	//�����R�[�h�擾
	UINT STR_UTL::GetCode ( PTCHAR ptch )
	{
#if	_UNICODE

		//UNICODE�̏ꍇ�A�����R�[�h�͒P���Ƀ��C�h������UINT�ϊ�
		return (UINT)*ptch;

#else	//_UNICODE

		UINT code;
		//�}���`�o�C�g�����̏ꍇ�A
		//1�o�C�g�����̃R�[�h��1�o�C�g�ڂ�UINT�ϊ��A
		//2�o�C�g�����̃R�[�h��[�擱�R�[�h]*256 + [�����R�[�h]
		if ( IsDBCSeadByte ( *ptch ) ) { code = (BYTE)ptch [ 0 ] << 8 | (BYTE)ptch [ 1 ]; }
		else { code = ptch [ 0 ]; }
		return code;

#endif	//_UNICODE
	}

	UINT STR_UTL::GetCode ( LPCTCH lpctch )
	{
#if	_UNICODE

		//UNICODE�̏ꍇ�A�����R�[�h�͒P���Ƀ��C�h������UINT�ϊ�
		return (UINT)*lpctch;

#else	//_UNICODE

		UINT code;
		//�}���`�o�C�g�����̏ꍇ�A
		//1�o�C�g�����̃R�[�h��1�o�C�g�ڂ�UINT�ϊ��A
		//2�o�C�g�����̃R�[�h��[�擱�R�[�h]*256 + [�����R�[�h]
		if ( IsDBCSeadByte ( *lpctch ) ) { code = (BYTE)lpctch [ 0 ] << 8 | (BYTE)lpctch [ 1 ]; }
		else { code = lpctch [ 0 ]; }
		return code;

#endif	//_UNICODE
	}

	UINT STR_UTL::GetCode ( char ascii )
	{
#if	_UNICODE
		//UNICODE�̏ꍇ�A�����R�[�h�͒P���Ƀ��C�h������UINT�ϊ�
		return (UINT)ascii;

#else	//_UNICODE

		UINT code;
		//�}���`�o�C�g�����̏ꍇ�A
		//1�o�C�g�����̃R�[�h��1�o�C�g�ڂ�UINT�ϊ��A
		//2�o�C�g�����̃R�[�h��[�擱�R�[�h]*256 + [�����R�[�h]
		if ( IsDBCSeadByte ( *lpctch ) ) { code = (BYTE)lpctch [ 0 ] << 8 | (BYTE)lpctch [ 1 ]; }
		else { code = lpctch [ 0 ]; }
		return code;

#endif	//_UNICODE
	}


	//�e�N�X�`���p
	//2�ׂ̂���⊮ ( 1 �` 65536 )
	LONG STR_UTL::PowerNormalize ( LONG ln )
	{
		const long LMT = 65536;
		long pw = 2;
		while ( pw <= LMT )
		{
			if ( ln <= pw ) { return pw; }
			pw *= 2;
		}
		return 1;	//�͈͊O�͂P
	}


}	//namespace GAME

