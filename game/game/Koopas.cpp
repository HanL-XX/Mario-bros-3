#include "Koopas.h"
#include "Utils.h"
#include "box.h"
#include "Coin.h"
#include "BackInvis.h"
#include "Mario.h"
#include "Street.h"
#include "Brick.h"
#include "Goomba.h"

CKoopas::CKoopas()
{
	SetState(KOOPAS_STATE_WALKING);
}

void CKoopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + KOOPAS_BBOX_WIDTH;

	if (state == KOOPAS_STATE_DIE||state== KOOPAS_STATE_DIE_SWAP||state==KOOPAS_STATE_BACKUP|| state == KOOPAS_STATE_BACKUP_SWAP)
		bottom = y + KOOPAS_BBOX_HEIGHT_DIE;
	else
		bottom = y + KOOPAS_BBOX_HEIGHT;
}

void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (timedie)
	{
		if (GetTickCount64() - timedie > KOOPAS_TIME_DIE_AGEL)
		{
			if(state==KOOPAS_STATE_DIE)
				SetState(KOOPAS_STATE_BACKUP);
			else
				SetState(KOOPAS_STATE_BACKUP_SWAP);
		}
	}
	if (timebackup)
	{
		if (GetTickCount64() - timebackup > KOOPAS_TIME_DIE_BACKUP)
		{
			timebackup = NULL;
			SetState(KOOPAS_STATE_WALKING);
			y = y + KOOPAS_BBOX_HEIGHT_DIE - KOOPAS_BBOX_HEIGHT;
		}
	}
	vy += KOOPAS_GRAVITY * dt;
	//DebugOut(L"\timedie = %f\n", y); 
	CGameObject::Update(dt, coObjects); 

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx, ny;
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
			else if (dynamic_cast<CCoin*>(e->obj) || dynamic_cast<CBackInvis*>(e->obj))
			{
				FilterCollisioncoin(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
			}
			else
			{
				FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
			}
		}
		//FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		if (nx != 0 && state != KOOPAS_STATE_DIE_SWAP)
		{
			if(nx<0&&vx>0||nx>0&&vx<0)
				vx = -vx;
		}
		if (ny != 0) vy = 0;
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult.at(i);
			if (dynamic_cast<CStreet*>(e->obj)|| dynamic_cast<Cbox*>(e->obj) || dynamic_cast<CBackInvis*>(e->obj))
			{
				CGameObject* game = dynamic_cast<CGameObject*>(e->obj);
				if (e->nx != 0&&abs(y-game->GetY())> CONST_VC&&state!= KOOPAS_STATE_DIE_SWAP)//hang so va cham
				{
					vx = lastvx;
				}
			}
		}
		if (state == KOOPAS_STATE_DIE_SWAP && ny != 0)
		{
			vx = 0;
		}

		CGameObject::Update(dt, coObjects);

		x += min_tx * dx + nx * 0.8f;
		y += min_ty * dy + ny * 0.4f;
	}
	lastvx = vx;
	lastx = x;
	lasty = y;
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CKoopas::Render()
{
	int ani = KOOPAS_ANI_WALKING_LEFT;
	if (state == KOOPAS_STATE_DIE) 
	{
		ani = KOOPAS_ANI_DIE;
	}
	else if (state == KOOPAS_STATE_BACKUP)
	{
		ani = KOOPAS_ANI_BACKUP;
	}
	else if (state == KOOPAS_STATE_BACKUP_SWAP)
	{
		ani = KOOPAS_ANI_BACKUP_SWAP;
	}
	else if (state == KOOPAS_STATE_DIE_SWAP)
	{
		ani = KOOPAS_ANI_DIE_SWAP;
	}
	else if (vx > 0) ani = KOOPAS_ANI_WALKING_RIGHT;
	else if (vx <= 0) ani = KOOPAS_ANI_WALKING_LEFT;

	animation_set->at(ani)->Render(x, y);

	RenderBoundingBox();
}

void CKoopas::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPAS_STATE_BACKUP_SWAP:
		timedie = NULL;
		if (!timebackup)
		{
			timebackup = GetTickCount64();
		}
		vx = 0;
		vy = 0;
		break;
	case KOOPAS_STATE_BACKUP:
		timedie = NULL;
		if (!timebackup)
		{
			timebackup = GetTickCount64();
		}
		vx = 0;
		vy = 0;
		break;
	case KOOPAS_STATE_DIE:
		if (!timedie)
		{
			timedie = GetTickCount64();
		}
		vx = 0;
		vy = 0;
		break;
	case KOOPAS_STATE_DIE_SWAP:
		if (!timedie)
		{
			timedie = GetTickCount64();
		}
		vx = 0;
		vy = -KOOPAS_FLY_FALL;
		break;
	case KOOPAS_STATE_WALKING:
		vx = KOOPAS_WALKING_SPEED;
		timedie = NULL;
	}
}