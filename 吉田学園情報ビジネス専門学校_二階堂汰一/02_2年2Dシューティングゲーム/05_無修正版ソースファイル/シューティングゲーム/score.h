//=============================================================================
//
// score���� [score.h]
// Author : ��K������
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "scene.h"
#include "number.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SCORE_SIZE_WIDTH 25		//�X�R�A�̕��̃T�C�Y
#define SCORE_SIZE_HEIGHT 25	//�X�R�A�̏c�̃T�C�Y
#define ADDSCORE_ITEM 500		//�A�C�e���ɂ���ĉ��Z�����X�R�A�l

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CScore :public CScene
{
public:
	CScore(int nPriority = 5);
	~CScore();
	static CScore * Create(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight);
	HRESULT Init(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void AddScore(int nValue);
	void SubScore(int nValue);
	void SetScore(int nScore);
private:
	CNumber *m_apNumber[MAX_NUMBER];
	int m_nScore;	//�X�R�A
};
#endif