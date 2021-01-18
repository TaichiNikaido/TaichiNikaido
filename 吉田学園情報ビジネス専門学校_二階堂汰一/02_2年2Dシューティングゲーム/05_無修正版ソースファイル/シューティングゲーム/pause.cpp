//=============================================================================
//
// �|�[�Y���� [pause.cpp]
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
#include "input.h"
#include "keyboard.h"
#include "joystick.h"
#include "sound.h"
#include "title.h"
#include "result.h"
#include "pause.h"
#include "dragon.h"
#include "wormhole.h"

LPDIRECT3DTEXTURE9 CPause::m_apTexture[TYPE_MAX] = {};

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CPause::CPause()
{
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nSizeX = 0;
	m_nSizeY = 0;
	m_nButtonPos = 2;
	memset(m_aButtonAlpha, 0, sizeof(m_aButtonAlpha));
	m_IsTrigger.Down.bTrigger = false;//������Ă邩�ǂ���
	m_IsTrigger.Up.bTrigger = false;
	m_IsTrigger.Left.bTrigger = false;
	m_IsTrigger.Right.bTrigger = false;
	m_IsTrigger.Down.nCount = 0;//������Ă邩�ǂ���
	m_IsTrigger.Up.nCount = 0;
	m_IsTrigger.Left.nCount = 0;
	m_IsTrigger.Right.nCount = 0;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CPause::~CPause()
{
}

//=============================================================================
// �e�N�X�`�����[�h�֐�
//=============================================================================
HRESULT CPause::Load(void)
{
	//�����_���[�̎擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		NULL,								     // �t�@�C���̖��O
		&m_apTexture[TYPE_BG]);					// �ǂݍ��ރ������[

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_FLAME,								// �t�@�C���̖��O
		&m_apTexture[TYPE_FLAME]);					// �ǂݍ��ރ������[

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_BACK_TO_THE_GAME,								// �t�@�C���̖��O
		&m_apTexture[TYPE_BACK_TO_THE_GAME]);		// �ǂݍ��ރ������[

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_RESTART,								// �t�@�C���̖��O
		&m_apTexture[TYPE_RESTART]);					// �ǂݍ��ރ������[

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_BACK_TO_THE_TITLE,								// �t�@�C���̖��O
		&m_apTexture[TYPE_BACK_TO_THE_TITLE]);		// �ǂݍ��ރ������[
	return S_OK;
}

//=============================================================================
// �e�N�X�`���A�����[�h�֐�
//=============================================================================
void CPause::Unload(void)
{
	// �e�N�X�`���̔j��
	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}

//=============================================================================
//�����֐�
//=============================================================================
CPause * CPause::Create(D3DXVECTOR3 pos, int sizeX, int sizeY)
{
	CPause * pPause;
	//�������m��
	pPause = new CPause;
	//������
	pPause->Init(pos, sizeX, sizeY);
	return pPause;
}

