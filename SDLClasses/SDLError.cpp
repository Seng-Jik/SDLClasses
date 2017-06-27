#include "..\include\SDLError.h"
#include <SDL.h>

const char * SDL::SDLError::what() const
{
	return SDL_GetError();
}

const std::string SDL::SDLError::What() const
{
	return what();
}