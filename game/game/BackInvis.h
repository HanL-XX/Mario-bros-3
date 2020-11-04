
#pragma once
#include "GameObject.h"

class CBackInvis : public CGameObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};