//=============================================================================
//�������֐�
//=============================================================================
HRESULT CPause::Init(D3DXVECTOR3 pos, int sizeX, int sizeY)
{
	//������
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	m_pos = pos;
	m_nSizeX = sizeX;
	m_nSizeY = sizeY;

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX * TYPE_MAX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_2D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&m_pVtxBuff,				// ���_�o�b�t�@�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�w�i
	pVtx[0].pos = D3DXVECTOR3(m_pos.x + (-SCREEN_WIDTH / 2), m_pos.y + (-SCREEN_HEIGHT / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (SCREEN_WIDTH / 2), m_pos.y + (-SCREEN_HEIGHT / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + (-SCREEN_WIDTH / 2), m_pos.y + (SCREEN_HEIGHT / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (SCREEN_WIDTH / 2), m_pos.y + (SCREEN_HEIGHT / 2), 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DCOLOR_RGBA(100, 100, 100, 100);
	pVtx[1].col = D3DCOLOR_RGBA(100, 100, 100, 100);
	pVtx[2].col = D3DCOLOR_RGBA(100, 100, 100, 100);
	pVtx[3].col = D3DCOLOR_RGBA(100, 100, 100, 100);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;

	//�t���[��
	pVtx[0].pos = D3DXVECTOR3(m_pos.x + (-FLAME_SIZE_WIDTH / 2), m_pos.y + (-FLAME_SIZE_HEIGHT / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (FLAME_SIZE_WIDTH / 2), m_pos.y + (-FLAME_SIZE_HEIGHT / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + (-FLAME_SIZE_WIDTH / 2), m_pos.y + (FLAME_SIZE_HEIGHT / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (FLAME_SIZE_WIDTH / 2), m_pos.y + (FLAME_SIZE_HEIGHT / 2), 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;

	//�Q�[���ɖ߂�{�^��
	pVtx[0].pos = D3DXVECTOR3(m_pos.x + (-BUTTON_SIZE_WIDTH / 2), 500.0f + (-BUTTON_SIZE_HEIGHT / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (BUTTON_SIZE_WIDTH / 2), 500.0f + (-BUTTON_SIZE_HEIGHT / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + (-BUTTON_SIZE_WIDTH / 2), 500.0f + (BUTTON_SIZE_HEIGHT / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (BUTTON_SIZE_WIDTH / 2), 500.0f + (BUTTON_SIZE_HEIGHT / 2), 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;

	//�ŏ�����{�^��
	pVtx[0].pos = D3DXVECTOR3(m_pos.x + (-BUTTON_SIZE_WIDTH / 2), 550.0f + (-BUTTON_SIZE_HEIGHT / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (BUTTON_SIZE_WIDTH / 2), 550.0f + (-BUTTON_SIZE_HEIGHT / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + (-BUTTON_SIZE_WIDTH / 2), 550.0f + (BUTTON_SIZE_HEIGHT / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (BUTTON_SIZE_WIDTH / 2), 550.0f + (BUTTON_SIZE_HEIGHT / 2), 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;

	//�^�C�g���ɖ߂�{�^��
	pVtx[0].pos = D3DXVECTOR3(m_pos.x + (-BUTTON_SIZE_WIDTH / 2), 600.0f + (-BUTTON_SIZE_HEIGHT / 2), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (BUTTON_SIZE_WIDTH / 2), 600.0f + (-BUTTON_SIZE_HEIGHT / 2), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + (-BUTTON_SIZE_WIDTH / 2), 600.0f + (BUTTON_SIZE_HEIGHT / 2), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (BUTTON_SIZE_WIDTH / 2), 600.0f + (BUTTON_SIZE_HEIGHT / 2), 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//pVtx += 4;

	m_pVtxBuff->Unlock();
	return S_OK;
}

//=============================================================================
//�I���֐�
//=============================================================================
void CPause::Uninit(void)
{
	//�I��
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//=============================================================================
//�X�V�֐�
//=============================================================================
void CPause::Update(void)
{
	//�T�E���h
	CSound * pSound = CManager::GetSound();
	if (CManager::GetbPause() == true)
	{
		//�W���C�p�b�h
		CInputJoystick * pInputJoystick = CManager::GetInputJoystick();
		LPDIRECTINPUTDEVICE8 lpDIDevice = CInputJoystick::GetDevice();
		DIJOYSTATE js;
		if (lpDIDevice != NULL)
		{
			lpDIDevice->Poll();
			lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE), &js);
		}

		if (lpDIDevice != NULL &&js.lY == -1000)//��
		{
			m_IsTrigger.Up.nCount++;
		}
		if (lpDIDevice != NULL &&js.lY == 1000)//��
		{
			m_IsTrigger.Down.nCount++;
		}

		if (m_IsTrigger.Up.nCount > COUNT_TRIGGER_PAUSE)
		{
			m_IsTrigger.Up.bTrigger = true;
			m_IsTrigger.Up.nCount = COUNT_TRIGGER_PAUSE - 5;
		}
		if (m_IsTrigger.Down.nCount > COUNT_TRIGGER_PAUSE)
		{
			m_IsTrigger.Down.bTrigger = true;
			m_IsTrigger.Down.nCount = COUNT_TRIGGER_PAUSE - 5;
		}
		//��������󂪉�����炽��
		if (m_IsTrigger.Down.bTrigger == true)
		{

			m_IsTrigger.Down.bTrigger = false;
			if (m_nButtonPos < 4)
			{
				////�V���b�g���̍Đ�
				//pSound->CSound::PlaySound(CSound::SOUND_LABEL_SE_SELECT);
				m_nButtonPos++;
			}
		}

		//�������󂪉������
		if (m_IsTrigger.Up.bTrigger == true)
		{

			m_IsTrigger.Up.bTrigger = false;
			if (m_nButtonPos > 2)
			{
				////�V���b�g���̍Đ�
				//pSound->CSound::PlaySound(CSound::SOUND_LABEL_SE_SELECT);
				m_nButtonPos--;
			}
		}

		if (lpDIDevice != NULL && pInputJoystick->GetJoystickTrigger(JS_A))//����
		{
			////�V���b�g���̍Đ�
			//pSound->CSound::PlaySound(CSound::SOUND_LABEL_SE_ENTER);
			switch (m_nButtonPos)
			{
			case 2://�Q�[���߂�{�^��
				CManager::SetbPause(false);
				m_nButtonPos = 2;
				break;
			case 3://�ŏ�����{�^��
				CDragon::SetSpawn(false);
				CDragon::SetDeath(false);
				CWormhole::SetSpawn(false);
				CManager::StartFade(CManager::MODE_GAME);
				CManager::SetbPause(false);
				m_nButtonPos = 2;
				break;
			case 4://�^�C�g���ɂ��ǂ�
				pSound->StopSound();
				CDragon::SetSpawn(false);
				CDragon::SetDeath(false);
				CWormhole::SetSpawn(false);
				CManager::StartFade(CManager::MODE_TITLE);
				CManager::SetbPause(false);
				m_nButtonPos = 2;
				break;
			default:
				break;
			}
		}

		for (int nCnt = 2; nCnt <= 4; nCnt++)
		{
			m_aButtonAlpha[nCnt] = 100;
		}
		switch (m_nButtonPos)
		{
		case 2://�Q�[���߂�{�^��
			m_aButtonAlpha[TYPE_BACK_TO_THE_GAME] = 255;
			break;
		case 3://�ŏ�����{�^��
			m_aButtonAlpha[TYPE_RESTART] = 255;
			break;
		case 4://�^�C�g���ɂ��ǂ�
			m_aButtonAlpha[TYPE_BACK_TO_THE_TITLE] = 255;
			break;
		default:
			break;
		}

		//���_����ݒ�
		VERTEX_2D *pVtx;

		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//�w�i
		pVtx[0].pos = D3DXVECTOR3(m_pos.x + (-SCREEN_WIDTH / 2), m_pos.y + (-SCREEN_HEIGHT / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + (SCREEN_WIDTH / 2), m_pos.y + (-SCREEN_HEIGHT / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x + (-SCREEN_WIDTH / 2), m_pos.y + (SCREEN_HEIGHT / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + (SCREEN_WIDTH / 2), m_pos.y + (SCREEN_HEIGHT / 2), 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DCOLOR_RGBA(100, 100, 100, 100);
		pVtx[1].col = D3DCOLOR_RGBA(100, 100, 100, 100);
		pVtx[2].col = D3DCOLOR_RGBA(100, 100, 100, 100);
		pVtx[3].col = D3DCOLOR_RGBA(100, 100, 100, 100);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;

		//�t���[��
		pVtx[0].pos = D3DXVECTOR3(m_pos.x + (-FLAME_SIZE_WIDTH / 2), m_pos.y + (-FLAME_SIZE_HEIGHT / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + (FLAME_SIZE_WIDTH / 2), m_pos.y + (-FLAME_SIZE_HEIGHT / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x + (-FLAME_SIZE_WIDTH / 2), m_pos.y + (FLAME_SIZE_HEIGHT / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + (FLAME_SIZE_WIDTH / 2), m_pos.y + (FLAME_SIZE_HEIGHT / 2), 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;

		//�Q�[���ɖ߂�{�^��
		pVtx[0].pos = D3DXVECTOR3(m_pos.x + (-BUTTON_SIZE_WIDTH / 2), 500.0f + (-BUTTON_SIZE_HEIGHT / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + (BUTTON_SIZE_WIDTH / 2), 500.0f + (-BUTTON_SIZE_HEIGHT / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x + (-BUTTON_SIZE_WIDTH / 2), 500.0f + (BUTTON_SIZE_HEIGHT / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + (BUTTON_SIZE_WIDTH / 2), 500.0f + (BUTTON_SIZE_HEIGHT / 2), 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, m_aButtonAlpha[TYPE_BACK_TO_THE_GAME]);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, m_aButtonAlpha[TYPE_BACK_TO_THE_GAME]);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, m_aButtonAlpha[TYPE_BACK_TO_THE_GAME]);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, m_aButtonAlpha[TYPE_BACK_TO_THE_GAME]);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;

		//�ŏ�����{�^��
		pVtx[0].pos = D3DXVECTOR3(m_pos.x + (-BUTTON_SIZE_WIDTH / 2), 550.0f + (-BUTTON_SIZE_HEIGHT / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + (BUTTON_SIZE_WIDTH / 2), 550.0f + (-BUTTON_SIZE_HEIGHT / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x + (-BUTTON_SIZE_WIDTH / 2), 550.0f + (BUTTON_SIZE_HEIGHT / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + (BUTTON_SIZE_WIDTH / 2), 550.0f + (BUTTON_SIZE_HEIGHT / 2), 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, m_aButtonAlpha[TYPE_RESTART]);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, m_aButtonAlpha[TYPE_RESTART]);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, m_aButtonAlpha[TYPE_RESTART]);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, m_aButtonAlpha[TYPE_RESTART]);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;

		//�^�C�g���ɖ߂�{�^��
		pVtx[0].pos = D3DXVECTOR3(m_pos.x + (-BUTTON_SIZE_WIDTH / 2), 600.0f + (-BUTTON_SIZE_HEIGHT / 2), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + (BUTTON_SIZE_WIDTH / 2), 600.0f + (-BUTTON_SIZE_HEIGHT / 2), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x + (-BUTTON_SIZE_WIDTH / 2), 600.0f + (BUTTON_SIZE_HEIGHT / 2), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + (BUTTON_SIZE_WIDTH / 2), 600.0f + (BUTTON_SIZE_HEIGHT / 2), 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, m_aButtonAlpha[TYPE_BACK_TO_THE_TITLE]);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, m_aButtonAlpha[TYPE_BACK_TO_THE_TITLE]);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, m_aButtonAlpha[TYPE_BACK_TO_THE_TITLE]);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, m_aButtonAlpha[TYPE_BACK_TO_THE_TITLE]);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//���_�o�b�t�@�̃A�����b�N
		m_pVtxBuff->Unlock();

		////�L�[�{�[�h�̃A�b�v�f�[�g(���ꂪ�Ȃ���Trigger������ɋ@�\���Ȃ�)
		//pInputKeyboard->UpdateInput();
		//�W���C�X�e�B�b�N�̃A�b�v�f�[�g(���ꂪ�Ȃ���Trigger������ɋ@�\���Ȃ�)
		pInputJoystick->UpdateInput();
	}
}

//=============================================================================
//�`��֐�
//=============================================================================
void CPause::Draw(void)
{
	////�`��
	//LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	//pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));
	//// ���_�t�H�[�}�b�g�̐ݒ�
	//pDevice->SetFVF(FVF_VERTEX_2D);

	//for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	//{
	//	// �e�N�X�`���̐ݒ�
	//	pDevice->SetTexture(0, m_apTexture[nCount]);
	//	// �|���S���̕`��
	//	pDevice->DrawPrimitive(
	//		D3DPT_TRIANGLESTRIP,
	//		(NUM_VERTEX * nCount),
	//		NUM_POLYGON);
	//}
}