//=============================================================================
//
// �|�[�Y���� [pause.h]
// Author : ��K������
//
//=============================================================================
#ifndef _PAUSE_H_
#define _PAUSE_H_
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_FLAME	"data/TEXTURE/Battlesahip.png"	//�v���C���[�̃e�N�X�`���̕ۑ���
#define TEXTURE_BACK_TO_THE_GAME	"data/TEXTURE/backgame.png"	//�v���C���[�̃e�N�X�`���̕ۑ���
#define TEXTURE_RESTART	"data/TEXTURE/restart.png"	//�v���C���[�̃e�N�X�`���̕ۑ���
#define TEXTURE_BACK_TO_THE_TITLE	"data/TEXTURE/ex.png"	//�v���C���[�̃e�N�X�`���̕ۑ���
#define BUTTON_SIZE_WIDTH 300
#define BUTTON_SIZE_HEIGHT 100
#define FLAME_SIZE_WIDTH 500
#define FLAME_SIZE_HEIGHT 600

#define COUNT_TRIGGER_PAUSE 5 //�������̃g���K�[�J�E���g
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CPause
{
public:
	typedef enum
	{
		TYPE_NONE = -1,
		TYPE_BG,
		TYPE_FLAME,
		TYPE_BACK_TO_THE_GAME,
		TYPE_RESTART,
		TYPE_BACK_TO_THE_TITLE,
		TYPE_MAX
	}TYPE;
	CPause();
	~CPause();
	static HRESULT Load(void);
	static void Unload(void);
	static CPause * Create(D3DXVECTOR3 pos, int sizeX, int sizeY);
	HRESULT Init(D3DXVECTOR3 pos, int sizeX, int sizeY);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:

	static LPDIRECT3DTEXTURE9 m_apTexture[TYPE_MAX];
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//�o�b�t�@
	D3DXVECTOR3 m_pos;
	int m_nSizeX;
	int m_nSizeY;
	typedef struct
	{
		int nCount;
		bool bTrigger;
	}IsCount;//������Ă邩�H�Ɖ������J�E���g
	typedef struct
	{
		IsCount Up;
		IsCount Down;
		IsCount Right;
		IsCount Left;
	}IsPress;//������Ă邩�H
	IsPress m_IsTrigger;                                         //������Ă邩�ǂ���
	int     m_TriggerCount;                                     //�������̃J�E���^
	int                       m_nButtonPos;
	int                       m_aButtonAlpha[TYPE_MAX];
};
#endif