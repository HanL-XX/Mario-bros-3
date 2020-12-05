#pragma once

#include "GameObject.h"

#define KOOPAS_WALKING_SPEED 0.03f;
#define KOOPAS_GRAVITY 0.001f
#define CONST_VC 11

#define KOOPAS_BBOX_WIDTH 16
#define KOOPAS_BBOX_HEIGHT 26
#define KOOPAS_BBOX_HEIGHT_DIE 16

#define KOOPAS_STATE_WALKING 100
#define KOOPAS_STATE_DIE 200
#define KOOPAS_STATE_DIE_SWAP 300
#define KOOPAS_STATE_BACKUP 400
#define KOOPAS_STATE_BACKUP_SWAP 500

#define KOOPAS_ANI_WALKING_LEFT 0
#define KOOPAS_ANI_WALKING_RIGHT 1
#define KOOPAS_ANI_DIE 2
#define KOOPAS_ANI_DIE_SWAP 3
#define KOOPAS_ANI_BACKUP 4
#define KOOPAS_ANI_BACKUP_SWAP 5

#define KOOPAS_TIME_DIE_AGEL 4000
#define KOOPAS_TIME_DIE_BACKUP 2000

class CKoopas : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	float lastvx, lastx, lasty;
	DWORD	timedie;
	DWORD	timebackup;
public:
	CKoopas();
	virtual void SetState(int state);
	float Getvx() { return vx; }
	void SetVy(float a) { vy = a; }
};