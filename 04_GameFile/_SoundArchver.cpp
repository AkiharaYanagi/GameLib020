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

	void _SoundArchiver::SetName ( CSIVSTR& ArchiveName, CSIVSTR& DirName, CSIVSTR& Condition )
	{
		ACV_FILENAME.assign ( ArchiveName );
		ACV_DIRNAME.assign ( DirName );
		ACV_CND.assign ( Condition );
	}

	//作成
	void _SoundArchiver::Make ()
	{
		//カレントディレクトリの取得
		TCHAR path [ MAX_PATH ];
		::GetCurrentDirectory ( MAX_PATH, path );

		//バイナリで書出用ファイルを開く
		HANDLE hWriteFile = CreateFile ( ACV_FILENAME.toWstr().c_str(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr );

		//ファイル個数を列挙
		m_nFile = CountFileNum ( ACV_CND.toWstr().c_str() );

		//ファイル個数を書出
		::WriteFile ( hWriteFile, & m_nFile, sizeof ( uint32 ), nullptr, nullptr );

		///ファイル実体を書出
		_Make ( hWriteFile, ACV_DIRNAME.toWstr().c_str(), ACV_CND.toWstr().c_str() );


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

#if 0

		//個数を数え上げ
		while ( T )
		{
			//次ファイルを取得
			if ( ::FindNextFile ( hFileList, & fileData ) )
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

#endif // 0

		do
		{
			//ディレクトリは飛ばす
			if ( FILE_ATTRIBUTE_DIRECTORY == fileData.dwFileAttributes ) { continue; }
			//システムファイル(Thumbs.dbなど)は飛ばす
			if ( FILE_ATTRIBUTE_SYSTEM & fileData.dwFileAttributes ) { continue; }

			++ ret;
		}
		while ( ::FindNextFile ( hFileList, & fileData ) );

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
#if 0

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

				//ファイル名書込
				DWORD nWrtn = 0;
				TCHAR fn [ MAX_PATH ];
				_tcscpy_s ( fn, MAX_PATH, fileData.cFileName );
				::WriteFile ( hWriteFile, fn, sizeof ( fn ), &nWrtn, nullptr );

				//バッファにファイルデータ読込
				tstring filename ( dirname );			
				filename.append ( fileData.cFileName );	//ファイルパス作成
				HANDLE hReadFile = CreateFile ( filename.c_str(), GENERIC_READ, 0, nullptr, 
					OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr );

				std::unique_ptr < BYTE[] > buf = std::make_unique < BYTE[] > ( fileSize );
				DWORD numberOfByteRead = 0;
				bool bRead = ::ReadFile ( hReadFile, buf.get(), fileSize, &numberOfByteRead, nullptr );
				(void)bRead;

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

#endif // 0


		do
		{
			//ディレクトリは飛ばす
			if ( FILE_ATTRIBUTE_DIRECTORY == fileData.dwFileAttributes ) { continue; }
			//システムファイル(Thumbs.dbなど)は飛ばす
			if ( FILE_ATTRIBUTE_SYSTEM & fileData.dwFileAttributes ) { continue; }



			//ファイルサイズ書込
			DWORD fileSize = fileData.nFileSizeLow;	//4Gbyte未満のみ
			DWORD numberOfBytesWritten = 0;
			::WriteFile ( hWriteFile, &fileSize, sizeof ( DWORD ), &numberOfBytesWritten, nullptr );

			//ファイル名書込
			DWORD nWrtn = 0;
			TCHAR fn [ MAX_PATH ];
			_tcscpy_s ( fn, MAX_PATH, fileData.cFileName );
			::WriteFile ( hWriteFile, fn, sizeof ( fn ), &nWrtn, nullptr );

			//バッファにファイルデータ読込
			tstring filename ( dirname );			
			filename.append ( fileData.cFileName );	//ファイルパス作成
			HANDLE hReadFile = CreateFile ( filename.c_str(), GENERIC_READ, 0, nullptr, 
				OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr );

			std::unique_ptr < BYTE[] > buf = std::make_unique < BYTE[] > ( fileSize );
			DWORD numberOfByteRead = 0;
			bool bRead = ::ReadFile ( hReadFile, buf.get(), fileSize, &numberOfByteRead, nullptr );
			(void)bRead;

			::CloseHandle ( hReadFile );

			//アーカイブにサイズ分書出
			::WriteFile ( hWriteFile, buf.get(), fileSize, &numberOfBytesWritten, nullptr );
		}
		while ( ::FindNextFile ( hFileList, & fileData ) );



		//終了
		FindClose ( hFileList );
	}


	//開
	void _SoundArchiver::Open ()
	{
		BOOL bRet = F;	//戻値

		//ファイル読込
		HANDLE hFile = CreateFile ( ACV_FILENAME.toWstr().c_str(), GENERIC_READ, 0, nullptr, OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL, nullptr );

		//ファイル個数合計を読込
		bRet = ::ReadFile ( hFile, & m_nFile, sizeof ( uint32 ), nullptr, nullptr );
		if ( ! bRet ) { return; }

		//各ファイル読込
		for ( uint32 i = 0; i < m_nFile; ++i )
		{
			DWORD numberOfByteRead = 0;
			DWORD fileSize = 0;

			//ファイルサイズ
			bRet = ::ReadFile ( hFile, &fileSize, sizeof ( DWORD ), & numberOfByteRead, nullptr );

			//ファイル名
			TCHAR fn [ MAX_PATH ] = _T("");
			bRet = ::ReadFile ( hFile, fn, sizeof ( fn ), & numberOfByteRead, nullptr );

			//実データ
			std::unique_ptr < BYTE [] > buf = std::make_unique < BYTE [] > ( fileSize );
			bRet = ::ReadFile ( hFile, buf.get(), fileSize, & numberOfByteRead, nullptr );

			//メモリ上からサウンドに変換
			s3d::MemoryReader mr { (void*)buf.get(), fileSize };
			//ma_sound.push_back ( s3d::Audio { s3d::Wave { std::move ( mr ) }, s3d::Loop::Yes } );

			//保存
			//デフォルトはループ無し
			P_Adi pAdi = std::make_shared < s3d::Audio > ( s3d::Wave { std::move ( mr ) }, s3d::Loop::No );
			map_adi.push_back ( pAdi );

			mhst_adi.emplace ( s3d::Unicode::FromWstring ( fn ), pAdi );

		}

		//閉じる
		CloseHandle ( hFile );
	}



	//------------------------------------------------------------------
	//再生
	void _SoundArchiver::Play ( uint32 id )
	{
		map_adi [ id ]->setVolume ( m_volume );

		map_adi [ id ]->setLoop ( F );
		map_adi [ id ]->play ();
		m_bPlay = T;
	}
	void _SoundArchiver::Play ( const s3d::String & filename )
	{
		if ( ! mhst_adi.contains ( filename ) ) { return; }

#if 0

		TRACE_F ( _T("■■■　SND: Volume\n") );
		for ( auto it = mhst_adi.begin (); it != mhst_adi.end (); ++ it )
		{
			TRACE_F ( _T("%d, ") , it->second->getVolume () );
		}
		for ( P_Adi pAdi : map_adi )
		{
			TRACE_F ( _T("%d, ") , pAdi->getVolume () );
		}
		TRACE_F ( _T("■■■\n") );

		double volume = mhst_adi [ filename ]->getVolume ();

#endif // 0

		mhst_adi [ filename ]->setVolume ( m_volume );

		mhst_adi [ filename ]->setLoop ( F );
		mhst_adi [ filename ]->play ();
		m_bPlay = T;
	}

	//ループ再生
	void _SoundArchiver::Play_Loop ( uint32 id )
	{


		double volume = map_adi [ id ]->getVolume ();

		map_adi [ id ]->setVolume ( m_volume );

		map_adi [ id ]->setLoop ( T );
		map_adi [ id ]->play ();
		m_bPlay = T;
	}
	void _SoundArchiver::Play_Loop ( const s3d::String & filename )
	{
		if ( ! mhst_adi.contains ( filename ) ) { return; }


		TRACE_F ( _T("■■■　SND: Volume\n") );
		for ( auto it = mhst_adi.begin (); it != mhst_adi.end (); ++ it )
		{
			TRACE_F ( _T("■%s:%lf, ") , it->first.toWstr().c_str(), it->second->getVolume () );
		}
		TRACE_F ( _T("\n") );
		for ( P_Adi pAdi : map_adi )
		{
			TRACE_F ( _T("%lf, ") , pAdi->getVolume () );
		}
		TRACE_F ( _T("\n■■■\n") );

#if 0
		double volume = mhst_adi [ filename ]->getVolume ();
#endif // 0


		mhst_adi [ filename ]->setVolume ( m_volume );


		P_Adi pAdi = mhst_adi [ filename ];
		pAdi->setLoop ( T );
		pAdi->play ();
		m_bPlay = T;
	}

	//１回 再生
	void _SoundArchiver::Play_OneShot ( uint32 id )
	{
		map_adi [ id ]->setLoop ( F );
		map_adi [ id ]->playOneShot ();
	}
	void _SoundArchiver::Play_OneShot ( const s3d::String & filename )
	{
		if ( ! mhst_adi.contains ( filename ) ) { return; }
		mhst_adi [ filename ]->setLoop ( F );
		mhst_adi [ filename ]->playOneShot ();
	}

	//停止
	void _SoundArchiver::Stop ( uint32 id )
	{
		map_adi [ id ]->stop ();
		m_bPlay = F;
	}
	void _SoundArchiver::Stop ( const s3d::String & filename )
	{
		if ( ! mhst_adi.contains ( filename ) ) { return; }
		mhst_adi [ filename ]->stop ();
		m_bPlay = F;
	}

	//すべて停止
	void _SoundArchiver::Stop_All ()
	{
		for ( P_Adi pAdi : map_adi )
		{
			//@info s3d::Audioをstop()するとVolumeが1.0にリセットされる
			pAdi->stop ();
		}



#if 0
		TRACE_F ( _T("■■■　SND: Volume\n") );
		for ( auto it = mhst_adi.begin (); it != mhst_adi.end (); ++ it )
		{
			TRACE_F ( _T("■%s:%lf, ") , it->first.toWstr().c_str(), it->second->getVolume () );
		}
		TRACE_F ( _T("\n") );
		for ( P_Adi pAdi : map_adi )
		{
			TRACE_F ( _T("%lf, ") , pAdi->getVolume () );
		}
		TRACE_F ( _T("\n■■■\n") );
#endif // 0



#if 0

		for ( P_Adi pAdi : map_adi )
		{
			for ( auto it = mhst_adi.begin (); it != mhst_adi.end (); ++ it )
			{
				if ( it->second == pAdi )
				{
					TRACE_F ( _T("■%s:") , it->first.toWstr().c_str() );
					break;
				}
			}
			TRACE_F ( _T("%lf, ->") , pAdi->getVolume () );


			//@info s3d::Audioをstop()するとVolumeが1.0にリセットされる
			pAdi->stop ();


			TRACE_F ( _T(" stop() ->%lf, \n") , pAdi->getVolume () );
		}

#endif // 0


#if 0
		TRACE_F ( _T("■■■　SND: Volume\n") );
		for ( auto it = mhst_adi.begin (); it != mhst_adi.end (); ++ it )
		{
			TRACE_F ( _T("■%s:%lf, ") , it->first.toWstr().c_str(), it->second->getVolume () );
		}
		TRACE_F ( _T("\n") );
		for ( P_Adi pAdi : map_adi )
		{
			TRACE_F ( _T("%lf, ") , pAdi->getVolume () );
		}
		TRACE_F ( _T("\n■■■\n") );
#endif // 0

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
#if 0
		for ( s3d::Audio & audio : ma_sound )
		{
			audio.setVolume ( volume );
		}
#endif // 0

		//stopするとvolumeがリセットされるので
		//値を保存しておいてPlay前に再設定する
		m_volume = volume;

		for ( P_Adi pAdi : map_adi )
		{
			pAdi->setVolume ( volume );
		}
	}


	bool _SoundArchiver::IsPlaying ( const s3d::String & filename )
	{
		if ( ! mhst_adi.contains ( filename ) ) { return F; }
		return mhst_adi [ filename ]->isPlaying ();
	}


	void _SoundArchiver::Test ()
	{
		TRACE_F ( _T("■■■------------------------------\n") );
		for ( auto [ str, pAdi ] : mhst_adi )
		{
			TRACE_F ( str.toWstr().c_str() );
			TRACE_F ( _T("\n") );
		}
		TRACE_F ( _T("■■■------------------------------\n") );
	}


}	//namespace GAME

