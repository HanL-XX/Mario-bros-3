#include "box.h"
void Cbox::Render()
{
	animation_set->at(0)->Render(x, y);
	RenderBoundingBox();
}

void Cbox::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BOX_BBOX_WIDTH;
	b = y + BOX_BBOX_HEIGHT;
}