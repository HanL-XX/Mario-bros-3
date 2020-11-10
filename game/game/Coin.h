#pragma once
#include "GameObject.h"

#define COIN_BBOX_WIDTH  16
#define COIN_BBOX_HEIGHT 16

#define	COIN_XH	1
#define COIN_BM	0

class CCoin : public CGameObject
{
public:
	CCoin();
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Clear();
};