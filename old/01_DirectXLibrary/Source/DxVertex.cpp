//=================================================================================================
//
// DirectX�ɂ����钸�_�̒�`
//
//=================================================================================================
#include "DxVertex.h"

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	DxVertex::DxVertex () 
		: m_lpVertexBuffer ( nullptr ), m_update ( true ), m_color ( 0xffffffff ), m_z ( Z_DEFALT )
		, m_valid ( T )
	{
	}

	//���_�����w�肵���R���X�g���N�^
	DxVertex::DxVertex ( UINT vertexNum )
		: m_lpVertexBuffer ( nullptr ), m_update ( true ), m_color ( 0xffffffff ), m_z ( Z_DEFALT )
		, m_valid ( T )
	{
		SetVertexNum ( vertexNum );
	}

	DxVertex::~DxVertex ()
	{
		Clear ();
		Rele ();
	}

	//���_����ݒ�
	void DxVertex::SetVertexNum ( UINT vertexNum )
	{
		//���Ɏw�肵�Ă���ꍇ�������Ȃ�
		if ( 0 < m_vVx.size () ) { return; }

		//���_�̐��ŏ�����
		m_vVx.resize ( vertexNum );
		UINT i = 0;
		for ( VX v : m_vVx )
		{
			SetVertex ( i ++, 0, 0, m_z, 1.f, m_color, 0, 0 );
		}
	}

	//���_�����Đݒ�
	void DxVertex::ResetVertexNum ( UINT vertexNum )
	{
		Clear ();
		SetVertexNum ( vertexNum );
	}

	//���_��������
	void DxVertex::Clear ()
	{
		m_vVx.clear ();
	}

	void DxVertex::Load ()
	{
		CreateVertexBuffer ();

		//����̍X�V�����Ȃ��Ƃ��ALoad()��ɂP�x�����s��
		if ( ! m_update )
		{
			ApplyPos ();
			WriteVertexBuffer ();
		}
	}

	void DxVertex::Rele ()
	{
		RELEASE ( m_lpVertexBuffer );
	}

	void DxVertex::Reset ()
	{
		Rele ();
		Load ();
	}

	void DxVertex::Move ()
	{
		//�ʒu�̍X�V
		if ( m_update ) 
		{
			ApplyPos (); 
			WriteVertexBuffer ();
		}
	}

	void DxVertex::DrawVertex ( TX lpTexture )
	{
		//�L���t���O
		if ( ! m_valid ) { return; }

		//�T�C�Y���O�̂Ƃ��͉������Ȃ�
		if ( m_vVx.empty () ) { return; }

		//���_�`��
		Dx3D::instance ()->DrawVertex
		(
			lpTexture,
			0,
			m_lpVertexBuffer,
			0,
			sizeof ( VX ),
			FVF_CUSTOM,
			D3DPT_TRIANGLESTRIP,
			0,
			(UINT)m_vVx.size () - 2
		);
	}

	void DxVertex::DrawVertexMultiple ( TX lpTexture )
	{
		//�L���t���O
		if ( ! m_valid ) { return; }

		//�T�C�Y���O�̂Ƃ��͉������Ȃ�
		if ( m_vVx.empty () ) { return; }

		//���_�`��
		Dx3D::instance ()->DrawVertexMultiple
		(
			lpTexture,
			0,
			m_lpVertexBuffer,
			0,
			sizeof ( VX ),
			FVF_CUSTOM,
			D3DPT_TRIANGLESTRIP,
			0,
			(UINT)m_vVx.size () - 2
		);
	}

	//���_�o�b�t�@���쐬
	void DxVertex::CreateVertexBuffer ()
	{
		//�T�C�Y���O�̂Ƃ��͉������Ȃ�
		if ( m_vVx.empty () ) { return; }

		try
		{
			HRESULT hr = Dx3D::instance()->GetDevice()->CreateVertexBuffer 
			( 
				sizeof ( VX ) * (UINT)m_vVx.size (),
				D3DUSAGE_WRITEONLY, 
				FVF_CUSTOM, 
				D3DPOOL_MANAGED, 
				&m_lpVertexBuffer, 
				nullptr
			);
			if ( FAILED ( hr ) ) { throw _T("���_�o�b�t�@�̍쐬�G���["); }

			//���_�o�b�t�@�ɏ�������
			WriteVertexBuffer ();
		}
		catch ( LPCTSTR str )
		{
			OutputDebugString ( str );
			////TRACE_F ( str );
			Rele ();
			return;
		}
	}

	//���_�o�b�t�@�ɒ��_������
	void DxVertex::WriteVertexBuffer ()
	{
		//�T�C�Y���O�̂Ƃ��͉������Ȃ�
		if ( m_vVx.empty () ) { return; }

		//�������ȑO�͉������Ȃ�
		if ( nullptr == m_lpVertexBuffer ) { return; }

		try 
		{
			//���_���̏���
			void* pData = nullptr;
			HRESULT hr;

			hr= m_lpVertexBuffer->Lock ( 0, sizeof ( VX ) * (UINT)m_vVx.size (), (void**)&pData, 0 );
			if ( FAILED ( hr ) ) { throw _T("���_�o�b�t�@�̃��b�N"); }

			memcpy ( pData, m_vVx.data(), sizeof ( VX ) * m_vVx.size () );

			hr = m_lpVertexBuffer->Unlock ();
			if ( FAILED ( hr ) ) { throw _T ("���_�o�b�t�@�̃A�����b�N"); }
		}
		catch ( LPCTSTR str )
		{
			TRACE_F ( str );
			Rele ();
			return;
		}
	}

	void DxVertex::SetVertex ( VX& vertex, float x, float y, float z, float rhw, DWORD color, float u, float v )
	{
		vertex.x = x;
		vertex.y = y;
		vertex.z = z;
		vertex.rhw = rhw;
		vertex.color = color;
		vertex.u = u;
		vertex.v = v;
	}

	void DxVertex::SetVertex ( UINT index, float x, float y, float z, float rhw, DWORD color, float u, float v )
	{
		assert ( index < m_vVx.size () );
		SetVertex ( m_vVx[index], x, y, z, rhw, color, u, v );
	}

	void DxVertex::SetPos ( UINT index, float x, float y, float z )
	{
		assert ( index < m_vVx.size () );
		m_vVx[index].x = x;
		m_vVx[index].y = y;
		m_vVx[index].z = z;
	}

	void DxVertex::SetPosXY ( UINT index, float x, float y )
	{
		assert ( index < m_vVx.size () );
		m_vVx[index].x = x;
		m_vVx[index].y = y;
	}

	void DxVertex::SetAllZ ( float z )
	{
		m_z = z;
		UINT i = 0;
		for ( VX vx : m_vVx ) { m_vVx[i++].z = z; }
	}

	void DxVertex::SetAllColor ( DWORD color )
	{
		m_color = color;
		UINT i = 0;
		for ( VX vx : m_vVx ) { m_vVx[i++].color = color; }
	}

	void DxVertex::SetColor ( UINT index, DWORD color )
	{
		assert ( index < m_vVx.size () );
		m_vVx[index].color = color;
	}

	void DxVertex::SetRhw ( UINT index, float rhw )
	{
		assert ( index < m_vVx.size () );
		m_vVx[index].rhw = rhw;
	}

	void DxVertex::SetTexturePos ( UINT index, float u, float v )
	{
		assert ( index < m_vVx.size () );
		m_vVx[index].u = u;
		m_vVx[index].v = v;
	}



