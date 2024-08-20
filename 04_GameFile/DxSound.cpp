//=================================================================================================
//
// DirectSound �̎���
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// �w�b�_�t�@�C���̃C���N���[�h
//-------------------------------------------------------------------------------------------------
#include "DxSound.h"

//-------------------------------------------------------------------------------------------------
// ��`
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//-------------------------------------------------------------------------------------------------
	//	�T�E���h�o�b�t�@�|�C���^
	//-------------------------------------------------------------------------------------------------
	void LPDxSoundBuffer::SetSoundBuffer ( LPDIRECTSOUND lpDxSound, DSBUFFERDESC* pDesc, char* pData )
	{
		UINT i = 0;

		//�T�E���h�o�b�t�@�̍쐬
		HRESULT hr = lpDxSound->CreateSoundBuffer ( pDesc, &( m_vpSB [ i ] ), nullptr );
		if ( FAILED ( hr ) ) { DXTRACE ( hr, _T ( "�T�E���h�o�b�t�@�̍쐬�Ɏ��s\n" ) ); return; }

		//�T�E���h�o�b�t�@��Wave�f�[�^��������
		LPVOID lpvWrite = 0;
		DWORD dwLength = 0;
		if ( DS_OK == m_vpSB [ i ]->Lock ( 0, 0, &lpvWrite, &dwLength, nullptr, nullptr, DSBLOCK_ENTIREBUFFER ) )
		{
			memcpy ( lpvWrite, pData, dwLength );
			m_vpSB [ i ]->Unlock ( lpvWrite, dwLength, nullptr, 0 );
		}
	}

	void LPDxSoundBuffer::SetSoundBufferEx ( UINT nBuf, LPDIRECTSOUND lpDxSound, DSBUFFERDESC* pDesc, char* pData )
	{
		//�o�b�t�@�����w��
		m_vpSB.resize ( nBuf );

		for ( UINT i = 0; i < nBuf; ++i )
		{
			//�T�E���h�o�b�t�@�̍쐬
			HRESULT hr = lpDxSound->CreateSoundBuffer ( pDesc, &( m_vpSB [ i ] ), nullptr );
			if ( FAILED ( hr ) ) { DXTRACE ( hr, _T ( "�T�E���h�o�b�t�@�̍쐬�Ɏ��s\n" ) ); return; }

			//�T�E���h�o�b�t�@��Wave�f�[�^��������
			LPVOID lpvWrite = 0;
			DWORD dwLength = 0;
			if ( DS_OK == m_vpSB [ i ]->Lock ( 0, 0, &lpvWrite, &dwLength, nullptr, nullptr, DSBLOCK_ENTIREBUFFER ) )
			{
				memcpy ( lpvWrite, pData, dwLength );
				m_vpSB [ i ]->Unlock ( lpvWrite, dwLength, nullptr, 0 );
			}
		}
	}

	void LPDxSoundBuffer::Play ( DWORD dwReserved1, DWORD dwPriority, DWORD dwFlags )
	{
		m_vpSB[m_count]->SetCurrentPosition ( 0 );

		//�{�����[����ʏ�ɐݒ�
//		m_vol = DSBVOLUME_MAX;

		m_vpSB[m_count]->SetVolume ( m_vol );

		//�Đ�
		m_vpSB[m_count]->Play ( dwReserved1, dwPriority, dwFlags );

		//�J�E���g���P�ǉ�
		//�A���ŌĂ΂ꂽ�Ƃ������Đ�
		if ( m_vpSB.size () == ++ m_count ) { m_count = 0; }
	}

	void LPDxSoundBuffer::Stop ()
	{
//		m_stop = true;
		for ( auto p : m_vpSB )
		{
			p->Stop (); 
		}
		m_stop = false; 
	}

	void LPDxSoundBuffer::Move ()
	{
#if 0
		if ( m_stop )
		{
			//�t�F�[�h�A�E�g
			// DSBVOLUME_MAX : ��������(0), DSBVOLUME_MIN : �ŏ��l(-10000)
			m_vol -= 50;
			if ( DSBVOLUME_MIN > m_vol )
			{
				for ( auto p : m_vpSB )
				{
					p->Stop (); 
				}
				m_stop = false; 
			}
			else
			{
				for ( auto p : m_vpSB ) { p->SetVolume ( m_vol ); }
			}
		}
#endif // 0
	}

	//------------------------------------------
	//	Static����
	//------------------------------------------
	// �V���O���g���I�u�W�F�N�g
	DxSound::P_DxSound		DxSound::m_inst;

	//-------------------------------------------------------------------------------------------------
	//	�R���X�g���N�^
	//-------------------------------------------------------------------------------------------------
	DxSound::DxSound () //: m_lpDS(nullptr)	//, m_lpDSBuffer(nullptr)
	{
	}

	//-------------------------------------------------------------------------------------------------
	//	�f�X�g���N�^
	//-------------------------------------------------------------------------------------------------
	DxSound::~DxSound ()
	{
#if 0

		if( m_lpDS ) { m_lpDS->Release (); m_lpDS = nullptr; }

		UINT size = m_vLPDSB.size ();
		for ( UINT i = 0; i < size; ++i )
		{
			delete m_vLPDSB[i];
		}
		m_vLPDSB.clear ();

#endif // 0
	}
	
	//-------------------------------------------------------------------------------------------------
	//	DirectSound ������
	//-------------------------------------------------------------------------------------------------
	void DxSound::Load ()
	{
		//DirectSound�̍쐬
		DirectSoundCreate ( nullptr, &m_lpDS, nullptr );
		m_lpDS->SetCooperativeLevel ( HWnd::Get(), DSSCL_PRIORITY );

#if	0
		//Wave�t�@�C���I�[�v��
		WAVEFORMATEX waveFormatEx;
		char* pWaveData = nullptr;
		DWORD waveSize = 0;
		if ( ! OpenWave ( _T("01_Panel de Pon (J)_001_spc.wav"), waveFormatEx, &pWaveData, waveSize ) ) return;
		
		//�T�E���h�f�o�C�X�쐬
		//�o�b�t�@�̃p�����[�^�w��
		DSBUFFERDESC desc;
		desc.dwSize = sizeof ( DSBUFFERDESC );
		desc.dwFlags = 0;
		desc.dwBufferBytes = waveSize;
		desc.dwReserved = 0;
		desc.lpwfxFormat = &waveFormatEx;
		desc.guid3DAlgorithm = GUID_NULL;

		//�Z�J���_���o�b�t�@�̍쐬
		m_lpDS->CreateSoundBuffer ( &desc, &m_lpDSBuffer, nullptr );
//		ptmpBuf->QueryInterface ( IID_IDirectSoundBuffer8, (void**)&m_lpDSBuffer );
//		ptmpBuf->Release ();
		if ( m_lpDSBuffer == nullptr ) { m_lpDS->Release (); return; }

		//�Z�J���_���o�b�t�@��Wave�f�[�^��������
		LPVOID lpvWrite = 0;
		DWORD dwLength = 0;
		if ( DS_OK == m_lpDSBuffer->Lock ( 0, 0, &lpvWrite, &dwLength, nullptr, nullptr, DSBLOCK_ENTIREBUFFER ) )
		{
			memcpy ( lpvWrite, pWaveData, dwLength );
			m_lpDSBuffer->Unlock ( lpvWrite, dwLength, nullptr, 0 );
		}
		delete[] pWaveData;		//���f�[�^�̉��
		pWaveData = nullptr;
#endif	//0
	}

	void DxSound::Move ()
	{
#if 0
		for ( auto p : m_vLPDSB )
		{
			p->Move ();
		}
#endif // 0
		for ( PP_DXSNDBUF p : mvpp_DXSNDBUF )
		{
			p->Move ();
		}
	}

	//�t�@�C���p�X����
	//Wave�t�@�C���I�[�v��
	bool DxSound::OpenWaveFromFile ( LPTSTR filepath, WAVEFORMATEX& waveFormatEx, char** ppData, DWORD& dataSize )
	{
		if ( nullptr == filepath ) { return false; }
		
		//�}���`���f�B�AI/O���	
		MMIOINFO mmioInfo;
		memset ( &mmioInfo, 0, sizeof ( MMIOINFO ) );

		MMIO_Open ( filepath, mmioInfo, waveFormatEx, ppData, dataSize );

#if 0
		//Wave�t�@�C���I�[�v��
		HMMIO hMmio = mmioOpen ( filepath, &mmioInfo, MMIO_READ );
		if ( ! hMmio ) { return false; }
		
#if 0
		//RIFF�`�����N����
		MMRESULT mmResult;
		MMCKINFO riffChunk;
		riffChunk.fccType = mmioFOURCC ( 'W', 'A', 'V', 'E' );
		mmResult = mmioDescend ( hMmio, &riffChunk, nullptr, MMIO_FINDRIFF );
		if ( mmResult != MMSYSERR_NOERROR ) { mmioClose ( hMmio, 0 ); return false; }

		//�t�H�[�}�b�g�`�����N����
		MMCKINFO formatChunk;
		formatChunk.ckid = mmioFOURCC ( 'f', 'm', 't', ' ' );
		mmResult = mmioDescend ( hMmio, &formatChunk, &riffChunk, MMIO_FINDCHUNK );
		if ( mmResult != MMSYSERR_NOERROR ) { mmioClose ( hMmio, 0 ); return false; }
	
		DWORD fmsize = formatChunk.cksize;
		DWORD size = mmioRead ( hMmio, (HPSTR)&waveFormatEx, fmsize );
		if ( size != fmsize ) { mmioClose ( hMmio, 0 ); return false; }

		mmioAscend ( hMmio, &formatChunk, 0 );

		//�f�[�^�`�����N����
		MMCKINFO dataChunk;
		dataChunk.ckid = mmioFOURCC ( 'd', 'a','t','a' );
		mmResult = mmioDescend ( hMmio, &dataChunk, &riffChunk, MMIO_FINDCHUNK );
		if ( mmResult != MMSYSERR_NOERROR ) { mmioClose ( hMmio, 0 ); return false; }

		*ppData = new char[ dataChunk.cksize ];
		size = mmioRead ( hMmio, (HPSTR)*ppData, dataChunk.cksize );
		dataSize = size;
#endif // 0

		MMIOtoMem ( hMmio, waveFormatEx, ppData, dataSize );

		//�n���h���N���[�Y
		mmioClose ( hMmio, 0 );
#endif // 0

		return true;
	}


	//�������ォ��Wave�t�@�C�����I�[�v��
	//	HPSTR pchBuffer : �Ǎ��o�b�t�@
	//	LONG memSize : �Ǎ��o�b�t�@�T�C�Y
	bool DxSound::OpenWaveFromMem ( HPSTR pchBuffer, LONG memSize, WAVEFORMATEX& waveFormatEx, char** ppData, DWORD& dataSize )
	{
		if ( pchBuffer == nullptr ) { return false; }

		MMIOINFO mmioInfo = { 0 };		//�}���`���f�B�AI/O���
		mmioInfo.pchBuffer = pchBuffer;		//�Ǎ��o�b�t�@�A�h���X
		mmioInfo.fccIOProc = FOURCC_MEM;	//4�����R�[�h�F����������Ǎ�
		mmioInfo.cchBuffer = memSize;		//�o�b�t�@�̃������T�C�Y

		MMIO_Open ( nullptr, mmioInfo, waveFormatEx, ppData, dataSize );

#if 0
		//Wave�t�@�C���I�[�v��
		//�}���`���f�B�AI/O�n���h��
		HMMIO hMmio = mmioOpen ( nullptr, &mmioInfo, MMIO_READ );
		if ( ! hMmio ) { return false; }

#if 0
		//RIFF�`�����N����
		MMRESULT mmResult;
		MMCKINFO riffChunk;
		riffChunk.fccType = mmioFOURCC ( 'W', 'A', 'V', 'E' );
		mmResult = mmioDescend ( hMmio, &riffChunk, nullptr, MMIO_FINDRIFF );
		if ( mmResult != MMSYSERR_NOERROR ) { mmioClose ( hMmio, 0 ); return false; }

		//�t�H�[�}�b�g�`�����N����
		MMCKINFO formatChunk;
		formatChunk.ckid = mmioFOURCC ( 'f', 'm', 't', ' ' );
		mmResult = mmioDescend ( hMmio, &formatChunk, &riffChunk, MMIO_FINDCHUNK );
		if ( mmResult != MMSYSERR_NOERROR ) { mmioClose ( hMmio, 0 ); return false; }

		DWORD fmsize = formatChunk.cksize;
		DWORD size = mmioRead ( hMmio, (HPSTR)&waveFormatEx, fmsize );
		if ( size != fmsize ) { mmioClose ( hMmio, 0 ); return false; }

		mmioAscend ( hMmio, &formatChunk, 0 );

		//�f�[�^�`�����N����
		MMCKINFO dataChunk;
		dataChunk.ckid = mmioFOURCC ( 'd', 'a', 't', 'a' );
		mmResult = mmioDescend ( hMmio, &dataChunk, &riffChunk, MMIO_FINDCHUNK );
		if ( mmResult != MMSYSERR_NOERROR ) { mmioClose ( hMmio, 0 ); return false; }

		*ppData = new char [ dataChunk.cksize ];
		size = mmioRead ( hMmio, (HPSTR)*ppData, dataChunk.cksize );
		dataSize = size;
#endif // 0
		MMIOtoMem ( hMmio, waveFormatEx, ppData, dataSize );

		//�n���h���N���[�Y
		mmioClose ( hMmio, 0 );
#endif // 0

		return true;
	}

	bool DxSound::MMIO_Open ( LPCTSTR filepath, MMIOINFO& mmioInfo, WAVEFORMATEX& waveFormatEx, char** ppData, DWORD& dataSize )
	{
		//Wave�t�@�C���I�[�v��
		//�}���`���f�B�AI/O�n���h��
		HMMIO hMmio = mmioOpen ( nullptr, &mmioInfo, MMIO_READ );
		if ( ! hMmio ) { return false; }

		MMIOtoMem ( hMmio, waveFormatEx, ppData, dataSize );

		//�n���h���N���[�Y
		mmioClose ( hMmio, 0 );

		return true;
	}

	bool DxSound::MMIOtoMem ( HMMIO hMmio, WAVEFORMATEX& waveFormatEx, char** ppData, DWORD& dataSize )
	{
		//RIFF�`�����N����
		MMRESULT mmResult;
		MMCKINFO riffChunk;
		riffChunk.fccType = mmioFOURCC ( 'W', 'A', 'V', 'E' );
		mmResult = mmioDescend ( hMmio, &riffChunk, nullptr, MMIO_FINDRIFF );
		if ( mmResult != MMSYSERR_NOERROR ) { mmioClose ( hMmio, 0 ); return false; }

		//�t�H�[�}�b�g�`�����N����
		MMCKINFO formatChunk;
		formatChunk.ckid = mmioFOURCC ( 'f', 'm', 't', ' ' );
		mmResult = mmioDescend ( hMmio, &formatChunk, &riffChunk, MMIO_FINDCHUNK );
		if ( mmResult != MMSYSERR_NOERROR ) { mmioClose ( hMmio, 0 ); return false; }

		
		DWORD fmsize = formatChunk.cksize;
		DWORD size = mmioRead ( hMmio, (HPSTR)&waveFormatEx, fmsize );
		if ( size != fmsize ) { mmioClose ( hMmio, 0 ); return false; }

		mmioAscend ( hMmio, &formatChunk, 0 );

		//�f�[�^�`�����N����
		MMCKINFO dataChunk;
		dataChunk.ckid = mmioFOURCC ( 'd', 'a', 't', 'a' );
		mmResult = mmioDescend ( hMmio, &dataChunk, &riffChunk, MMIO_FINDCHUNK );
		if ( mmResult != MMSYSERR_NOERROR ) { mmioClose ( hMmio, 0 ); return false; }

		*ppData = new char [ dataChunk.cksize ];
		size = mmioRead ( hMmio, (HPSTR)*ppData, dataChunk.cksize );
		dataSize = size;

		//�n���h���N���[�Y
		mmioClose ( hMmio, 0 );

		return true;
	}


