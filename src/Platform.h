#pragma once
#include "Object.h"
#include "mFramework.h"
#include "Enemy.h"
#include <stdlib.h>


class Platform : public MoveableObject
{
private:
	bool haveAlreadyJumped = false;
	bool withEnemy = false;
	bool withBonus = false;
private:
	void EnemySpawn();
	void BonusSpawn();
public:
	Platform(float x, float y, float width, float height, bool withBonus = false, bool withEnemy = false) : MoveableObject(x, y, width, height)
	{
		deltaY = 0.55;
		if (withEnemy)
			EnemySpawn();
		if (withBonus)
			BonusSpawn();
		

	}

	~Platform()
	{
	}
	void move() override;
	const bool IsJumped() { return haveAlreadyJumped; };
	void Jumped() { haveAlreadyJumped = true; };
};

