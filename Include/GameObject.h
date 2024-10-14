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
#include "00_Common.h"
#include "Fade.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class GameObject
	{
		bool		m_valid { T };		//表示 ;個別ON/OFF
		uint32		m_indexTexture { 0 };	//テクスチャ指定添字
		Fade		m_fade;				//フェード (単色指定もフェードに統合)

		//表示パラメータ
		VEC2		m_vecPos { 0, 0 };			//自オブジェクト位置
		VEC2		m_scalingCenter { 0, 0 };	//スケーリングの中心座標
		VEC2		m_scaling { 1.f, 1.f };		//スケーリング(拡大率)
//		float		m_scalingRotation { 0 };	//拡大回転の要素
		VEC2		m_rotationCenter { 0, 0 };	//回転時の中心座標
		float		m_radian { 0 };				//角度[rad]

		s3d::RectF	m_rectf { 0, 0, 0, 0 };		//表示領域

		float		m_z { 0.5f };				//疑似z位置(順番で描画位置を表現する)

		bool		m_bScalingCntrOfTx { F };		//描画時に拡大中心位置をテクスチャの位置にする
		bool		m_bRotationCntrOfTx { F };	//描画時に回転中心位置をテクスチャの位置にする

	public:
		GameObject ();
		GameObject ( const GameObject& rhs );	//コピー可能
		~GameObject ();

		void PreMove ();
		
		//有効・無効
		void SetValid ( bool b ) { m_valid = b; }
		bool GetValid () const { return m_valid; }


		//テクスチャインデックス
		void SetIndexTexture ( uint32 i ) { m_indexTexture = i; }
		uint32 GetIndexTexture () const { return m_indexTexture; }
		void NextIndexTexture ();
		void PrevIndexTexture ();

		//色
		void SetColor ( _CLR c ) { m_fade.SetColor ( c ); }
		_CLR GetColor () const { return m_fade.GetColor (); }

		//フェード
		void SetFade ( uint32 time, _CLR clr_start, _CLR clr_end )
		{
			m_valid = true;
			m_fade.SetFade ( time, clr_start, clr_end ); 
		}
		void SetFadeIn  ( uint32 time )
		{
			m_valid = true;
			m_fade.SetFade ( time, 0x00ffffff, 0xffffffff );
		}
		void SetFadeOut ( uint32 time )
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

		void SetScalingCenter ( float x, float y ) { m_scalingCenter.x = x, m_scalingCenter.y = y; }
		void SetScalingCenter ( VEC2 v ) { m_scalingCenter = v; }
		VEC2 GetScalingCenter () const { return m_scalingCenter; }
		void SetbScalingCntrOfTx ( bool b ) { m_bScalingCntrOfTx = b; }
		bool GetbScalingCntrOfTx () const { return m_bScalingCntrOfTx; }

		VEC2 GetScaling () const { return m_scaling; }
		void SetScaling ( VEC2 v ) { m_scaling = v; }
		void SetScaling ( float x, float y ) { m_scaling.x = x, m_scaling.y = y; }

		void SetRotationCenter ( VEC2 v ) { m_rotationCenter = v; }
		VEC2 GetRotationCenter () const { return m_rotationCenter; }
		void SetbRotationCntrOfTx ( bool b ) { m_bRotationCntrOfTx = b; }
		bool GetbRotationCntrOfTx () const { return m_bRotationCntrOfTx; }

		void SetRadian ( float rad ) { m_radian = rad; }
		float GetRadian () const { return m_radian; }

		s3d::RectF GetRectF () const { return m_rectf; }
		void SetRectF ( s3d::RectF rectf ) { m_rectf = rectf; }
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

