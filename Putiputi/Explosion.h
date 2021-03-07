#pragma once
#include "Object.h"

class Explosion : public Object{
public:
	Explosion(float x, float y);

	static const int damage = 120;
	static const int range = 200;
	void UpdateExplosion(float deltaTime, int maxRange);

	int getAlpha();
private:
	int alpha;
	float centerX;
	float centerY;

};

