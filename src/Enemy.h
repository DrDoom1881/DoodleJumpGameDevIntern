#pragma once
#include "Object.h"
#include "Framework.h"
#include "mFramework.h"
class Enemy : public MoveableObject
{
private:
	int platformID = 0;
	int type = 0;
	Sprite* spr;
	bool status = true;

public:
	Enemy(float x, float y, float width, float height, int type) : MoveableObject(x, y, width, height), type(type)
	{
		deltaY = 0.55;
		switch (type)
		{
		case 0:
			spr = createSprite("data/enemy_1.png");
			break;
		case 1:
			spr = createSprite("data/enemy_2.png");
			break;
		case 2:
			spr = createSprite("data/enemy_3.png");
			break;
		}
		setSpriteSize(spr, width, height);
		deltaY = 0.55;

	}
	void move() override;
	const bool getStatus() { return status; };
	bool setStatus(bool newStatus) { status = newStatus; };
	Sprite* sprite() { return spr; };
};

