//=============================================================================
//
// �Q�[�W�̘g [gaugeflame.h]
// Author : ��K������
//
//=============================================================================
#ifndef _FLAME_H_
#define _FLAME_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "Base/scene2d.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CGaugeFlame :public CScene2d
{
public:
	CGaugeFlame(int nPriority = PRIORITY_POLYGON2D);
	~CGaugeFlame();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetAnimationPattern(int nAnimationPattern) { m_nAnimationPattern = nAnimationPattern; }
	void SetAnimationValue(float fAnimationValue) { m_fAnimationValue = fAnimationValue; }
	void SetScriptPass(char * pScriptPass) { m_apScriptPass[0] = pScriptPass; }
private:
	int m_nAnimationPattern;				//�A�j���[�V�����p�^�[��
	float m_fAnimationValue;				//�A�j���[�V�����̒l
	char * m_apScriptPass[MAX_PASS_LETTER];	//�X�N���v�g�p�X
};
#endif