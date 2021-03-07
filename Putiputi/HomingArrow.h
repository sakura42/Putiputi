#pragma once
#include "Game.h"
#include "Enemy.h"

class HomingArrow : public Object{
public:
	HomingArrow(Enemy* objfrom, Enemy* objto);

	void UpdateArrow(float deltaTime);
	Enemy* objto;	

private:
	static const float speed;
	float oldSinx, oldCosx;
};

