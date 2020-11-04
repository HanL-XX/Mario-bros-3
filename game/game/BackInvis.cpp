#include "BackInvis.h"
void CBackInvis::Render()
{
	animation_set->at(0)->Render(x, y);
	RenderBoundingBox();
}

void CBackInvis::GetBoundingBox(float& l, float& t, float& r, float& b)
{

}