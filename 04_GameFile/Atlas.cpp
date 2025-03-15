//=================================================================================================
//
//	Atlasソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Atlas.h"

namespace FS = std::filesystem;


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	Atlas::Atlas ()
	{
	}

	Atlas::Atlas ( const Atlas & rhs )
	{
		m_aryCmprs = rhs.m_aryCmprs;
	}

	Atlas::~Atlas ()
	{
	}

	void Atlas::Copy ( const Atlas & rhs )
	{
		m_aryCmprs = rhs.m_aryCmprs;
	}

	void Atlas::Do ()
	{
	}

	void Atlas::Write ()
	{
	}

	//イメージファイル群を格納したディレクトリから作成
	void Atlas::Make( FS::path dir )
	{
		//ファイル列挙
		for ( const auto& entry : FS::directory_iterator ( dir ) )
		{
			s3d::Image img ( Unicode::Widen ( entry.path().string() ) );

			P_Compress cmprs = std::make_shared < Compress > ();
			cmprs->Do ( img );

			//データを保存
			m_aryCmprs.push_back ( cmprs );
		}
	}

	//C#からバイナリで.png形式をまとめた.imgファイルから作成
	void Atlas::Conversion ( s3d::String filepath )
	{
		//ファイル存在確認
		if ( ! FS::exists  ( filepath.str() ) ) { return; }

		//バイナリリーダ
		s3d::BinaryReader br { filepath };
		if ( not br ) { throw s3d::Error { filepath }; }

		//ファイル数
		uint32 filenum = 0;
		br.read ( filenum );

		//データクリア
		m_aryCmprs.clear ();
		m_aryCmprs.resize ( filenum );


		for ( uint32 nf = 0; nf < filenum; ++ nf )
		{
			//名前
			byte namesize = 0;
			br.read ( namesize );

			UP_BYTE buf = std::make_unique < byte [] > ( namesize );
			for ( uint32 i = 0; i < namesize; ++ i )
			{
				br.read ( buf[i] );
			}
			std::string name ( (char*)buf.get(), namesize );

			s3d::String s3dStr = s3d::Unicode::FromUTF8 ( name );
			s3d::Logger << s3dStr << U"\n";

			//サイズ
			uint32 imgsize = 0;
			br.read ( imgsize );

			UP_BYTE bufImg = std::make_unique < byte [] > ( imgsize );
			br.read ( bufImg.get(), imgsize );

			//メモリ上の.pngからImageに変換
			s3d::MemoryReader mr ( bufImg.get(), imgsize );
			s3d::Image img { std::move ( mr ), s3d::ImageFormat::PNG };

			//ImageをCompress
			P_Compress pCmprs = std::make_shared < Compress > ();
			m_aryCmprs [ nf ] = pCmprs;
			m_aryCmprs [ nf ]->Do ( img );
			s3d::Logger << nf << U"\n";
		}

	}


	P_Tx Atlas::GetpTx ()
	{
		P_Tx ptx;
		if ( m_aryCmprs.size () > 0 )
		{
			return m_aryCmprs[0]->Tx_Thawing();
		}
		return ptx;
	}

	PAP_Tx Atlas::GetpapTx ()
	{
		PAP_Tx paptx = std::make_shared < AP_Tx > ();
		paptx->resize ( m_aryCmprs.size() );

		size_t index = 0;
		for ( P_Compress p : m_aryCmprs )
		{
			(*paptx) [ index ++ ] = p->Tx_Thawing ();	//空白をチェックして解凍
		}
		return paptx;
	}


	//---------------------------------------------

	void Srl_Atlas::Save ( const Atlas & atls )
	{
		(void)atls;

		//バイナリ書出
		s3d::Serializer < BinaryWriter > sbw ( FILE_NAME );


		//test
		s3d::String str = U"serial_test";
		sbw ( str );

#if 0
		int i = 123;
		sbw ( i );

		GameScore gameScore;
		sbw ( gameScore );
		
#endif // 0

//		Atlas atls;
//		sbw ( atls );
	}


	void Srl_Atlas::Load ( Atlas & atls )
	{
		(void)atls;


		//バイナリ読込
		s3d::Deserializer < BinaryReader > sbr ( FILE_NAME );


		//test
		s3d::String str = U"";
		sbr ( str );


//		Atlas atls;
//		sbr ( atls );
	}


}	//namespace GAME
