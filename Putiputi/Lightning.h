#pragma once
#include "Object.h"
#include "Enemy.h"
#include "Game.h"
#include <SDL.h>
#include <vector>

class Lightning : public Object{
public:
	Lightning(Enemy* objfrom, std::vector<Enemy*> enemies, int maxTarget);

	void UpdateLightning(float deltaTime);
	void RenderLightning(SDL_Renderer* renderer);

	bool GetEnd();

private:
	std::vector<Enemy*> objto;
	int rendering;
	bool end;
	static const int damage = 5000;
};

