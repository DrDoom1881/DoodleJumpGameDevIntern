#pragma once
#include "Framework.h"
#include "Doodle.h"
#include "Platform.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Bonus.h"
#include<vector>
class Doodle;
class Platform;
class Bullet;
class Enemy;
class Bonus;
class MovingPlatform;

class mFramework : public Framework
{
private:
	int window_W = 0; //Aplication's size
	int window_H = 0; //standart size: 800x600
	float scopeKoefW = (window_W / 640), scopeKoefH = (window_H / 1024);
	float doodleW = 100 * scopeKoefW, doodleH = 100 * scopeKoefH;
	const int enemySpawnChance = 25;
	float platformW = 100 * scopeKoefW, platformH = 20 * scopeKoefH;
	bool screenType = 0; //standart type: false
	float genStartLen = window_H - 3 * platformH - 10, genRangeY = 1.5 * platformH + 10;
	float ballW = 10 * scopeKoefW, ballH = 10 * scopeKoefH;
	float bulletSpeedX = 0, bulletSpeedY = 0;
	unsigned int score = 0;
	unsigned int pltPassed = 0;
	int bonusScore = 0;
	bool game = true;
	
private:
	void DoodleDirect(float, float);
	void platformGenerator(int);
	
public:
	Doodle* doodle;
	Bonus* bonus;

	Sprite* background;
	Sprite* chunk;
	Sprite* commonPlatform;
	Sprite* gameOver;
	Sprite* lifePoint;
	Sprite* bullet;
	Sprite* bonusSpr;
	Sprite* bonusAuraSpr;

	std::vector< Enemy*> enemies;
	std::vector<Bullet*> bullets;
	std::vector<Platform*> platforms;
	
	bool pause = false;
	float bonusW = 50 * scopeKoefW, bonusH = 50 * scopeKoefW;
	const int chunkW = 160, chunkH = window_H / 2;
	int platformAmount = 25;
	const int chunkInLine = window_W / chunkW;//how much chunks in 1 line
	int chunkAmount = 0;
public:

	mFramework(int window_W = 640, int window_H = 1024, bool screenType = false): window_W(window_W < 640 ? 640 : window_W) 
																				, window_H(window_H < 1024 ? 1024 : window_H)
																				,screenType(screenType)
	{}
	//
	// no function calls are available here, this function should only return width, height and fullscreen values
	virtual void PreInit(int& width, int& height, bool& fullscreen) override;

	// return : true - ok, false - failed, application will exit
	virtual bool Init() override;

	virtual void Close() override;

	// return value: if true will exit the application
	virtual bool Tick() override;

	// param: xrel, yrel: The relative motion in the X/Y direction 
	// param: x, y : coordinate, relative to window
	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) override;

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) override;

	virtual void onKeyPressed(FRKey k) override;

	virtual void onKeyReleased(FRKey k) override;

	virtual const char* GetTitle() override;

	void scoreIncrease() { score += 75; pltPassed += 1; };

};

