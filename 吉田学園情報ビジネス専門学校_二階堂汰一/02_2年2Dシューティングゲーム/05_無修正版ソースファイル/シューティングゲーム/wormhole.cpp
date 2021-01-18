//=============================================================================
//
// ���[���z�[������ [wormhole.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "scene2d.h"
#include "wormhole.h"
#include "player.h"
#include "dragon.h"
#include "enemy.h"

LPDIRECT3DTEXTURE9 CWormhole::m_pTexture[MAX_WORMHOLE_TEXTURE] = {};
bool CWormhole::m_bSpawn = false;
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CWormhole::CWormhole(int nPriority)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//���_���W
		m_col[nCount] = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);	//���_�J���[
	}
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//����
	m_Type = TYPE_NONE;						//�^�C�v
	m_fAngle = 0.0f;						//�p�x
	m_fLength = 0.0f;						//����
	m_fScale = 0.1f;						//�傫��
	m_fAddScale = 0.01f;					//�傫���̉��Z��
	m_Texture = TEX_NONE;
	m_nCountSpawn = 0;
	m_bSpawn = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CWormhole::~CWormhole()
{
}

//=============================================================================
// �e�N�X�`�����[�h
//=============================================================================
HRESULT CWormhole::Load(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_WORMHOLE,							// �t�@�C���̖��O
		&m_pTexture[TEX_HOLE]);					// �ǂݍ��ރ������[

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_WORMHOLEEFFECT,						// �t�@�C���̖��O
		&m_pTexture[TEX_EFFECT]);					// �ǂݍ��ރ������[
	return S_OK;
}

