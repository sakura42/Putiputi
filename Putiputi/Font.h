#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include <string>
#include <vector>
#include <unordered_map>

class Font{
public:
	Font();

	bool Load(const std::string& fileName);
	void Unload();

	void SetColor(int r, int g, int b);
	void SetAlpha(int a);
	bool RenderText(SDL_Renderer* renderer, std::string text, int size, int x, int y);
	bool RenderTextCenter(SDL_Renderer* renderer, std::string text, int size, int x, int y);
	
private:
	std::unordered_map<int, TTF_Font*> fontData;
	SDL_Color color;
};