//-------------------------------------------------------------------------------------------------
	DxParticularVertex::DxParticularVertex ( UINT vertexNum ) : DxVertex ( vertexNum )
	{
		m_pos.x = 0;
		m_pos.y = 0;
	}


//-------------------------------------------------------------------------------------------------
	DxVertexRect::DxVertexRect () : DxParticularVertex ( 4 )
	{
		//���_�̏�����
		D3DXVECTOR2 pos = GetPos ();
		m_w = 100;
		m_h = 100;

		SetVertex ( 0, pos.x + m_w, pos.y      , 0.f, 1.f, 0xffffffff, 1.f, 0.f ); 
		SetVertex ( 1, pos.x + m_w, pos.y + m_h, 0.f, 1.f, 0xffffffff, 1.f, 1.f );
		SetVertex ( 2, pos.x      , pos.y      , 0.f, 1.f, 0xffffffff, 0.f, 0.f ); 
		SetVertex ( 3, pos.x      , pos.y + m_h, 0.f, 1.f, 0xffffffff, 0.f, 1.f ); 
	}

	DxVertexRect::~DxVertexRect ()
	{
	}

	void DxVertexRect::SetTxUVWH ( float u, float v, float w, float h )
	{
		//@info		Tx��uv���W�� [ 0.0f ~ 1.0f ] �Ő��K��

		SetTexturePos ( 0, u + w, v		);
		SetTexturePos ( 1, u + w, v + h );
		SetTexturePos ( 2, u	, v		);
		SetTexturePos ( 3, u	, v + h );
	}

	//�ʒu�ݒ�
	void DxVertexRect::ApplyPos ()
	{
		//�ʒu�̍X�V
		D3DXVECTOR2 pos = GetPos ();
		DxVertex::SetPosXY ( 0, pos.x + m_w, pos.y       ); 
		DxVertex::SetPosXY ( 1, pos.x + m_w, pos.y + m_h );
		DxVertex::SetPosXY ( 2, pos.x      , pos.y       ); 
		DxVertex::SetPosXY ( 3, pos.x      , pos.y + m_h ); 
	}


