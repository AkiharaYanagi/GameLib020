//=================================================================================================
//
// GameSound ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "GameSound.h"
#include "_SoundArchiver.h"

//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//------------------------------------------
	//	Static実体
	//------------------------------------------
	// シングルトンオブジェクト
	GameSound::P_GameSound		GameSound::m_inst;



	//------------------------------------------
	//	定数
	//------------------------------------------
	CSIVSTR	GameSound::ACV_FILENAME_BGM		= U"Bgm.dat";	
	CSIVSTR	GameSound::ACV_DIRNAME_BGM		= U"Bgm/";
	CSIVSTR	GameSound::ACV_CND_BGM			= U"Bgm/*.wav";	

	CSIVSTR	GameSound::ACV_FILENAME_SE		= U"Se.dat";
	CSIVSTR	GameSound::ACV_DIRNAME_SE		= U"Se/";	
	CSIVSTR	GameSound::ACV_CND_SE			= U"Se/*.wav";

	CSIVSTR	GameSound::ACV_FILENAME_VC		= U"Vc.dat";
	CSIVSTR	GameSound::ACV_DIRNAME_VC		= U"Vc/";
	CSIVSTR	GameSound::ACV_CND_VC			= U"Vc/*.wav";


	//------------------------------------------
	GameSound::GameSound ()
	{
	}

	GameSound::~GameSound ()
	{
	}


	void GameSound::Load ()
	{
		m_bgm.SetName ( ACV_FILENAME_BGM, ACV_DIRNAME_BGM, ACV_CND_BGM );
		m_se.SetName ( ACV_FILENAME_SE, ACV_DIRNAME_SE, ACV_CND_SE );
		m_vc.SetName ( ACV_FILENAME_VC, ACV_DIRNAME_VC, ACV_CND_VC );
	}

	void GameSound::Make ()
	{
		m_bgm.Make ();
		m_se.Make ();
		m_vc.Make ();
	}

	void GameSound::Open ()
	{
		m_bgm.Open ();
		m_se.Open ();
		m_vc.Open ();
	}

	void GameSound::SetVolume ( double vol )
	{
		m_bgm.SetVolume ( vol );
		m_se.SetVolume ( vol );
		m_vc.SetVolume ( vol );
	}


	void GameSound::Test ()
	{
		m_bgm.Test (  );
		m_se.Test (  );
		m_vc.Test (  );
	}


}	//namespace GAME

