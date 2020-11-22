#pragma once
#include "GameObject.h"

#define MARIO_WALKING_SPEED		0.1f 
//0.1f
#define MARIO_JUMP_SPEED_Y		0.5f
#define MARIO_JUMP_DEFLECT_SPEED 0.5f
#define MARIO_GRAVITY			0.002f
#define MARIO_DIE_DEFLECT_SPEED	 0.5f
#define MARIO_RUN_SPEED	0.15f
#define MARIO_RUN_FAST_SPEED	0.25f


#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200
#define MARIO_STATE_JUMP			300
#define MARIO_STATE_DIE				400
#define MARIO_STATE_SMALL_RUN_FAST_RIGHT			500
#define MARIO_STATE_SMALL_RUN_FAST_LEFT			600
#define MARIO_STATE_SMALL_RUN_FAST2HAND_RIGHT	700
#define MARIO_STATE_SMALL_RUN_FAST2HAND_LEFT	800
#define MARIO_STATE_SMALL_JUM_FAST	900
#define MARIO_STATE_SMALL_TURN 1000
#define MARIO_STATE_BOW	1001
#define MARIO_STATE_BOW_JUMP 1002



#define MARIO_ANI_BIG_IDLE_RIGHT		0
#define MARIO_ANI_BIG_IDLE_LEFT			1
#define MARIO_ANI_SMALL_IDLE_RIGHT		2
#define MARIO_ANI_SMALL_IDLE_LEFT			3

#define MARIO_ANI_BIG_WALKING_RIGHT			4
#define MARIO_ANI_BIG_WALKING_LEFT			5
#define MARIO_ANI_SMALL_WALKING_RIGHT		6
#define MARIO_ANI_SMALL_WALKING_LEFT		7

#define MARIO_ANI_DIE				8

#define	MARIO_ANI_JUMP_RIGHT	9
#define	MARIO_ANI_JUMP_LEFT	10

#define MARIO_ANI_BIG_JUMP_LEFT_DOWN	11
#define MARIO_ANI_BIG_JUMP_LEFT_UP	12
#define MARIO_ANI_BIG_JUMP_RIGHT_DOWN	13
#define MARIO_ANI_BIG_JUMP_RIGHT_UP	14

#define MARIO_ANI_SMALL_RUN_FAST_RIGHT 15
#define MARIO_ANI_SMALL_RUN_FAST_LEFT 16

#define MARIO_ANI_SMALL_RUN_2HAND_RIGHT 17
#define MARIO_ANI_SMALL_RUN_2HAND_LEFT 18

#define MARIO_ANI_JUM_FAST_RIGHT 19
#define MARIO_ANI_JUM_FAST_LEFT 20
#define MARIO_ANI_SMALL_TURN_LEFT 21
#define MARIO_ANI_SMALL_TURN_RIGHT 22

#define MARIO_ANI_BIG_RUN_LEFT	23
#define MARIO_ANI_BIG_RUN_RIGHT	24

#define MARIO_ANI_BIG_RUN2HAND_RIGHT	25
#define MARIO_ANI_BIG_RUN2HAND_LEFT	26

#define MARIO_ANI_BIG_TURN_RIGHT	27
#define MARIO_ANI_BIG_TURN_LEFT	28

#define MARIO_ANI_BIG_JUMP_RIGHT	29
#define MARIO_ANI_BIG_JUMP_LEFT	30

#define	MARI_ANI_BIG_BOW_RIGHT	31
#define	MARI_ANI_BIG_BOW_LEFT	32

#define MARIO_ANI_FIRE_IDE_RIGHT 33
#define MARIO_ANI_FIRE_IDE_LEFT 34
#define MARIO_ANI_FIRE_WALK_RIGHT	35
#define MARIO_ANI_FIRE_WALK_LEFT	36
#define	MARIO_ANI_FIRE_RUN_RIGHT	37
#define	MARIO_ANI_FIRE_RUN_LEFT	38
#define MARIO_ANI_FIRE_2HAND_RIGHT	39
#define MARIO_ANI_FIRE_2HAND_LEFT	40
#define MARIO_ANI_FIRE_TURN_RIGHT 41
#define MARIO_ANI_FIRE_TURN_LEFT 42
#define MARIO_ANI_FIRE_JUMP_UP_RIGHT 43
#define MARIO_ANI_FIRE_JUMP_DOWN_RIGHT 44
#define MARIO_ANI_FIRE_JUMP_UP_LEFT 45
#define MARIO_ANI_FIRE_JUMP_DOWN_LEFT 46
#define MARIO_ANI_BOW_RIGHT	47
#define MARIO_ANI_BOW_LEFT	48
#define MARIO_ANI_JUM_FAST_RIGHT	49
#define MARIO_ANI_JUM_FAST_LEFT		50

#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define MARIO_LEVEL_FIRE	3

#define MARIO_BIG_BBOX_WIDTH  16
#define MARIO_BIG_BBOX_HEIGHT 27

#define MARIO_BIG_BBOX_BOW_WIDTH  14
#define MARIO_BIG_BBOX_BOW_HEIGHT 18

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 15

#define MARIO_UNTOUCHABLE_TIME 5000
#define MARIO_TIMERUN_2HAND 1000
#define MARIO_TIME_TURN	95

class CMario : public CGameObject
{
	int level;
	int untouchable;
	DWORD untouchable_start;
	DWORD timerun;
	DWORD timeturn;
	int run;
	int lastrun;
	int turn;
	int laststate;
	float lastvx;
	float lastafterbow_x;
	float lastafterbow_y;
	int bowjump;

	float start_x;			// initial position of Mario at scene
	float start_y;
public:
	CMario(float x = 0.0f, float y = 0.0f);

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();

	void SetState(int state);
	void SetLevel(int l) { level = l; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

	void Reset();
	int GetRun() { return this->run; }
	int GetBoWJump() { return this->bowjump; }

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};