//=================================================================================================
//
// Siv3d利用 Sound クラス
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Define_Siv3D.h"		//Siv3D定義


//-------------------------------------------------------------------------------------------------
// ライブラリのリンク
//-------------------------------------------------------------------------------------------------
#pragma comment (lib, "dsound.lib")
#pragma comment (lib, "winmm.lib")

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//サウンド
	class GameSound
	{
		s3d::Audio		m_audio;		//サウンド
		UINT			m_count { 0 };	//内部カウント
		bool			m_stop { F };	//停止フラグ
		LONG			m_vol { 0 };	//ボリューム

	public:
		GameSound () {}
		GameSound ( const GameSound & rhs ) = delete;		//コピー禁止
		~GameSound () {}

		void Make ( s3d::FilePath filepath );

		void SetVolume ( LONG vol ) { m_vol = vol; }
		void Play ();

#if 0
		void SetSoundBuffer ( LPDIRECTSOUND lpDxSound, DSBUFFERDESC* pDesc, char* pData );
		void SetSoundBufferEx ( UINT nBuf, LPDIRECTSOUND lpDxSound, DSBUFFERDESC* pDesc, char* pData );

		
		//再生
		//	dwReserved1		:０のみ
		//	dwPriority		:優先度
		//	dwFlags			:フラグ [ループ] DSBPLAY_LOOPING, 
		void Play ( DWORD dwReserved1, DWORD dwPriority, DWORD dwFlags );
		void Stop ();

		void Move ();	//毎回の更新
#endif // 0
	};

//	using PP_DXSNDBUF = std::shared_ptr < LPDxSoundBuffer >;


	//------------------------------------------
	//	SivSound
	//------------------------------------------
	class SivSound
	{
		//--------------------------------------------------
		//シングルトンパターン
	private:
		using P_SivSound = std::unique_ptr < SivSound >;
		static P_SivSound	m_inst;
		SivSound () {}
		SivSound ( const SivSound & obj ) = delete;
	public:
		~SivSound () {}
		static void Create () { if ( ! m_inst ) { m_inst = P_SivSound ( new SivSound () ); } }
		static P_SivSound & Inst () { return m_inst; }
		//--------------------------------------------------
	
	private:

	public:

		//メモリ上からGameSoundを作成
	
	};

#if 0
	{
	//--------------------------------------------------
	//シングルトンパターン
	private:
		using P_DxSound = std::unique_ptr < DxSound >;
		static P_DxSound	m_inst;
		DxSound ();
		DxSound ( const DxSound & obj ) = delete;
	public:
		~DxSound ();
		static void Create () { if ( ! m_inst ) { m_inst = P_DxSound ( new DxSound () ); } }
		static P_DxSound & instance () { return m_inst; }
	//--------------------------------------------------

	private:

		LPDIRECTSOUND			m_lpDS;			//DirectSoundインターフェース
//		IDirectSoundBuffer8*	m_lpDSBuffer;	//サウンドバッファ
//		LPDIRECTSOUNDBUFFER		m_lpDSBuffer;	//サウンドバッファ
//		IDirectSoundBuffer*		m_lpBuf;		//セカンダリバッファ

		//サウンドバッファを使用する数だけ確保する
//		vector < LPDIRECTSOUNDBUFFER >		m_vecSoundBuffer;

		//同時再生用に１種類に複数確保
//		vector < LPDxSoundBuffer * >	m_vLPDSB;
		vector < PP_DXSNDBUF >	mvpp_DXSNDBUF;

	public:
		void Load ();
		void Move ();

		//ファイルパスから
		//Waveファイルオープン関数
		bool OpenWaveFromFile ( LPTSTR filepath, WAVEFORMATEX& waveFormatEx, char** ppData, DWORD& dataSize );

		//メモリ上からWaveファイルをオープン
		//	HPSTR pchBuffer : 読込バッファ
		//	LONG memSize : 読込バッファサイズ
		bool OpenWaveFromMem ( HPSTR pchBuffer, LONG memSize, WAVEFORMATEX& waveFormatEx, char** ppData, DWORD& dataSize );
		
		//グローバルで事前に複数waveファイルを読込しておく
		void LoadWaveFromFile ( LPTSTR filepath );
		void LoadWaveFromMem ( HPSTR pchBuffer, LONG memSize );

		//同時再生バッファ数を指定
		void LoadWaveFromMemEx ( UINT nBuf, HPSTR pchBuffer, LONG memSize, LONG vol );


		//使用するときはIDを指定する
		void Play ( UINT id );
		void PlayLoop ( UINT id );
		void Stop ( UINT id );

	private:
		bool MMIO_Open ( LPCTSTR filepath, MMIOINFO& mmioInfo, WAVEFORMATEX& waveFormatEx, char** ppData, DWORD& dataSize );
		bool MMIOtoMem ( HMMIO hMmio, WAVEFORMATEX& waveFormatEx, char** ppData, DWORD& dataSize );
	};
#endif // 0



}	//namespace GAME

