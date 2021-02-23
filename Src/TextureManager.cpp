#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* path)
{
	SDL_Surface* tempSurface = IMG_Load(path);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	return tex;
}

SDL_Texture* TextureManager::LoadText(const char* message)
{
	SDL_Color color = { 0, 0, 0 };
	TTF_Font* font = TTF_OpenFont("assets/achafont.ttf", 72);

	SDL_Surface* tempSurface = TTF_RenderText_Solid(font, message, color);
	SDL_Texture* text = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	TTF_CloseFont(font);

	return text;
}

void TextureManager::Render(SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect)
{
	SDL_RenderCopy(Game::renderer, texture, &srcRect, &destRect);
}