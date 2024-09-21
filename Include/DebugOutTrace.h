//=================================================================================================
//
// デバッグ出力 IDE
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

	//IDEデバッグウィンドウ出力 [ TRACE() ]
	class DebugOutTrace
	{
		DebugOutTrace () = delete;	//staticクラスとして実体化禁止

	public:

		//文字列フォーマットを表示(TCHAR)
		static void DebugOutf ( LPCTSTR format, ... );

		//文字列フォーマットを表示(char*)
		static void DebugOutchf ( LPCSTR format, ... );

		//GetLastError()からのWIN32APIのエラーメッセージ表示
		//引数：呼出側で__FILE__, __LINE__を指定
		static void OutputLastError ( LPCSTR file, DWORD line );


		//Siv3D対応デバッグ出力表示
		static void DebugOutf_s3d ( s3d::String str );
		static void DebugOutf_s3d ( s3d::Error err );

	};

//シングルトンアクセス用
#define TRACE_F		DebugOutTrace::DebugOutf
#define TRACE_CHF	DebugOutTrace::DebugOutchf

#define TRACE_F_S	DebugOutTrace::DebugOutf_s3d


#define BREAK_POINT		DebugOutTrace::DebugOutf ( "" );


}	//namespace GAME

