#pragma once
#include "Object.h"
#include "Enemy.h"
#include <vector>
#include <cmath>

class Arrow : public Object{
public:
	Arrow(Enemy* objfrom, float sinx, float cosx);

	void UpdateArrow(float deltaTime);

private:
	float speed;
	float sinx, cosx;
};

class Barrage{
public:
	Barrage(Enemy* objfrom, float xto, float yto, int arrowNum);
	std::vector<class Arrow*> arrows;
	static const int damage = 1000;
};