//-------------------------------------------------------------------------------------------------
	DxVertexFree4::DxVertexFree4 () : DxVertex ( 4 )
	{
		//���_�̏�����
		SetVertex ( 0, m_vec[0].x, m_vec[0].y, 0.f, 1.f, 0xffffffff, 1.f, 0.f ); 
		SetVertex ( 1, m_vec[1].x, m_vec[1].y, 0.f, 1.f, 0xffffffff, 1.f, 1.f );
		SetVertex ( 2, m_vec[2].x, m_vec[2].y, 0.f, 1.f, 0xffffffff, 0.f, 0.f ); 
		SetVertex ( 3, m_vec[3].x, m_vec[3].y, 0.f, 1.f, 0xffffffff, 0.f, 1.f ); 
	}

	DxVertexFree4::~DxVertexFree4 ()
	{
	}

	//�ʒu�ݒ�
	void DxVertexFree4::ApplyPos ()
	{
		//�ʒu�̍X�V
		DxVertex::SetPosXY ( 0, m_vec[0].x, m_vec[0].y ); 
		DxVertex::SetPosXY ( 1, m_vec[1].x, m_vec[1].y );
		DxVertex::SetPosXY ( 2, m_vec[2].x, m_vec[2].y ); 
		DxVertex::SetPosXY ( 3, m_vec[3].x, m_vec[3].y ); 
	}


