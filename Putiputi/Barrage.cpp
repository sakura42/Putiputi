#include "Barrage.h"

#define PI 3.14159265

Arrow::Arrow(Enemy* objfrom, float sinx, float cosx) {
	this->x = objfrom->GetX() + objfrom->GetSize() / 2;
	this->y = objfrom->GetY() + objfrom->GetSize() / 2;
	this->size = 10.0f;
	this->speed = 800.0f;
	this->cosx = cosx;
	this->sinx = sinx;
}

void Arrow::UpdateArrow(float deltaTime) {
	this->x += this->speed * deltaTime * cosx;
	this->y += this->speed * deltaTime * sinx;
}

Barrage::Barrage(Enemy* objfrom, float xto, float yto, int arrowNum){
	float sinx, cosx;
	sinx = (yto - objfrom->GetY()) / objfrom->Distance(xto, yto);
	float angle = asin(sinx) - ((arrowNum - 1) / 2) * (PI / 60);
	sinx = sin(angle);
	if (xto > objfrom->GetX()) {
		cosx = cos(angle);
	}
	else {
		cosx = -cos(angle);
	}

	for (int i = 0; i < arrowNum; i++) {
		this->arrows.insert(arrows.end(), new Arrow(objfrom, sinx, cosx));
		angle += (float)PI / 60;
		sinx = sin(angle);
		if (xto > objfrom->GetX()) {
			cosx = cos(angle);
		}
		else {
			cosx = -cos(angle);
		}
	}
}
