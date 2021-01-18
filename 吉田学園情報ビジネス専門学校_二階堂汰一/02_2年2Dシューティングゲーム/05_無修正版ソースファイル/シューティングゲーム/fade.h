//=============================================================================
//
// �t�F�[�h���� [fade.h]
// Author : ��K������
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FADE_RATE 0.1f

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CFade
{
public:
	typedef enum
	{
		FADE_NONE = -1,
		FADE_IN,
		FADE_OUT,
		FADE_MAX
	}FADE;
	CFade();
	~CFade();
	static CFade * Create(D3DXVECTOR3 pos, int sizeX, int sizeY, CManager::MODE mode);
	HRESULT Init(D3DXVECTOR3 pos,int sizeX, int sizeY, CManager::MODE mode);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//�o�b�t�@
	D3DXVECTOR3 m_pos;
	int m_nSizeX;
	int m_nSizeY;
	FADE m_fade;	//�t�F�[�h
	CManager::MODE m_ModeNext;
	D3DXCOLOR m_colorFade;	//�J���[
};
#endif