//=================================================================================================
//
// StopWatch ヘッダファイル
//		Siv3D時間計測
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "GameTask.h"
#include "Define_Siv3D.h"
#include "DebugOutGameWindow.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class StopWatch
	{
		s3d::Stopwatch			m_sw;
		s3d::Array < double >	m_time;
		s3d::Array < double >	m_ave;		//平均も次の表示まで保持する
		uint32_t				m_count { 0 };

	public:
		StopWatch ();
		StopWatch ( const StopWatch & rhs ) = delete;
		~StopWatch ();

		void Start ();
		void ReStart () { m_sw.restart (); }

		void Disp ( DBGOUT_LINE index, LPCUSTR str );
		void Lap ( DBGOUT_LINE index, LPCUSTR str );

		void Count ();

		double GetAve ( DBGOUT_LINE index ) const { return m_ave [ index ]; }
	};

	using P_StopWatch = std::unique_ptr < StopWatch >;


}	//namespace GAME


