//=================================================================================================
//
// �t�@�C���A�[�J�C�o
//		Debug���[�h����Archive�f�B���N�g���ɂ���t�@�C����archive.dat�ɏ����o���A
//		Debug���[�h, Release���[�h����archive.dat����t�@�C���|�C���^��ǂݍ���
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "Define.h"
#include "DebugOutTrace.h"


//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME 
{
	//========================================================
	//	���A�[�J�C�u�o�C�i���t�@�C���@�w�b�_�t�H�[�}�b�g
	//	DWORD				fileNum		//�t�@�C���̌�
	//	ARCHIVE_HEADER[]	...			//fileNum��������
	//	BYTE				...			//�o�C�i���f�[�^
	//========================================================

	//�t�@�C�����z�u
	//map�ɂ�����[���O]���L�[�ɂŎ擾�������f�[�^
	struct ARCHIVE_ALIGN
	{
		DWORD		offset;		//(�w�b�_������)�f�[�^�J�n�ʒu����̃|�C���^�ʒu�I�t�Z�b�g
		DWORD		fileSize;	//�t�@�C���T�C�Y
	};

	//�����p(�傫�����萔��TCHAR[]��p����)
	struct ARCHIVE_HEADER
	{
		TCHAR			fileName[ MAX_PATH ];	//�t�@�C����
		ARCHIVE_ALIGN	align;					//�z�u
	};
	using ACV_H = ARCHIVE_HEADER;

	//�����p(�����񑀍삪���₷��tstring��p����)
	struct ARCHIVE_HEADER_SEARCH
	{
		tstring			fileName;	//�t�@�C����
		ARCHIVE_ALIGN	align;		//�z�u
	};
	using ACV_H_SRC = ARCHIVE_HEADER_SEARCH;

	//�ߒl�p
	struct ARCHIVE_FILE_USE
	{
		LPCVOID		filePointer;	//�t�@�C���|�C���^
		DWORD		fileSize;		//�t�@�C���T�C�Y
	};
	using ACV_FL_USE = ARCHIVE_FILE_USE;

	//map�^�錾
	using ARCHIVE_MAP = std::map < tstring, ARCHIVE_ALIGN >;


	//�A�[�J�C�o�N���X
	class Archiver
	{
	//--------------------------------------------------
	//�V���O���g���p�^�[��
	private:
		using P_Archiver = std::unique_ptr < Archiver >;
		static P_Archiver	m_inst;
		Archiver ();
		Archiver ( const Archiver & rhs ) = delete;
	public:
		~Archiver ();
		static void Create () { if ( ! m_inst ) { m_inst = P_Archiver ( new Archiver () ); } }
		static P_Archiver & Inst() { return m_inst; }	//�C���X�^���X�擾
	//--------------------------------------------------

	private:
		HANDLE					m_hMap;		//�f�[�^�̃t�@�C���}�b�s���O�n���h��
		LPVOID					m_pFile;	//�t�@�C���}�b�s���O�̊J�n�A�h���X

		ARCHIVE_MAP				m_map;		//���f�[�^�����p�}�b�v

		//Release���[�h�ł͋L�^����Ȃ�
		//�A�[�J�C�u�t�@�C���̃f�[�^�w�b�_���Q�Ƃ���
		std::vector < ACV_H_SRC >	m_vFilename;	//�Ώۃf�[�^�t�@�C�������X�g

		//�t�@�C���񋓂̂Ƃ��AFind()�ɂ����ăf�B���N�g���ōċA����̂ŃJ�E���g�͊O���ɋL�^����
		DWORD					m_current_offset;	//���݃I�t�Z�b�g�ʒu
		
		static const TCHAR		ARCHIVE_FILE_NAME[];
		static const TCHAR		ARCHIVE_DIR_NAME[];
		static const TCHAR		SEARCH_CONDITION[];
		static const TCHAR		MAP_NAME[];

	public:
		void Make ();		//�A�[�J�C�u�t�@�C���쐬
		void Open ();		//�A�[�J�C�u�t�@�C���Ǎ�
		void Close ();		//�A�[�J�C�u�t�@�C����

		//���̃t�@�C��������A�[�J�C�u���̃t�@�C���|�C���^�𓾂�
		ACV_FL_USE GetFilePointer ( LPCTSTR fileName );

	private:
		//�t�@�C�������̍ċA
		void Find ( LPCTSTR path );
	};

	#define ACVR	Archiver::Inst


}	//namespace GAME

