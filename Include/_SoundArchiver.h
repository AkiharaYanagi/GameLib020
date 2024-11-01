//=================================================================================================
//
// SoundArchiver ヘッダファイル
//
//		Debugモード時にSoundディレクトリにあるwaveファイルをsound.datに書き出し、
//		Debugモード, Releaseモード時にsound.datからwaveを読み込む
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Define.h"
#include "00_Common.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	using CSIVSTR = const s3d::String;
	using P_Adi = std::shared_ptr < s3d::Audio >;
	using AP_Adi = s3d::Array < P_Adi >;


	//========================================================
	//	◆ サウンドアーカイブ フォーマット
	//	----
	//	UINT	4byte	//サイズ
	//	BYTE	...		//バイナリデータ
	//	----
	//	n個の列挙
	//	検索するときは定数添字
	//========================================================

	class _SoundArchiver
	{
		//--------------------------------------------------
		//ファイル名
		s3d::String		ACV_FILENAME;	//作成するサウンドアーカイブファイル名
		s3d::String		ACV_DIRNAME;	//アーカイブ作成のため読み込むディレクトリ名
		s3d::String		ACV_CND;		//アーカイブ作成のため読み込むファイル名条件

		//--------------------------------------------------
		//サウンドデータ
//		s3d::Array < s3d::Audio >	ma_sound;
		AP_Adi		map_adi;

		//名前とサウンドデータ
		s3d::HashTable < s3d::String, P_Adi >	mhst_adi;
		

		uint32		m_nFile { 0 };	//ファイル個数

#if 0
		// DSBVOLUME_MAX : 減衰無し(0), DSBVOLUME_MIN : 最小値(-10000) [1/100dB]
//		LONG		m_volume { 0 };		//全体ボリューム
#endif // 0
		double		m_volume { 0.5 };	//音量（保存用）

		bool		m_bPlay { F };	//すでにプレイ中かどうか

	public:
		_SoundArchiver ();
		_SoundArchiver ( const _SoundArchiver & rhs ) = delete;
		~_SoundArchiver ();

		void SetName ( CSIVSTR& ArchiveName, CSIVSTR& DirName, CSIVSTR& Condition );

		void Make ();
		void Open ();

		void Play ( uint32 id );
		void Play ( const s3d::String & filename );
		void Play_Loop ( uint32 id );
		void Play_Loop ( const s3d::String & filename );
		void Play_OneShot ( uint32 id );
		void Play_OneShot ( const s3d::String & filename );
		void Stop ( uint32 id );
		void Stop ( const s3d::String & filename );
		void Stop_All ();

		bool IsPlaying ( uint32 id ) { return map_adi [ id ]->isPlaying (); }
		bool IsPlaying ( const s3d::String & filename );


#if 0

		//------------------------------------------------------------------
		void Play_BGM ( UINT BGM_ID );
		void Play_Loop_BGM ( UINT BGM_ID );
		void Stop_BGM ( UINT BGM_ID );
		void All_Stop () {}

		//すでにプレイ中でなければ再生
		//明示的にStop_BGM()を実行すれば再生される
		void If_Play_Loop_BGM ( UINT BGM_ID );

		void Play_SE ( UINT SE_ID );

#endif // 0

		//音量設定 ( 0.0 ～ 1.0 )
		void SetVolume ( double volume );

		void Test ();

	private:

		//条件のファイル数え上げ
		UINT CountFileNum ( LPCTSTR condition );
//		uint32 CountFileNum ( s3d::String condition );

		//作成
		void _Make ( HANDLE hWriteFile, LPCTSTR dirname, LPCTSTR condition );
	};

	//外部利用定義
//#define		SOUND	SoundArchiver::Inst()


}	//namespace GAME

