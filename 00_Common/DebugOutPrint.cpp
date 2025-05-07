//=================================================================================================
//
// デバッグ出力 コマンドプロンプト Print
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "DebugOutPrint.h"
#include "Format.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
#if 0
	//--------------------------------------------------
	//シングルトンパターン	static実体
	P_DBG_PRNT	DBG_PRNT::m_inst = nullptr;
	//--------------------------------------------------


	//コンストラクタ
	DebugOutPrint::DebugOutPrint ()
	{
	}


	DebugOutPrint::~DebugOutPrint ()
	{
	}
#endif // 0

#if 0

	//文字列フォーマットを表示
	void DebugOutPrint::DebugOutf ( LPCTSTR format, ... )
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
	void DebugOutPrint::DebugOutchf ( LPCSTR format, ... )
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
	void DebugOutPrint::OutputLastError ( LPCSTR file, DWORD line )
	{
		TCHAR filePath [ MAX_PATH ] = _T("");
		size_t _PptNumOfCharConverted = 0;
//		::MultiByteToWideChar ( CP_THREAD_ACP, MB_PRECOMPOSED, file, -1, filePath, 0 );
		setlocale ( LC_ALL, "japanese" );
		size_t sizefile = strlen ( file );
		//multibyte文字からWCHARに変換
		mbstowcs_s ( &_PptNumOfCharConverted, filePath, sizefile, file, _TRUNCATE );

		//OutputDebugString( filePath );
		std::cout << filePath;

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
#endif // 0


	//新規コマンドプロンプト表示
	void DebugOutPrint::OpenPrompt ()
	{
		if ( ::AllocConsole () )
		{
			FILE* stream;
			::freopen_s ( &stream, "CONOUT$", "w", stdout );

			//コンソールのコードページをUTF-8に設定
			::SetConsoleOutputCP ( CP_UTF8 );
		}
	}

	//Siv3D対応デバッグ出力表示
	void DebugOutPrint::DebugOutf_s3d ( s3d::String str )
	{
		std::cout << str.toUTF8();
	}

	void DebugOutPrint::DebugOutf_s3d ( s3d::Error err )
	{
		std::cout << err.what().toUTF8 ();
	}


}	//namespace GAME

