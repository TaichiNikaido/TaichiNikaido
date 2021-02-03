//=============================================================================
//
// number���� [number.h]
// Author : ��K������
//
//=============================================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_NUMBER "data/TEXTURE/number000.png"
#define MAX_NUMBER 10
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CNumber
{
public:
	CNumber();
	~CNumber();
	static HRESULT Load(void);
	static void Unload(void);
	static CNumber * Create(D3DXVECTOR3 pos, float SizeWidth,float SizeHeight);
	HRESULT Init(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetNumber(int nNumber);
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//�o�b�t�@
	int m_nPatternAnim;						//�A�j���p�^�[��
};
#endif