#pragma once
#include "Object.h"
#include "mFramework.h"
#include<iostream>
class Doodle : public MoveableObject 
{
private:
	int HP = 5;
	int window_w, window_h;
	float jumpH = 160;
	float jumpCoord = y - jump;
	float speedScale = 1;
	int direct = 0;
	float jumpCheck = y2;
	float g = 0;
	unsigned int fireTick = 0;
	unsigned int bonusTick = 0;
	unsigned int tickCounter = 0;
	Sprite* NormalLeftDoodleSpr;
	Sprite* NormalRightDoodleSpr;
	Sprite* JumpLeftDoodleSpr;
	Sprite* JumpRightDoodleSpr;
	Sprite* noseUP;
	Sprite* noseR;
	Sprite* noseL;

public:
	static int killCount;
	bool jump = false;
	bool fire = false;
	Sprite* LeftDoodleSpr;
	Sprite* RightDoodleSpr;



public:
	Doodle(float x, float y, float width, float height) : MoveableObject(x, y, width, height){
		speedX = 1.95f; 
		speedY = 1;
		deltaY = 0.95;
		NormalLeftDoodleSpr = createSprite("data/lik-left@2x.png");
		NormalRightDoodleSpr = createSprite("data/lik-right@2x.png");
		JumpLeftDoodleSpr = createSprite("data/lik-left-odskok@2x.png");
		JumpRightDoodleSpr = createSprite("data/lik-right-odskok@2x.png");
		noseUP = createSprite("data/jungle-njuska_UP@2x.png");
		noseR = createSprite("data/jungle-njuska_R@2x.png");
		noseL = createSprite("data/jungle-njuska_L@2x.png");

		setSpriteSize(noseR, width, height);
		setSpriteSize(noseL, width, height);
		setSpriteSize(noseUP, width, height);
		setSpriteSize(NormalLeftDoodleSpr, width, height);
		setSpriteSize(NormalRightDoodleSpr, width, height);
		setSpriteSize(JumpLeftDoodleSpr, width, height);
		setSpriteSize(JumpRightDoodleSpr, width, height);
		getScreenSize(window_w, window_h);


	};
	~Doodle()
	{
		LeftDoodleSpr = 0;
		RightDoodleSpr = 0;
		destroySprite(NormalLeftDoodleSpr);
		destroySprite(NormalRightDoodleSpr);
		destroySprite(JumpLeftDoodleSpr);
		destroySprite(JumpRightDoodleSpr);
		destroySprite(noseR);
		destroySprite(noseL);
		destroySprite(noseUP);
	}
	void Fire(int tick);
	int& giveHP() { return HP; };
	void directSet(int d) { direct = d; };
	int directGet() { return direct; };
	void move() override;
	void collision();
	const float getJump() { return jump; };
	float& JumpY() { return jumpCoord; };
	void dead();


};


