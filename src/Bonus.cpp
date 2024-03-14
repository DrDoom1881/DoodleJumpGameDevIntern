#include "Bonus.h"

Bonus::~Bonus()
{
	Framework->bonus = 0;
}

void Bonus::move()
{
	y += deltaY;
	y2 = y + width;
}
