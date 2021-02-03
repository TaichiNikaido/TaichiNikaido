//=============================================================================
//
// ���e�̃e�N�X�`������ [bombtexture.h]
// Author : ��K������
//
//=============================================================================
#ifndef _BOMBTEXTURE_H_
#define _BOMBTEXTURE_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_BOMB "data/TEXTURE/bomb.png"	//�{���̃e�N�X�`���̕ۑ���

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CBombTexture
{
public:
	CBombTexture();
	~CBombTexture();
	static HRESULT Load(void);
	static void Unload(void);
	static CBombTexture * Create(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight);
	HRESULT Init(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetBombTexture(int nAlpha);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//�o�b�t�@
	int m_nPatternAnim;						//�A�j���p�^�[��
};
#endif