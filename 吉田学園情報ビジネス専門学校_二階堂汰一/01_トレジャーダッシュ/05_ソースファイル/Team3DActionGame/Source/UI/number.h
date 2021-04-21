//================================================
//
// 数字表示処理 [number.h]
// Author : 佐藤颯紀
//
//================================================

#ifndef  _NUMBER_H_
#define  _NUMBER_H_

#include "Base/main.h"
//================================================
//マクロ定義
//================================================
#define NUMBER_TYPE (2)		// 数字の種類

//================================================
//クラス宣言
//================================================
class CNumber
{
public:
	typedef enum
	{
		NUMBERTYPE_NONE = -1,
		NUMBERTYPE_DAIYA,
		NUMBERTYPE_MEAT,
		NUMBERTYPE_SCORE,
		NUMBERTYPE_MAX
	}NUMBERTYPE;

	CNumber();
	~CNumber();

	static HRESULT Load(void);
	static void Unload(void);
	static CNumber *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, NUMBERTYPE type);

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, NUMBERTYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetNumber(int nNumber);

	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	D3DXVECTOR3 GetSize(void) { return m_size; }

private:
	static LPDIRECT3DTEXTURE9	m_apTexture[NUMBERTYPE_MAX];
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;
	NUMBERTYPE  m_type;
	D3DXVECTOR3	m_pos;	//ポリゴンの位置
	D3DXVECTOR3 m_size;	//ポリゴンのサイズ

	int m_nNumber;		//ナンバー

};

#endif // ! _NUMBER_H_