//=============================================================================
// �e�N�X�`���A�����[�h
//=============================================================================
void CWormhole::Unload(void)
{
	for (int nCount = 0; nCount < MAX_WORMHOLE_TEXTURE; nCount++)
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
CWormhole * CWormhole::Create(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight, TYPE type, TEXTURE texture, D3DCOLOR col)
{
	CWormhole * pWormhole;
	pWormhole = new CWormhole;
	pWormhole->Init(pos, SizeWidth, SizeHeight, type,texture, col);
	return pWormhole;
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CWormhole::Init(D3DXVECTOR3 pos, float SizeWidth, float SizeHeight, TYPE type, TEXTURE texture, D3DCOLOR col)
{
	CScene2d::Init(pos, SizeWidth,SizeHeight);
	
	//�I�u�W�F�^�C�v�����[���z�[����
	SetObjType(CScene::OBJTYPE_WORMHOLE);

	//�����_���[�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	m_pos = pos;	//�ʒu
	for (int nCount = 0; nCount < NUM_VERTEX; nCount++)
	{
		m_vpos[nCount] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//���_���W
		m_col[nCount] = col;							//���_�J���[
	}
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 10.0f);				//����
	m_fLength = sqrtf((float)(((SizeWidth / 2) * (SizeWidth / 2)) + ((SizeHeight / 2) * (SizeHeight / 2))));	//����
	m_fAngle = atan2f((SizeWidth / 2), (SizeWidth / 2));														//�p�x
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//����
	m_Type = type;			//�^�C�v
	m_Texture = texture;
	m_fScale = 0.1f;		//�傫��
	m_fAddScale = 0.01f;	//�傫���̉��Z��
	m_nCountSpawn = 0;
	m_bSpawn = false;
	//���_�J���[�̃Z�b�g
	SetColor(m_col);

	//���_���W�̐ݒ�
	m_vpos[0].x = m_pos.x - cosf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	m_vpos[0].y = m_pos.y - sinf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	m_vpos[0].z = 0.0f;
	//���_���W�̐ݒ�
	m_vpos[1].x = m_pos.x + cosf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	m_vpos[1].y = m_pos.y - sinf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	m_vpos[1].z = 0.0f;
	//���_���W�̐ݒ�
	m_vpos[2].x = m_pos.x - cosf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	m_vpos[2].y = m_pos.y + sinf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	m_vpos[2].z = 0.0f;
	//���_���W�̐ݒ�
	m_vpos[3].x = m_pos.x + cosf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	m_vpos[3].y = m_pos.y + sinf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	m_vpos[3].z = 0.0f;

	//���_���W�̃Z�b�g
	SetVertexPosition(m_vpos);
	//�e�N�X�`���̃Z�b�g
	SetTex(0.0f, 0.0f, 1.0f, 1.0f);
	//�e�N�X�`���̊��蓖��
	BindTexture(m_pTexture[m_Texture]);
	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CWormhole::Uninit(void)
{
	CScene2d::Uninit();
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CWormhole::Update(void)
{
	CScene2d::Update();

	//�ʒu�̎擾
	m_pos = GetPosition();

	// ��]
	m_rot.z -= D3DX_PI * 0.01f;

	if (m_rot.z >= D3DX_PI)
	{
		m_rot.z += D3DX_PI * 2.0f;
	}

	if (m_bSpawn == false)
	{
		if (m_fScale <= 2.0f)
		{
			m_fScale += m_fAddScale;
		}
		else
		{
			if (m_nCountSpawn == 70)
			{
				Spawn();
			}
			m_nCountSpawn++;
		}
	}

	if (CDragon::GetSpawn() == true)
	{
			m_fScale -= m_fAddScale;
	}

	if (m_fScale <= 0.0f)
	{
		m_bSpawn = false;
		Uninit();
		return;
	}

	for (int nCountPriority = 0; nCountPriority < PRIORITY_MAX; nCountPriority++)
	{
		for (int nCountScene = 0; nCountScene < MAX_SCENE; nCountScene++)
		{
			//�V�[�����擾
			CScene * pScene = GetScene(nCountPriority, nCountScene);

			if (pScene != NULL)
			{
				//�I�u�W�F�^�C�v�̎擾
				OBJTYPE objType;
				objType = pScene->GetObjType();

				//�v���C���[�̈ʒu���擾
				D3DXVECTOR3 player_pos;
				player_pos = pScene->GetPosition();
			}
		}
	}

	//���_���W�̐ݒ�
	m_vpos[0].x = m_pos.x - cosf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	m_vpos[0].y = m_pos.y - sinf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	m_vpos[0].z = 0.0f;
	//���_���W�̐ݒ�
	m_vpos[1].x = m_pos.x + cosf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	m_vpos[1].y = m_pos.y - sinf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	m_vpos[1].z = 0.0f;
	//���_���W�̐ݒ�
	m_vpos[2].x = m_pos.x - cosf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	m_vpos[2].y = m_pos.y + sinf(m_fAngle + m_rot.z) * m_fLength * m_fScale;
	m_vpos[2].z = 0.0f;
	//���_���W�̐ݒ�
	m_vpos[3].x = m_pos.x + cosf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	m_vpos[3].y = m_pos.y + sinf(m_fAngle - m_rot.z) * m_fLength * m_fScale;
	m_vpos[3].z = 0.0f;

	//���_���W�̃Z�b�g
	SetVertexPosition(m_vpos);
	//���݈ʒu�̃Z�b�g
	SetPosition(m_pos);
	//�e�N�X�`���̃Z�b�g
	SetTex(0.0f, 0.0f, 1.0f,1.0f);
}

//=============================================================================
// �`��֐�
//=============================================================================
void CWormhole::Draw(void)
{
	CScene2d::Draw();
}

//=============================================================================
// �X�|�[���֐�
//=============================================================================
void CWormhole::Spawn(void)
{
	//�����e�N�X�`�����z�[����������
	if (m_Texture == TEX_HOLE)
	{
		//�����^�C�v���h���S����������
		if (m_Type == TYPE_DRAGON)
		{
			//�h���S���̐���
			CDragon::Create(m_pos, DRAGON_SIZE_WIDTH, DRAGON_SIZE_HEIGHT, DRAGON_MAX_HP);
		}
		m_bSpawn = true;
		m_nCountSpawn = 0;
	}
}

void CWormhole::SetSpawn(bool bSpawn)
{
	m_bSpawn = bSpawn;
}
