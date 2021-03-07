#include "CoolDownBar.h"

#include "Game.h"
#include "Player.h"

CoolDownBar::CoolDownBar(int skillNum){
	this->r = 255;
	this->g = 255;
	this->b = 255;
	this->a = 255;
	this->barRect.x = (Game::WindowWidth / Player::skillNumMax) * skillNum;
	this->barRect.y = Game::WindowHeight - SkillButton::buttonHeight - CoolDownBar::BarHeight;
	this->barRect.w = Game::WindowWidth / Player::skillNumMax;
	this->barRect.h = CoolDownBar::BarHeight;
	this->skillNum = skillNum;
	this->cdMax = Player::coolDownMax[skillNum];
	this->cd = 0;
}

void CoolDownBar::SetColor(int r, int g, int b, int a) {
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

void CoolDownBar::RenderBar(SDL_Renderer* renderer, float coolDown){
	float percentage = (cdMax - coolDown) / cdMax;
	this->barRect.w = (Game::WindowWidth / Player::skillNumMax) * percentage;

	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_RenderFillRect(renderer, &(this->barRect));
}
