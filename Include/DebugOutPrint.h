//=================================================================================================
//
// デバッグ出力 コマンドプロンプト Print
//　		
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
//	インクルードファイル
//-------------------------------------------------------------------------------------------------
#include "Define.h"


//-------------------------------------------------------------------------------------------------
//	宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
#if 0
	//--------------------------------------------------
	//シングルトンパターン
	class DebugOutPrint;
	using DBG_PRNT = DebugOutPrint;
	using P_DBG_PRNT = std::unique_ptr < DBG_PRNT >;
	//--------------------------------------------------
#endif // 0


	//IDEデバッグウィンドウ出力 [ PRINT () ]
	class DebugOutPrint
	{
#if 0
	//--------------------------------------------------
	//シングルトンパターン
	private:
		static P_DBG_PRNT	m_inst;
		DebugOutPrint ();
		DebugOutPrint ( const P_DBG_PRNT & rhs ) = delete;
	public:
		~DebugOutPrint ();
		static void Create() { if ( ! m_inst ) { m_inst = P_DBG_PRNT ( new DBG_PRNT () ); } }
		static P_DBG_PRNT & Inst() { return m_inst; }
	//--------------------------------------------------
#endif // 0
	
		DebugOutPrint () = delete;	//staticクラスとしてコンストラクタを廃止し、実体化禁止

	public:
#if 0

		//文字列フォーマットを表示(TCHAR)
		static void DebugOutf ( LPCTSTR format, ... );

		//文字列フォーマットを表示(char*)
		static void DebugOutchf ( LPCSTR format, ... );

		//GetLastError()からのWIN32APIのエラーメッセージ表示
		//引数：呼出側で__FILE__, __LINE__を指定
		static void OutputLastError ( LPCSTR file, DWORD line );
#endif // 0

		//新規コマンドプロンプト表示
		static void OpenPrompt ();


		//Siv3D対応デバッグ出力表示
		static void DebugOutf_s3d ( s3d::String str );
		static void DebugOutf_s3d ( s3d::Error err );

	};

//スタティッククラス アクセス用
//#define PRINT_F		DebugOutPrint::DebugOutf
//#define PRINT_CHF	DebugOutPrint::DebugOutchf
#define PRINT_F_S	DebugOutPrint::DebugOutf_s3d


}	//namespace GAME

