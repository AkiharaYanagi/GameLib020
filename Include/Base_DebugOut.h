//=================================================================================================
//
//	基本情報表示
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Define.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class Base_DebugOut
	{
//		s3d::Font	m_font { 20 };
		bool		m_valid { T };
		VEC2		m_pos { 0, 0 };		//基準位置
		s3d::String m_str { U"Base" };		

#if 0
		VP_VxRct	mvp_vx;		//頂点集合(矩形)
		static const UINT	SIZE;
		tstring		m_tstr;		//表示文字列
		std::string		m_str;		//char形式で保存
#endif // 0

	public:
		Base_DebugOut ();
		Base_DebugOut ( const Base_DebugOut & rhs ) = delete;
		~Base_DebugOut ();

		void Draw ();

		void SetPos ( VEC2 v );
		void SetStr ( s3d::String str );
		void SetValid ( bool b ) { m_valid = b; }

		void ToggleValid () { m_valid = ! m_valid; }
		void Off () { m_valid = F; }
		void On () { m_valid = T; }
	};


}	//namespace GAME

