//=============================================================================
//
// �A�C�e������ [item.cpp]
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
#include "game.h"
#include "player.h"
#include "sound.h"
#include "score.h"
#include "item.h"
#include "own.h"
#include "ownui.h"

//*****************************************************************************
// �ÓI�����o�ϐ��̏�����
//*****************************************************************************
LPDIRECT3DTEXTURE9 CItem::m_pTexture[MAX_ITEM_TEXTURE] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CItem::CItem()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//���_���W
	}
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړ���
	m_Type = TYPE_NONE;						//�^�C�v
	m_fWidth = 0.0f;						//��
	m_fHeight = 0.0f;						//����
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CItem::~CItem()
{
}

//=============================================================================
// �e�N�X�`�����[�h
//=============================================================================
HRESULT CItem::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_OWN_ITEM,							// �t�@�C���̖��O
		&m_pTexture[TYPE_OWN]);						// �ǂݍ��ރ������[

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_LEVEL_ITEM,							// �t�@�C���̖��O
		&m_pTexture[TYPE_LEVEL]);					// �ǂݍ��ރ������[

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_SCORE_ITEM,							// �t�@�C���̖��O
		&m_pTexture[TYPE_SCORE]);					// �ǂݍ��ރ������[

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_BOMB_ITEM,							// �t�@�C���̖��O
		&m_pTexture[TYPE_BOMB]);					// �ǂݍ��ރ������[

	return S_OK;
}

//=============================================================================
// �e�N�X�`���A�����[�h
//=============================================================================
void CItem::Unload(void)
{
	for (int nCount = 0; nCount < MAX_ITEM_TEXTURE; nCount++)
	{
		// �e�N�X�`���̔j��
		if (m_pTexture[nCount] != NULL)
		{
			m_pTexture[nCount]->Release();
			m_pTexture[nCount] = NULL;
		}
	}
}

