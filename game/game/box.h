#pragma once
#include "GameObject.h"

#define BOX_BBOX_WIDTH  16
#define BOX_BBOX_HEIGHT 0

class Cbox : public CGameObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};