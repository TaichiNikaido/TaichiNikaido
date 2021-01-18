//=============================================================================
//
// �{�X���� [boss.cpp]
// Author : ��K������
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "scene2d.h"
#include "score.h"
#include "bullet.h"
#include "boss.h"
#include "player.h"

LPDIRECT3DTEXTURE9 CBoss::m_apTexture[PART_MAX] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBoss::CBoss(int nPriority) :CScene2d(nPriority)
{
	memset(m_apScene, 0, sizeof(m_apScene));
	memset(m_PartStatus, 0, sizeof(m_PartStatus));
	m_nLife = 0;
	m_nCountBullet = 0;					//�e�̃J�E���g
	m_pBullet = NULL;					//�e�̃|�C���^
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBoss::~CBoss()
{
}

//=============================================================================
// �e�N�X�`���̃��[�h�֐�
//=============================================================================
HRESULT CBoss::Load(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		PART00_TEXTURE,								// �t�@�C���̖��O
		&m_apTexture[CORE_02]);						// �ǂݍ��ރ������[

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		PART01_TEXTURE,								// �t�@�C���̖��O
		&m_apTexture[CORE]);						// �ǂݍ��ރ������[

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		PART02_TEXTURE,								// �t�@�C���̖��O
		&m_apTexture[CORE_01]);						// �ǂݍ��ރ������[

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		PART03_TEXTURE,								// �t�@�C���̖��O
		&m_apTexture[BODY_RIGHT]);					// �ǂݍ��ރ������[

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		PART04_TEXTURE,								// �t�@�C���̖��O
		&m_apTexture[BODY_LEFT]);					// �ǂݍ��ރ������[

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		PART05_TEXTURE,								// �t�@�C���̖��O
		&m_apTexture[HAND_RIGHT]);					// �ǂݍ��ރ������[

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		PART06_TEXTURE,								// �t�@�C���̖��O
		&m_apTexture[HAND_LEFT]);					// �ǂݍ��ރ������[

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		PART07_TEXTURE,								// �t�@�C���̖��O
		&m_apTexture[FOREARM_RIGHT]);				// �ǂݍ��ރ������[

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		PART08_TEXTURE,								// �t�@�C���̖��O
		&m_apTexture[FOREARM_LEFT]);				// �ǂݍ��ރ������[

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		PART09_TEXTURE,								// �t�@�C���̖��O
		&m_apTexture[UPPERARM_RIGHT]);				// �ǂݍ��ރ������[

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		PART10_TEXTURE,								// �t�@�C���̖��O
		&m_apTexture[UPPERARM_LEFT]);				// �ǂݍ��ރ������[

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		PART11_TEXTURE,								// �t�@�C���̖��O
		&m_apTexture[HEAD]);						// �ǂݍ��ރ������[

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		PART12_TEXTURE,								// �t�@�C���̖��O
		&m_apTexture[CHIN]);						// �ǂݍ��ރ������[

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		PART13_TEXTURE,								// �t�@�C���̖��O
		&m_apTexture[EYE]);							// �ǂݍ��ރ������[

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		PART14_TEXTURE,								// �t�@�C���̖��O
		&m_apTexture[EYEFLAME]);					// �ǂݍ��ރ������[

	return S_OK;
}