//-------------------------------------------------------------------------------------------------
	DxVertexLine::DxVertexLine () : DxVertex ( 4 )
	{
		m_w = 10.f;

		ApplyPos ();
		SetUpdate ( false );	//Move()����ApplyPos()���s��Ȃ�
	}

	DxVertexLine::~DxVertexLine ()
	{
	}

	//�ʒu�ݒ�
	void DxVertexLine::ApplyPos ()
	{
#if	0
		//���_�`�揇�Ԃɂ��A������[0]������悤�ɂ���
		if ( m_vec[0].x < m_vec[1].x )
		{
			D3DXVECTOR2 temp = m_vec[1];
			m_vec[1] = m_vec[0];
			m_vec[0] = temp;
		}
#endif	//0

		//�����̂Ȃ��p�x
		float theta = atan2 ( m_vec[0].y - m_vec[1].y, m_vec[0].x - m_vec[1].x );
//		float theta = 0.5f;

#if 0
		D3DXVECTOR2 v[4];
		v[0].x = m_vec[0].x + (m_w / 2) * cos ( theta - D3DX_PI / 2 );
		v[0].y = m_vec[0].y + (m_w / 2) * sin ( theta - D3DX_PI / 2 );
		v[1].x = m_vec[0].x + (m_w / 2) * cos ( theta + D3DX_PI / 2 );
		v[1].y = m_vec[0].y + (m_w / 2) * sin ( theta + D3DX_PI / 2 );
		v[2].x = m_vec[1].x + (m_w / 2) * cos ( theta - D3DX_PI / 2 );
		v[2].y = m_vec[1].y + (m_w / 2) * sin ( theta - D3DX_PI / 2 );
		v[3].x = m_vec[1].x + (m_w / 2) * cos ( theta + D3DX_PI / 2 );
		v[3].y = m_vec[1].y + (m_w / 2) * sin ( theta + D3DX_PI / 2 );
#else	//0

		float theta_minus_pi_half = theta - D3DX_PI_HALF;
		float theta_plus_pi_half  = theta + D3DX_PI_HALF;
		float m_w_half = m_w * 0.5f;
		
		float w_cos_minus = m_w_half * cos ( theta_minus_pi_half );
		float w_sin_minus = m_w_half * sin ( theta_minus_pi_half );
		float w_cos_plus  = m_w_half * cos ( theta_plus_pi_half  );
		float w_sin_plus  = m_w_half * sin ( theta_plus_pi_half  );

		VEC2 v[4];
		v[0].x = m_vec[0].x + w_cos_minus;
		v[0].y = m_vec[0].y + w_sin_minus;
		v[1].x = m_vec[0].x + w_cos_plus;
		v[1].y = m_vec[0].y + w_sin_plus;
		v[2].x = m_vec[1].x + w_cos_minus;
		v[2].y = m_vec[1].y + w_sin_minus;
		v[3].x = m_vec[1].x + w_cos_plus;
		v[3].y = m_vec[1].y + w_sin_plus;
#endif	//0

		//�ʒu�̍X�V
		DxVertex::SetPosXY ( 0, v[0].x, v[0].y ); 
		DxVertex::SetPosXY ( 1, v[1].x, v[1].y );
		DxVertex::SetPosXY ( 2, v[2].x, v[2].y ); 
		DxVertex::SetPosXY ( 3, v[3].x, v[3].y ); 

//		DebugOutFile::instance()->DebugOutf ( TEXT("(%lf,%lf),(%lf,%lf),(%lf,%lf),(%lf,%lf)"),
//			v[0].x, v[0].y, v[1].x, v[1].y, v[2].x, v[2].y, v[3].x, v[3].y );
	}


//-------------------------------------------------------------------------------------------------
	DxVertex3::DxVertex3 () : DxParticularVertex ( 3 )
	{
		//���_�̏�����
		VEC2 pos = GetPos ();
		m_w = 10;
		m_rad = 100;

		float x1, y1, x2, y2;
		x1 = pos.x + m_w * cos(m_rad - D3DX_PIBY6);
		y1 = pos.y + m_w * sin(m_rad - D3DX_PIBY6);
		x2 = pos.x + m_w * cos(m_rad + D3DX_PIBY6);
		y2 = pos.y + m_w * sin(m_rad + D3DX_PIBY6);

		SetVertex ( 0, pos.x , pos.y, 0.f, 1.f, 0xffffffff, 0.f, 0.f ); 
		SetVertex ( 1, x1    , y1   , 0.f, 1.f, 0xffffffff, 0.f, 0.f );
		SetVertex ( 2, x2    , y2   , 0.f, 1.f, 0xffffffff, 0.f, 0.f ); 
	}

	DxVertex3::~DxVertex3 ()
	{
	}

	//�ʒu�ݒ�
	void DxVertex3::ApplyPos ()
	{
		//�ʒu�̍X�V
		VEC2 pos = GetPos ();
		float x1, y1, x2, y2;
		x1 = pos.x + m_w * cos(m_rad - D3DX_PIBY6);
		y1 = pos.y + m_w * sin(m_rad - D3DX_PIBY6);
		x2 = pos.x + m_w * cos(m_rad + D3DX_PIBY6);
		y2 = pos.y + m_w * sin(m_rad + D3DX_PIBY6);

		DxVertex::SetPosXY ( 0, pos.x , pos.y ); 
		DxVertex::SetPosXY ( 1, x1    , y1    );
		DxVertex::SetPosXY ( 2, x2    , y2    ); 
	}
