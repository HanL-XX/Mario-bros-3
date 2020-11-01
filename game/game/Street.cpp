#include "Street.h"
void CStreet::Render()
{
	animation_set->at(0)->Render(x, y);
	RenderBoundingBox();
}

void CStreet::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + STREET_BBOX_WIDTH;
	b = y + STREET_BBOX_HEIGHT;
}