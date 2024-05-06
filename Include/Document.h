//=================================================================================================
//
// �Q�[���h�L�������g�@�w�b�_�t�@�C��
//		
//		Element�^�O��Attribute�̕�܂ɂ���ċL�q�����xml�͕�̃c���[��f�[�^�\��
//		<Element.name Attribute.name="Attribute.value"></Element.name>
//		
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���@�C���N���[�h
//-------------------------------------------------------------------------------------------------
//#include "DebugLibrary.h"
#include "Define.h"


//-------------------------------------------------------------------------------------------------
// �錾
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//----------------------------------------------------------
	//�A�g���r���[�g
	//	���O�ƒl������
	//----------------------------------------------------------
	class Attribute
	{
		tstring		m_name;
		tstring		m_value;

	public:
		Attribute ( tstring name, tstring value ) :	m_name ( name ), m_value ( value ) {}
		Attribute ( const Attribute& rhs ) = delete;		//�R�s�[�֎~
		~Attribute () = default;

		void Clear () {}
		void Print ()
		{
			tostringstream oss;
			oss << m_name.c_str() << (" = ") << m_value.c_str() << (", ");
			OutputDebugString ( oss.str().c_str() );
		}
		tstring GetName () const { return m_name; }
		tstring GetValue () const { return m_value; }
	};

	typedef std::shared_ptr < Attribute >	P_Attribute;
	typedef std::vector < P_Attribute >		VP_Attribute;
	typedef std::shared_ptr < VP_Attribute >	PVP_Attribute;


	//----------------------------------------------------------
	//�G�������g
	//	�O�ȏ�̃A�g���r���[�g�ƂO�ȏ�̃G�������g������
	//----------------------------------------------------------
	class Element;
	typedef std::shared_ptr < Element >		P_Element;
	typedef std::vector < P_Element >		VP_Element;
	typedef std::shared_ptr < VP_Element >	PVP_Element;

	class Element
	{
		tstring			m_name;			//���O
		PVP_Attribute	m_attributes;	//���g�̃A�g���r���[�g�z��
		PVP_Element		m_elements;		//���g�̃G�������g�z��
		P_Element		m_pParent;		//�e�G�������g�̃|�C���^

	public:
		Element ();
		Element ( const Element& rhs ) = delete;		//�R�s�[�֎~
		~Element () { Clear (); }

		//�A�g���r���[�g�z��̐擪���擾
		const PVP_Attribute GetpvpAttribute () const { return m_attributes; }

		//�G�������g�z��̐擪���擾
		const PVP_Element GetpvpElement () const { return m_elements; }

		//�e�G�������g�̃|�C���^
		void SetpParent ( P_Element pElement ) { m_pParent = pElement; }
		P_Element GetpParent () { return m_pParent; }

		//�A�g���r���[�g�z��̒ǉ�
		void AddpAttribute ( P_Attribute pAttribute ) { m_attributes->push_back ( pAttribute ); }

		//�G�������g�z��̒ǉ�
		void AddpElement ( P_Element pElement ) { m_elements->push_back ( pElement ); }

		void Clear ();

		void SetName ( tstring str ) { m_name.assign ( str ); }
		tstring GetName () const { return m_name; }

		void Print ();
	};


	//----------------------------------------------------------
	//�h�L�������g
	//	�؍\���ł���G�������g�̍��ƂȂ�root������
	//----------------------------------------------------------
	class Document
	{
		P_Element		root;

	public:
		enum STATE
		{
			START,
			ELEMENT_START,
			ELEMENT,
			ELEMENT_END,
			ATTRIBUTE_NAME_START,
			ATTRIBUTE_NAME_END,
			ATTRIBUTE_VALUE_START,
			ATTRIBUTE_VALUE,
			ATTRIBUTE_VALUE_END,
			ELEMENT_CLOSING,
			END,
		};

		//�R���X�g���N�^
		Document () = default;
		Document ( const Document& rhs ) = delete;	//�R�s�[�֎~	
		
		//�h�L�������g�t�@�C��������Ǎ�
		Document ( tstring fileName );

		//�e�L�X�g�X�g���[������Ǎ�
		Document ( tistringstream& tiss );

		//�o�C�i���f�[�^����Ǎ�
		Document ( char* buf, UINT size );

		//�f�X�g���N�^
		~Document ();

		void DocumentFromStream ( tistream& tistrm );			//�����F���̓X�g���[��
//		void DocumentFromBinary ( TCHAR* buf );			//�����F�e�L�X�g�f�[�^
		void Print () { root->Print(); }

		const P_Element Root () const { return root; }
	};


}	//namespace GAME


