#include "main.h"
#include "manager.h"
#include "mode_game.h"
#include "renderer.h"
#include "CollisionBlock.h"
#include "player.h"

CCollisionBlock::CCollisionBlock()
{
}

CCollisionBlock::~CCollisionBlock()
{
}

CCollisionBlock * CCollisionBlock::Create(D3DXVECTOR3 Position, D3DXVECTOR3 Size)
{
	CCollisionBlock * pCollisionBlock = NULL;
	if (pCollisionBlock == NULL)
	{
		pCollisionBlock = new CCollisionBlock;
	}
	if (pCollisionBlock != NULL)
	{
		pCollisionBlock->Init();
		pCollisionBlock->SetPosition(Position);
		pCollisionBlock->SetSize(Size);
	}
	return pCollisionBlock;
}

HRESULT CCollisionBlock::Init(void)
{
	CBillboard::Init();
	SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f,1.0f));
	return S_OK;
}

void CCollisionBlock::Uninit(void)
{
	CBillboard::Uninit();
}

void CCollisionBlock::Update(void)
{
	CBillboard::Update();
	//CPlayer * pPlayer = CGameMode::GetPlayer();
	//D3DXVECTOR3 PlayerPosition = D3DXVECTOR3(pPlayer->GetModel(0)->GetModelData().mtxWorld._41, pPlayer->GetModel(0)->GetModelData().mtxWorld._42 - 20.0f, pPlayer->GetModel(0)->GetModelData().mtxWorld._43);
	//D3DXVECTOR3 PlayerCollisionSize = pPlayer->GetCollisionSize();
	//SetPosition(PlayerPosition);
	//SetSize(PlayerCollisionSize);
}

void CCollisionBlock::Draw(void)
{
	CBillboard::Draw();
}
