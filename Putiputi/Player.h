#pragma once
#include "Game.h"
#include "Enemy.h"
#include <memory.h>
#include <limits>
#include <vector>

class Player : public Enemy{
public:
	Player();

	void ProcessKeyboard(const uint8_t* state);
	void UpdatePlayer(float deltaTime);
	void IncSp(int inc);
	int GetSp();
	void IncSkillLevel(int skillNum);
	int GetSkillLevel(int skillNum);

	static const int skillNumMax = 4;
	static const int skillLevelMax = 10;
	static const int upgradePoint[skillNumMax][skillLevelMax];
	static const int skill[skillNumMax][skillLevelMax];
	static const float coolDownMax[skillNumMax];

private:
	float speed;
	float rightSpeed;
	float downSpeed;
	int sp;
	std::vector<int> skillLevel;
};

