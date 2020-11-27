#pragma once
#include "GameObject.h"

#define MARIO_WALKING_SPEED		0.1f 
//0.1f
#define MARIO_JUMP_SPEED_Y		0.5f
#define MARIO_JUMP_SPEED_Y_SLOMOTION	0.3f
#define MARIO_JUMP_SPEED_Y_FALL_S	0.07f
#define MARIO_JUMP_SPEED_Y_FALL_X	0.01f
#define MARIO_FLY_S	0.1f
#define MARIO_FLY_X	0.3f

#define MARIO_JUMP_DEFLECT_SPEED 0.5f
#define MARIO_GRAVITY			0.002f
#define MARIO_DIE_DEFLECT_SPEED	 0.5f
#define MARIO_RUN_SPEED	0.15f
#define MARIO_RUN_FAST_SPEED	0.25f

#define MARIO_JUMP_HIGH	80


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
#define MARIO_STATE_BOW_JUMP_SLOMOTION 1003
#define MARIO_STATE_JUM_SLOMOTION	1004
#define MARIO_STATE_JUM_DOWN_SLO_S 1005
#define MARIO_STATE_FLY_S 1006
#define MARIO_STATE_FLY_X 1007
#define MARIO_STATE_JUM_DOWN_SLO_X 1008
#define MARIO_STATE_TICKTAIL 1009

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
#define MARIO_ANI_FIRE_BOW_RIGHT	47
#define MARIO_ANI_FIRE_BOW_LEFT	48
#define MARIO_ANI_FIRE_JUM_FAST_RIGHT	49
#define MARIO_ANI_FIRE_JUM_FAST_LEFT		50

#define MARIO_ANI_TAIL_IDE_RIGHT 51
#define MARIO_ANI_TAIL_IDE_LEFT 52
#define MARIO_ANI_TAIL_WALK_RIGHT	53
#define MARIO_ANI_TAIL_WALK_LEFT	54
#define MARIO_ANI_TAIL_RUN_RIGHT 55
#define MARIO_ANI_TAIL_RUN_LEFT 56
#define MARIO_ANI_TAIL_2HAND_RIGHT 57
#define MARIO_ANI_TAIL_2HAND_LEFT 58
#define MARIO_ANI_TAIL_TURN_RIGHT 59
#define MARIO_ANI_TAIL_TURN_LEFT	60
#define MARIO_ANI_TAIL_BOW_RIGHT 61
#define MARIO_ANI_TAIL_BOW_LEFT 62
#define MARIO_ANI_TAIL_JUMP_UP_RIGHT 63
#define MARIO_ANI_TAIL_JUMP_DOWN_RIGHT 64
#define MARIO_ANI_TAIL_JUMP_UP_LEFT	65
#define MARIO_ANI_TAIL_JUMP_DOWN_LEFT	66
#define MARIO_ANI_TAIL_JUMP_DOWN_LEFT_SLO 68
#define MARIO_ANI_TAIL_JUMP_DOWN_RIGHT_SLO 67
#define MARIO_ANI_TAIL_FLY_RIGHT	69
#define MARIO_ANI_TAIL_FLY_LEFT	70
#define MARIO_ANI_TAIL_JUM_FAST_RIGHT 71
#define MARIO_ANI_TAIL_JUM_FAST_LEFT	72
#define MARIO_ANI_TAIL_FALL_FLY_RIGHT 73
#define MARIO_ANI_TAIL_FALL_FLY_LEFT 74
#define MARIO_ANI_TAIL_TICKTAIL_RIGHT	75
#define MARIO_ANI_TAIL_TICKTAIL_LEFT	76

#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define MARIO_LEVEL_FIRE	3
#define MARIO_LEVEL_TAIL	4

#define MARIO_BIG_BBOX_WIDTH  16
#define MARIO_BIG_BBOX_HEIGHT 27

#define MARIO_BIG_BBOX_BOW_WIDTH  14
#define MARIO_BIG_BBOX_BOW_HEIGHT 18

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 15

#define MARIO_TAIL_BBOX_WIDTH	19
#define MARIO_TAIL_BBOX_HEIGHT	28

#define MARIO_TAIL_BOW_BBOX_WIDTH	19
#define MARIO_TAIL_BOW_BBOX_HEIGHT	18

#define MARIO_UNTOUCHABLE_TIME 5000
#define MARIO_TIMERUN_2HAND 1000
#define MARIO_TIME_TURN	95
#define MARIO_TIME_FLY	5000

class CMario : public CGameObject
{
	int level;
	int untouchable;
	DWORD untouchable_start;
	DWORD timerun;
	DWORD timeturn;
	DWORD timefly;
	int fly;
	int flyset = 0;
	int run;
	int lastrun;
	int turn;
	int laststate;
	float lastvx;
	float lastafterbow_x;
	float lastafterbow_y;
	int bowjump;
	float checkfallY;
	int checkS;


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
	int GetJump() { return this->jump; }
	int CheckFall() 
	{
		if (jump == 0)
		{
			checkfallY = y;
			checkS = 0;
		}
		if (vy > 0)
			checkS = 1;
		if (checkfallY - this->y >= MARIO_JUMP_HIGH)
		{
			checkS = 1;
			return 1;
		}
		else
			return 0;
	}
	int CheckS() { return this->checkS; }
	int GetLevel() { return this->level; }
	int Fly() { return this->fly; }
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};