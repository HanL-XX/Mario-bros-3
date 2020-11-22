#include "Goomba.h"
#include <ctime>
#include "Utils.h"
#include "box.h"
#include "Coin.h"
#include "Street.h"
#include "BackInvis.h"


CGoomba::CGoomba()
{
	SetState(GOOMBA_STATE_WALKING);
}

void CGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	if (state==GOOMBA_STATE_BM)
	{
		left = NULL;
		top = NULL;
		right = NULL;
		bottom = NULL;
	}
	else if (state == GOOMBA_STATE_DIE)
		bottom = y + GOOMBA_BBOX_HEIGHT_DIE;
	else if (state == GOOMBA_STATE_PARA_WALK)
	{
		right = x + GOOMBA_BBOX_PARA_WIDTH;
		bottom = y + GOOMBA_BBOX_PARA_HEIGHT;
	}
	else if (state == GOOMBA_STATE_PARA_FLY)
	{
		right = x + GOOMBA_BBOX_PARA_FLY_WIDTH;
		bottom = y + GOOMBA_BBOX_PARA_FLY_HEIGHT;
	}
	else 
	{
		bottom = y + GOOMBA_BBOX_HEIGHT;
		right = x + GOOMBA_BBOX_WIDTH;
	}
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	if (timedie != NULL)
	{
		DWORD td = GetTickCount64() - timedie;
		if (td > GOOMBA_TIME_DIE)
			SetState(GOOMBA_STATE_BM);
		//DebugOut(L"\timedie = %f\n", td);
	}
	if (state == GOOMBA_STATE_BM)
	{
		return;
	}
	vy += GOOMBA_GRAVITY * &dt;
	CGameObject::Update(dt, coObjects);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();
	if (state != GOOMBA_STATE_DIE) {
		CalcPotentialCollisions(coObjects, coEvents);
	}
	else
		return;
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx , ny;
		float rdx = 0;
		float rdy = 0;
		// TODO: This is a very ugly designed function!!!!
		for (UINT i = 0; i < coEvents.size(); i++)
		{
			LPCOLLISIONEVENT e = coEvents[i];
			if (dynamic_cast<Cbox*>(e->obj))
			{
				FilterCollisionbox(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
			}
			else if (dynamic_cast<CCoin*>(e->obj)|| dynamic_cast<CBackInvis*>(e->obj))
			{
				FilterCollisioncoin(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
			}
			else
			{
				FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
			}
		}
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			//DebugOut(L"\nsize: %d", coEventsResult.size());

			LPCOLLISIONEVENT e = coEventsResult.at(i);
			if (nx != 0) vx = -vx;
			if (ny < 0) vy = 0;
			x += min_tx * dx + nx * 0.8f;
			y += min_ty * dy + ny * 0.4f;
		}
	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
void CGoomba::Render()
{
	int ani = GOOMBA_ANI_WALKING;
	if (state == GOOMBA_STATE_BM)
		return;
	if (state == GOOMBA_STATE_DIE)
	{
		ani = GOOMBA_ANI_DIE;
	}
	if (state == GOOMBA_STATE_PARA_WALK)
	{
		ani = GOOMBA_ANI_PARA_WALK;
	}
	if (state == GOOMBA_STATE_PARA_FLY)
	{
		ani = GOOMBA_ANI_PARA_FLY;
	}
	animation_set->at(ani)->Render(x, y);
	//DebugOut(L"\nStateRender: %d", state);
}
void CGoomba::FilterCollision(
	vector<LPCOLLISIONEVENT>& coEvents,
	vector<LPCOLLISIONEVENT>& coEventsResult,
	float& min_tx, float& min_ty,
	float& nx, float& ny, float& rdx, float& rdy)
{
	min_tx = 1.0f;
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	nx = 0.0f;
	ny = 0.0f;

	coEventsResult.clear();

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT c = coEvents[i];
		if (c->t < min_tx && c->nx != 0) {
			min_tx = c->t; nx = c->nx; min_ix = i; rdx = c->dx;
		}
		if (c->t < min_ty && c->ny != 0) {
			min_ty = c->t; ny = c->ny; min_iy = i; rdy = c->dy;
		}
	}
	if (min_ix >= 0) coEventsResult.push_back(coEvents[min_ix]);
	if (min_iy >= 0) coEventsResult.push_back(coEvents[min_iy]);
}
void CGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	timedie = NULL;
	switch (state)
	{
	case GOOMBA_STATE_DIE:
		y += GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE + 1;
		timedie = GetTickCount64();
		vx = 0;
		vy = 0;
		break;
	case GOOMBA_STATE_WALKING:
		vx = -GOOMBA_WALKING_SPEED;
		break;
	case GOOMBA_STATE_PARA_WALK:
		vx = -GOOMBA_WALKING_SPEED;
		break;
	case GOOMBA_STATE_PARA_FLY:
		vx = -GOOMBA_WALKING_SPEED;
		break;
	}
	//DebugOut(L"\nrun = %f\n", timedie);

}
void CGoomba::Clear()
{
	SetState(GOOMBA_STATE_DIE);
}