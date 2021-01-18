//=============================================================================
//
// ���@�̕\������ [own.h]
// Author : ��K������
//
//=============================================================================
#ifndef _OWN_H_
#define _OWN_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_OWN "data/TEXTURE/Battleship.png"	//���@�̃e�N�X�`���̕ۑ���
#define MAX_OWN 5	//���@�̍ő吔
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class COwn
{
public:
	COwn();
	~COwn();
	static HRESULT Load(void);
	static void Unload(void);
	static COwn * Create(D3DXVECTOR3 pos,float SizeWidth,float SizeHeight);
	HRESULT Init(D3DXVECTOR3 pos,float SizeWidth,float SizeHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetOwn(int nAlpha);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//�o�b�t�@
	int m_nPatternAnim;	//�A�j���p�^�[��
};
#endif