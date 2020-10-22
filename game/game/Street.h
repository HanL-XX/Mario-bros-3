#pragma once
#include "GameObject.h"

#define STREET_BBOX_WIDTH  16
#define STREET_BBOX_HEIGHT 16

class CStreet : public CGameObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};