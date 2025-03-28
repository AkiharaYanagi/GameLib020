//=================================================================================================
//
//	キーコンフィグ
//		"ゲーム内で用いるキー" を "外部のデバイス入力" から変換する
//
//		・ジョイスティックにおけるAXISとPOVに対応する
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
//#include "DebugLibrary.h"
//#include "DxInput.h"
//#include <fstream>
#include "KeyDefine.h"
#include "DeviceInput.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class KeyConfig
	{
	//--------------------------------------------------
	//シングルトンパターン
	private:
		using P_KeyConfig = std::unique_ptr < KeyConfig >;
		static P_KeyConfig		m_inst;
		KeyConfig ();
		KeyConfig ( const KeyConfig & rhs );
	public:
		~KeyConfig ();
		static void Create () { if ( ! m_inst ) { m_inst = P_KeyConfig ( new KeyConfig () ); } }
		static P_KeyConfig & Inst () { return m_inst; }
	//--------------------------------------------------

	private:
		//デバイスインプット配列
		DeviceInput		m_deviceInput [ GAME_USE_KEY_NUM ];

	public:
		//ゲーム利用 (キーで1p/2p指定)
		bool IsKey ( GAME_USE_KEY key ) const;
		bool OffKey ( GAME_USE_KEY key ) const;
		bool PushKey ( GAME_USE_KEY key ) const;
		bool ReleKey ( GAME_USE_KEY key ) const;

		//ゲーム利用 (1p/2p共通)
		bool IsKey_12 ( PLAYER_INPUT key ) const;
		bool OffKey_12 ( PLAYER_INPUT key ) const;
		bool PushKey_12 ( PLAYER_INPUT key ) const;
		bool ReleKey_12 ( PLAYER_INPUT key ) const;

		//ゲーム利用 (引数で1p/2pを指定)
		bool IsKey_PL ( PLAYER_ID id, PLAYER_INPUT key ) const;
		bool OffKey_PL ( PLAYER_ID id, PLAYER_INPUT key ) const;
		bool PushKey_PL ( PLAYER_ID id, PLAYER_INPUT key ) const;
		bool ReleKey_PL ( PLAYER_ID id, PLAYER_INPUT key ) const;

		//プレイヤーとキー種類から判定値を取得する
		static GAME_USE_KEY InputFromPlayer ( PLAYER_ID id, PLAYER_INPUT input ); 

	private:
		void SetInitial ();		//初期化

	private:
		void Save ();		//保存
	public:
		void Load ();		//読込
	private:
		void _Load ();
		uint8 ReadUInt8 ( s3d::BinaryReader & br );

	public:
		s3d::String ToString ();
	
	private:

		bool Is_Joy ( GamePadInput gpi ) const;
		bool Is_Axis_Vl ( uint32 ID, AXIS_VALUE vl ) const;
//		bool Is_POV_Lvr ( uint32 ID, LEVER_DIR lvr ) const;
		bool Is_POV_Vl ( uint32 ID, POV_VALUE vl ) const;
		bool Is_Keyboard ( KEY_NAME key ) const;

		bool Push_Joy ( GamePadInput gpi ) const;
		bool Push_Axis_Vl ( uint32 ID, AXIS_VALUE vl ) const;
//		bool Push_POV_Lvr ( uint32 ID, LEVER_DIR lvr ) const;
		bool Push_POV_Vl ( uint32 ID, POV_VALUE vl ) const;
		bool Push_Keyboard ( KEY_NAME key ) const;

		bool Rele_Joy ( GamePadInput gpi ) const;
		bool Rele_Axis_Vl ( uint32 ID, AXIS_VALUE vl ) const;
//		bool Rele_POV_Lvr ( uint32 ID, LEVER_DIR lvr ) const;
		bool Rele_POV_Lvr ( uint32 ID, POV_VALUE vl ) const;
		bool Rele_Keyboard ( KEY_NAME key ) const;
	};


//シングルトンアクセス用

//キーでプレイヤも指定
#define CFG_IS_KEY		KeyConfig::Inst()->IsKey 
#define CFG_OFF_KEY		KeyConfig::Inst()->OffKey 
#define CFG_PUSH_KEY	KeyConfig::Inst()->PushKey 
#define CFG_RELE_KEY	KeyConfig::Inst()->ReleaseKey 

//プレイヤ両方の入力を見る
#define CFG_IS_KEY_12	KeyConfig::Inst()->IsKey_12
#define CFG_OFF_KEY_12	KeyConfig::Inst()->OffKey_12
#define CFG_PUSH_KEY_12 KeyConfig::Inst()->PushKey_12
#define CFG_RELE_KEY_12 KeyConfig::Inst()->ReleaseKey_12

//プレイヤを引数で指定
#define CFG_IS_KEY_PL		KeyConfig::Inst()->IsKey_PL 
#define CFG_OFF_KEY_PL		KeyConfig::Inst()->OffKey_PL 
#define CFG_PUSH_KEY_PL		KeyConfig::Inst()->PushKey_PL 
#define CFG_RELE_KEY_PL		KeyConfig::Inst()->ReleaseKey_PL 


//プレイヤーとキー種類から判定値を取得する
#define CFG_PL_KEY KeyConfig::InputFromPlayer


}	//namespace GAME

