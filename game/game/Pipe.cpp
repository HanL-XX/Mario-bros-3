#include "Pipe.h"
void CPIPE::Render()
{
	animation_set->at(0)->Render(x, y);
	RenderBoundingBox();
}

void CPIPE::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + PIPE_BBOX_WIDTH;
	b = y + PIPE_BBOX_HEIGHT;
}