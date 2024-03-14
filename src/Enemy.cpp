#include "Enemy.h"

void Enemy::move()
{
	y += deltaY;
	y2 = y + width;
}
