﻿//=================================================================================================
//
//	テスト
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class Test	: public TASK_VEC
	{
		P_Grp		m_grp;

		P_GrpDemo	m_grp_Ketsu;
		P_GrpDemo	m_grp_chaku;
		P_GrpDemo	m_grpLight0;
		P_GrpDemo	m_grpLight1;


	public:
		Test ();
		Test ( const Test & rhs ) = delete;
		~Test ();

		void Init ();
		void Move ();
	};


}	//namespace GAME