//-------------------------------------------------------------------------------------------------


	_DxPoliVertex::_DxPoliVertex () 
	{
		m_w = 10.f;

		//	[�P] �R�_��ݒ肷��
		m_vec[0].x = 100;
		m_vec[0].y = 200;
		m_vec[1].x = 200;
		m_vec[1].y = 100;
		m_vec[2].x = 300;
		m_vec[2].y = 200;

		//���݂̓_�̌���2�{�Œ��_�𐶐�����
		SetVertexNum ( 3 * 2 );
	}

	_DxPoliVertex::~_DxPoliVertex ()
	{
	}

	//�ʒu�ݒ�
	void _DxPoliVertex::ApplyPos ()
	{
		//	[�Q] �S�p�_���Q�ݒ肷��
		D3DXVECTOR2 r[2][4];
		SetRectVec ( r[0], m_vec );
		SetRectVec ( r[1], m_vec + 1 );

		//	[�R] �U���_��ݒ肷��
		D3DXVECTOR2 v[6];
		v[0].x = r[0][0].x;
		v[0].y = r[0][0].y;
		v[1].x = r[0][1].x;
		v[1].y = r[0][1].y;

		//��_
		SetCrossVec ( v[2], r[0][0], r[0][2], r[1][0], r[1][2] );
		SetCrossVec ( v[3], r[0][1], r[0][3], r[1][1], r[1][3] );

		v[4].x = r[1][2].x;
		v[4].y = r[1][2].y;
		v[5].x = r[1][3].x;
		v[5].y = r[1][3].y;

		//�ʒu�̍X�V
		for ( UINT i = 0; i < 6; i++ )
		{
			DxVertex::SetPosXY ( i, v[i].x, v[i].y ); 
		}
	}


	//�Q�_����S�p�_���v�Z����
	//�����F
	//	rectVec[4]		(out) �S�p�_
	//	vec[2]			(in) �n�_�ƏI�_
	void _DxPoliVertex::SetRectVec ( VEC2 rectVec[], VEC2 vec[] ) const
	{
		//�����̂Ȃ��p�x
		float theta = atan2 ( vec[0].y - vec[1].y, vec[0].x - vec[1].x );

		float theta_minus_pi_half = theta - D3DX_PI_HALF;
		float theta_plus_pi_half  = theta + D3DX_PI_HALF;
		float m_w_half = m_w * 0.5f;
		
		float w_cos_minus = m_w_half * cos ( theta_minus_pi_half );
		float w_sin_minus = m_w_half * sin ( theta_minus_pi_half );
		float w_cos_plus  = m_w_half * cos ( theta_plus_pi_half  );
		float w_sin_plus  = m_w_half * sin ( theta_plus_pi_half  );

		rectVec[0].x = vec[0].x + w_cos_minus;
		rectVec[0].y = vec[0].y + w_sin_minus;
		rectVec[1].x = vec[0].x + w_cos_plus;
		rectVec[1].y = vec[0].y + w_sin_plus;
		rectVec[2].x = vec[1].x + w_cos_minus;
		rectVec[2].y = vec[1].y + w_sin_minus;
		rectVec[3].x = vec[1].x + w_cos_plus;
		rectVec[3].y = vec[1].y + w_sin_plus;
	}

	//�Q���������_�����߂�
	//�����F
	//crossVec		(out) ��_
	//vec			(in) (vec0,vec1)��(vec2,vec3)�̂Q����
	void _DxPoliVertex::SetCrossVec ( VEC2& crossVec,
		const VEC2& vec0, const VEC2& vec1,
		const VEC2& vec2, const VEC2& vec3 ) const
	{
		//�����̎�
		float a0 = ( vec1.y - vec0.y ) / ( vec1.x - vec0.x );
		float b0 = ( vec1.x * vec0.y - vec0.x * vec1.y ) / ( vec1.x - vec0.x );
		float a1 = ( vec3.y - vec2.y ) / ( vec3.x - vec2.x );
		float b1 = ( vec3.x * vec2.y - vec2.x * vec3.y ) / ( vec3.x - vec2.x );

		crossVec.x = ( b1 - b0 ) / ( a0 - a1 );
		crossVec.y = ( a0 * b1 - a1 * b0 ) / ( a0 - a1 );
	}


