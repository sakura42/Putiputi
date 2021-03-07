#include "Player.h"

Player::Player() {
	this->x = Game::WindowWidth / 2;
	this->y = Game::WindowHeight / 2;
	this->speed = 200.0f;
	this->rightSpeed = 0.0f;
	this->downSpeed = 0.0f;
	this->size = 15.0f;
	this->hp = 100;
	this->sp = 0;
	for (int i = 0; i < Player::skillNumMax; i++) {
		this->skillLevel.insert(this->skillLevel.end(),0);
	}
}

const int Player::upgradePoint[skillNumMax][skillLevelMax] = {
	{100, 200, 400, 800, 1200, 1600, 2000, 3000, 4000, 5000},
	{1200, 1600, 2000, 3000, 4000, 5000, 8000, 12000, 15000, 20000},
	{20000, 12000, 15000, 20000, 25000, 30000, 40000, 60000, 80000, 100000},
	{50000, 25000, 30000, 40000, 60000, 80000, 100000, 125000, 150000, 200000},
};

const int Player::skill[skillNumMax][skillLevelMax] = {
	{100, 150 ,200, 250, 300, 350, 400, 450, 500, 550},
	{9, 11, 13, 15, 17, 19, 21, 23, 25, 27},
	{100, 125 ,150, 175, 200, 225, 250, 275, 300, 350},
	{9, 13, 17, 21, 25, 30, 35, 40, 46, 55},
};

const float Player::coolDownMax[skillNumMax] = {
	0.3f, 1.2f, 1.6f, 1.8f
};

void Player::ProcessKeyboard(const uint8_t* state) {
	this->rightSpeed = 0.0f;
	this->downSpeed = 0.0f;
	if (state[SDL_SCANCODE_W] || state[SDL_SCANCODE_UP]) {
		this->downSpeed -= this->speed;
	}
	if (state[SDL_SCANCODE_A] || state[SDL_SCANCODE_LEFT]) {
		this->rightSpeed -= this->speed;
	}
	if (state[SDL_SCANCODE_S] || state[SDL_SCANCODE_DOWN]) {
		this->downSpeed += this->speed;
	}
	if (state[SDL_SCANCODE_D] || state[SDL_SCANCODE_RIGHT]) {
		this->rightSpeed += this->speed;
	}
}

void Player::UpdatePlayer(float deltaTime) {
	this->x += this->rightSpeed * deltaTime;
	this->y += this->downSpeed * deltaTime;
	if (x > Game::WindowWidth - size) {
		x = Game::WindowWidth - size;
	}
	if (x < 0) {
		x = 0;
	}
	if (y > Game::WindowHeight - size) {
		y = Game::WindowHeight - size;
	}
	if (y < 0) {
		y = 0;
	}
}


void Player::IncSp(int inc)
{
	this->sp += inc;
}
int Player::GetSp()
{
	return this->sp;
}

void Player::IncSkillLevel(int skillNum){
	this->skillLevel[skillNum] += 1;
}

int Player::GetSkillLevel(int skillNum)
{
	return this->skillLevel[skillNum];
}


