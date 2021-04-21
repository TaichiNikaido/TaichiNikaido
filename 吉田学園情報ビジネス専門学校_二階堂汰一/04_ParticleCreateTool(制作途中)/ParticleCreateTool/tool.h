//=============================================================================
//
// �c�[�� [tool.h]
// Author : ��K������
//
//=============================================================================
#ifndef _TOOL_H_
#define _TOOL_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CTool
{
public:
	CTool();
	~CTool();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	D3DXVECTOR3 GetPosition(void) { return m_Position; }
	D3DXVECTOR3 GetRotation(void) { return m_Rotation; }
	D3DXVECTOR3 GetSize(void) { return m_Size; }
	D3DXVECTOR3 GetMove(void) { return m_Move; }
	D3DXCOLOR GetColor(void) { return m_Color; }
	int GetLife(void) { return m_nLife; }
	float GetScale(void) { return m_fScale; }
	float GetAngle(void) { return m_fAngle; }
	bool GetbScale(void) { return m_bScale; }
	bool GetbLife(void) { return m_bLife; }
private:
	void TextSave(void);
	void TextLoad(void);
	D3DXVECTOR3 m_Position;				//�ʒu
	D3DXVECTOR3 m_Rotation;				//����
	D3DXVECTOR3 m_Size;					//�T�C�Y
	D3DXVECTOR3 m_Move;					//�ړ���
	D3DXCOLOR m_Color;					//�F
	int m_nLife;						//�̗�
	int m_nCreateInterval;				//�����Ԋu
	int m_nCreateTime;					//��������
	float m_fScale;						//�g�k
	float m_fAngle;						//�p�x
	char m_aSaveTextName[MAX_TEXT];		//�Z�[�u����e�L�X�g�̖��O
	char m_aLoadTextName[MAX_TEXT];		//���[�h����e�L�X�g�̖��O
	bool m_bWindow;						//�E�B���h�E���g�p���Ă��邩
	bool m_bScale;						//�g�k���g�p���邩
	bool m_bLife;						//�̗͂��g�p���邩
};
#endif
