#include "Enemy.h"
#include "Game.h"

Enemy::Enemy(int hp) {
	this->size = 8.0f;
	std::random_device rnd;
	std::mt19937 mt(rnd());
	std::uniform_int_distribution<> randWidth(0, (int)(Game::WindowWidth-size));
	std::uniform_int_distribution<> randHeight(0, (int)(Game::WindowHeight-SkillButton::buttonHeight-size));
	this->x = (float)randWidth(mt);
	this->y = (float)randHeight(mt);
	this->hp = hp;
	this->isExplosion = false;
}

Enemy::Enemy(){
	Enemy(100);
}

void Enemy::Damage(int dec){
	this->hp -= dec;
	if (this->hp < 0) {
		this->hp = 0;
	}
}

int Enemy::GetHp(){
	return this->hp;
}
void Enemy::SetHp(int hp) {
	this->hp = hp;
}

bool Enemy::GetIsExplosion()
{
	return this->isExplosion;
}

void Enemy::SetIsExplosion(bool isExplosion){
	this->isExplosion = isExplosion;
}
