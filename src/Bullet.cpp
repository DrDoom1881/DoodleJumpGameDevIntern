#include "Bullet.h"


void Bullet::move()
{
	for (int i = 0; i < Framework->enemies.size(); ++i)
	{
		if ((Framework->enemies[i]->x <= x) && (Framework->enemies[i]->x2 >= x) && (Framework->enemies[i]->y <= y) && (Framework->enemies[i]->y2 >= y) ||
			(x + width >= Framework->enemies[i]->x) && (x + width <= Framework->enemies[i]->x2) && (Framework->enemies[i]->y <= y + height) && (Framework->enemies[i]->y2 >= y + height) ||
			(Framework->enemies[i]->x <= x + width) && (Framework->enemies[i]->x2 >= x + width) && (Framework->enemies[i]->y <= y) && (Framework->enemies[i]->y2 >= y) ||
			(Framework->enemies[i]->x <= x) && (Framework->enemies[i]->x2 >= x) && (Framework->enemies[i]->y <= y + height) && (Framework->enemies[i]->y2 >= y + height))
		{
			delete Framework->enemies[i];
			Framework->enemies.erase(Framework->enemies.begin() + i);
			x = -1;
			y = -1;
			speedX = 0;
			speedY = 0;
			break;
		}
	}
	y += ((deltaY * speedY * speedScale));

	if (x + width >= window_w)
	{
		if (x > window_w)
			x = 0;
		x2 = window_w - x;
	}
	else
		x2 = x + width;

	if (x + deltaX <= 0)
		x = window_w + ((deltaX * speedX * speedScale));
	else
		x += ((deltaX * speedX * speedScale));

	y2 = y + height;

}

void Bullet::collision(int i)
{
}

void Bullet::Start(float sX, float sY)
{
	speedX = sX;
	speedY = sY;
	switch (Framework->doodle->directGet())
	{
	case 0:
		x = Framework->doodle->x2;
		break;
	case 1:
		x = Framework->doodle->x;
		break;
	case 3:
		x = Framework->doodle->x + Framework->doodle->width / 2 - width / 2;
		break;

	}
	//x = Framework->doodle->x + Framework->doodle->width / 2 - width / 2;
	y = Framework->doodle->y - height;
	x2 = x + width;
	y2 = y + height;

}



