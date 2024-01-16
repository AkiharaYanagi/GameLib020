//=================================================================================================
//
//	������t�H�[�}�b�g
//		�ϐ���p���Ȃ��X�^�e�B�b�N�ȃN���X�łǂ�����ł�������
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���@�C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Define.h"


//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class Format final
	{
	public:
		Format () = delete;	//static�N���X�Ƃ��Ď��̉��֎~
		~Format () = delete;

	private:
		static TOSS		m_toss;

		//�ċA���[
		static void _f ( LPCTSTR tstr )
		{
			m_toss << *(tstr++);
			return;
		}

		//�ċA�p
		template < typename First, typename... Rest >
		static void _f ( LPCTSTR tstr, const First & first, const Rest&... rest )
		{
			while ( *tstr )
			{
				//�t�H�[�}�b�g�w��q����
				if ( _T ( '%' ) == (*tstr) && _T ( '%' ) != *(tstr) )
				{
					m_toss << first;

					//���݂���Ύ����ċA
					_f ( *tstr ? ++tstr : tstr, rest... );
					return;
				}
			}
			return;
		}

	public:
		
		template < typename... Args >
		static void Addf ( LPCTSTR tstr, const Args&... args )
		{
			_f ( tstr, args... );
		}
		static const TOSS & RefToss () { return m_toss; }

		//�t�H�[�}�b�g���擾
		template < typename... Args >
		static LPCTSTR f ( LPCTSTR tstr, const Args&... args )
		{
			m_toss.clear ();
			_f ( tstr, args... );
			return m_toss.str().c_str ();
		}

		//---------------------------------------------------------------
		//va_list �ψ���
		static UP_TSTR GetFormatStr ( LPCTSTR format, ... );
		
		static UP_TSTR Printf_Args ( LPCTSTR format, va_list args );
	};


}	//namespace GAME