#if 0
	void DxSound::LoadWaveFromFile ( LPTSTR filepath )
	{
		//Wave�t�@�C���I�[�v��
		WAVEFORMATEX waveFormatEx;
		char* pWaveData = nullptr;
		DWORD waveSize = 0;
		if ( ! OpenWave ( filepath, waveFormatEx, & pWaveData, waveSize ) ) { return; }

		//�o�b�t�@�̃p�����[�^�w��
		DSBUFFERDESC desc;
		desc.dwSize = sizeof ( DSBUFFERDESC );
		desc.dwFlags = 0;
		desc.dwBufferBytes = waveSize;
		desc.dwReserved = 0;
		desc.lpwfxFormat = &waveFormatEx;
		desc.guid3DAlgorithm = GUID_NULL;

		//�T�E���h�o�b�t�@�̍쐬
		LPDIRECTSOUNDBUFFER lpDSBuffer = nullptr;
		HRESULT hr = m_lpDS->CreateSoundBuffer ( &desc, &lpDSBuffer, nullptr );
		if ( FAILED ( hr ) ) { DXTRACE(hr, _T("")); return; }

		//�T�E���h�o�b�t�@��Wave�f�[�^��������
		LPVOID lpvWrite = 0;
		DWORD dwLength = 0;
		if ( DS_OK == lpDSBuffer->Lock ( 0, 0, &lpvWrite, &dwLength, nullptr, nullptr, DSBLOCK_ENTIREBUFFER ) )
		{
			memcpy ( lpvWrite, pWaveData, dwLength );
			lpDSBuffer->Unlock ( lpvWrite, dwLength, nullptr, 0 );
		}
		delete[] pWaveData;		//���f�[�^�̉��
		pWaveData = nullptr;

		//�z��ɒǉ�
		m_vecSoundBuffer.push_back ( lpDSBuffer );
	}