//=============================================================================
// �����֐�
//=============================================================================
CItem * CItem::Create(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight, TYPE type)
{
	CItem * pItem;
	pItem = new CItem;
	pItem->Init(pos, SizeWidth, SizeHeight,type);
	return pItem;
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CItem::Init(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight, TYPE type)
{
	CScene2d::Init(pos, SizeWidth, SizeHeight);

	//�I�u�W�F�^�C�v���A�C�e����
	SetObjType(CScene::OBJTYPE_ITEM);

	//�����_���[�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	m_pos = pos;			//�ʒu
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//���_���W
	}
	m_move = D3DXVECTOR3(0.0f, ITEM_SPEED, 0.0f);	//�ړ���
	m_Type = type;			//�^�C�v
	m_fWidth = SizeWidth;	//��
	m_fHeight = SizeHeight; //����

	// ���_���W��ݒ�
	m_vpos[0] = D3DXVECTOR3(m_pos.x + (-m_fWidth / 2), m_pos.y + (-m_fHeight / 2), 0.0f);
	m_vpos[1] = D3DXVECTOR3(m_pos.x + (m_fWidth / 2), m_pos.y + (-m_fHeight / 2), 0.0f);
	m_vpos[2] = D3DXVECTOR3(m_pos.x + (-m_fWidth / 2), m_pos.y + (m_fHeight / 2), 0.0f);
	m_vpos[3] = D3DXVECTOR3(m_pos.x + (m_fWidth / 2), m_pos.y + (m_fHeight / 2), 0.0f);
	//���_���W���Z�b�g
	SetVertexPosition(m_vpos);
	//�e�N�X�`���̃Z�b�g
	SetTex(0.0f,
		0.0f,
		1.0f,
		1.0f);
	//�e�N�X�`���̊��蓖��
	BindTexture(m_pTexture[m_Type]);
	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CItem::Uninit(void)
{
	CScene2d::Uninit();
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CItem::Update(void)
{
	CScene2d::Update();

	for (int nCountScene = 0; nCountScene < GetNumAll(); nCountScene++)
	{
		//�V�[���̎擾
		CScene * pScene = GetScene(4, nCountScene);
		//�X�R�A�̎擾
		CScore * pScore = CGame::GetScore();
		//�v���C���[�̃|�C���^
		CPlayer * pPlayer;

		if (pScene != NULL)
		{
			//�I�u�W�F�^�C�v�̎擾
			OBJTYPE objType;
			objType = pScene->GetObjType();

			//�I�u�W�F�̈ʒu
			D3DXVECTOR3 objPos;
			objPos = pScene->GetPosition();

			//�����I�u�W�F�^�C�v���v���C���[��������
			if (objType == OBJTYPE_PLAYER)
			{
				//�����Փ˔��肪ture��������
				if (isCollision(objPos) == true)
				{
					//�^�C�v�ɂ�鏈������
					switch (m_Type)
					{
						//�����^�C�v�����@��������
					case TYPE_OWN:
						pPlayer = dynamic_cast<CPlayer*> (pScene);
						//�v���C���[�̎��@�����Z
						pPlayer->AddOwn(PLAYER_ADD_OWN);
						Uninit();
						return;
						break;
						//�����^�C�v�����x����������
					case TYPE_LEVEL:
						pPlayer = dynamic_cast<CPlayer*> (pScene);
						//�v���C���[�̃��x�������Z
						pPlayer->AddLevel(PLAYER_ADD_LEVEL);
						Uninit();
						return;
						break;
						//�����^�C�v���X�R�A��������
					case TYPE_SCORE:
						//�v���C���[�̃X�R�A�����Z
						pScore->AddScore(ADDSCORE_ITEM);
						Uninit();
						return;
						break;
						//�����^�C�v���{����������
					case TYPE_BOMB:
						pPlayer = dynamic_cast<CPlayer*> (pScene);
						//�v���C���[�̔��e�����Z
						pPlayer->AddBomb(PLAYER_ADD_BOMB);
						Uninit();
						return;
						break;
					default:
						break;
					}
				}
			}
		}
	}

	//�ʒu�Ɉړ��ʂ����Z
	m_pos += m_move;

	//�����A�C�e������ʊO�Ɍ�������
	if (m_pos.y > FIELD_HEIGHT ||
		m_pos.x < 0 ||
		m_pos.x > FIELD_WIDTH)
	{
		Uninit();
		return;
	}

	// ���_���W��ݒ�
	m_vpos[0] = D3DXVECTOR3(m_pos.x + (-m_fWidth / 2), m_pos.y + (-m_fHeight / 2), 0.0f);
	m_vpos[1] = D3DXVECTOR3(m_pos.x + (m_fWidth / 2), m_pos.y + (-m_fHeight / 2), 0.0f);
	m_vpos[2] = D3DXVECTOR3(m_pos.x + (-m_fWidth / 2), m_pos.y + (m_fHeight / 2), 0.0f);
	m_vpos[3] = D3DXVECTOR3(m_pos.x + (m_fWidth / 2), m_pos.y + (m_fHeight / 2), 0.0f);

	//���_���W�̃Z�b�g
	SetVertexPosition(m_vpos);
	//���݈ʒu�̃Z�b�g
	SetPosition(m_pos);
	//�e�N�X�`���̃Z�b�g
	SetTex(0.0f,
		0.0f,
		1.0f,
		1.0f);
}

//=============================================================================
// �`��֐�
//=============================================================================
void CItem::Draw(void)
{
	CScene2d::Draw();
}

//=============================================================================
// �Փˏ���
//=============================================================================
bool CItem::isCollision(D3DXVECTOR3 pos)
{
	if (CPlayer::GetbDeath() == false)
	{
		if (m_pos.x + ITEM_SIZE / 2 > pos.x - (PLAYER_SIZE / 2) &&
			m_pos.x - ITEM_SIZE / 2 < pos.x + (PLAYER_SIZE / 2) &&
			m_pos.y + ITEM_SIZE / 2 > pos.y - (PLAYER_SIZE / 2) &&
			m_pos.y - ITEM_SIZE / 2 < pos.y + (PLAYER_SIZE / 2))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}