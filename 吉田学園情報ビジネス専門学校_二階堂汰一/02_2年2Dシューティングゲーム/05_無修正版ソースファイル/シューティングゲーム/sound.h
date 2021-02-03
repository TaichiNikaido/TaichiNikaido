//=============================================================================
//
// �� [sound.h]
// Author : ��K������
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_
//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include <xaudio2.h>
//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CSound
{
public:
	//*****************************************************************************
	// �T�E���h�t�@�C��
	//*****************************************************************************
	typedef enum
	{
		SOUND_LABEL_SE_SHOT = 0,
		SOUND_LABEL_SE_EXPLOSION,
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
	// �p�����[�^�\���̒�`
	//*****************************************************************************
	typedef struct
	{
		char *pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g
	} PARAM;
	IXAudio2 *m_pXAudio2;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice;			// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// �\�[�X�{�C�X
	BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^�T�C�Y
	static PARAM m_aParam[SOUND_LABEL_MAX];
};
#endif