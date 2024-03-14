#include "mFramework.h"
#include "Doodle.h"
#include<iostream>
#include <conio.h>
#include "Bullet.h"

void mFramework::platformGenerator(int N)
{
	int regPlatform = 0;
	if(N > 0) 
	{
		while (regPlatform <= N)
		{

			bool a = true;
			const int range = window_W - platformW;
			float x = (rand() % range) + (rand() % 100 + 1) / 100;
			float y = ((rand() % (int)genRangeY + (int)genStartLen)) + (rand() % 100 + 1) / 100;
			for (int i = 0; i < platforms.size(); ++i)
			{
				if ((platforms[i]->x <= x) && (platforms[i]->x2 >= x) && (platforms[i]->y <= y) && (platforms[i]->y2 >= y) ||
					(x + platformW >= platforms[i]->x) && (x + platformW <= platforms[i]->x2) && (platforms[i]->y <= y + platformH) && (platforms[i]->y2 >= y + platformH) ||
					(platforms[i]->x <= x + platformW) && (platforms[i]->x2 >= x + platformW) && (platforms[i]->y <= y) && (platforms[i]->y2 >= y) ||
					(platforms[i]->x <= x) && (platforms[i]->x2 >= x) && (platforms[i]->y <= y + platformH) && (platforms[i]->y2 >= y + platformH))
				{
					a = false;
					continue;
				}

			}
			for (int i = 0; i < enemies.size(); ++i)
			{
				if ((enemies[i]->x <= x) && (enemies[i]->x2 >= x) && (enemies[i]->y <= y) && (enemies[i]->y2 >= y) ||
					(x + platformW >= enemies[i]->x) && (x + platformW <= enemies[i]->x2) && (enemies[i]->y <= y + platformH) && (enemies[i]->y2 >= y + platformH) ||
					(enemies[i]->x <= x + platformW) && (enemies[i]->x2 >= x + platformW) && (enemies[i]->y <= y) && (enemies[i]->y2 >= y) ||
					(enemies[i]->x <= x) && (enemies[i]->x2 >= x) && (enemies[i]->y <= y + platformH) && (enemies[i]->y2 >= y + platformH))
				{
					a = false;
					continue; 
				}
			}
			if (!a)
				continue;
			Platform* RegPlat;
			if ((rand() % enemySpawnChance) == 1 && (y < window_H / 2))
				RegPlat = new Platform(x, y, platformW, platformH, false, true);
			else
			{
				if (score - bonusScore >= 1000)//((score % 1000) == 0 && score >= 1000)
				{
					RegPlat = new Platform(x, y, platformW, platformH, true, false);
					bonusScore = score;
				}
				else
				{
					RegPlat = new Platform(x, y, platformW, platformH);

				}
			}

			platforms.push_back(RegPlat);
			++regPlatform;
		}
	}
}

void mFramework::DoodleDirect(float mouseX, float mouseY)
{
	float middle = (doodle->x + doodle->x2) / 2;
	if (mouseX > middle)
		doodle->directSet(0);
	else 
		doodle->directSet(1);
	if (mouseX > doodle->x - doodleW / 2 && mouseX < doodle->x2 + doodleW / 2)
		doodle->directSet(3);
	float tempX = mouseX - doodle->x, tempY = mouseY - doodle->y;
	bulletSpeedX = (tempX / std::sqrt(tempX * tempX + tempY * tempY));
	bulletSpeedY = (tempY / std::sqrt(tempX * tempX + tempY * tempY)) > 0 ? (tempY / std::sqrt(tempX * tempX + tempY * tempY)) * -1 : (tempY / std::sqrt(tempX * tempX + tempY * tempY));
}

void mFramework::PreInit(int& width, int& height, bool& fullscreen)
{
	width = window_W;
	height = window_H;
	fullscreen = screenType;
}

