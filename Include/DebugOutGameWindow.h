//=================================================================================================
//
// ゲーム画面へのデバッグテキスト表示
//		ゲーム画面への頂点を用いたテキスト表示
//		DebugTextNum = 15までのインデックスを指定
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Define.h"
#include "02_GameGraphic.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME 
{

	constexpr size_t DBGOUT_WND_N = 10;		//表示行数


	class DebugOutGameWindow;
	using DBGO_WND = DebugOutGameWindow;
	using P_DBG_WND = std::unique_ptr < DBGO_WND >;


	// ゲーム画面へのデバッグテキスト表示
	class DebugOutGameWindow
	{
	//--------------------------------------------------
	//シングルトンパターン
	private:
		static P_DBG_WND	m_inst;
		DebugOutGameWindow ();
		DebugOutGameWindow ( const DBGO_WND & rhs ) = delete;
	public:
		~DebugOutGameWindow ();
		static void Create() { if ( ! m_inst ) { m_inst = P_DBG_WND ( new DBGO_WND () ); } }
		static P_DBG_WND & Inst() { return m_inst; }
	//--------------------------------------------------

	private:
		s3d::Array < P_GrpStr >		ma_str { DBGOUT_WND_N };

	public:
		void Load ();
		void Draw ();

		void DebugOutf ( uint32 index, s3d::String str );


		void On ();
		void Off ();

		//====================================================
		//基本情報
	private:
		//Base_DebugOut		m_frame;
		P_GrpStr		m_frame;

	public:
		//固定表示 : 稼働時間[F]
		void DebugOutWnd_Frame ( UINT frame );
#if 0

	private:

	public:
		//定数
		enum Const_DebugOutGameWindow
		{
			DebugTextNum = 15,
			DebugVertexNum = 32,
		};
	private:
		//デバッグ表示配列
		TX			m_texture[DebugTextNum];	//テクスチャ
		Vx_Rect		m_vertex[DebugTextNum];		//頂点処理オブジェクト
		tstring		m_tstr[DebugTextNum];		//文字列

		//デバッグ用固定表示
		ConstDebugOut_ASCII		m_frame;
		ConstDebugOut_ASCII		m_FPS;
		ConstDebugOut_ASCII		m_moveTime;
		ConstDebugOut_ASCII		m_drawTime;
		ConstDebugOut_ASCII		m_sleepTime;

	public:
		void Load ();
		void Rele ();
		void Reset ( D3DDEV d3dDevice );	//再設定
		void DrawVertex ();		//頂点による描画


		//-----------------------------------------------------

		//表示文字列指定
		void SetStr ( UINT index, LPCTSTR lpctstr );
		void SetStr ( UINT index, tstring& tstr );
		void SetStr ( UINT index, UP_TSTR pstr );

		//位置指定
		void SetPos ( UINT index, float x, float y ) { m_vertex[index].SetPos ( x, y ); }

		//画面にテキスト描画する文字列フォーマットを設定
		void DebugOutf ( UINT index, LPCTSTR format, ... );

		//-----------------------------------------------------
		//固定表示 : 稼働時間[F]
		void DebugOutWnd_Frame ( UINT frame );
		//固定表示 : FPS
		void DebugOutWnd_FPS ( UINT FPS );
		//固定表示 : 休眠時間[ms]
		void DebugOutWnd_SleepTime ( float sleepTile );
		//固定表示 : 動作時間[ms]
		void DebugOutWnd_MoveTime ( float moveTime );
		//固定表示 : 描画時間[ms]
		void DebugOutWnd_DrawTime ( float drawTime );

		//-----------------------------------------------------
		//非表示
//		void Off ();

		void Off ();
		void On ();

	private:
		void DebugOutWnd ( UP_TSTR up_tstr, VP_VxRct& vpVpRct );
#endif // 0

	};


//シングルトンアクセス用
#define DBGOUT_WND		DBGO_WND::Inst
#define DBGOUT_WND_F	DBGO_WND::Inst()->DebugOutf
#define DBGOUT_WND_OFF	DBGO_WND::Inst()->Off
#define DBGOUT_WND_ON	DBGO_WND::Inst()->On



}	//namespace GAME


