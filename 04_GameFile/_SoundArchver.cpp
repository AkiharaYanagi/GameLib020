//=================================================================================================
//
// _SoundArchiver ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "_SoundArchiver.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//@info 読み込むディレクトリをSEとBGMに分け、SEはバッファを複数、BGMはバッファを単一で持つ
	//IDはSE，BGM共通で監理, 呼び出しからのID指定は別enumで行う


	//------------------------------------------
	//コンストラクタ
	_SoundArchiver::_SoundArchiver ()
	{
	}

	//デストラクタ
	_SoundArchiver::~_SoundArchiver ()
	{
	}

	void _SoundArchiver::SetName ( s3d::String& ArchiveName, s3d::String& DirName, s3d::String& Condition )
	{
		m_archiveFileName.assign ( ArchiveName );
		m_archiveDirName.assign ( DirName );
		m_searchCondition.assign ( Condition );
	}

	//作成
	void _SoundArchiver::Make ()
	{
		//カレントディレクトリの取得
		TCHAR path [ MAX_PATH ];
		::GetCurrentDirectory ( MAX_PATH, path );

		//バイナリで書出用ファイルを開く
		HANDLE hWriteFile = CreateFile ( m_archiveFileName.toWstr().c_str(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr );

		//ファイル個数を列挙
		m_nFile = CountFileNum ( m_searchCondition.toWstr().c_str() );

		//ファイル個数を書出
		::WriteFile ( hWriteFile, & m_nFile, sizeof ( uint32 ), nullptr, nullptr );

		///ファイル実体を書出
		_Make ( hWriteFile, m_archiveDirName.toWstr().c_str(), m_searchCondition.toWstr().c_str() );


		//終了
		CloseHandle ( hWriteFile );
	}

	//条件のファイル数え上げ
	UINT _SoundArchiver::CountFileNum ( LPCTSTR condition )
	{
		UINT ret = 0;

		//ファイル列挙( OpenHandle )
		WIN32_FIND_DATA		fileData;
		//ディレクトリ指定("sound/*.*")
		HANDLE hFileList = ::FindFirstFile ( condition, & fileData );

		//個数を数え上げ
		while ( T )
		{
			//次ファイルを取得
			if ( ::FindNextFile ( hFileList, &fileData ) )
			{
				//ディレクトリは飛ばす
				if ( FILE_ATTRIBUTE_DIRECTORY == fileData.dwFileAttributes ) { continue; }
				//システムファイル(Thumbs.dbなど)は飛ばす
				if ( FILE_ATTRIBUTE_SYSTEM & fileData.dwFileAttributes ) { continue; }

				++ ret;
			}
			//次ファイルが取得できなかったとき
			else
			{
				break;
			}
		}
		::FindClose ( hFileList );

		return ret;
	}


	//作成
	void _SoundArchiver::_Make ( HANDLE hWriteFile, LPCTSTR dirname, LPCTSTR condition )
	{
		//再列挙
		WIN32_FIND_DATA		fileData;
		HANDLE hFileList = ::FindFirstFile ( condition, &fileData );	//ディレクトリ指定("sound/*.*")

		//書出
		while ( T )
		{
			//次ファイルを取得
			if ( ::FindNextFile ( hFileList, &fileData ) )
			{
				//ディレクトリは飛ばす
				if ( FILE_ATTRIBUTE_DIRECTORY == fileData.dwFileAttributes ) { continue; }
				//システムファイル(Thumbs.dbなど)は飛ばす
				if ( FILE_ATTRIBUTE_SYSTEM & fileData.dwFileAttributes ) { continue; }

				//ファイルサイズ書込
				DWORD fileSize = fileData.nFileSizeLow;	//4Gbyte未満のみ
				DWORD numberOfBytesWritten = 0;
				::WriteFile ( hWriteFile, &fileSize, sizeof ( DWORD ), &numberOfBytesWritten, nullptr );

				//バッファにファイルデータ読込
				tstring filename ( dirname );			
				filename.append ( fileData.cFileName );	//ファイルパス作成
				HANDLE hReadFile = CreateFile ( filename.c_str(), GENERIC_READ, 0, nullptr, 
					OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr );

				std::unique_ptr < BYTE[] > buf = std::make_unique < BYTE[] > ( fileSize );
				DWORD numberOfByteRead = 0;
				::ReadFile ( hReadFile, buf.get(), fileSize, &numberOfByteRead, nullptr );

				::CloseHandle ( hReadFile );

				//アーカイブにサイズ分書出
				::WriteFile ( hWriteFile, buf.get(), fileSize, &numberOfBytesWritten, nullptr );
			}
			//次ファイルが取得できなかったとき
			else 
			{
				break;
			}
		}
		//終了
		FindClose ( hFileList );
	}


	//開
	void _SoundArchiver::Open ()
	{
		BOOL bRet = F;	//戻値

		//ファイル読込
		HANDLE hFile = CreateFile ( m_archiveFileName.toWstr().c_str(), GENERIC_READ, 0, nullptr, OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL, nullptr );

		//ファイル個数合計を読込
		bRet = ::ReadFile ( hFile, & m_nFile, sizeof ( uint32 ), nullptr, nullptr );
		if ( ! bRet ) { return; }

		//各ファイル読込
		for ( uint32 i = 0; i < m_nFile; ++i )
		{
			DWORD numberOfByteRead = 0;
			DWORD fileSize = 0;
			bRet = ::ReadFile ( hFile, &fileSize, sizeof ( DWORD ), &numberOfByteRead, nullptr );
			std::unique_ptr < BYTE [] > buf = std::make_unique < BYTE [] > ( fileSize );
			bRet = ::ReadFile ( hFile, buf.get(), fileSize, &numberOfByteRead, nullptr );

			//メモリ上からサウンドに変換
			s3d::MemoryReader mr { (void*)buf.get(), fileSize };
			ma_sound.push_back ( s3d::Audio { s3d::Wave { std::move ( mr ) }, s3d::Loop::Yes } );

		}

		//閉じる
		CloseHandle ( hFile );
	}

#if 0
	//------------------------------------------------------------------
	//再生
	void SoundArchiver::Play_BGM ( UINT BGM_ID )
	{
		//DxSound::instance()->Play ( BGM_ID );
		ma_sound [ BGM_ID ].setLoop ( F );
		ma_sound [ BGM_ID ].play ();
		m_bPlay = T;
	}

	//ループ再生
	void SoundArchiver::Play_Loop_BGM ( UINT BGM_ID )
	{
		//DxSound::instance()->PlayLoop ( BGM_ID );
		ma_sound [ BGM_ID ].setLoop ( T );
		ma_sound [ BGM_ID ].play ();
		m_bPlay = T;
	}

	//停止
	void SoundArchiver::Stop_BGM ( UINT BGM_ID )
	{
		//DxSound::instance()->Stop ( BGM_ID );
		ma_sound [ BGM_ID ].stop ();
		m_bPlay = F;
	}

	//すでにプレイ中でなければ再生
	void SoundArchiver::If_Play_Loop_BGM ( UINT BGM_ID )
	{
		if ( m_bPlay ) { return; }
		//DxSound::instance()->PlayLoop ( BGM_ID );
		ma_sound [ BGM_ID ].play ();
		m_bPlay = T;
	}


	//再生
	void SoundArchiver::Play_SE ( UINT SE_ID )
	{
		//@info リリースモード時にMake()を通らないため、m_nBGMはファイルから読み込む
		//BGMの数だけオフセットして指定
		//DxSound::instance()->Play ( m_nBGM + SE_ID );
		ma_sound [ m_nBGM + SE_ID ].playOneShot ();
	}
#endif // 0

	void _SoundArchiver::SetVolume ( double volume )
	{
		for ( s3d::Audio & audio : ma_sound )
		{
			audio.setVolume ( volume );
		}
	}


}	//namespace GAME