bool mFramework::Init()
{
	while ((genStartLen) > 0 + platformH)//(platforms.size() < 25)//
	{
		int N = rand() % 3;
		platformGenerator(N);
		genStartLen -= genRangeY;
	}
	genStartLen = platforms[platforms.size() - 1]->y;

	int startPlfID = rand() % 1;
	float spawnX = ((platforms[startPlfID]->x + platforms[startPlfID]->x2) / 2) - ((doodleW) / 2);
	doodle = new Doodle(spawnX, platforms[startPlfID]->y - doodleH, doodleW, doodleH);

	if (game)
	{
		gameOver = createSprite("data/GameOverTitle.png");
		background = createSprite("data/bck@2x.png");
		chunk = createSprite("data/chunk.png");
		lifePoint = createSprite("data/60-Breakout-Tiles.png");
		commonPlatform = createSprite("data/CommonPlatform.png");
		bullet = createSprite("data/projectile@2x.png");
		bonusSpr = createSprite("data/bonus.png");
		bonusAuraSpr = createSprite("data/bonus.png");

		setSpriteSize(bonusAuraSpr, doodleW, doodleW);
		setSpriteSize(bonusSpr, bonusW, bonusH);
		setSpriteSize(bullet, ballW, ballH);
		setSpriteSize(background, window_W, window_H);
		setSpriteSize(gameOver, window_W, window_W * 0.55);
		setSpriteSize(chunk, chunkW, chunkH);
		setSpriteSize(lifePoint, 1.5 * platformH, 1.5 * platformH);
		setSpriteSize(commonPlatform, platformW, platformH);
	}
	else
		game = true;
	return true;
}

