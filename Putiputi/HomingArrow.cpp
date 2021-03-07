#include "HomingArrow.h"

HomingArrow::HomingArrow(Enemy* objfrom, Enemy* objto){
	this->x = objfrom->GetX() + objfrom->GetSize()/2;
	this->y = objfrom->GetY() + objfrom->GetSize()/2;
	this->objto = objto;
	this->size = 5.0f;
	this->oldCosx = 1;
	this->oldSinx = 0;
}

const float HomingArrow::speed = 500.0f;

void HomingArrow::UpdateArrow(float deltaTime){
	float sinx, cosx;
	if (this->objto->GetHp() > 0) {
		sinx = (this->objto->GetY() - this->y) / this->Distance(objto);
		cosx = (this->objto->GetX() - this->x) / this->Distance(objto);
	}
	else {
		sinx = oldSinx;
		cosx = oldCosx;
	}

	this->x += speed * deltaTime * cosx;
	this->y += speed * deltaTime * sinx;

	this->oldCosx = cosx;
	this->oldSinx = sinx;
}