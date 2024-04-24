//=================================================================================================
//
// GameObject ヘッダファイル
//		テクスチャ以外のグラフィックの実体
//		タスクではないのでグラフィック内で手動操作する
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
//#include "GameMatrix.h"
#include "Fade.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class GameObject
	{
//		GameMatrix	m_matrix;			//座標
		bool		m_valid { T };		//表示 ON/OFF
		UINT		m_indexTexture { 0 };	//テクスチャ指定添字
		Fade		m_fade;				//フェード (単色指定もフェードに統合)

		//表示パラメータ
		VEC2		m_vecPos { 0, 0 };			//自オブジェクト位置
		VEC2		m_scalingCenter { 0, 0 };	//スケーリングの中心座標
		VEC2		m_scaling { 0, 0 };			//スケーリング(拡大率)
//		float		m_scalingRotation { 0 };	//拡大回転の要素
		VEC2		m_rotationCenter { 0, 0 };	//回転時の中心座標
		float		m_radian { 0 };				//角度[rad]

	public:
		GameObject ();
		GameObject ( const GameObject& rhs );	//コピー可能
		~GameObject ();

		void PreMove ();
		void Move ();
		
		//有効・無効
		void SetValid ( bool b ) { m_valid = b; }
		bool GetValid () const { return m_valid; }


		//テクスチャインデックス
		void SetIndexTexture ( UINT i ) { m_indexTexture = i; }
		UINT GetIndexTexture () const { return m_indexTexture; }

		//色
		void SetColor ( _CLR c ) { m_fade.SetColor ( c ); }
		_CLR GetColor () const { return m_fade.GetColor (); }

		//フェード
		void SetFade ( UINT time, _CLR clr_start, _CLR clr_end )
		{
			m_valid = true;
			m_fade.SetFade ( time, clr_start, clr_end ); 
		}
		void SetFadeIn  ( UINT time )
		{
			m_valid = true;
			m_fade.SetFade ( time, 0x00ffffff, 0xffffffff );
		}
		void SetFadeOut ( UINT time )
		{
			m_valid = true;
			m_fade.SetFade ( time, 0xffffffff, 0x00ffffff );
		}
		void EndFade ( _CLR clr ) { m_fade.End ( clr ); }


		//表示パラメータ
		VEC2 GetPos () const { return m_vecPos; }
		void SetPos ( VEC2 v ) { m_vecPos = v; }
		void SetPos ( float x, float y ) { m_vecPos.x = x; m_vecPos.y = y; }
		void SetPosX ( float x ) { m_vecPos.x = x; }
		void SetPosY ( float y ) { m_vecPos.y = y; }
		void AddPos ( VEC2 v ) { m_vecPos + v; }
		void AddPos ( float x, float y ) { m_vecPos += VEC2 ( x, y ); }
		void AddPosX ( float x ) { m_vecPos.x += x; }
		void AddPosY ( float y ) { m_vecPos.y += y; }

		void SetScalingCenter ( VEC2 v ) { m_scalingCenter = v; }
		VEC2 GetScalingCenter () const { return m_scalingCenter; }

		VEC2 GetScaling () const { return m_scaling; }
		void SetScaling ( VEC2 v ) { m_scaling = v; }
		void SetScaling ( float x, float y ) { m_scaling.x = x, m_scaling.y = y; }

		//		void SetScalingRotation ( float f ) { m_matrix.SetScalingRotation ( f ); }
		//		void SetRotationCenter ( VEC2 v ) { m_matrix.SetRotationCenter ( v ); }
		//		void SetRadian ( float f ) { m_matrix.SetRadian ( f ); }

		void SetRotationCenter ( VEC2 v ) { m_scalingCenter = v; }
		VEC2 GetRotationCenter () const { return m_scalingCenter; }

		float GetRadian () const { return m_radian; }
		void SetRadian ( float rad ) { m_radian = rad; }
	};

	//型定義
#if 0
	typedef std::vector < P_Object > VP_Object;
	typedef std::shared_ptr < GameObject > P_Object;
	typedef std::shared_ptr < VP_Object > PVP_Object;
#endif // 0


	using P_Ob = std::shared_ptr < GameObject >;
	using AP_Ob = s3d::Array < P_Ob >;
	using PAP_Ob = std::shared_ptr < AP_Ob >;

}	//namespace GAME

