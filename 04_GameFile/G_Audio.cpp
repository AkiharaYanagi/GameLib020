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
				std::cout << path << std::endl;
				//アセットに登録
				const std::u32string str32 = path.u32string();
				LPCUSTR str = str32.c_str();
				s3d::AudioAsset::Register(str, str);
//				s3d::AudioAsset::LoadAsync(str);
				list.push_back ( str32 );
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


}	//namespace GAME

