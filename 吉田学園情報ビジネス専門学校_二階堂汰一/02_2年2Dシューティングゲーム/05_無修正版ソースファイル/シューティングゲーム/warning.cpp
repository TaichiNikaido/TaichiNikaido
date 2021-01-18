//=============================================================================
//
//	�댯�n�я��� [warning.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "scene.h"
#include "scene2d.h"
#include "renderer.h"
#include "manager.h"
#include "bullet.h"
#include "warning.h"

LPDIRECT3DTEXTURE9 CWarning::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CWarning::CWarning()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//���_���W
		m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
	m_fWidth = 0;		//��
	m_fHeight = 0;		//����
	m_nColCount = 0;
	m_nCount = 0;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CWarning::~CWarning()
{
}

//=============================================================================
// �e�N�X�`�����[�h�֐�
//=============================================================================
HRESULT CWarning::Load(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_WARNING,								// �t�@�C���̖��O
		&m_pTexture);								// �ǂݍ��ރ������[
	return S_OK;
}

//=============================================================================
// �e�N�X�`���A�����[�h�֐�
//=============================================================================
void CWarning::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// �����֐�
//=============================================================================
CWarning * CWarning::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float SizeWidth, float SizeHeight)
{
	CWarning * pWarning;
	pWarning = new CWarning;
	pWarning->SetPosition(pos);
	pWarning->Init(pos,move, SizeWidth, SizeHeight);

	return pWarning;
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CWarning::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, float SizeWidth, float SizeHeight)
{
	CScene2d::Init(pos, SizeWidth, SizeHeight);

	m_pos = pos;
	m_move = move;
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//���_���W
		m_col[nCount] = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
	m_fWidth = SizeWidth;	//��
	m_fHeight = SizeHeight; //����
	m_nColCount = 0;
	m_nCount = 0;
	// ���_���W��ݒ�
	m_vpos[0] = D3DXVECTOR3(pos.x + (-SizeWidth / 2), pos.y + (-SizeHeight / 2), 0.0f);
	m_vpos[1] = D3DXVECTOR3(pos.x + (SizeWidth / 2), pos.y + (-SizeHeight / 2), 0.0f);
	m_vpos[2] = D3DXVECTOR3(pos.x + (-SizeWidth / 2), pos.y + (SizeHeight / 2), 0.0f);
	m_vpos[3] = D3DXVECTOR3(pos.x + (SizeWidth / 2), pos.y + (SizeHeight / 2), 0.0f);

	//���_���W�̃Z�b�g
	SetVertexPosition(m_vpos);
	//�e�N�X�`���̊��蓖��
	BindTexture(m_pTexture);
	SetTex(
		0.0f, 0.0f, 1.0f, 1.0f
	);
	//�F�̃Z�b�g
	SetColor(m_col);
	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CWarning::Uninit(void)
{
	CScene2d::Uninit();
}

//=============================================================================
// �����X�V�֐�
//=============================================================================
void CWarning::Update(void)
{
	//�X�V
	CScene2d::Update();
	//�ʒu�̎擾
	D3DXVECTOR3 pos = GetPosition();

	for (int nCountPriority = 1; nCountPriority < 5; nCountPriority++)
	{
		for (int nCountScene = 0; nCountScene < GetNumAll(); nCountScene++)
		{
			CScene * pScene = GetScene(nCountPriority, nCountScene);

			if (pScene != NULL)
			{
				//�I�u�W�F�^�C�v�̎擾
				OBJTYPE objType;
				objType = pScene->GetObjType();
				//�G�̈ʒu���擾
				D3DXVECTOR3 target_pos;
				target_pos = pScene->GetPosition();

				if (objType == OBJTYPE_FIREBALL)
				{
					m_pos.x = target_pos.x;
					//m_move.x = 1.0f;
				}

				if (objType == OBJTYPE_PLAYER)
				{
					m_pos.y = target_pos.y;
				}
			}
		}
	}

	//�ʒu�X�V
	//m_pos.x += m_move.x;
	//m_pos.y += m_move.y;

	if (m_nCount % 10 == 0)
	{
		if (m_nColCount % 2 == 0)
		{
			for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
			{
				m_col[nCount] = D3DCOLOR_RGBA(255, 255, 0, 255);
			}
		}
		else
		{
			for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
			{
				m_col[nCount] = D3DCOLOR_RGBA(255, 0, 0, 255);
			}
		}
		m_nColCount++;
	}

	m_nCount++;

	if (CBullet::GetbFireBall() == false)
	{
		Uninit();
		return;
	}

	// ���_���W��ݒ�
	m_vpos[0] = D3DXVECTOR3(pos.x + (-m_fWidth / 2), pos.y + (-m_fHeight / 2), 0.0f);
	m_vpos[1] = D3DXVECTOR3(pos.x + (m_fWidth / 2), pos.y + (-m_fHeight / 2), 0.0f);
	m_vpos[2] = D3DXVECTOR3(pos.x + (-m_fWidth / 2), pos.y + (m_fHeight / 2), 0.0f);
	m_vpos[3] = D3DXVECTOR3(pos.x + (m_fWidth / 2), pos.y + (m_fHeight / 2), 0.0f);
	//���݈ʒu�̃Z�b�g
	SetPosition(m_pos);
	//���_���W�̐ݒ�
	SetVertexPosition(m_vpos);

	SetTex(
		0.0f, 0.0f, 1.0f, 1.0f
	);
	//�F�̃Z�b�g
	SetColor(m_col);
}


//=============================================================================
// �`��֐�
//=============================================================================
void CWarning::Draw(void)
{
	CScene2d::Draw();
}