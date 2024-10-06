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
//#include "SivSound.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//========================================================
	//	◆ サウンドアーカイブ フォーマット
	//	----
	//	UINT	4byte	//サイズ
	//	BYTE	...		//バイナリデータ
	//	----
	//	n個の列挙
	//	検索するときは定数添字
	//========================================================

	class SoundArchiver
	{
	//--------------------------------------------------
	//シングルトンパターン
	private:
		using P_SoundArchiver = std::unique_ptr < SoundArchiver >;
		static P_SoundArchiver		m_inst;
		SoundArchiver ();
		SoundArchiver ( const SoundArchiver& rhs ) = delete;
	public:
		~SoundArchiver ();
		static void Create () { if ( ! m_inst ) { m_inst = P_SoundArchiver ( new SoundArchiver () ); } }
		static P_SoundArchiver & Inst () { return m_inst; }
	//--------------------------------------------------

	private:
		//--------------------------------------------------
		//名前 定数
		static LPCTSTR	m_archiveFileName;	//作成するサウンドアーカイブファイル名
		static LPCTSTR	m_archiveDirName;	//アーカイブ作成のため読み込むディレクトリ名
		static LPCTSTR	m_searchCondition;	//アーカイブ作成のため読み込むファイル名条件
		static LPCTSTR	m_archiveDirName_SE;	//アーカイブ作成のため読み込むディレクトリ名
		static LPCTSTR	m_searchCondition_SE;	//アーカイブ作成のため読み込むファイル名条件
		//--------------------------------------------------


		//サウンドデータ
		s3d::Array < s3d::Audio >	ma_sound;


		DWORD		m_nBGM { 0 };	//BGM読込個数
		DWORD		m_nSE { 0 };	//SE読込個数

		// DSBVOLUME_MAX : 減衰無し(0), DSBVOLUME_MIN : 最小値(-10000) [1/100dB]
		LONG		m_volume { 0 };		//全体ボリューム

		bool		m_bPlay { F };	//すでにプレイ中かどうか

	public:
		void Make ();
		void Open ();

		//------------------------------------------------------------------
		void Play_BGM ( UINT BGM_ID );
		void Play_Loop_BGM ( UINT BGM_ID );
		void Stop_BGM ( UINT BGM_ID );
		void All_Stop ();

		//すでにプレイ中でなければ再生
		//明示的にStop_BGM()を実行すれば再生される
		void If_Play_Loop_BGM ( UINT BGM_ID );

		void Play_SE ( UINT SE_ID );

		//音量設定
		// DSBVOLUME_MAX : 減衰無し(0), DSBVOLUME_MIN : 最小値(-10000) [1/100dB]
		void SetVolume ( LONG volume ) { m_volume = volume; }

	private:

		//条件のファイル数え上げ
		UINT CountFileNum ( LPCTSTR condition );

		//作成
		void _Make ( HANDLE hWriteFile, LPCTSTR dirname, LPCTSTR condition );
	};

	//外部利用定義
	#define		SOUND	SoundArchiver::Inst()


}	//namespace GAME

