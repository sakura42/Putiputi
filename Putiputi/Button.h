#pragma once
#include "Game.h"
#include "Font.h"
#include "Player.h"
#include <string>
#include <SDL.h>

class Button{
public:
	Button();

	void ProcessInput(bool isClicked);

	void SetColor(int r, int g, int b, int a);
	void SetRect(int x, int y, int w, int h);
	void SetRect(SDL_Rect rect);
	bool GetIsAvailable();
	void SetIsAvailable(bool isAvailable);
	bool GetIsSelected();

	virtual void RenderButton(SDL_Renderer* renderer);

	bool IsPressed();
protected:
	bool isClicked;
	bool isMouseUp;
	bool isSelected;
	bool isAvailable;
	int r, g, b, a;
	SDL_Point mousePosition;
	SDL_Rect buttonRect;
};

class SkillButton : public Button{
public:
	SkillButton(int skillNum);

	void RenderButton(SDL_Renderer* renderer, Font* font, std::string textL, std::string textS);

	static const int buttonHeight = 150;

private:
	int skillNum;
};

class SquareButton : public Button {
public:
	SquareButton();
	SquareButton(int x, int y);

	void RenderButton(SDL_Renderer* renderer, Font* font, std::string text);

private:
	static const int buttonSize = 50;
};

class RectButton : public SquareButton {
public:
	RectButton(int x, int y);
	static const int buttonWidth = 700;
	static const int buttonHeight = 100;
};