#pragma once
#include "Object.h"
#include "Framework.h"
#include "mFramework.h"
#include<iostream>
class Bullet : public MoveableObject
{
private:
	int window_w, window_h;
	float speedScale = 1;
	bool start;
	
public:
	Bullet(float width, float height, bool start = true) : MoveableObject(0, 0, width, height), start(start) {
		deltaX = 0.9f;
		deltaY = 0.9f;
		getScreenSize(window_w, window_h);


	};
	void Fire() { start = false; };
	void move() override;
	void collision(int i);
	void Start(float, float);

};