//-------------------------------------------------------------------------------------------------


	DxPoliVertex::DxPoliVertex ()// : m_vec ( nullptr )
	{
		m_w = 10.f;
//		m_numVec = 1;		//�ŏ��̈��

		ApplyPos ();
		SetUpdate ( false );	//Move()����ApplyPos()���s��Ȃ�
	}

	DxPoliVertex::~DxPoliVertex ()
	{
		m_listVec.clear ();
	}

	void DxPoliVertex::Load ()
	{
//		ApplyPos ();

		//���_�o�b�t�@�쐬
//		CreateVertexBuffer ();
		WriteVertexBuffer ();
	}

	void DxPoliVertex::Rele ()
	{
		DxVertex::Rele ();
	}

	void DxPoliVertex::Reset ()
	{
		Rele ();
		DxVertex::Load ();		//Reset���̂�Load���Ă�
	}


	//�_�ݒ�
	void DxPoliVertex::SetVec ( UINT index, const D3DXVECTOR2& vec )
	{
//		assert ( index < m_maxVec );
		ApplyPos ();
	}

	//�_��ǉ�����
	void DxPoliVertex::AddVec ( D3DXVECTOR2& vec )
	{
		m_listVec.push_back ( vec );
//		_ApplyPos ();
		ApplyPos ();
		//VertexBuffer�̉���ƍĐݒ�
		Reset ();
	}

	//�_���폜����
	void DxPoliVertex::DelVec ()
	{
		if ( m_listVec.size () == 0 ) { return; }

		m_listVec.pop_back ();
		ApplyPos ();
		//VertexBuffer�̉���ƍĐݒ�
		Reset ();
	}

	//�_�����ׂč폜����
	void DxPoliVertex::ClearVec ()
	{
		m_listVec.clear ();
		ApplyPos ();
		Reset ();
	}

	//�ʒu�ݒ� ���X�g���p
	void DxPoliVertex::ApplyPos ()
	{
		//�_�̌����擾
		UINT num = (UINT)m_listVec.size ();

		//�_���P�ȉ��̂Ƃ��͉������Ȃ�
		if ( num <= 1 )
		{
			Clear ();	//���_�̏�����
			return; 
		}

		//���_���̍Đݒ�
		//���݂̓_�̌���2�{�Œ��_�𐶐�����
		ResetVertexNum ( num * 2 );

		//�l�p�_���S�~(���|�P�j�Z�o
		VEC2** r = new VEC2* [ num - 1 ];
		VEC2 vec[2];
		L_VEC2::iterator it = m_listVec.begin ();
		for ( UINT i = 0; i < num - 1; ++i )
		{
			r[i] = new D3DXVECTOR2 [ 4 ];
			vec[0] = (*it);
			++it;
			vec[1] = (*it);
			SetRectVec ( r[i], vec );
		}


		//���_���Q���Z�o
		UINT n = 2 * num;		//���_��
		D3DXVECTOR2* v = new D3DXVECTOR2 [ n ];

		v[0].x = r[0][0].x;
		v[0].y = r[0][0].y;
		v[1].x = r[0][1].x;
		v[1].y = r[0][1].y;

		if ( num > 2 )
		{
			//��_
			UINT rd = 0;	//�l�p�_�̓Y����
			for ( UINT i = 2; i < n - 2; i += 2 )
			{
				SetCrossVec ( v[i+0], r[rd][0], r[rd][2], r[rd+1][0], r[rd+1][2] );
				SetCrossVec ( v[i+1], r[rd][1], r[rd][3], r[rd+1][1], r[rd+1][3] );
				rd++;
			}
		}

		v[n-2].x = r[num-2][2].x;
		v[n-2].y = r[num-2][2].y;
		v[n-1].x = r[num-2][3].x;
		v[n-1].y = r[num-2][3].y;

		//�ʒu�̍X�V
		for ( UINT i = 0; i < n; i++ )
		{
			DxVertex::SetPosXY ( i, v[i].x, v[i].y ); 
		}

		//���
		delete[] v;
		for ( UINT i = 0; i < num - 1; i++ )
		{
			delete[] r[i];
		}
		delete[] r;
	}

