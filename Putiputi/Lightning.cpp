#include "Lightning.h"

Lightning::Lightning(Enemy* objfrom, std::vector<Enemy*> enemies, int maxTarget){
	this->objto.insert(objto.end(), objfrom);
	while (this->objto.size() < maxTarget) {
		float min = Game::WindowWidth*2;
		Enemy* closestEnemy;
		for (auto j : enemies) {
			if (std::find(objto.begin(), objto.end(), j) == objto.end()) {
				if (objto[objto.size() - 1]->Distance(j) < min) {
					min = objto[objto.size() - 1]->Distance(j);
					closestEnemy = j;
				}
			}
		}
		this->objto.insert(objto.end(), closestEnemy);
	}
	this->rendering = -1;
	this->end = false;
}

void Lightning::UpdateLightning(float deltaTime){
	this->rendering += 1;
	if (rendering + 1 >= objto.size()) {
		this->rendering -= 1;
		this->end = true;
	}
	objto[rendering]->Damage(Lightning::damage);
	objto[rendering + 1]->Damage(Lightning::damage);
}

void Lightning::RenderLightning(SDL_Renderer* renderer) {
	SDL_RenderDrawLine(renderer,
		(int)(objto[rendering]->GetX() - 1), (int)(objto[rendering]->GetY() - 1),
		(int)(objto[rendering + 1]->GetX() - 1), (int)(objto[rendering + 1]->GetY() - 1));
	SDL_RenderDrawLine(renderer,
		(int)(objto[rendering]->GetX()), (int)(objto[rendering]->GetY() - 1),
		(int)(objto[rendering + 1]->GetX()), (int)(objto[rendering + 1]->GetY() - 1));
	SDL_RenderDrawLine(renderer,
		(int)(objto[rendering]->GetX() + 1), (int)(objto[rendering]->GetY() - 1),
		(int)(objto[rendering + 1]->GetX() + 1), (int)(objto[rendering + 1]->GetY() - 1));
	SDL_RenderDrawLine(renderer,
		(int)(objto[rendering]->GetX() - 1), (int)(objto[rendering]->GetY()),
		(int)(objto[rendering + 1]->GetX() - 1), (int)(objto[rendering + 1]->GetY()));
	SDL_RenderDrawLine(renderer,
		(int)(objto[rendering]->GetX()), (int)(objto[rendering]->GetY()),
		(int)(objto[rendering + 1]->GetX()), (int)(objto[rendering + 1]->GetY()));
	SDL_RenderDrawLine(renderer,
		(int)(objto[rendering]->GetX() + 1), (int)(objto[rendering]->GetY()),
		(int)(objto[rendering + 1]->GetX() + 1), (int)(objto[rendering + 1]->GetY()));
	SDL_RenderDrawLine(renderer,
		(int)(objto[rendering]->GetX() - 1), (int)(objto[rendering]->GetY() + 1),
		(int)(objto[rendering + 1]->GetX() - 1), (int)(objto[rendering + 1]->GetY() + 1));
	SDL_RenderDrawLine(renderer,
		(int)(objto[rendering]->GetX() + 1), (int)(objto[rendering]->GetY() + 1),
		(int)(objto[rendering + 1]->GetX()), (int)(objto[rendering + 1]->GetY() + 1));
	SDL_RenderDrawLine(renderer,
		(int)(objto[rendering]->GetX() + 1), (int)(objto[rendering]->GetY() + 1),
		(int)(objto[rendering + 1]->GetX() + 1), ((int)objto[rendering + 1]->GetY() + 1));
}

bool Lightning::GetEnd(){
	return this->end;
}
