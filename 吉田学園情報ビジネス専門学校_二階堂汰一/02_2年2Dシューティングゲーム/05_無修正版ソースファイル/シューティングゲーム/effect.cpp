//=============================================================================
//
//	�G�t�F�N�g [effect.cpp]
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
#include "effect.h"

LPDIRECT3DTEXTURE9 CEffect::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEffect::CEffect(int nPriority) : CScene2d(nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);;
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	memset(m_col, 0, sizeof(m_col));
	m_Type = TYPE_NONE;
	m_nLife = 0;
	m_fWidth = 0.0f;
	m_fHeight = 0.0f;
	m_nAlpha = 0;
	m_fScale = 0.0f;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CEffect::~CEffect()
{
}

//=============================================================================
// �e�N�X�`�����[�h�֐�
//=============================================================================
HRESULT CEffect::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_EFFECT,								// �t�@�C���̖��O
		&m_pTexture);								// �ǂݍ��ރ������[
	return S_OK;
}

//=============================================================================
// �e�N�X�`���A�����[�h�֐�
//=============================================================================
void CEffect::Unload(void)
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
CEffect * CEffect::Create(D3DXVECTOR3 pos, D3DCOLOR col, float SizeHeight, float SizeWidth, int nLife, TYPE nType)
{
	CEffect * pEffect;
	pEffect = new CEffect;

	pEffect->Init(pos, col, SizeHeight, SizeWidth,nLife, nType);
	pEffect->SetPosition(pos);

	return pEffect;
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CEffect::Init(D3DXVECTOR3 pos, D3DCOLOR col, float SizeHeight, float SizeWidth, int nLife, TYPE nType)
{
	//�I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CScene::OBJTYPE_BULLET);
	CScene2d::Init(pos, SizeHeight, SizeWidth);

	m_pos = pos;
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_col[nCount] = col;
	}
	m_nLife = nLife;
	m_Type = nType;
	m_fWidth = SizeWidth;
	m_fHeight = SizeHeight;
	m_nAlpha = 255;
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 10.0f);
	m_fLength = sqrtf((float)(((SizeWidth / 2) * (SizeWidth / 2)) + ((SizeHeight / 2) * (SizeHeight / 2))));
	m_fAngle = atan2f((SizeWidth / 2), (SizeWidth / 2));
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fScale = 1.0f;

	// ���_���W��ݒ�
	m_vpos[0].x = m_pos.x - cosf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	m_vpos[0].y = m_pos.y - sinf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	m_vpos[0].z = 0.0f;

	m_vpos[1].x = m_pos.x + cosf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	m_vpos[1].y = m_pos.y - sinf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	m_vpos[1].z = 0.0f;

	m_vpos[2].x = m_pos.x - cosf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	m_vpos[2].y = m_pos.y + sinf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	m_vpos[2].z = 0.0f;

	m_vpos[3].x = m_pos.x + cosf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	m_vpos[3].y = m_pos.y + sinf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	m_vpos[3].z = 0.0f;

	SetVertexPosition(m_vpos);
	SetColor(m_col);
	SetTex(
		0.0f,
		0.0f,
		1.0f,
		1.0f);
	BindTexture(m_pTexture);
	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CEffect::Uninit(void)
{
	CScene2d::Uninit();
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CEffect::Update(void)
{
	D3DXVECTOR3 pos;
	pos = GetPosition();

	CScene2d::Update();

	
	if (m_nLife <= 0)
	{
		Uninit();
		return;
	}
	m_nLife--;

	// ���_���W��ݒ�
	m_vpos[0].x = m_pos.x - cosf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	m_vpos[0].y = m_pos.y - sinf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	m_vpos[0].z = 0.0f;

	m_vpos[1].x = m_pos.x + cosf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	m_vpos[1].y = m_pos.y - sinf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	m_vpos[1].z = 0.0f;

	m_vpos[2].x = m_pos.x - cosf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	m_vpos[2].y = m_pos.y + sinf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	m_vpos[2].z = 0.0f;

	m_vpos[3].x = m_pos.x + cosf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	m_vpos[3].y = m_pos.y + sinf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	m_vpos[3].z = 0.0f;

	SetVertexPosition(m_vpos);
	SetTex(
		0.0f,
		0.0f,
		1.0f,
		1.0f);

	switch (m_Type)
	{
	case TYPE_PLAYER:
		if (m_nLife > 0)
		{
			m_nAlpha -= 10;
			m_fScale -= 0.1f;
		}
		break;
	case TYPE_ENEMY:
		if (m_nLife > 0)
		{
			m_nAlpha -= 10;
			m_fScale -= 0.1f;
		}
		break;
	case TYPE_DRAGON:

		if (m_nLife > 0)
		{
			m_nAlpha -= 10;
			m_fScale -= 0.05f;
		}
		break;
	default:
		break;
	}

	//for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	//{
	//	m_col[nCount] = D3DCOLOR_RGBA(255,255,255,m_nAlpha);
	//}
	SetColor(m_col);
	SetPosition(pos);
}

//=============================================================================
// �`��֐�
//=============================================================================
void CEffect::Draw(void)
{
	CRenderer * pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	CScene2d::Draw();
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}