#include "Explosion.h"

Explosion::Explosion(float x, float y){
	this->centerX = x;
	this->centerY = y;
	this->alpha = 50;
	this->size = 0;
}

void Explosion::UpdateExplosion(float deltaTime, int maxRange){
	if (size >= maxRange) {
		size = (float)maxRange;
		alpha -= 75 * deltaTime;
		if (alpha < 0) {
			alpha = 0;
		}
	}
	else {
		size += 300 * deltaTime;
		if (size >= maxRange) {
			size = (float)maxRange;
		}
	}

	this->x = centerX - (size / 2);
	this->y = centerY - (size / 2);
}

int Explosion::getAlpha()
{
	return this->alpha;
}
