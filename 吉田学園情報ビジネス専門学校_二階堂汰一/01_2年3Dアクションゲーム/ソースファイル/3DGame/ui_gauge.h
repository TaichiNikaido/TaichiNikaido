//=============================================================================
//
// UI�̃Q�[�W [ui_gauge.h]
// Author : ��K������
//
//=============================================================================
#ifndef _UI_GAUGE_H_
#define _UI_GAUGE_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CGauge
{
public:
	CGauge();
	~CGauge();
	static HRESULT TextureLoad(void);
	static void TextureUnload(void);
	static CGauge * Create(D3DXVECTOR3 Position,D3DXVECTOR3 Size,D3DXCOLOR Color);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPosition(D3DXVECTOR3 Position) { m_Position = Position; }
	void SetSize(D3DXVECTOR3 Size) { m_Size = Size; }
	void SetColor(D3DXCOLOR Color) { m_Color = Color; }
	void SetMaxValue(int nMaxValue) { m_nMaxValue = nMaxValue; }
	void SetValue(int nValue) { m_nValue = nValue; }
private:
	static LPDIRECT3DTEXTURE9 m_pTexture;		//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//���_�o�b�t�@�̃|�C���^
	D3DXVECTOR3 m_Position;						//�ʒu
	D3DXVECTOR3 m_Size;							//�T�C�Y
	D3DXCOLOR m_Color;							//�F
	int m_nMaxValue;							//�l�̍ő�l
	int m_nValue;								//�l
};
#endif