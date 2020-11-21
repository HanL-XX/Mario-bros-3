#pragma once
#include "GameObject.h"

#define GOOMBA_WALKING_SPEED 0.05f;
#define GOOMBA_JUMP_SPEED 0.5f;
#define GOOMBA_GRAVITY	0.001f;


#define GOOMBA_BBOX_WIDTH 16
#define GOOMBA_BBOX_HEIGHT 15
#define GOOMBA_BBOX_HEIGHT_DIE 9
#define GOOMBA_BBOX_PARA_WIDTH	20
#define GOOMBA_BBOX_PARA_HEIGHT	19

#define GOOMBA_BBOX_PARA_FLY_WIDTH	20
#define GOOMBA_BBOX_PARA_FLY_HEIGHT	24

#define GOOMBA_STATE_WALKING 100
#define GOOMBA_STATE_DIE 200
#define	GOOMBA_STATE_BM	300
#define GOOMBA_STATE_PARA_WALK 400
#define GOOMBA_STATE_PARA_FLY 500

#define GOOMBA_ANI_WALKING 0
#define GOOMBA_ANI_DIE 1
#define GOOMBA_ANI_PARA_WALK 2
#define GOOMBA_ANI_PARA_FLY	3

#define GOOMBA_LEVEL_BT	0
#define GOOMBA_LEVEL_PARA 1

#define	GOOMBA_TIME_DIE	200

class CGoomba : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	DWORD	timedie;

public:
	CGoomba();
	virtual void SetState(int state);
	virtual void CGoomba::FilterCollision(
		vector<LPCOLLISIONEVENT>& coEvents,
		vector<LPCOLLISIONEVENT>& coEventsResult,
		float& min_tx, float& min_ty,
		float& nx, float& ny, float& rdx, float& rdy);
	void Clear();
};