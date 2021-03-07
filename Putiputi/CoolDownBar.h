#pragma once
#include <SDL.h>

class CoolDownBar{
public:
	CoolDownBar(int skillNum);

	void SetColor(int r, int g, int b, int a);
	void RenderBar(SDL_Renderer* renderer, float coolDown);

	static const int BarHeight = 10;
private:
	int r, g, b, a;
	int skillNum;
	SDL_Rect barRect;
	float cdMax;
	float cd;
};

