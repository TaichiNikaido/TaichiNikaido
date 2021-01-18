//=============================================================================
//
// ポーズ処理 [pause.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _PAUSE_H_
#define _PAUSE_H_
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_FLAME	"data/TEXTURE/Battlesahip.png"	//プレイヤーのテクスチャの保存先
#define TEXTURE_BACK_TO_THE_GAME	"data/TEXTURE/backgame.png"	//プレイヤーのテクスチャの保存先
#define TEXTURE_RESTART	"data/TEXTURE/restart.png"	//プレイヤーのテクスチャの保存先
#define TEXTURE_BACK_TO_THE_TITLE	"data/TEXTURE/ex.png"	//プレイヤーのテクスチャの保存先
#define BUTTON_SIZE_WIDTH 300
#define BUTTON_SIZE_HEIGHT 100
#define FLAME_SIZE_WIDTH 500
#define FLAME_SIZE_HEIGHT 600

#define COUNT_TRIGGER_PAUSE 5 //押し中のトリガーカウント
//*****************************************************************************
// クラス定義
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
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	//バッファ
	D3DXVECTOR3 m_pos;
	int m_nSizeX;
	int m_nSizeY;
	typedef struct
	{
		int nCount;
		bool bTrigger;
	}IsCount;//推されてるか？と押し中カウント
	typedef struct
	{
		IsCount Up;
		IsCount Down;
		IsCount Right;
		IsCount Left;
	}IsPress;//推されてるか？
	IsPress m_IsTrigger;                                         //推されてるかどうか
	int     m_TriggerCount;                                     //押し中のカウンタ
	int                       m_nButtonPos;
	int                       m_aButtonAlpha[TYPE_MAX];
};
#endif