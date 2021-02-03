//=============================================================================
//
// ���e��UI���� [ownui.h]
// Author : ��K������
//
//=============================================================================
#ifndef _BOMBUI_H_
#define _BOMBUI_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "bombtexture.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BOMBUI_SIZE_WIDTH 30		//���@��UI�̕��̃T�C�Y
#define BOMBUI_SIZE_HEIGHT 30		//���@��UI�̍����̃T�C�Y

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CBombUI :public CScene
{
public:
	CBombUI(int nPriority = 5);
	~CBombUI();
	static CBombUI * Create(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight);
	HRESULT Init(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetBombUI(int nBomb);
	void AddBombUI(int nValue);
	void SubBombUI(int nValue);
private:
	CBombTexture *m_apBombUI[PLAYER_MAX_BOMB];	//�{���̃e�N�X�`���ւ̃|�C���^
	int m_nBombUI;	//���e��UI
};
#endif