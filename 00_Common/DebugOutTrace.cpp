//=================================================================================================
//
// デバッグマネージャ　実装
//	・テキストファイル出力
//	・IDEデバッグ出力
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "DebugOutTrace.h"
#include "Format.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	/*===========================================================================*/
	//	IDEデバッグウィンドウ出力 [ TRACE() ]
	/*===========================================================================*/

	//文字列フォーマットを表示
	void DebugOutTrace::DebugOutf ( LPCTSTR format, ... )
	{
		va_list args;	//可変長リスト
		va_start ( args, format );	//文字列の先頭ポインタをセット
		UP_TSTR buf = Format::Printf_Args ( format, args );
		va_end ( args );	//可変長リスト終了

		//デバッグウィンドウに出力
		OutputDebugString ( buf.get () );
//		OutputDebugString ( Format::f ( format, args ) );
	}


	//文字列フォーマットを表示(char*)
	void DebugOutTrace::DebugOutchf ( LPCSTR format, ... )
	{
		va_list args;	//可変長リスト
		va_start ( args, format );	//文字列の先頭ポインタをセット

		int size = _vscprintf ( format, args ) + 1;		//'\0'を最後につけたサイズを得る
		std::unique_ptr < char[] > buf = std::make_unique < char[] > ( size );		//バッファを確保
		vsprintf_s ( buf.get (), size, format, args );	//バッファに書き込み

		va_end ( args );

		//multibyte文字からTCHAR(WCHAR)に変換
		std::unique_ptr < TCHAR[] > tbuf = std::make_unique < TCHAR[] > ( size );		//バッファを確保
		size_t _PptNumOfCharConverted = 0;
		size_t sizebuf = strlen ( buf.get() ) + 1;
		mbstowcs_s ( &_PptNumOfCharConverted, tbuf.get(), sizebuf, buf.get(), _TRUNCATE );

		//デバッグウィンドウに出力
		OutputDebugString ( tbuf.get () );
	}


	//GetLastError()からのWIN32APIのエラーメッセージ表示
	//引数：呼出側で__FILE__, __LINE__を指定
	void DebugOutTrace::OutputLastError ( LPCSTR file, DWORD line )
	{
		TCHAR filePath [ MAX_PATH ] = _T("");
		size_t _PptNumOfCharConverted = 0;
//		::MultiByteToWideChar ( CP_THREAD_ACP, MB_PRECOMPOSED, file, -1, filePath, 0 );
		setlocale ( LC_ALL, "japanese" );
		size_t sizefile = strlen ( file );
		//multibyte文字からWCHARに変換
		mbstowcs_s ( &_PptNumOfCharConverted, filePath, sizefile, file, _TRUNCATE );
		OutputDebugString( filePath );

		TCHAR lineStr [255];
		size_t size =  sizeof(TEXT(" () : ")) + sizeof ( line );
		_stprintf_s ( lineStr, size, TEXT(" (%d) : "), line );
		OutputDebugString( lineStr );
//		OutputDebugString( TEXT ( __FILE__ ) );
//		OutputDebugString( TEXT ( "(%d)\n" ), __LINE__);

		DWORD error = ::GetLastError();
		LPTSTR lpBuffer = nullptr;
		::FormatMessage ( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
			nullptr, error, LANG_USER_DEFAULT, (LPTSTR)&lpBuffer, 0, nullptr );
		OutputDebugString ( lpBuffer );
		::LocalFree ( lpBuffer );
	}


	//Siv3D対応デバッグ出力表示
	void DebugOutTrace::DebugOutf_s3d ( s3d::String str )
	{
		s3d::Print << str;
	}

	void DebugOutTrace::DebugOutf_s3d ( s3d::Error err )
	{
		s3d::Print << err;
	}


}	//namespace GAME

