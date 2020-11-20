#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Portal.h"
#include"box.h"
#include "Street.h"
#include "Coin.h"

CMario::CMario(float x, float y) : CGameObject()
{
	level = MARIO_LEVEL_SMALL;
	untouchable = 0;
	SetState(MARIO_STATE_IDLE);
	turn = 0;
	timeturn = NULL;
	start_x = x;
	start_y = y;
	this->x = x;
	this->y = y;
}

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{	
	// Simple fall down
	vy += MARIO_GRAVITY * dt;
	// Calculate dx, dy 
	CGameObject::Update(dt);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	//turn = 0;
	// turn off collision when die 
	if (state != MARIO_STATE_BOW)
	{
		lastafterbow_x = x;
		lastafterbow_y = y;
	}
	if (state != MARIO_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);
	if (timeturn)
	{
		if (GetTickCount64() - timeturn <= MARIO_TIME_TURN)
		{
			SetState(MARIO_STATE_SMALL_TURN);
			turn = 1;
			//DebugOut(L"vx = %f\n", turn);
		}
		else
		{
			timeturn = NULL;
			turn = 0;
		}
	}
	if (timerun)
	{
		if (GetTickCount64() - timerun > MARIO_TIMERUN_2HAND)
		{
			run = 1;
		}
		//DebugOut(L"\count = %f\n", GetTickCount64());
	}
	// reset untouchable timer if untouchable time has passed
	if (GetTickCount() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}
	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
		jump = 1;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;
		jump = 1;
		// TODO: This is a very ugly designed function!!!!
		for (UINT i = 0; i < coEvents.size(); i++)
		{
			LPCOLLISIONEVENT e = coEvents[i];

			if (dynamic_cast<Cbox*>(e->obj))
			{
				FilterCollisionbox(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
			}
			else if (dynamic_cast<CCoin*>(e->obj))
			{
				FilterCollisioncoin(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
			}
			else
				FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
		}

		// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
		/*if (rdx != 0 && rdx!=dx)
			x += nx*abs(rdx); */

		// block every object first!
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
		/*if (vy == 0)
			jump = 0;*/

		//
		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (e->ny < 0)
			{
				jump = 0;
			}

			if (dynamic_cast<CStreet*>(e->obj))
			{
				CStreet* brick = dynamic_cast<CStreet*>(e->obj);
				/*x += min_tx * dx + nx * 0.4f;
				y += min_ty * dy + ny * 0.001f;*/

			}
			if (dynamic_cast<CCoin*>(e->obj))
			{
				CCoin* Coin = dynamic_cast<CCoin*>(e->obj);

				if (e->ny != 0||e->nx!=0)
				{
					Coin->Clear();
				}
			}
			if (dynamic_cast<CGoomba*>(e->obj)) // if e->obj is Goomba 
			{
				CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

				// jump on top >> kill Goomba and deflect a bit 
				if (e->ny < 0)
				{
					if (goomba->GetState() != GOOMBA_STATE_DIE)
					{
						goomba->Clear();
						vy = -MARIO_JUMP_DEFLECT_SPEED;
					}
					//if (goomba->GetState() == GOOMBA_STATE_DIE)
					//{
					//	goomba->Clear();
					//}
				}
				else if (e->nx != 0)
				{
					if (untouchable == 0)
					{
						if (goomba->GetState() != GOOMBA_STATE_DIE)
						{
							if (level > MARIO_LEVEL_SMALL)
							{
								level = MARIO_LEVEL_SMALL;
								StartUntouchable();
							}
							else
							{
								SetState(MARIO_STATE_DIE);
							}
						}
					}
				}
			} // if Goomba
			else if (dynamic_cast<CPortal*>(e->obj))
			{
				CPortal* p = dynamic_cast<CPortal*>(e->obj);
				CGame::GetInstance()->SwitchScene(p->GetSceneId());
			}
		}

	}
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CMario::Render()
{
	int ani = -1;
	if (state == MARIO_STATE_DIE)
		ani = MARIO_ANI_DIE;
	else
		if (level == MARIO_LEVEL_BIG)
		{
			if (state == MARIO_STATE_BOW||state== MARIO_STATE_BOW_JUMP)
			{
				if (nx > 0)
					ani = MARI_ANI_BIG_BOW_RIGHT;
				else
					ani = MARI_ANI_BIG_BOW_LEFT;
			}
			else if (turn == 1)
			{
				if (nx < 0)
					ani = MARIO_ANI_BIG_TURN_LEFT;
				else
					ani = MARIO_ANI_BIG_TURN_RIGHT;
			}
			else if (run == 1 && jump != 1)
			{
				if (nx < 0)
					ani = MARIO_ANI_BIG_RUN2HAND_LEFT;
				else
					ani = MARIO_ANI_BIG_RUN2HAND_RIGHT;
			}
			else if (jump == 1)
			{
				if (run == 1)
				{
					if (nx > 0)
						ani = MARIO_ANI_BIG_JUMP_RIGHT;
					else
						ani = MARIO_ANI_BIG_JUMP_LEFT;
				}
				else
				{
					if (vy < 0)
					{
						if (nx > 0)
							ani = MARIO_ANI_BIG_JUMP_RIGHT_UP;
						else
							ani = MARIO_ANI_BIG_JUMP_LEFT_UP;
					}
					else
					{
						if (nx > 0)
							ani = MARIO_ANI_BIG_JUMP_RIGHT_DOWN;
						else
							ani = MARIO_ANI_BIG_JUMP_LEFT_DOWN;
					}
				}
			}
			else
			{
				if (vx == 0)
				{
					if (nx > 0) ani = MARIO_ANI_BIG_IDLE_RIGHT;
					if (nx < 0) ani = MARIO_ANI_BIG_IDLE_LEFT;
				}
				else if (vx > 0)
				{
					if (state == MARIO_STATE_SMALL_RUN_FAST_RIGHT)
					{
						ani = MARIO_ANI_BIG_RUN_RIGHT;
					}
					else
						ani = MARIO_ANI_BIG_WALKING_RIGHT;
				}
				else if (vx < 0)
				{
					if (state == MARIO_STATE_SMALL_RUN_FAST_LEFT)
					{
						ani = MARIO_ANI_BIG_RUN_LEFT;
					}
					else
						ani = MARIO_ANI_BIG_WALKING_LEFT;
				}
			}
		}
		else if (level == MARIO_LEVEL_SMALL)
		{
			if (turn==1)
			{
				if (nx < 0)
					ani = MARIO_ANI_SMALL_TURN_LEFT;
				else
					ani = MARIO_ANI_SMALL_TURN_RIGHT;
			}
			else if (run == 1 && jump != 1)
			{

				if (nx > 0)	ani = MARIO_ANI_SMALL_RUN_2HAND_RIGHT;
				else
				{
					ani = MARIO_ANI_SMALL_RUN_2HAND_LEFT;
				}
			}
			else 
			{
				if (vx == 0 && jump == 0)
				{
					if (nx > 0) ani = MARIO_ANI_SMALL_IDLE_RIGHT;
					else ani = MARIO_ANI_SMALL_IDLE_LEFT;
				}
				else if (vx > 0 && jump == 0)
					if (state == MARIO_STATE_SMALL_RUN_FAST_RIGHT)
					{
						ani = MARIO_ANI_SMALL_RUN_FAST_RIGHT;
					}
					else
						ani = MARIO_ANI_SMALL_WALKING_RIGHT;
				else if (vx < 0 && jump == 0)
					if (state == MARIO_STATE_SMALL_RUN_FAST_LEFT)
					{
						ani = MARIO_ANI_SMALL_RUN_FAST_LEFT;
					}
					else
						ani = MARIO_ANI_SMALL_WALKING_LEFT;
				else if (jump == 1)
				{
					if (run == 1)
					{
						if (nx > 0)
							ani = MARIO_ANI_JUM_FAST_RIGHT;
						if (nx < 0)
							ani = MARIO_ANI_JUM_FAST_LEFT;
					}
					else
					{
						if (nx > 0)
						{
							ani = MARIO_ANI_JUMP_RIGHT;
						}
						if (nx < 0)
						{
							ani = MARIO_ANI_JUMP_LEFT;
						}
					}
				}
			}
		}
	int alpha = 255;
	if (untouchable) alpha = 128;

	animation_set->at(ani)->Render(x, y, alpha);

	RenderBoundingBox();
}

void CMario::SetState(int state)
{
	
	if (state == MARIO_STATE_BOW && jump == 1)
		return;
	
	CGameObject::SetState(state);
	if (jump == 1)
	{
		turn = 0;
		timeturn = NULL;
	}
	else
		bowjump = 0;
	if (bowjump == 1)
	{
		switch (state)
		{
		case MARIO_STATE_WALKING_RIGHT:
			vx = MARIO_WALKING_SPEED;
			nx = 1;
			break;
		case MARIO_STATE_WALKING_LEFT:
			vx = -MARIO_WALKING_SPEED;
			nx = -1;
			break;
		case MARIO_STATE_SMALL_RUN_FAST_LEFT:
			vx = -MARIO_WALKING_SPEED;
			nx = -1;
			break;
		case MARIO_STATE_SMALL_RUN_FAST_RIGHT:
			vx = MARIO_WALKING_SPEED;
			nx = 1;
			break;
			break;
		}
		CGameObject::SetState(MARIO_STATE_BOW_JUMP);
	}
	if (!timeturn)
	{
		switch (state)
		{
		case MARIO_STATE_WALKING_RIGHT:
			vx = MARIO_WALKING_SPEED;
			nx = 1;
			lastrun = 0;
			timerun = NULL;
			timeturn = NULL;
			turn = 0;
			run = 0;
			break;
		case MARIO_STATE_WALKING_LEFT:
			vx = -MARIO_WALKING_SPEED;
			nx = -1;
			lastrun = 0;
			timerun = NULL;
			timeturn = NULL;
			turn = 0;
			run = 0;
			break;
		case MARIO_STATE_JUMP:
			// TODO: need to check if Mario is *current* on a platform before allowing to jump again
			vy = -MARIO_JUMP_SPEED_Y;
			lastrun = 0;
			timerun = NULL;
			timeturn = NULL;
			turn = 0;
			break;
		case MARIO_STATE_IDLE:
			vx = 0;
			lastrun = 0;
			timerun = NULL;
			timeturn = NULL;
			turn = 0;
			run = 0;
			break;
		case MARIO_STATE_DIE:
			vy = -MARIO_DIE_DEFLECT_SPEED;
			lastrun = 0;
			timerun = NULL;
			timeturn = NULL;
			turn = 0;
			run = 0;
			break;
		case MARIO_STATE_SMALL_RUN_FAST_LEFT:
			if (lastrun == 0)
			{
				timerun = GetTickCount64();
				vx = -MARIO_RUN_SPEED;
				nx = -1;
				timeturn = NULL;
				turn = 0;
				lastrun = 1;
			}
			else
			{
				vx = -MARIO_RUN_SPEED;
				timeturn = NULL;
				nx = -1;
				turn = 0;
				if (run == 1)
				{
					vx = -MARIO_RUN_FAST_SPEED;
				}
			}
			break;
		case MARIO_STATE_SMALL_RUN_FAST_RIGHT:
			if (lastrun == 0)
			{
				timerun = GetTickCount64();
				vx = MARIO_RUN_SPEED;
				nx = 1;
				timeturn = NULL;
				turn = 0;
				lastrun = 1;
			}
			else
			{
				vx = MARIO_RUN_SPEED;
				timeturn = NULL;
				turn = 0;
				nx = 1;
				if (run == 1)
				{
					vx = MARIO_RUN_FAST_SPEED;
				}
			}
			break;
		case MARIO_STATE_SMALL_JUM_FAST:
			vy = -MARIO_JUMP_SPEED_Y;
			timeturn = NULL;
			turn = 0;
			break;
		case MARIO_STATE_SMALL_TURN:
			vx = 0;
			lastrun = 0;
			timerun = NULL;
			run = 0;
			turn = 1;
			break;
		case MARIO_STATE_BOW:
			vx = 0;
			lastrun = 0;
			timerun = NULL;
			timeturn = NULL;
			turn = 0;
			run = 0;
			break;
		case MARIO_STATE_BOW_JUMP:
			vy = -MARIO_JUMP_SPEED_Y;
			vx = 0;
			lastrun = 0;
			timerun = NULL;
			timeturn = NULL;
			turn = 0;
			run = 0;
			bowjump = 1;
			break;
		}
	}
	if (laststate)
	{
		if (laststate == MARIO_STATE_BOW && state != MARIO_STATE_BOW||laststate==MARIO_STATE_BOW_JUMP&&state!= MARIO_STATE_BOW_JUMP)
		{
			SetPosition(x, y+ MARIO_BIG_BBOX_BOW_HEIGHT- MARIO_BIG_BBOX_HEIGHT);
		}
	}
	if (lastvx * vx < 0)
	{
		if (state != MARIO_STATE_BOW_JUMP)
		{
			timeturn = GetTickCount64();
			turn = 1;
		}
	}
	if (timeturn)
	{
		vx = 0;
		timerun = 0;
		lastrun = NULL;
		run = 0;
		turn = 1;
	}
	lastvx = vx;
	laststate = state;
	DebugOut(L"\nbowjum = %i", bowjump);
}

void CMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;

	if (level == MARIO_LEVEL_BIG)
	{
		if (state == MARIO_STATE_BOW)
		{
			right = x + MARIO_BIG_BBOX_BOW_WIDTH;
			bottom = y + MARIO_BIG_BBOX_BOW_HEIGHT;
		}
		else
		{
			right = x + MARIO_BIG_BBOX_WIDTH;
			bottom = y + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else
	{
		right = x + MARIO_SMALL_BBOX_WIDTH;
		bottom = y + MARIO_SMALL_BBOX_HEIGHT;
	}
}

/*
	Reset Mario status to the beginning state of a scene
*/
void CMario::Reset()
{
	SetState(MARIO_STATE_IDLE);
	SetLevel(MARIO_LEVEL_BIG);
	SetPosition(start_x, start_y);
	SetSpeed(0, 0);
}

