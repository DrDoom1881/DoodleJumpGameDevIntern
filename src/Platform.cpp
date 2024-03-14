#include "Platform.h"
#include "Bonus.h"
#include "mFramework.h"

void Platform::EnemySpawn()
{
	int window_w, window_h;
	getScreenSize(window_w, window_h);
	float scopeKoefW = (window_w / 640), scopeKoefH = (window_h / 1024);
	int type = rand() % 3;
	float monsterW = 0;
	float monsterH = 0;
	Enemy* monster = 0;
	switch (type)
	{
	case 0:
		type = 0;
		monsterW = 100 * scopeKoefW;
		monsterH = 200 * scopeKoefH;
		break;
	case 1:
		type = 1;
		monsterW = 200 * scopeKoefW;
		monsterH = 100 * scopeKoefH;
		break;
	case 2:
		type = 2;
		monsterW = 200 * scopeKoefW;
		monsterH = 100 * scopeKoefH;
		break;
	}
	monster = new Enemy((x + (width / 2)) - (monsterW / 2), y - monsterH, monsterW, monsterH, type);
	Framework->enemies.push_back(monster);
}

void Platform::BonusSpawn()
{
	Framework->bonus = new Bonus((x + (width / 2)) - (Framework->bonusW / 2), y - Framework->bonusH, Framework->bonusW, Framework->bonusH);
}

void Platform::move()
{
	//roof += deltaY;
	//bottom += deltaY;
	y += deltaY;
	y2 = y + width;
		
}