#endif // 0

	void DxSound::LoadWaveFromFile ( LPTSTR filepath )
	{
		//Wave�t�@�C���I�[�v��
		WAVEFORMATEX waveFormatEx;
		char* pWaveData = nullptr;
		DWORD waveSize = 0;
		if ( ! OpenWaveFromFile ( filepath, waveFormatEx, &pWaveData, waveSize ) ) { return; }

		//�o�b�t�@�̃p�����[�^�w��
		DSBUFFERDESC desc;
		desc.dwSize = sizeof ( DSBUFFERDESC );
		desc.dwFlags = 0;
		desc.dwBufferBytes = waveSize;
		desc.dwReserved = 0;
		desc.lpwfxFormat = &waveFormatEx;
		desc.guid3DAlgorithm = GUID_NULL;

		//�T�E���h�o�b�t�@�̍쐬
		//�T�E���h�o�b�t�@��Wave�f�[�^��������
//		LPDxSoundBuffer* pLPDSB = new LPDxSoundBuffer;
		PP_DXSNDBUF pLPDSB = std::make_shared < LPDxSoundBuffer > ();
		pLPDSB->SetSoundBuffer ( m_lpDS, &desc, pWaveData );

		delete[] pWaveData;		//���f�[�^�̉��
		pWaveData = nullptr;

		//�z��ɒǉ�
//		m_vLPDSB.push_back ( pLPDSB );
		mvpp_DXSNDBUF.push_back ( pLPDSB );
	}

	void DxSound::LoadWaveFromMem ( HPSTR pchBuffer, LONG memSize )
	{
		//Wave�t�@�C���I�[�v��
		WAVEFORMATEX waveFormatEx;
		char* pWaveData = nullptr;
		DWORD waveSize = 0;
		if ( ! OpenWaveFromMem ( pchBuffer, memSize, waveFormatEx, &pWaveData, waveSize ) ) { return; }

		//�o�b�t�@�̃p�����[�^�w��
		DSBUFFERDESC desc;
		desc.dwSize = sizeof ( DSBUFFERDESC );
		desc.dwFlags = DSBCAPS_CTRLVOLUME;		//�{�����[���ύX
		desc.dwBufferBytes = waveSize;
		desc.dwReserved = 0;
		desc.lpwfxFormat = &waveFormatEx;
		desc.guid3DAlgorithm = GUID_NULL;

		//�T�E���h�o�b�t�@�̍쐬
		//�T�E���h�o�b�t�@��Wave�f�[�^��������
		PP_DXSNDBUF pLPDSB = std::make_shared < LPDxSoundBuffer > ();
		pLPDSB->SetSoundBuffer ( m_lpDS, &desc, pWaveData );

		delete [] pWaveData;		//���f�[�^�̉��
		pWaveData = nullptr;

		//�z��ɒǉ�
		mvpp_DXSNDBUF.push_back ( pLPDSB );
	}

	void DxSound::LoadWaveFromMemEx ( UINT nBuf, HPSTR pchBuffer, LONG memSize, LONG vol )
	{
		//Wave�t�@�C���I�[�v��
		WAVEFORMATEX waveFormatEx;
		char* pWaveData = nullptr;
		DWORD waveSize = 0;
		if ( ! OpenWaveFromMem ( pchBuffer, memSize, waveFormatEx, &pWaveData, waveSize ) ) { return; }

		//�o�b�t�@�̃p�����[�^�w��
		DSBUFFERDESC desc;
		desc.dwSize = sizeof ( DSBUFFERDESC );
		desc.dwFlags = DSBCAPS_CTRLVOLUME;		//�{�����[���ύX
		desc.dwBufferBytes = waveSize;
		desc.dwReserved = 0;
		desc.lpwfxFormat = &waveFormatEx;
		desc.guid3DAlgorithm = GUID_NULL;

		//�T�E���h�o�b�t�@�̍쐬
		//�T�E���h�o�b�t�@��Wave�f�[�^��������
		PP_DXSNDBUF pLPDSB = std::make_shared < LPDxSoundBuffer > ();
		pLPDSB->SetSoundBufferEx ( nBuf, m_lpDS, &desc, pWaveData );
		pLPDSB->SetVolume ( vol );

		delete [] pWaveData;		//���f�[�^�̉��
		pWaveData = nullptr;

		//�z��ɒǉ�
		mvpp_DXSNDBUF.push_back ( pLPDSB );
	}




	void DxSound::Play ( UINT id )
	{
#if 0
		if ( id >= m_vLPDSB.size () ) { return; }
		m_vLPDSB[id]->Play ( 0, 0, 0 );
#endif // 0
		if ( id >= mvpp_DXSNDBUF.size () ) { return; }
		mvpp_DXSNDBUF [ id ]->Play ( 0, 0, 0 );
	}
	
	void DxSound::PlayLoop ( UINT id )
	{
#if 0
		if ( id >= m_vLPDSB.size () ) { return; }
		m_vLPDSB[id]->Play ( 0, 0, DSBPLAY_LOOPING );
#endif // 0
		if ( id >= mvpp_DXSNDBUF.size () ) { return; }
		mvpp_DXSNDBUF [ id ]->Play ( 0, 0, DSBPLAY_LOOPING );
	}

#if 0
	void DxSound::Play ( UINT id )
	{
		if ( id >= m_vecSoundBuffer.size () ) { return; }

		m_vecSoundBuffer[id]->Play ( 0, 0, 0 );
	}
#endif // 0

	void DxSound::Stop ( UINT id )
	{
#if 0
		if ( id >= m_vLPDSB.size () ) { return; }
		m_vLPDSB[id]->Stop ();
#endif // 0
		if ( id >= mvpp_DXSNDBUF.size () ) { return; }
		mvpp_DXSNDBUF [ id ]->Stop ();
	}
	

}	//namespace GAME

