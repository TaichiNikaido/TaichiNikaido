//=============================================================================
//
// ranking [ranking.h]
// Author : 二階堂汰一
//
//=============================================================================
#ifndef _RANKING_H_
#define _RANKING_H_
//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "scene.h"
#include "scene2d.h"
#include "name.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_RANKING	"data/TEXTURE/rankingbg.png"
#define MAX_RANKING_TEXTURE 3
#define MAX_RANKING 10				// ランキングデータ数
#define NAME "test"
#define SERVER_IP_NUM "127.0.0.1"
#define SERVER_PORT_NUM 12345
#define BUFFER_NUM 1024

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CResult;

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CRanking :public CScene
{
public:
	typedef struct
	{
		int nScore;
		char aName[MAX_NAME];
	} RankingData;

	typedef enum
	{
		COMMAND_TYPE_NONE = 0,
		COMMAND_TYPE_GET_RANKING,		// ランキング一覧を取得
		COMMAND_TYPE_SET_RANKING		// ランキングを設定
	} COMMAND_TYPE;

	CRanking(int nPriority = 0);
	~CRanking();
	static HRESULT Load(void);
	static void Unload(void);
	static CRanking * Create(D3DXVECTOR3 pos, float SizeHeight, float SizeWidth);
	HRESULT Init(D3DXVECTOR3 pos, float SizeHeight, float SizeWidth);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static RankingData * GetRankingData(void) { return m_aRankingData; }
	void    GetRanking(RankingData * pRankingData);
	int     SetRanking(int nScore, char aName[MAX_NAME]);
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_RANKING_TEXTURE];
	static RankingData	m_aRankingData[MAX_RANKING];//ランキングデータ
	D3DXVECTOR3 m_pos;
	CScene2d * m_apScene[MAX_POLYGON];
	D3DXVECTOR3 m_vpos[NUM_VERTEX];
	D3DCOLOR m_col[NUM_VERTEX];
	float m_fTextureX;
	float m_fTextureY;
	float m_fFastMove;
	float m_fSlowMove;
	float m_fMove;
	float m_fWidth;
	float m_fHeight;
};
#endif