#include "Font.h"

Font::Font(){
	fontData = {};
	this->color.r = 255;
	this->color.g = 255;
	this->color.b = 255;
	this->color.a = 255;
}

bool Font::Load(const std::string& fileName)
{
	std::vector<int> fontSizes = {12, 24, 36, 48, 128, 256};

	for (auto& size : fontSizes) {
		TTF_Font* font = TTF_OpenFont(fileName.c_str(), size);
		if (!font) {
			SDL_Log(u8"フォントの読み込みに失敗しました:%s", SDL_GetError());
			return false;
		}
		fontData.emplace(size, font);
	}
	return true;
}

void Font::Unload() {
	for (auto& font : fontData) {
		TTF_CloseFont(font.second);
	}
}

void Font::SetColor(int r, int g, int b){
	this->color.r = r;
	this->color.g = g;
	this->color.b = b;
}

void Font::SetAlpha(int a){
	this->color.a = a;
}

bool Font::RenderText(SDL_Renderer* renderer, std::string text, int size, int x, int y){
	auto iter = fontData.find(size);
	if (iter == fontData.end()) {
		SDL_Log(u8"フォントサイズの呼び出しに失敗しました");
		return false;
	}
	TTF_Font* font = iter->second;
	SDL_Surface* surface = TTF_RenderUTF8_Blended(font, text.c_str(), this->color);
	if (!surface) {
		SDL_Log(u8"テキストの描画に失敗しました:%s", SDL_GetError());
		return false;
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (!texture) {
		SDL_Log(u8"テクスチャの生成に失敗しました:%s", SDL_GetError());
		return false;
	}

	int w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	SDL_Rect paste{ x,y,w,h };
	SDL_RenderCopy(renderer, texture, NULL, &paste);

	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
	return true;
}

bool Font::RenderTextCenter(SDL_Renderer* renderer, std::string text, int size, int x, int y) {
	auto iter = fontData.find(size);
	if (iter == fontData.end()) {
		SDL_Log(u8"フォントサイズの呼び出しに失敗しました");
		return false;
	}
	TTF_Font* font = iter->second;
	SDL_Surface* surface = TTF_RenderUTF8_Blended(font, text.c_str(), this->color);
	if (!surface) {
		SDL_Log(u8"テキストの描画に失敗しました:%s", SDL_GetError());
		return false;
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (!texture) {
		SDL_Log(u8"テクスチャの生成に失敗しました:%s", SDL_GetError());
		return false;
	}

	int w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	SDL_Rect paste{ x-w/2, y-h/2, w, h };
	SDL_RenderCopy(renderer, texture, NULL, &paste);

	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
	return true;
}