void mFramework::Close()
{
	for (int i = 0; i < platforms.size(); ++i)
		delete platforms[i];
	for (int i = 0; i < bullets.size(); ++i)
		delete bullets[i];
	for (int i = 0; i < enemies.size(); ++i)
		delete enemies[i];
	bullets.clear();
	platforms.clear();
	enemies.clear();
	delete bonus;
	delete doodle;
	destroySprite(background);
	destroySprite(chunk);
	destroySprite(commonPlatform);
	destroySprite(gameOver);
	destroySprite(lifePoint);
	destroySprite(bullet);
	destroySprite(bonusSpr);
	destroySprite(bonusAuraSpr);

}
unsigned int tickCounter = 0;
bool mFramework::Tick()
{
	drawSprite(background, 0, 0);
	if (!game)
	{
		drawSprite(gameOver,0 , window_H * 0.3);
		genStartLen = window_H - 3 * platformH - 10;
		genRangeY = 3 * platformH + 10;
		score = 0;
		for (int i = 0; i < platforms.size(); ++i)
			delete platforms[i];
		for (int i = 0; i < bullets.size(); ++i)
			delete bullets[i];
		for (int i = 0; i < enemies.size(); ++i)
			delete enemies[i];
		bullets.clear();
		platforms.clear();
		enemies.clear();
		delete bonus;
		
		return false;
	}

	for (int i = 1; i <= doodle->giveHP() ; ++i)
	{
		drawSprite(lifePoint, window_W - (i * 1.2 * 1.5 *platformH), 5);
	}

	for (int i = 0; i < enemies.size(); ++i)
	{
		drawSprite(enemies[i]->sprite(), enemies[i]->x, enemies[i]->y);
	}

	for (int i = 0; i < platforms.size(); ++i)
	{
		drawSprite(commonPlatform, platforms[i]->x, platforms[i]->y);
	}

	doodle->move();
	if(bonus)
		drawSprite(bonusSpr, bonus->x, bonus->y);
	if (!bullets.empty())
	{
		for (int i = 0; i < bullets.size(); ++i)
		{
			bullets[i]->move();
			if (bullets[i]->y < 0 || bullets[i]->y > window_H)
			{
				delete bullets[i];
				bullets.erase(bullets.begin() + i);
			}
		}
		for (int i = 0; i < bullets.size(); ++i)
		{
			drawSprite(bullet, bullets[i]->x, bullets[i]->y);

		}
	}
	if (doodle->unbreakable)
		drawSprite(bonusAuraSpr, doodle->x, doodle->y);
	if (doodle->x + doodleW > window_W || doodle->x <= 0)
	{
		if (doodle->directGet())
		{
			drawSprite(doodle->LeftDoodleSpr, doodle->x, doodle->y);
			drawSprite(doodle->LeftDoodleSpr, -doodle->x2, doodle->y);
		}
		else
		{
			drawSprite(doodle->RightDoodleSpr, doodle->x, doodle->y);
			drawSprite(doodle->RightDoodleSpr, -doodle->x2, doodle->y);
		}
	}
	else
	{
		if (doodle->directGet())
			drawSprite(doodle->LeftDoodleSpr, doodle->x, doodle->y);
		else
			drawSprite(doodle->RightDoodleSpr, doodle->x, doodle->y);
	}

	if (doodle->JumpY() - (window_H - (window_H * 0.5)) < 0)
	{
		for (int i = 0; i < platforms.size(); ++i)
		{
			if (platforms[i]->y > window_H)
			{
				delete platforms[i];
				platforms.erase(platforms.begin() + i);
			}
		}
		for (int i = 0; i < enemies.size(); ++i)
		{
			if (enemies[i]->y > window_H)
			{
				delete enemies[i];
				enemies.erase(enemies.begin() + i);
			}
		}
		if (bonus && bonus->y > window_H)
		{
			delete bonus;
			bonus = 0;
		}
		genStartLen = platforms[platforms.size() - 1]->y - 2 * genRangeY;
		while ((genStartLen) > 0 + platformH)
		{
			int N = rand() % 2;
			platformGenerator(N);
			genStartLen -= 2 * genRangeY;
		}
	}

	//if (getTickCount() - tickCounter > 300)
	//{

	//	tickCounter = getTickCount();
	//	int  type;
	//	switch (rand() % 2)
	//	{
	//	case 0:
	//		type = 0;
	//		break;
	//	case 1:
	//		type = 1;
	//		break;
	//	case 2:
	//		type = 2;
	//		break;
	//	}
	// 
	//// 		for (int i = 0; i < Framework->enemies.size(); ++i)
	//{
	//	Framework->enemies.
	//}
	// 
	//}
	if (doodle->giveHP() == -1 )
		game = false;
	std::cout << "Score: " << score <<"\nPlatforms passed: "<< pltPassed <<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << std::endl; //system(“cls”) or "\033c" and another simular things make big lags for game!
	return false;
}

void mFramework::onMouseMove(int x, int y, int xrelative, int yrelative)
{
	DoodleDirect(x, y);
}

void mFramework::onMouseButtonClick(FRMouseButton button, bool isReleased)
{
	if (isReleased)
		return;
	if (!game)
	{
		if (button == FRMouseButton::LEFT || button == FRMouseButton::RIGHT)
		{
			delete doodle;
			Init();
		}
	}
	else
	{
		if (button == FRMouseButton::LEFT)
		{
			doodle->Fire(getTickCount());
			Bullet* bullet = new Bullet(ballW, ballH);
			bullets.push_back(bullet);
			bullet->Start(bulletSpeedX, bulletSpeedY);
		}
		if (button == FRMouseButton::MIDDLE)
			pause = !pause;
	}
}

void mFramework::onKeyPressed(FRKey k) {
	if (k == FRKey::RIGHT)
		doodle->DeltaX() = doodle->SpeedX();
	if (k == FRKey::LEFT)
		doodle->DeltaX() = -1 * doodle->SpeedX();
}

void mFramework::onKeyReleased(FRKey k) {
	if (k == FRKey::RIGHT)
		doodle->DeltaX() = 0;
	if (k == FRKey::LEFT)
		doodle->DeltaX() = 0;
}

const char* mFramework::GetTitle()
{
	return nullptr;
}
