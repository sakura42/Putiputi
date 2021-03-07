#pragma once
#include "Object.h"
#include <random>

class Enemy : public Object{
public:
	Enemy(int hp);
	Enemy();

	void Damage(int dec);

	int GetHp();
	void SetHp(int hp);
	bool GetIsExplosion();
	void SetIsExplosion(bool isExplosion);

protected:
	int hp;
	bool isExplosion;
};

