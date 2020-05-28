#ifndef RECTCOLLIDER_H
#define RECTCOLLIDER_H

#include "Vector2D/Vector2D.h"

struct RectCollider
{
	int x;
	int y;
	int w_2;
	int h_2;
	Vector2D normal;
};

#endif 