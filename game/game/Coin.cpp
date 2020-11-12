#include "Coin.h"

CCoin::CCoin()
{
	SetState(COIN_XH);
}
void CCoin::Render()
{
	if (state == COIN_XH)
	{
		animation_set->at(0)->Render(x, y);
		RenderBoundingBox();
	}
	else
		return;
}
void CCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	//
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
	// 
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	if (state == COIN_BM)
	{
		return;
	}
}
void CCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (state == COIN_BM)
	{
		l = NULL;
		t = NULL;
		r = NULL;
		b = NULL;
	}
	else
	{
		l = x;
		t = y;
		r = x + COIN_BBOX_WIDTH;
		b = y + COIN_BBOX_HEIGHT;
	}
}
void CCoin::Clear()
{
	SetState(COIN_BM);
}