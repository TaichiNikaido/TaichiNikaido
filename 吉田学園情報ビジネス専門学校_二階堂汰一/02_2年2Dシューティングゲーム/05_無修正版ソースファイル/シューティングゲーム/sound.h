//=============================================================================
//
// 音 [sound.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include <xaudio2.h>
//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CSound
{
public:
	//*****************************************************************************
	// サウンドファイル
	//*****************************************************************************
	typedef enum
	{
		SOUND_LABEL_SE_SHOT = 0,		// 弾発射音
		SOUND_LABEL_SE_EXPLOSION,	// 爆発音
		SOUND_LABEL_BGM01,
		SOUND_LABEL_DRAGON,
		SOUND_LABEL_BREATHE,
		SOUND_LABEL_LVUP,
		SOUND_LABEL_CHARGE,
		SOUND_LABEL_TITLE,
		SOUND_LABEL_NAME,
		SOUND_LABEL_RESULT,
		SOUND_LABEL_RANKING,
		SOUND_LABEL_BOMBEXPLOSION,
		SOUND_LABEL_ENTER,
		SOUND_LABEL_TUTORIAL,
		SOUND_LABEL_MAX
	} SOUND_LABEL;
	//SOUND_LABEL_SE_HIT,			// ヒット音
	//SOUND_LABEL_BGM000 = 0,		// BGM0
	//SOUND_LABEL_BGM001,			// BGM1
	//SOUND_LABEL_BGM002,			// BGM2

	CSound();
	~CSound();
	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);

private:
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
	//*****************************************************************************
	// パラメータ構造体定義
	//*****************************************************************************
	typedef struct
	{
		char *pFilename;	// ファイル名
		int nCntLoop;		// ループカウント
	} PARAM;
	IXAudio2 *m_pXAudio2;								// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *m_pMasteringVoice;			// マスターボイス
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// ソースボイス
	BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// オーディオデータサイズ
	static PARAM m_aParam[SOUND_LABEL_MAX];
};
#endif