#if	0
	//�ʒu�ݒ�
	void DxPoliVertex::ApplyPos ()
	{
		//�P�ȉ��͉������Ȃ�
		if ( m_numVec <= 1 ) { return; }

		//�l�p�_���S�~(���|�P�j�Z�o
		D3DXVECTOR2** r = new D3DXVECTOR2* [ m_numVec - 1 ];
		for ( UINT i = 0; i < m_numVec - 1; i++ )
		{
			r[i] = new D3DXVECTOR2 [ 4 ];
			SetRectVec ( r[i], m_vec + i );
		}


		//���_���Q���Z�o
		UINT n = 2 * m_numVec;		//���_��
		D3DXVECTOR2* v = new D3DXVECTOR2 [ n ];

		v[0].x = r[0][0].x;
		v[0].y = r[0][0].y;
		v[1].x = r[0][1].x;
		v[1].y = r[0][1].y;

		if ( m_numVec > 2 )
		{
			//��_
			UINT rd = 0;	//�l�p�_�̓Y����
			for ( UINT i = 2; i < n - 2; i += 2 )
			{
				SetCrossVec ( v[i+0], r[rd][0], r[rd][2], r[rd+1][0], r[rd+1][2] );
				SetCrossVec ( v[i+1], r[rd][1], r[rd][3], r[rd+1][1], r[rd+1][3] );
				rd++;
			}
		}

		v[n-2].x = r[m_numVec-2][2].x;
		v[n-2].y = r[m_numVec-2][2].y;
		v[n-1].x = r[m_numVec-2][3].x;
		v[n-1].y = r[m_numVec-2][3].y;


		//�ʒu�̍X�V
		for ( UINT i = 0; i < n; i++ )
		{
			DxVertex::SetPos ( i, v[i].x, v[i].y, 0 ); 
		}

		//���
		delete[] v;
		for ( UINT i = 0; i < m_numVec - 1; i++ )
		{
			delete[] r[i];
		}
		delete[] r;
	}
#endif	//0


	//�Q�_����S�p�_���v�Z����
	//�����F
	//	rectVec[4]		(out) �S�p�_
	//	vec[2]			(in) �n�_�ƏI�_
	void DxPoliVertex::SetRectVec ( VEC2 rectVec[], VEC2 vec[] ) const
	{
		//�����̂Ȃ��p�x
		float theta = atan2 ( vec[0].y - vec[1].y, vec[0].x - vec[1].x );

		float theta_minus_pi_half = theta - D3DX_PI_HALF;
		float theta_plus_pi_half  = theta + D3DX_PI_HALF;
		float m_w_half = m_w * 0.5f;
		
		float w_cos_minus = m_w_half * cos ( theta_minus_pi_half );
		float w_sin_minus = m_w_half * sin ( theta_minus_pi_half );
		float w_cos_plus  = m_w_half * cos ( theta_plus_pi_half  );
		float w_sin_plus  = m_w_half * sin ( theta_plus_pi_half  );

		rectVec[0].x = vec[0].x + w_cos_minus;
		rectVec[0].y = vec[0].y + w_sin_minus;
		rectVec[1].x = vec[0].x + w_cos_plus;
		rectVec[1].y = vec[0].y + w_sin_plus;
		rectVec[2].x = vec[1].x + w_cos_minus;
		rectVec[2].y = vec[1].y + w_sin_minus;
		rectVec[3].x = vec[1].x + w_cos_plus;
		rectVec[3].y = vec[1].y + w_sin_plus;
	}

	//�Q���������_�����߂�
	//�����F
	//crossVec		(out) ��_
	//vec			(in) (vec0,vec1)��(vec2,vec3)�̂Q����
	void DxPoliVertex::SetCrossVec ( VEC2& crossVec,
		const VEC2& vec0, const VEC2& vec1,
		const VEC2& vec2, const VEC2& vec3 ) const
	{
		//�����̎�
		float a0 = ( vec1.y - vec0.y ) / ( vec1.x - vec0.x );
		float b0 = ( vec1.x * vec0.y - vec0.x * vec1.y ) / ( vec1.x - vec0.x );
		float a1 = ( vec3.y - vec2.y ) / ( vec3.x - vec2.x );
		float b1 = ( vec3.x * vec2.y - vec2.x * vec3.y ) / ( vec3.x - vec2.x );

		crossVec.x = ( b1 - b0 ) / ( a0 - a1 );
		crossVec.y = ( a0 * b1 - a1 * b0 ) / ( a0 - a1 );
	}


//-------------------------------------------------------------------------------------------------


}	//namespace GAME

