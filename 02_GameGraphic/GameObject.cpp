//=================================================================================================
//
// GameObject ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "GameObject.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	GameObject::GameObject ()
	{
	}

	GameObject::GameObject ( const GameObject& rhs )
	{
		m_valid = rhs.m_valid;
		m_indexTexture = rhs.m_indexTexture;
		m_fade = rhs.m_fade;

		m_vecPos = rhs.m_vecPos;
		m_scalingCenter = rhs.m_scalingCenter;
		m_scaling = rhs.m_scaling;
		m_rotationCenter = rhs.m_rotationCenter;
		m_radian = rhs.m_radian;
	}

	GameObject::~GameObject ()
	{
	}

	void GameObject::PreMove ()
	{
		m_fade.PreMove ();
	}

	void GameObject::Move ()
	{
//		m_matrix.Move ();
	}

}	//namespace GAME

