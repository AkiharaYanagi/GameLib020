//=================================================================================================
//
// ゲームグラフィック　クラス　ヘッダ
//		グラフィックを扱うオブジェクトを定義する
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイル　インクルード
//-------------------------------------------------------------------------------------------------
#include "00_Common.h"
#include "GameGraphicCore.h"
#include "GameObject.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//■=======================================================================
	// ゲームグラフィック　ベース
	//		・複数テクスチャと複数オブジェクトを持つゲームタスク
	//		・テクスチャが指定されていないときは何もしない
	//		・オブジェクトは自動で１つ生成する。指定個数使用する場合は０にクリアしてから追加する
	//■=======================================================================
	class GameGraphicBase : public GameGraphicCore
	{
		//テクスチャ配列(インデックスはオブジェクトが持つ)
		PAP_Tx		mpap_Texture;

		//オブジェクト配列
		PAP_Ob		mpap_Object;

		//シェーダ利用フラグ
		bool		m_shader { F };

	public:
		GameGraphicBase ();
		GameGraphicBase ( const GameGraphicBase & rhs ) = delete;
		~GameGraphicBase ();

		//---------------------------------------------------------------------
		void Move ();
		void Draw ();
		void _Draw ();

		void SetShader ( bool b ) { m_shader = b; }
		void ShaderDraw ();

		//---------------------------------------------------------------------
		//テクスチャ
		PAP_Tx Getpap_tx () const { return mpap_Texture; }

		void ClearTexture () { mpap_Texture->clear (); }
		void AddTexture ();
		void AddTexture ( s3d::String filename );
		void AddTexture_FromArchive ( s3d::String filename );
		void AddpTexture ( P_Tx ptx );
		void SetpTexture ( P_Tx ptx );
		VEC2 GetCenterOfTexture ( uint32 index );

		//---------------------------------------------------------------------
		// オブジェクト

		//オブジェクト配列
		PAP_Ob Getpap_ob () const { return mpap_Object; }
		P_Ob GetpObject ( size_t index ) { return mpap_Object->at ( index ); }

		void AddObject ();
		void AddpObject ( P_Ob pOb );
		void ClearObject () { mpap_Object->clear (); }

		//オブジェクト先頭の直接制御
		//単体で用いるときは、オブジェクトを指定しなくてよい
		void SetValid ( bool b ) { m_valid = b; mpap_Object->at ( 0 )->SetValid ( b ); }
		bool GetValid () const { return mpap_Object->at(0)->GetValid (); }

		void SetPos ( VEC2 v ) { mpap_Object->at ( 0 )->SetPos ( v ); }
		void SetPos ( float x, float y ) { mpap_Object->at ( 0 )->SetPos ( x, y ); }
		void SetPosX ( float x ) {  mpap_Object->at ( 0 )->SetPosX ( x ); }
		void SetPosY ( float y ) {  mpap_Object->at ( 0 )->SetPosY ( y ); }

		VEC2 GetPos () const { return mpap_Object->at ( 0 )->GetPos (); }
		void AddPos ( VEC2 v ) { mpap_Object->at ( 0 )->AddPos ( v ); }

		void SetScaling ( float x, float y ) { mpap_Object->at(0)->SetScaling ( x, y ); }
		void SetScaling ( VEC2 v ) { mpap_Object->at(0)->SetScaling ( v ); }
		void SetScalingCenter ( float x, float y ) { mpap_Object->at(0)->SetScalingCenter ( x, y ); }
		void SetScalingCenter ( VEC2 v ) { mpap_Object->at(0)->SetScalingCenter ( v ); }

		void SetRotationCenter ( VEC2 v ) { mpap_Object->at(0)->SetRotationCenter ( v ); }
		VEC2 GetRotationCenter () const { return mpap_Object->at(0)->GetRotationCenter (); }

		void SetRadian ( float rad ) { mpap_Object->at(0)->SetRadian ( rad ); }
		float GetRadian () const { return mpap_Object->at(0)->GetRadian (); }

		void SetRectF ( s3d::RectF rectf ) { mpap_Object->at(0)->SetRectF ( rectf ); }
		void SetAllRectF ( s3d::RectF rectf );
		void SetAllRectF_Size ( s3d::Size size );
		void ApplyTxSize_ToOb ( P_Tx ptx, P_Ob pob );


		void SetIndexTexture ( uint32 index ) { mpap_Object->at(0)->SetIndexTexture ( index ); }
		void NextIndexTexture ();
		void PrevIndexTexture ();
		
		void SetColor ( uint32 clr ) { mpap_Object->at(0)->SetColor ( clr ); }
		void SetColor ( _CLR clr ) { mpap_Object->at(0)->SetColor ( clr ); }

		//---------------------------------------------------------------------
	};

	using GrpBs = GameGraphicBase;
	using P_GrpBs = std::shared_ptr < GrpBs >;



	//---------------------------------------------------------------------
	class GameGraphic : public GameGraphicBase
	{
	};

	using P_Grp = std::shared_ptr < GameGraphic >;
	
	using	AP_Grp = s3d::Array < P_Grp >;
	using	UPAP_Grp = std::unique_ptr < AP_Grp >;



}	//namespace GAME

