#ifndef _TEXT_H_
#define _TEXT_H_

#define MAX_TEXT 10
#define FONT_NAME "PixelMplus12"

class CText
{
public:
	//typedef enum
	//{
	//	MODE_GAME,
	//	MODE_RESULT,
	//	MODE_RANKING,
	//	MODE_MAX
	//};
	CText();
	~CText();
	static HRESULT Load(void);
	static void Unload(void);
	static CText *Create(D3DXVECTOR3 pos, float fSizeWidth, float fSizeHeight);
	HRESULT Init(D3DXVECTOR3 pos, float fSizeWidth, float fSizeHeight);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void IsDrawText(bool bDraw) { m_IsDraw = bDraw; };
private:
	LPD3DXFONT				m_pFont;		// フォントへのポインタ
	RECT                    m_Rect[4];
	int                     posX;
	int                     posY;
	static char                  m_str[256];
	//CManager::PlayerData m_playerData;//プレイヤーデータ
	static bool             m_IsDraw;

};
#endif // !_TEXT_H_