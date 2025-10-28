//=================================================================================================
//
// グローバル　オーディオ
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイル　インクルード
//-------------------------------------------------------------------------------------------------
#include "G_Audio.h"
namespace fs = std::filesystem;


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//--------------------------------------------------
	//シングルトンパターン	static実体
	P_G_Audio	G_Audio::m_inst = nullptr;
	//--------------------------------------------------

    const fs::path BGM_Dir = "Audio\\BGM";
    const fs::path SE_Dir = "Audio\\SE";
    const fs::path VC_Dir = "Audio\\VC";


	//=======================================================================
	//	Rect 
	//=======================================================================
	G_Audio::G_Audio ()
	{
	}

	G_Audio::~G_Audio ()
	{
	}

	void G_Audio::Load ()
	{
		//指定ディレクトリ内のファイル列挙してアセット化
		//ファイル名でアクセス

		try
		{
			//BGM
			LoadDir ( BGM_Dir, m_bgm_list );

			//SE
			LoadDir ( SE_Dir, m_se_list );

			//VC
			LoadDir ( VC_Dir, m_vc_list );

		}
		catch (const fs::filesystem_error& e)
		{
			std::cerr << "エラー: " << e.what() << std::endl;
		}
	}

	void G_Audio::LoadDir ( const std::filesystem::path & dirPath, s3d::Array<s3d::String> & list  )
	{
		//指定ディレクトリ内のファイル列挙してアセット化
		//ファイル名でアクセス
		if (fs::exists(dirPath) && fs::is_directory(dirPath))
		{
			for (const auto& entry : fs::directory_iterator(dirPath))
			{
				fs::path path = entry.path();
				fs::path name = entry.path().filename();
				std::cout << path << std::endl;
				//アセットに登録
				const std::u32string str32_path = path.u32string();
				const std::u32string str32_name = name.u32string();
				s3d::AudioAsset::Register( str32_name.c_str(), str32_path.c_str() );
//				s3d::AudioAsset::LoadAsync(str);
				list.push_back ( str32_name );
			}
		}
		else
		{
			std::cerr << "指定されたパスは存在しないか、ディレクトリではありません。" << std::endl;
		}
	}


	void G_Audio::HandLoad ()
	{
		for ( const s3d::String & bgm_name : m_bgm_list )
		{
			s3d::AudioAsset::LoadAsync ( bgm_name );
		}
		for ( const s3d::String & se_name : m_se_list )
		{
			s3d::AudioAsset::LoadAsync ( se_name );
		}
		for ( const s3d::String & vc_name : m_vc_list )
		{
			s3d::AudioAsset::LoadAsync ( vc_name );
		}
	}


	void G_Audio::CheckAudio ()
	{
		for ( const s3d::String & bgm_name : m_bgm_list )
		{
			s3d::AudioAsset::IsReady ( bgm_name ) ?
				s3d::Print ( U"[OK] " + bgm_name ) :
				s3d::Print ( U"[NG] " + bgm_name );
		}

		int32 count_se = 0;
		for ( const s3d::String & se_name : m_se_list )
		{
			if ( s3d::AudioAsset::IsReady ( se_name ) )
			{
				++ count_se;
			}
		}
		s3d::Print ( U"SE: {}/{}"_fmt( count_se, m_se_list.size () ) );


		int32 count_vc = 0;
		for ( const s3d::String & vc_name : m_vc_list )
		{
			if ( s3d::AudioAsset::IsReady ( vc_name ) )
			{
				++ count_vc;
			}
		}
		s3d::Print ( U"VC: {}/{}"_fmt( count_vc, m_vc_list.size () ) );
	}


	void G_Audio::AllWait ()
	{
		for ( const s3d::String & bgm_name : m_bgm_list )
		{
			s3d::AudioAsset::Wait ( bgm_name );
		}
		for ( const s3d::String & se_name : m_se_list )
		{
			s3d::AudioAsset::Wait ( se_name );
		}
		for ( const s3d::String & vc_name : m_vc_list )
		{
			s3d::AudioAsset::Wait ( vc_name );
		}
	}


	void G_Audio::SetVolume ( double vol )
	{
		m_bgmVolume = vol;
		m_seVolume =vol;
		m_vcVolume = vol;
	}


	//------------------------------------------------------------
	void G_Audio::PlayBGM ( LPCUSTR BGM_NAME )
	{
		const s3d::Audio & aud = s3d::AudioAsset ( BGM_NAME );
		aud.setVolume ( m_bgmVolume );
		aud.setLoop ( F );
		aud.play ();
	}

	void G_Audio::PlayLoopBGM ( LPCUSTR BGM_NAME )
	{
		const s3d::Audio & aud = s3d::AudioAsset ( BGM_NAME );
		aud.setVolume ( m_bgmVolume );
		aud.setLoop ( T );
		aud.play ();
	}

	void G_Audio::StopBGM ( LPCUSTR BGM_NAME )
	{
		const s3d::Audio & aud = s3d::AudioAsset ( BGM_NAME );
		aud.stop ();
	}

	void G_Audio::Stop_All_BGM ()
	{
		for ( const s3d::String & bgm_name : m_bgm_list )
		{
			s3d::AudioAsset( bgm_name ).stop ();
		}
	}

	bool G_Audio::IsPlayBGM ( LPCUSTR BGM_NAME )
	{
		const s3d::Audio & aud = s3d::AudioAsset ( BGM_NAME );
		return aud.isPlaying ();
	}

	//------------------------------------------------------------
	void G_Audio::PlaySE ( LPCUSTR SE_NAME )
	{
		const s3d::Audio & aud = s3d::AudioAsset ( SE_NAME );
		aud.setVolume ( m_seVolume );
		aud.setLoop ( F );
		aud.play ();
	}

	void G_Audio::Play_OneShotSE ( LPCUSTR SE_NAME )
	{
		const s3d::Audio & aud = s3d::AudioAsset ( SE_NAME );
		aud.setVolume ( m_seVolume );
		aud.setLoop ( F );
		aud.playOneShot ();
	}

	void G_Audio::StopSE ( LPCUSTR SE_NAME )
	{
		const s3d::Audio & aud = s3d::AudioAsset ( SE_NAME );
		aud.stop ();
	}

	void G_Audio::Stop_All_SE ()
	{
		for ( const s3d::String & se_name : m_vc_list )
		{
			s3d::AudioAsset ( se_name ).stop ();
		}
	}

	//------------------------------------------------------------
	void G_Audio::PlayVC ( LPCUSTR VC_NAME )
	{
		const s3d::Audio & aud = s3d::AudioAsset ( VC_NAME );
		aud.setVolume ( m_seVolume );
		aud.setLoop ( F );
		aud.play ();
	}

	void G_Audio::Play_OneShotVC ( LPCUSTR VC_NAME )
	{
		const s3d::Audio & aud = s3d::AudioAsset ( VC_NAME );
		aud.setVolume ( m_seVolume );
		aud.setLoop ( F );
		aud.playOneShot ();
	}

	void G_Audio::StopVC ( LPCUSTR VC_NAME )
	{
		const s3d::Audio & aud = s3d::AudioAsset ( VC_NAME );
		aud.stop ();
	}

	void G_Audio::Stop_All_VC ()
	{
		for ( const s3d::String & vc_name : m_vc_list )
		{
			s3d::AudioAsset ( vc_name ).stop ();
		}
	}

	//------------------------------------------------------------


}	//namespace GAME

