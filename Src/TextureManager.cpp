#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* FILE_NAME)
{
	SDL_Surface* tempSurface = IMG_Load(FILE_NAME);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	return tex;
}

void TextureManager::Render(SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect)
{
	SDL_RenderCopy(Game::renderer, texture, &srcRect, &destRect);
}