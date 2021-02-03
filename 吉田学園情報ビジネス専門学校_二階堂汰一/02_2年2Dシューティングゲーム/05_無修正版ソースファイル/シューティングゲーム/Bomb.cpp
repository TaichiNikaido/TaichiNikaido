//=============================================================================
//
//	���e [bomb.cpp]
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
#include "Bomb.h"
#include "explosion.h"
#include "sound.h"
#include "player.h"
#include "enemy.h"

LPDIRECT3DTEXTURE9 CBomb::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBomb::CBomb()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//���_���W
	}
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړ���
	m_Type = TYPE_NONE;	//�^�C�v
	m_nLife = 0;		//���C�t
	m_nAttack = 0;		//�U����
	m_fWidth = 0.0f;	//��
	m_fHeight = 0.0f;	//����
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CBomb::~CBomb()
{
}

//=============================================================================
// �e�N�X�`�����[�h�֐�
//=============================================================================
HRESULT CBomb::Load(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_BOMB,								// �t�@�C���̖��O
		&m_pTexture);								// �ǂݍ��ރ������[
	return S_OK;
}

//=============================================================================
// �e�N�X�`���A�����[�h�֐�
//=============================================================================
void CBomb::Unload(void)
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
CBomb * CBomb::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float SizeWidth, float SizeHeight,  int nLife, int nAttack)
{
	CBomb * pBomb;
	pBomb = new CBomb;
	pBomb->Init(pos, move, SizeHeight, SizeWidth,  nLife, nAttack);
	pBomb->SetPosition(pos);
	return pBomb;
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CBomb::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, float SizeWidth, float SizeHeight,  int nLife, int nAttack)
{
	CScene2d::Init(pos, SizeHeight,SizeWidth);
	//�I�u�W�F�^�C�v�𔚒e��
	SetObjType(CScene::OBJTYPE_BOMB);
	//�ʒu��ݒ肷��
	m_pos = pos;
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//���_���W
	}
	m_move = move;			//�ړ���
	m_Type = TYPE_NONE;		//�^�C�v
	m_nLife = nLife;		//���C�t
	m_nAttack = nAttack;	//�U����
	m_fWidth = SizeWidth;	//��
	m_fHeight = SizeHeight;	//����
	// ���_���W��ݒ�
	m_vpos[0] = D3DXVECTOR3(pos.x + (-SizeWidth / 2), pos.y + (-SizeHeight / 2), 0.0f);
	m_vpos[1] = D3DXVECTOR3(pos.x + (SizeWidth / 2), pos.y + (-SizeHeight / 2), 0.0f);
	m_vpos[2] = D3DXVECTOR3(pos.x + (-SizeWidth / 2), pos.y + (SizeHeight / 2), 0.0f);
	m_vpos[3] = D3DXVECTOR3(pos.x + (SizeWidth / 2), pos.y + (SizeHeight / 2), 0.0f);
	//���_���W�̃Z�b�g
	SetVertexPosition(m_vpos);
	//�e�N�X�`���̐ݒ�
	SetTex(0.0f,
		0.0f,
		1.0f,
		1.0f);
	//�e�N�X�`���̊��蓖��
	BindTexture(m_pTexture);
	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CBomb::Uninit(void)
{
	CScene2d::Uninit();
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CBomb::Update(void)
{
	CScene2d::Update();
	//�ʒu�̎擾
	m_pos = GetPosition();
	//�ʒu�Ɉړ��ʂ����Z
	m_pos += m_move;
	//�̗͌��Z�����֐�
	SubLife();
	// ���_���W��ݒ�
	m_vpos[0] = D3DXVECTOR3(m_pos.x + (-m_fWidth / 2), m_pos.y + (-m_fHeight / 2), 0.0f);
	m_vpos[1] = D3DXVECTOR3(m_pos.x + (m_fWidth / 2), m_pos.y + (-m_fHeight / 2), 0.0f);
	m_vpos[2] = D3DXVECTOR3(m_pos.x + (-m_fWidth / 2), m_pos.y + (m_fHeight / 2), 0.0f);
	m_vpos[3] = D3DXVECTOR3(m_pos.x + (m_fWidth / 2), m_pos.y + (m_fHeight / 2), 0.0f);
	//���_���W�̐ݒ�
	SetVertexPosition(m_vpos);
	//�e�N�X�`���̐ݒ�
	SetTex(0.0f,
		   0.0f, 
		   1.0f,
		   1.0f);
	//�ʒu�̐ݒ�
	SetPosition(m_pos);
}

//=============================================================================
// �`��֐�
//=============================================================================
void CBomb::Draw(void)
{
	CScene2d::Draw();
}

//=============================================================================
// �̗͌��Z�����֐�
//=============================================================================
void CBomb::SubLife(void)
{
	//���y�̎擾
	CSound * pSound = CManager::GetSound();
	//���C�t�̌��Z
	m_nLife--;
	//�������C�t��0�ȉ��ɂȂ�����
	if (m_nLife <= 0)
	{
		//�����̐���
		CExplosion::Create(m_pos, BOMB_EXPLOSION_SIZE, BOMB_EXPLOSION_SIZE, CExplosion::TYPE_BOMB);
		//�������̐���
		pSound->PlaySound(CSound::SOUND_LABEL_BOMBEXPLOSION);
		Uninit();
		return;
	}
}
