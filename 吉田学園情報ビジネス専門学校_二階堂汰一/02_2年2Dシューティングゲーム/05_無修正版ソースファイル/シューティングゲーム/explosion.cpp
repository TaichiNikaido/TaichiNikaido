//=============================================================================
//
//	�������� [explosion.cpp]
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
#include "explosion.h"
#include "enemy.h"
#include "bullet.h"
#include "player.h"

LPDIRECT3DTEXTURE9 CExplosion::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CExplosion::CExplosion()
{
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//���_���W
	}
	m_nCounterAnim = 0;	//�A�j���J�E���^
	m_nPatternAnim = 0;	//�A�j���p�^�[��
	m_fWidth = 0;		//��
	m_fHeight = 0;		//����
	m_type = TYPE_NONE;	//�^�C�v
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CExplosion::~CExplosion()
{
}

//=============================================================================
// �e�N�X�`�����[�h�֐�
//=============================================================================
HRESULT CExplosion::Load(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_EXPLOSION,								// �t�@�C���̖��O
		&m_pTexture);								// �ǂݍ��ރ������[
	return S_OK;
}

//=============================================================================
// �e�N�X�`���A�����[�h�֐�
//=============================================================================
void CExplosion::Unload(void)
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
CExplosion * CExplosion::Create(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight,  TYPE type)
{
	CExplosion * pExplosion;
	pExplosion = new CExplosion;
	pExplosion->SetPosition(pos);
	pExplosion->Init(pos,SizeWidth,SizeHeight,type);

	return pExplosion;
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CExplosion::Init(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight, TYPE type)
{
	CScene2d::Init(pos,SizeWidth,SizeHeight);

	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//���_���W
	}
	m_nCounterAnim = 0;		//�A�j���J�E���^
	m_nPatternAnim = 0;		//�A�j���p�^�[��
	m_fWidth = SizeWidth;	//��
	m_fHeight = SizeHeight; //����
	m_type = type;			//�^�C�v

	// ���_���W��ݒ�
	m_vpos[0] = D3DXVECTOR3(pos.x + (-SizeWidth / 2), pos.y + (-SizeHeight / 2), 0.0f);
	m_vpos[1] = D3DXVECTOR3(pos.x + (SizeWidth / 2), pos.y + (-SizeHeight / 2), 0.0f);
	m_vpos[2] = D3DXVECTOR3(pos.x + (-SizeWidth / 2), pos.y + (SizeHeight / 2), 0.0f);
	m_vpos[3] = D3DXVECTOR3(pos.x + (SizeWidth / 2), pos.y + (SizeHeight / 2), 0.0f);

	//�e�N�X�`���Z�b�g
	SetTex(m_nPatternAnim * 0.125f,
		0.0f,
		m_nPatternAnim * 0.125f + 0.125f,
		1.0f);

	//���_���W�̃Z�b�g
	SetVertexPosition(m_vpos);
	//�e�N�X�`���̊��蓖��
	BindTexture(m_pTexture);
	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CExplosion::Uninit(void)
{
	CScene2d::Uninit();
}

//=============================================================================
// �����X�V�֐�
//=============================================================================
void CExplosion::Update(void)
{
	//�X�V
	CScene2d::Update();
	//�ʒu�̎擾
	D3DXVECTOR3 pos = GetPosition();

	//�^�C�v�ɂ�鏈������
	switch (m_type)
	{
	case TYPE_BULLET:
		break;
	case TYPE_BOMB:
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
					//�V�[���I�u�W�F�N�g�̈ʒu���擾
					D3DXVECTOR3 Scene_pos;
					Scene_pos = pScene->GetPosition();

					switch (objType)
					{
					case OBJTYPE_ENEMY:
						if (pos.x + m_fWidth / 2 > Scene_pos.x - (EYE_SIZE / 2) &&
							pos.x - m_fWidth / 2 < Scene_pos.x + (EYE_SIZE / 2) &&
							pos.y + m_fHeight / 2 > Scene_pos.y - (EYE_SIZE / 2) &&
							pos.y - m_fHeight / 2 < Scene_pos.y + (EYE_SIZE / 2))
						{
							//�G�l�~�[�̃��C�t���Z
							CEnemy * pEnemy = dynamic_cast<CEnemy*> (pScene);
							if (pScene != NULL)
							{
								pEnemy->SubLife(100);
							}
						}
						break;
					case OBJTYPE_BULLET:
						if (pos.x + BOMB_EXPLOSION_SIZE / 2 > Scene_pos.x - (BULLET_SIZE / 2) &&
							pos.x - BOMB_EXPLOSION_SIZE / 2 < Scene_pos.x + (BULLET_SIZE / 2) &&
							pos.y + BOMB_EXPLOSION_SIZE / 2 > Scene_pos.y - (BULLET_SIZE / 2) &&
							pos.y - BOMB_EXPLOSION_SIZE / 2 < Scene_pos.y + (BULLET_SIZE / 2))
						{
							pScene->Uninit();
						}
						break;
					default:
						break;
					}
				}
			}
		}
		
	
	case TYPE_FIERBALL:
		for (int nCountScene = 0; nCountScene < GetNumAll(); nCountScene++)
		{
			CScene * pScene = GetScene(4, nCountScene);
			if (pScene != NULL)
			{
				//�I�u�W�F�^�C�v�̎擾
				OBJTYPE objType;
				objType = pScene->GetObjType();
				//�V�[���I�u�W�F�N�g�̈ʒu���擾
				D3DXVECTOR3 Scene_pos;
				Scene_pos = pScene->GetPosition();

				if (objType == OBJTYPE_PLAYER)
				{
					if (pos.x + m_fWidth / 2 > Scene_pos.x - (PLAYER_SIZE / 2) &&
						pos.x - m_fWidth / 2 < Scene_pos.x + (PLAYER_SIZE / 2) &&
						pos.y + m_fHeight / 2 > Scene_pos.y - (PLAYER_SIZE / 2) &&
						pos.y - m_fHeight / 2 < Scene_pos.y + (PLAYER_SIZE / 2))
					{
						//�G�l�~�[�̃��C�t���Z
						CPlayer * pPlayer = dynamic_cast<CPlayer*> (pScene);
						if (pScene != NULL)
						{
							pPlayer->SubOwn(1);
						}
					}
				}
			}
		}
		break;
	default:
		break;
	}
	//�J�E���g�C���N�������g
	m_nCounterAnim++;
	//�J�E���g��4�ȏ�ɂȂ����ꍇ
	if (m_nCounterAnim > 4)
	{
		//�J�E���g��0�ɂ���
		m_nCounterAnim = 0;

		//�p�^�[���̃C���N�������g
		m_nPatternAnim++;
		//�p�^�[����8�ɂȂ����ꍇ
		if (m_nPatternAnim > 8)
		{
			//�I��
			Uninit();
			return;
		}
	}
	//�e�N�X�`���Z�b�g
	SetTex(m_nPatternAnim * 0.125f,
		0.0f,
		m_nPatternAnim * 0.125f + 0.125f,
		1.0f);

	// ���_���W��ݒ�
	m_vpos[0] = D3DXVECTOR3(pos.x + (-m_fWidth / 2), pos.y + (-m_fHeight / 2), 0.0f);
	m_vpos[1] = D3DXVECTOR3(pos.x + (m_fWidth / 2), pos.y + (-m_fHeight / 2), 0.0f);
	m_vpos[2] = D3DXVECTOR3(pos.x + (-m_fWidth / 2), pos.y + (m_fHeight / 2), 0.0f);
	m_vpos[3] = D3DXVECTOR3(pos.x + (m_fWidth / 2), pos.y + (m_fHeight / 2), 0.0f);

	//���_���W�̐ݒ�
	SetVertexPosition(m_vpos);
}


//=============================================================================
// �`��֐�
//=============================================================================
void CExplosion::Draw(void)
{
	CScene2d::Draw();
}