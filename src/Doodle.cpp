#include "Doodle.h"



void Doodle::Fire(int tick)
{

	fireTick = tick;
	fire = true;
}

void Doodle::move()
{

	collision();
	int deltaTime = getTickCount() - tickCounter;
	tickCounter = getTickCount();

	if (fireTick + 70 > getTickCount() )
	{
		switch (direct)
		{
		case 0:
			LeftDoodleSpr = noseR;
			RightDoodleSpr = noseR;
			break;
		case 1:
			LeftDoodleSpr = noseL;
			RightDoodleSpr = noseL;
			break;
		case 3:
			LeftDoodleSpr = noseUP;
			RightDoodleSpr = noseUP;
			break;

		}
	}
	else
		fire = false;
	

	if (jump == true && y <= jumpCoord)
	{
		jump = false;
		speedY *= -1;
	}

	y += deltaY * speedY + g;

	if (y > window_h)
	{
		dead();
	}

	if (x + width >= window_w)
	{
		if (x > window_w)
			x = 0;
		x2 = window_w - x;
	}
	else
		x2 = x + width;

	if (x + deltaX <= 0)
		x = window_w + deltaX;
	else
		x += deltaX;

	y2 = y + height;
}

void Doodle::collision()
{
	if (unbreakable == true && (getTickCount() - bonusTick )/ 1000 == 20)
	{
		unbreakable = false;
	}
	float realSize = Framework->doodle->width * 0.3;
	if(y2 <= jumpCheck)
	{
		LeftDoodleSpr = NormalLeftDoodleSpr;
		RightDoodleSpr = NormalRightDoodleSpr;
	}
	for (int j = 0; j < Framework->platforms.size(); ++j)
	{
		if (!jump )
		{
			
			if ((Framework->platforms[j]->x <= x + width - realSize) && (Framework->platforms[j]->x + Framework->platforms[j]->width >= x + realSize) &&
				(Framework->platforms[j]->y >= y2 ) && (Framework->platforms[j]->y - Framework->platforms[j]->height / 4 <= y2))
			{
				if (!Framework->platforms[j]->IsJumped())
				{
					Framework->platforms[j]->Jumped();
					Framework->scoreIncrease();
					//std::cout << "jump!:" << jumpCheck << " " << y2 << std::endl;
				}
				jumpCheck = Framework->platforms[j]->y - jumpH * 0.75;
				LeftDoodleSpr = JumpLeftDoodleSpr;
				RightDoodleSpr = JumpRightDoodleSpr;
				speedY *= -1;
				jumpCoord = y - jumpH;
				jump = true;
				break;
			}
			speedY *= 1;
		}
	}
	if ((Framework->bonus) && (Framework->bonus->x <= x + width - realSize) && (Framework->bonus->x2 >= x + realSize) &&
		(Framework->bonus->y <= y2) && (Framework->bonus->y2 >= y) )
	{
		unbreakable = true;
		bonusTick = getTickCount();
		delete Framework->bonus;
	}

	for (int i = 0; i < Framework->enemies.size(); ++i)
	{
		if ((Framework->enemies[i]->x <= x + width - realSize) && (Framework->enemies[i]->x + Framework->enemies[i]->width >= x + realSize) &&
			(Framework->enemies[i]->y >= y2) && (Framework->enemies[i]->y - Framework->enemies[i]->height / 4 <= y2))
		{
			delete Framework->enemies[i];
			Framework->enemies.erase(Framework->enemies.begin() + i);
			LeftDoodleSpr = JumpLeftDoodleSpr;
			RightDoodleSpr = JumpRightDoodleSpr;
			if(jump)
				speedY *= 1;
			else
				speedY *= -1;
			jumpCoord = y - jumpH;
			jump = true;
			break;
		}
		if ((Framework->enemies[i]->x <= x + width - realSize) && (Framework->enemies[i]->x2 >= x + realSize) &&
			(Framework->enemies[i]->y <= y2) && (Framework->enemies[i]->y2 >= y && !unbreakable))
		{ 
			dead();
		}
	}

	if (jump && y < window_h - (window_h * 0.5))
	{
		
		float anhcor = Framework->platforms[Framework->platforms.size() - 1]->y;
		for (int j = 0; j < Framework->platforms.size(); ++j)
		{
			Framework->platforms[j]->move();
			Framework->platforms[j]->move();
			g = 1.2;

		}
		for (int i = 0; i < Framework->enemies.size(); ++i)
		{
			Framework->enemies[i]->move();
			Framework->enemies[i]->move();
		}
		if(Framework->bonus)
		{
			Framework->bonus->move();
			Framework->bonus->move();
		}
		
		jumpCoord += deltaY;
		jumpCheck += deltaY;

	}
	else 
	{
		g = 0;
	}
}

void Doodle::dead()
{
	--HP;
	y = Framework->platforms[0]->y - height;
	y2 = y + height;
	x = ((Framework->platforms[0]->x + Framework->platforms[0]->x2) / 2) - ((width) / 2);
	x2 = x + width;
}


