#include "Button.h"

Button::Button(){
	this->r = 255;
	this->g = 255;
	this->b = 255;
	this->a = 255;
	this->isClicked = false;
	this->isMouseUp = false;
	this->isSelected = false;
	this->isAvailable = false;
	this->mousePosition = { 0,0 };
	this->buttonRect.x = 0;
	this->buttonRect.y = 0;
	this->buttonRect.w = 0;
	this->buttonRect.h = 0;
}

void Button::ProcessInput(bool isClicked){
	SDL_GetMouseState(&(this->mousePosition.x), &(this->mousePosition.y));

	if (this->isClicked == true && isClicked == false) {
		this->isMouseUp = true;
	}
	else {
		this->isMouseUp = false;
	}
	this->isClicked = isClicked;

	isSelected = SDL_EnclosePoints(&mousePosition, 1, &buttonRect, NULL);
}

void Button::SetColor(int r, int g, int b, int a){
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

void Button::SetRect(int x, int y, int w, int h) {
	this->buttonRect.x = x;
	this->buttonRect.y = y;
	this->buttonRect.w = w;
	this->buttonRect.h = h;
}

void Button::SetRect(SDL_Rect rect) {
	this->buttonRect = rect;
}

bool Button::GetIsAvailable()
{
	return this->isAvailable;
}

void Button::SetIsAvailable(bool isAvailable){
	this->isAvailable = isAvailable;
}

bool Button::GetIsSelected(){
	return this->isSelected;
}

void Button::RenderButton(SDL_Renderer* renderer){
	if (this->isSelected && this->isAvailable) {
		SDL_SetRenderDrawColor(renderer, r, g, b, a - 50);
	}
	else {
		SDL_SetRenderDrawColor(renderer, r, g, b, a);
	}

	SDL_Rect copyRect = buttonRect;
	if (this->isSelected && this->isClicked && this->isAvailable) {
		copyRect.x += 2;
		copyRect.y += 2;
	}
	SDL_RenderDrawRect(renderer, &copyRect);
}

bool Button::IsPressed()
{
	if (isSelected && isMouseUp) {
		return true;
	}
	else {
		return false;
	}
}

SkillButton::SkillButton(int skillNum){
	this->r = 255;
	this->g = 255;
	this->b = 255;
	this->a = 255;
	this->isClicked = false;
	this->isMouseUp = false;
	this->isSelected = false;
	this->isAvailable = false;
	this->mousePosition = { 0,0 };
	this->skillNum = skillNum;
	this->buttonRect.x = (int)(Game::WindowWidth / Player::skillNumMax) * this->skillNum;
	this->buttonRect.y = Game::WindowHeight - buttonHeight;
	this->buttonRect.w = Game::WindowWidth / Player::skillNumMax;
	this->buttonRect.h = buttonHeight;
}

void SkillButton::RenderButton(SDL_Renderer* renderer, Font* font, std::string textL , std::string textS) {

	Button::RenderButton(renderer);

	if (!(this->isAvailable)) {
		font->SetAlpha(150);
	}

	int sizeL = 36;
	int sizeS = 24;
	SDL_Rect copyRect = buttonRect;
	if (this->isSelected && this->isClicked && this->isAvailable) {
		copyRect.x += 2;
		copyRect.y += 2;
	}
	font->RenderTextCenter(renderer, textL, sizeL, copyRect.x + copyRect.w / 2, copyRect.y + copyRect.h / 2);
	font->RenderTextCenter(renderer, textS, sizeS, copyRect.x + copyRect.w / 2, copyRect.y + copyRect.h / 2 + (sizeL+sizeS)/2 + 15);


	font->SetAlpha(255);

}

SquareButton::SquareButton(int x, int y){
	this->r = 255;
	this->g = 255;
	this->b = 255;
	this->a = 255;
	this->isClicked = false;
	this->isMouseUp = false;
	this->isSelected = false;
	this->isAvailable = false;
	this->mousePosition = { 0,0 };
	this->buttonRect.x = x;
	this->buttonRect.y = y;
	this->buttonRect.w = buttonSize;
	this->buttonRect.h = buttonSize;
}

SquareButton::SquareButton() {
	SquareButton(0,0);
}

void SquareButton::RenderButton(SDL_Renderer* renderer, Font* font, std::string text){
	Button::RenderButton(renderer);

	if (!(this->isAvailable)) {
		font->SetAlpha(150);
	}

	SDL_Rect copyRect = buttonRect;
	if (this->isSelected && this->isClicked && this->isAvailable) {
		copyRect.x += 2;
		copyRect.y += 2;
	}
	font->RenderTextCenter(renderer, text, 48, copyRect.x + copyRect.w / 2, copyRect.y + copyRect.h / 2);

	font->SetAlpha(255);
}

RectButton::RectButton(int x, int y) {
	this->r = 255;
	this->g = 255;
	this->b = 255;
	this->a = 255;
	this->isClicked = false;
	this->isMouseUp = false;
	this->isSelected = false;
	this->isAvailable = false;
	this->mousePosition = { 0,0 };
	this->buttonRect.x = x;
	this->buttonRect.y = y;
	this->buttonRect.w = buttonWidth;
	this->buttonRect.h = buttonHeight;
}