//=============================================================================
// �e�N�X�`���̃A�����[�h�֐�
//=============================================================================
void CBoss::Unload(void)
{
	for (int nCount = 0; nCount < PART_MAX; nCount++)
	{
		//�e�N�X�`���̔j��
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}

//=============================================================================
// �����֐�
//=============================================================================
CBoss * CBoss::Create(D3DXVECTOR3 pos, float SizeHeight, float SizeWidth)
{
	CBoss * pBoss;
	pBoss = new CBoss;
	pBoss->Init(pos, SizeHeight, SizeWidth);
	return pBoss;
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CBoss::Init(D3DXVECTOR3 pos, float SizeHeight, float SizeWidth)
{
	SetObjType(CScene::OBJTYPE_ENEMY);

	for (int nCount = 0; nCount < PART_MAX; nCount++)
	{
		m_apScene[nCount] = new CScene2d(5);
		m_apScene[nCount]->Init(pos, SizeWidth, SizeHeight);

		for (int nCnt = 0; nCnt < NUM_VERTEX; nCnt++)
		{
			m_PartStatus[nCount].m_vpos[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//���_���W
		}
		m_PartStatus[nCount].m_pos = pos;										//�ʒu
		m_PartStatus[nCount].m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ړ���
		m_PartStatus[nCount].m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//����
		m_PartStatus[nCount].m_fWidth = 100.0f;									//��
		m_PartStatus[nCount].m_fHeight = 100.0f;								//����
		m_PartStatus[nCount].m_fLength = sqrtf((float)(((m_PartStatus[nCount].m_fWidth / 2) * (m_PartStatus[nCount].m_fWidth / 2)) + ((m_PartStatus[nCount].m_fHeight / 2) * (m_PartStatus[nCount].m_fHeight / 2))));	//����
		m_PartStatus[nCount].m_fAngle = atan2f((m_PartStatus[nCount].m_fHeight / 2), (m_PartStatus[nCount].m_fWidth / 2));//�p�x
		m_PartStatus[nCount].m_fScale = 0.5f;									//�g��

		// ���_���W��ݒ�
		m_PartStatus[nCount].m_vpos[0].x = m_PartStatus[nCount].m_pos.x - cosf(m_PartStatus[nCount].m_fAngle - m_PartStatus[nCount].m_rot.z) * m_PartStatus[nCount].m_fLength * m_PartStatus[nCount].m_fScale;
		m_PartStatus[nCount].m_vpos[0].y = m_PartStatus[nCount].m_pos.y - sinf(m_PartStatus[nCount].m_fAngle - m_PartStatus[nCount].m_rot.z) * m_PartStatus[nCount].m_fLength * m_PartStatus[nCount].m_fScale;
		m_PartStatus[nCount].m_vpos[0].z = 0.0f;

		m_PartStatus[nCount].m_vpos[1].x = m_PartStatus[nCount].m_pos.x + cosf(m_PartStatus[nCount].m_fAngle + m_PartStatus[nCount].m_rot.z) * m_PartStatus[nCount].m_fLength * m_PartStatus[nCount].m_fScale;
		m_PartStatus[nCount].m_vpos[1].y = m_PartStatus[nCount].m_pos.y - sinf(m_PartStatus[nCount].m_fAngle + m_PartStatus[nCount].m_rot.z) * m_PartStatus[nCount].m_fLength * m_PartStatus[nCount].m_fScale;
		m_PartStatus[nCount].m_vpos[1].z = 0.0f;

		m_PartStatus[nCount].m_vpos[2].x = m_PartStatus[nCount].m_pos.x - cosf(m_PartStatus[nCount].m_fAngle + m_PartStatus[nCount].m_rot.z) * m_PartStatus[nCount].m_fLength * m_PartStatus[nCount].m_fScale;
		m_PartStatus[nCount].m_vpos[2].y = m_PartStatus[nCount].m_pos.y + sinf(m_PartStatus[nCount].m_fAngle + m_PartStatus[nCount].m_rot.z) * m_PartStatus[nCount].m_fLength * m_PartStatus[nCount].m_fScale;
		m_PartStatus[nCount].m_vpos[2].z = 0.0f;

		m_PartStatus[nCount].m_vpos[3].x = m_PartStatus[nCount].m_pos.x + cosf(m_PartStatus[nCount].m_fAngle - m_PartStatus[nCount].m_rot.z) * m_PartStatus[nCount].m_fLength * m_PartStatus[nCount].m_fScale;
		m_PartStatus[nCount].m_vpos[3].y = m_PartStatus[nCount].m_pos.y + sinf(m_PartStatus[nCount].m_fAngle - m_PartStatus[nCount].m_rot.z) * m_PartStatus[nCount].m_fLength * m_PartStatus[nCount].m_fScale;
		m_PartStatus[nCount].m_vpos[3].z = 0.0f;

		//�ʒu�̃Z�b�g
		m_apScene[nCount]->SetPosition(m_PartStatus[nCount].m_pos);
		//���_���W�̃Z�b�g
		m_apScene[nCount]->SetVertexPosition(m_PartStatus[nCount].m_vpos);
		//�e�N�X�`�����Z�b�g
		m_apScene[nCount]->SetTex(
			0.0f,
			0.0f,
			1.0f,
			1.0f);
		//�e�N�X�`���̊��蓖��
		m_apScene[nCount]->BindTexture(m_apTexture[nCount]);
	}
		m_PartStatus[HEAD].m_pos = D3DXVECTOR3(FIELD_WIDTH / 2 + 1 * m_PartStatus[HEAD].m_fScale, FIELD_HEIGHT / 4, 0.0f);
		m_PartStatus[HEAD].m_fWidth = 300.0f;	//��
		m_PartStatus[HEAD].m_fHeight = 360.0f;	//����
		m_PartStatus[HEAD].m_fLength = sqrtf((float)(((m_PartStatus[HEAD].m_fWidth / 2) * (m_PartStatus[HEAD].m_fWidth / 2)) + ((m_PartStatus[HEAD].m_fHeight / 2) * (m_PartStatus[HEAD].m_fHeight / 2))));	//����
		m_PartStatus[HEAD].m_fAngle = atan2f((m_PartStatus[HEAD].m_fHeight / 2), (m_PartStatus[HEAD].m_fWidth / 2));//�p�x

		m_PartStatus[EYE].m_pos = D3DXVECTOR3(m_PartStatus[HEAD].m_pos.x, m_PartStatus[HEAD].m_pos.y + -10.0f * m_PartStatus[EYE].m_fScale, 0.0f);
		m_PartStatus[EYE].m_fWidth = 80.0f;		//��
		m_PartStatus[EYE].m_fHeight = 80.0f;	//����
		m_PartStatus[EYE].m_fLength = sqrtf((float)(((m_PartStatus[EYE].m_fWidth / 2) * (m_PartStatus[EYE].m_fWidth / 2)) + ((m_PartStatus[EYE].m_fHeight / 2) * (m_PartStatus[EYE].m_fHeight / 2))));	//����
		m_PartStatus[EYE].m_fAngle = atan2f((m_PartStatus[EYE].m_fHeight / 2), (m_PartStatus[EYE].m_fWidth / 2));//�p�x

		m_PartStatus[EYEFLAME].m_pos = D3DXVECTOR3(m_PartStatus[HEAD].m_pos.x, m_PartStatus[HEAD].m_pos.y - 20.0f * m_PartStatus[EYEFLAME].m_fScale, 0.0f);
		m_PartStatus[EYEFLAME].m_fWidth = 220.0f;	//��
		m_PartStatus[EYEFLAME].m_fHeight = 190.0f;	//����
		m_PartStatus[EYEFLAME].m_fLength = sqrtf((float)(((m_PartStatus[EYEFLAME].m_fWidth / 2) * (m_PartStatus[EYEFLAME].m_fWidth / 2)) + ((m_PartStatus[EYEFLAME].m_fHeight / 2) * (m_PartStatus[EYEFLAME].m_fHeight / 2))));	//����
		m_PartStatus[EYEFLAME].m_fAngle = atan2f((m_PartStatus[EYEFLAME].m_fHeight / 2), (m_PartStatus[EYEFLAME].m_fWidth / 2));//�p�x

		m_PartStatus[CHIN].m_pos = D3DXVECTOR3(m_PartStatus[HEAD].m_pos.x, m_PartStatus[HEAD].m_pos.y + 150.0f * m_PartStatus[CHIN].m_fScale, 0.0f);
		m_PartStatus[CHIN].m_fWidth = 130.0f;	//��
		m_PartStatus[CHIN].m_fHeight = 70.0f;	//����
		m_PartStatus[CHIN].m_fLength = sqrtf((float)(((m_PartStatus[CHIN].m_fWidth / 2) * (m_PartStatus[CHIN].m_fWidth / 2)) + ((m_PartStatus[CHIN].m_fHeight / 2) * (m_PartStatus[CHIN].m_fHeight / 2))));	//����
		m_PartStatus[CHIN].m_fAngle = atan2f((m_PartStatus[CHIN].m_fHeight / 2), (m_PartStatus[CHIN].m_fWidth / 2));//�p�x

		m_PartStatus[CORE_02].m_pos = D3DXVECTOR3(600.0f * m_PartStatus[CORE_02].m_fScale, m_PartStatus[HEAD].m_pos.y + 375.0f * m_PartStatus[CORE_02].m_fScale, 0.0f);
		m_PartStatus[CORE_02].m_fWidth = 400;	//��
		m_PartStatus[CORE_02].m_fHeight = 480;	//����
		m_PartStatus[CORE_02].m_fLength = sqrtf((float)(((m_PartStatus[CORE_02].m_fWidth / 2) * (m_PartStatus[CORE_02].m_fWidth / 2)) + ((m_PartStatus[CORE_02].m_fHeight / 2) * (m_PartStatus[CORE_02].m_fHeight / 2))));	//����
		m_PartStatus[CORE_02].m_fAngle = atan2f((m_PartStatus[CORE_02].m_fHeight / 2), (m_PartStatus[CORE_02].m_fWidth / 2));//�p�x

		m_PartStatus[CORE].m_pos = D3DXVECTOR3(FIELD_WIDTH / 2 + 1 * m_PartStatus[CORE].m_fScale, m_PartStatus[HEAD].m_pos.y + 550.0f * m_PartStatus[CORE].m_fScale, 0.0f);
		m_PartStatus[CORE].m_fWidth = 120;	//��
		m_PartStatus[CORE].m_fHeight = 120;	//����
		m_PartStatus[CORE].m_fLength = sqrtf((float)(((m_PartStatus[CORE].m_fWidth / 2) * (m_PartStatus[CORE].m_fWidth / 2)) + ((m_PartStatus[CORE].m_fHeight / 2) * (m_PartStatus[CORE].m_fHeight / 2))));	//����
		m_PartStatus[CORE].m_fAngle = atan2f((m_PartStatus[CORE].m_fHeight / 2), (m_PartStatus[CORE].m_fWidth / 2));//�p�x

		m_PartStatus[CORE_01].m_pos = D3DXVECTOR3(600.0f * m_PartStatus[CORE_01].m_fScale, m_PartStatus[HEAD].m_pos.y + 520.0f * m_PartStatus[CORE_01].m_fScale, 0.0f);
		m_PartStatus[CORE_01].m_fWidth = 260;	//��
		m_PartStatus[CORE_01].m_fHeight = 600;	//����
		m_PartStatus[CORE_01].m_fLength = sqrtf((float)(((m_PartStatus[CORE_01].m_fWidth / 2) * (m_PartStatus[CORE_01].m_fWidth / 2)) + ((m_PartStatus[CORE_01].m_fHeight / 2) * (m_PartStatus[CORE_01].m_fHeight / 2))));	//����
		m_PartStatus[CORE_01].m_fAngle = atan2f((m_PartStatus[CORE_01].m_fHeight / 2), (m_PartStatus[CORE_01].m_fWidth / 2));//�p�x

		m_PartStatus[BODY_RIGHT].m_pos = D3DXVECTOR3(450.0f * m_PartStatus[BODY_RIGHT].m_fScale, m_PartStatus[HEAD].m_pos.y + 390.0f * m_PartStatus[BODY_RIGHT].m_fScale, 0.0f);
		m_PartStatus[BODY_RIGHT].m_fWidth = 300;	//��
		m_PartStatus[BODY_RIGHT].m_fHeight = 600;	//����
		m_PartStatus[BODY_RIGHT].m_fLength = sqrtf((float)(((m_PartStatus[BODY_RIGHT].m_fWidth / 2) * (m_PartStatus[BODY_RIGHT].m_fWidth / 2)) + ((m_PartStatus[BODY_RIGHT].m_fHeight / 2) * (m_PartStatus[BODY_RIGHT].m_fHeight / 2))));	//����
		m_PartStatus[BODY_RIGHT].m_fAngle = atan2f((m_PartStatus[BODY_RIGHT].m_fHeight / 2), (m_PartStatus[BODY_RIGHT].m_fWidth / 2));//�p�x

		m_PartStatus[BODY_LEFT].m_pos = D3DXVECTOR3(745 * m_PartStatus[BODY_LEFT].m_fScale, m_PartStatus[HEAD].m_pos.y + 390.0f * m_PartStatus[BODY_LEFT].m_fScale, 0.0f);
		m_PartStatus[BODY_LEFT].m_fWidth = 300;	//��
		m_PartStatus[BODY_LEFT].m_fHeight = 600;	//����
		m_PartStatus[BODY_LEFT].m_fLength = sqrtf((float)(((m_PartStatus[BODY_LEFT].m_fWidth / 2) * (m_PartStatus[BODY_LEFT].m_fWidth / 2)) + ((m_PartStatus[BODY_LEFT].m_fHeight / 2) * (m_PartStatus[BODY_LEFT].m_fHeight / 2))));	//����
		m_PartStatus[BODY_LEFT].m_fAngle = atan2f((m_PartStatus[BODY_LEFT].m_fHeight / 2), (m_PartStatus[BODY_LEFT].m_fWidth / 2));//�p�x

		m_PartStatus[HAND_RIGHT].m_pos = D3DXVECTOR3(m_PartStatus[HEAD].m_pos.x + -1250.0f * m_PartStatus[HAND_RIGHT].m_fScale, m_PartStatus[HEAD].m_pos.y + 250.0f * m_PartStatus[HAND_RIGHT].m_fScale, 0.0f);
		m_PartStatus[HAND_RIGHT].m_fWidth = 240;	//��
		m_PartStatus[HAND_RIGHT].m_fHeight = 165;	//����
		m_PartStatus[HAND_RIGHT].m_rot.z = D3DXToRadian(180.0f);
		m_PartStatus[HAND_RIGHT].m_fLength = sqrtf((float)(((m_PartStatus[HAND_RIGHT].m_fWidth / 2) * (m_PartStatus[HAND_RIGHT].m_fWidth / 2)) + ((m_PartStatus[HAND_RIGHT].m_fHeight / 2) * (m_PartStatus[HAND_RIGHT].m_fHeight / 2))));	//����
		m_PartStatus[HAND_RIGHT].m_fAngle = atan2f((m_PartStatus[HAND_RIGHT].m_fHeight / 2), (m_PartStatus[HAND_RIGHT].m_fWidth / 2));//�p�x

		//m_PartStatus[HAND_LEFT].m_pos = D3DXVECTOR3(445 * m_PartStatus[HAND_LEFT].m_fScale, m_PartStatus[HEAD].m_pos.y + 250.0f * m_PartStatus[HAND_LEFT].m_fScale, 0.0f);
		//m_PartStatus[HAND_LEFT].m_fWidth = 240;	//��
		//m_PartStatus[HAND_LEFT].m_fHeight = 165;	//����
		//m_PartStatus[HAND_LEFT].m_fLength = sqrtf((float)(((m_PartStatus[HAND_LEFT].m_fWidth / 2) * (m_PartStatus[HAND_LEFT].m_fWidth / 2)) + ((m_PartStatus[HAND_LEFT].m_fHeight / 2) * (m_PartStatus[HAND_LEFT].m_fHeight / 2))));	//����
		//m_PartStatus[HAND_LEFT].m_fAngle = atan2f((m_PartStatus[HAND_LEFT].m_fHeight / 2), (m_PartStatus[HAND_LEFT].m_fWidth / 2));//�p�x

		m_PartStatus[FOREARM_RIGHT].m_pos = D3DXVECTOR3(m_PartStatus[HAND_RIGHT].m_pos.x + 300.0f * m_PartStatus[FOREARM_RIGHT].m_fScale, m_PartStatus[HAND_RIGHT].m_pos.y + -20.0f * m_PartStatus[FOREARM_RIGHT].m_fScale, 0.0f);
		m_PartStatus[FOREARM_RIGHT].m_fWidth = 470;	//��
		m_PartStatus[FOREARM_RIGHT].m_fHeight = 120;	//����
		m_PartStatus[FOREARM_RIGHT].m_rot.z = D3DXToRadian(180.0f);
		m_PartStatus[FOREARM_RIGHT].m_fLength = sqrtf((float)(((m_PartStatus[FOREARM_RIGHT].m_fWidth / 2) * (m_PartStatus[FOREARM_RIGHT].m_fWidth / 2)) + ((m_PartStatus[FOREARM_RIGHT].m_fHeight / 2) * (m_PartStatus[FOREARM_RIGHT].m_fHeight / 2))));	//����
		m_PartStatus[FOREARM_RIGHT].m_fAngle = atan2f((m_PartStatus[FOREARM_RIGHT].m_fHeight / 2), (m_PartStatus[FOREARM_RIGHT].m_fWidth / 2));//�p�x

		//m_PartStatus[FOREARM_LEFT].m_pos = D3DXVECTOR3(445 * m_PartStatus[FOREARM_LEFT].m_fScale, m_PartStatus[HEAD].m_pos.y + 390.0f * m_PartStatus[FOREARM_LEFT].m_fScale, 0.0f);
		//m_PartStatus[FOREARM_LEFT].m_fWidth = 470;	//��
		//m_PartStatus[FOREARM_LEFT].m_fHeight = 120;	//����
		//m_PartStatus[FOREARM_LEFT].m_fLength = sqrtf((float)(((m_PartStatus[FOREARM_LEFT].m_fWidth / 2) * (m_PartStatus[FOREARM_LEFT].m_fWidth / 2)) + ((m_PartStatus[FOREARM_LEFT].m_fHeight / 2) * (m_PartStatus[FOREARM_LEFT].m_fHeight / 2))));	//����
		//m_PartStatus[FOREARM_LEFT].m_fAngle = atan2f((m_PartStatus[FOREARM_LEFT].m_fHeight / 2), (m_PartStatus[FOREARM_LEFT].m_fWidth / 2));//�p�x

		m_PartStatus[UPPERARM_RIGHT].m_pos = D3DXVECTOR3(m_PartStatus[HAND_RIGHT].m_pos.x + 750.0f * m_PartStatus[UPPERARM_RIGHT].m_fScale, m_PartStatus[HAND_RIGHT].m_pos.y + -20.0f * m_PartStatus[UPPERARM_RIGHT].m_fScale, 0.0f);
		m_PartStatus[UPPERARM_RIGHT].m_fWidth = 440;	//��
		m_PartStatus[UPPERARM_RIGHT].m_fHeight = 140;	//����
		m_PartStatus[UPPERARM_RIGHT].m_rot.z = D3DXToRadian(0.0f);
		m_PartStatus[UPPERARM_RIGHT].m_fLength = sqrtf((float)(((m_PartStatus[UPPERARM_RIGHT].m_fWidth / 2) * (m_PartStatus[UPPERARM_RIGHT].m_fWidth / 2)) + ((m_PartStatus[UPPERARM_RIGHT].m_fHeight / 2) * (m_PartStatus[UPPERARM_RIGHT].m_fHeight / 2))));	//����
		m_PartStatus[UPPERARM_RIGHT].m_fAngle = atan2f((m_PartStatus[UPPERARM_RIGHT].m_fHeight / 2), (m_PartStatus[UPPERARM_RIGHT].m_fWidth / 2));//�p�x

		//m_PartStatus[UPPERARM_LEFT].m_pos = D3DXVECTOR3(445 * m_PartStatus[UPPERARM_LEFT].m_fScale, m_PartStatus[HEAD].m_pos.y + 390.0f * m_PartStatus[UPPERARM_LEFT].m_fScale, 0.0f);
		//m_PartStatus[UPPERARM_LEFT].m_fWidth = 440;	//��
		//m_PartStatus[UPPERARM_LEFT].m_fHeight = 140;	//����
		//m_PartStatus[UPPERARM_LEFT].m_fLength = sqrtf((float)(((m_PartStatus[UPPERARM_LEFT].m_fWidth / 2) * (m_PartStatus[UPPERARM_LEFT].m_fWidth / 2)) + ((m_PartStatus[UPPERARM_LEFT].m_fHeight / 2) * (m_PartStatus[UPPERARM_LEFT].m_fHeight / 2))));	//����
		//m_PartStatus[UPPERARM_LEFT].m_fAngle = atan2f((m_PartStatus[UPPERARM_LEFT].m_fHeight / 2), (m_PartStatus[UPPERARM_LEFT].m_fWidth / 2));//�p�x

		for (int nCount = 0; nCount < PART_MAX; nCount++)
		{
			//�ʒu�̃Z�b�g
			m_apScene[nCount]->SetPosition(m_PartStatus[nCount].m_pos);
			//���_���W�̃Z�b�g
			m_apScene[nCount]->SetVertexPosition(m_PartStatus[nCount].m_vpos);
			//�e�N�X�`�����Z�b�g
			m_apScene[nCount]->SetTex(
				0.0f,
				0.0f,
				1.0f,
				1.0f);
			//�e�N�X�`���̊��蓖��
			m_apScene[nCount]->BindTexture(m_apTexture[nCount]);
		}
	m_nLife = BOSS_LIFE;
	m_nCountBullet = 0;
	return S_OK;
}

//=============================================================================
// �I���֐�
//=============================================================================
void CBoss::Uninit(void)
{
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CBoss::Update(void)
{
	int nCountPriority = 4;

	for (int nCountScene = 0; nCountScene < GetNumAll(); nCountScene++)
	{
		CScene * pScene = GetScene(nCountPriority, nCountScene);

		if (pScene != NULL)
		{
			//�v���C���[�̈ʒu���擾
			D3DXVECTOR3 player_pos;
			player_pos = pScene->GetPosition();
			//�I�u�W�F�^�C�v�̎擾
			OBJTYPE objType;
			objType = pScene->GetObjType();

			if (objType == OBJTYPE_PLAYER)
			{
				m_PartStatus[HEAD].m_pos.x = player_pos.x;
			}

			//���̉�]
		/*	m_PartStatus[HEAD].m_rot.z -= D3DX_PI * 0.01f;

			if (m_PartStatus[HEAD].m_rot.z >= D3DX_PI)
			{
				m_PartStatus[HEAD].m_rot.z += D3DX_PI * 2.0f;
			}

			m_PartStatus[EYE].m_rot.z -= D3DX_PI * 0.01f;

			if (m_PartStatus[EYE].m_rot.z >= D3DX_PI)
			{
				m_PartStatus[EYE].m_rot.z += D3DX_PI * 2.0f;
			}

			m_PartStatus[EYEFLAME].m_rot.z -= D3DX_PI * 0.01f;

			if (m_PartStatus[EYEFLAME].m_rot.z >= D3DX_PI)
			{
				m_PartStatus[EYEFLAME].m_rot.z += D3DX_PI * 2.0f;
			}

			m_PartStatus[CHIN].m_rot.z -= D3DX_PI * 0.01f;

			if (m_PartStatus[CHIN].m_rot.z >= D3DX_PI)
			{
				m_PartStatus[CHIN].m_rot.z += D3DX_PI * 2.0f;
			}*/

			m_PartStatus[EYE].m_pos = D3DXVECTOR3(m_PartStatus[HEAD].m_pos.x, m_PartStatus[HEAD].m_pos.y + -10.0f * m_PartStatus[EYE].m_fScale, 0.0f);
			m_PartStatus[EYEFLAME].m_pos = D3DXVECTOR3(m_PartStatus[HEAD].m_pos.x, m_PartStatus[HEAD].m_pos.y - 20.0f * m_PartStatus[EYEFLAME].m_fScale, 0.0f);
			m_PartStatus[CHIN].m_pos = D3DXVECTOR3(m_PartStatus[HEAD].m_pos.x, m_PartStatus[HEAD].m_pos.y + 150.0f * m_PartStatus[CHIN].m_fScale, 0.0f);

			m_PartStatus[CORE_01].m_pos = D3DXVECTOR3(m_PartStatus[CORE].m_pos.x, m_PartStatus[CORE].m_pos.y + -40.0f * m_PartStatus[CORE_01].m_fScale, 0.0f);
			m_PartStatus[CORE_02].m_pos = D3DXVECTOR3(m_PartStatus[CORE].m_pos.x, m_PartStatus[CORE].m_pos.y + -150.0f * m_PartStatus[CORE_02].m_fScale, 0.0f);
			m_PartStatus[BODY_RIGHT].m_pos = D3DXVECTOR3(m_PartStatus[CORE].m_pos.x - 145.0f * m_PartStatus[BODY_RIGHT].m_fScale, m_PartStatus[CORE].m_pos.y + -170.0f * m_PartStatus[BODY_RIGHT].m_fScale, 0.0f);
			m_PartStatus[BODY_LEFT].m_pos = D3DXVECTOR3(m_PartStatus[CORE].m_pos.x + 145.0f * m_PartStatus[BODY_RIGHT].m_fScale, m_PartStatus[CORE].m_pos.y + -170.0f * m_PartStatus[BODY_LEFT].m_fScale, 0.0f);

			m_PartStatus[HAND_RIGHT].m_rot.z = 60.0f;
			m_PartStatus[FOREARM_RIGHT].m_rot.z = 60.0f;  //120 + 235
			m_PartStatus[FOREARM_RIGHT].m_pos.y = 180.0f; //540
			m_PartStatus[UPPERARM_RIGHT].m_rot.z = 60.0f;
			//m_PartStatus[FOREARM_RIGHT].m_pos.y + 60.0f;
		}
	}

	for (int nCount = 0; nCount < PART_MAX; nCount++)
	{
		m_apScene[nCount]->Update();

		// ���_���W��ݒ�
		m_PartStatus[nCount].m_vpos[0].x = m_PartStatus[nCount].m_pos.x - cosf(m_PartStatus[nCount].m_fAngle - m_PartStatus[nCount].m_rot.z) * m_PartStatus[nCount].m_fLength * m_PartStatus[nCount].m_fScale;
		m_PartStatus[nCount].m_vpos[0].y = m_PartStatus[nCount].m_pos.y - sinf(m_PartStatus[nCount].m_fAngle - m_PartStatus[nCount].m_rot.z) * m_PartStatus[nCount].m_fLength * m_PartStatus[nCount].m_fScale;
		m_PartStatus[nCount].m_vpos[0].z = 0.0f;

		m_PartStatus[nCount].m_vpos[1].x = m_PartStatus[nCount].m_pos.x + cosf(m_PartStatus[nCount].m_fAngle + m_PartStatus[nCount].m_rot.z) * m_PartStatus[nCount].m_fLength * m_PartStatus[nCount].m_fScale;
		m_PartStatus[nCount].m_vpos[1].y = m_PartStatus[nCount].m_pos.y - sinf(m_PartStatus[nCount].m_fAngle + m_PartStatus[nCount].m_rot.z) * m_PartStatus[nCount].m_fLength * m_PartStatus[nCount].m_fScale;
		m_PartStatus[nCount].m_vpos[1].z = 0.0f;

		m_PartStatus[nCount].m_vpos[2].x = m_PartStatus[nCount].m_pos.x - cosf(m_PartStatus[nCount].m_fAngle + m_PartStatus[nCount].m_rot.z) * m_PartStatus[nCount].m_fLength * m_PartStatus[nCount].m_fScale;
		m_PartStatus[nCount].m_vpos[2].y = m_PartStatus[nCount].m_pos.y + sinf(m_PartStatus[nCount].m_fAngle + m_PartStatus[nCount].m_rot.z) * m_PartStatus[nCount].m_fLength * m_PartStatus[nCount].m_fScale;
		m_PartStatus[nCount].m_vpos[2].z = 0.0f;

		m_PartStatus[nCount].m_vpos[3].x = m_PartStatus[nCount].m_pos.x + cosf(m_PartStatus[nCount].m_fAngle - m_PartStatus[nCount].m_rot.z) * m_PartStatus[nCount].m_fLength * m_PartStatus[nCount].m_fScale;
		m_PartStatus[nCount].m_vpos[3].y = m_PartStatus[nCount].m_pos.y + sinf(m_PartStatus[nCount].m_fAngle - m_PartStatus[nCount].m_rot.z) * m_PartStatus[nCount].m_fLength * m_PartStatus[nCount].m_fScale;
		m_PartStatus[nCount].m_vpos[3].z = 0.0f;

		//�ʒu�X�V
		m_PartStatus[nCount].m_pos += m_PartStatus[nCount].m_move;
		//�ʒu�̃Z�b�g
		m_apScene[nCount]->SetPosition(m_PartStatus[nCount].m_pos);
		//���_���W�̃Z�b�g
		m_apScene[nCount]->SetVertexPosition(m_PartStatus[nCount].m_vpos);
		//�e�N�X�`�����Z�b�g
		m_apScene[nCount]->SetTex(
			0.0f,
			0.0f,
			1.0f,
			1.0f);
	}
}

//=============================================================================
// �`��֐�
//=============================================================================
void CBoss::Draw(void)
{
}

//=============================================================================
// �̗͂̌��Z�֐�
//=============================================================================
void CBoss::SubLife(int nValue)
{
}
