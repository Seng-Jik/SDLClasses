#include "..\include\Library.h"
#include <SDL.h>

using namespace SDL;

void * SDL::Library::loadFunction(const std::string & funcName)
{
	return SDL_LoadFunction(libraryHandle_, funcName.c_str());
}

SDL::Library::Library(const std::string & libName)
{
	libraryHandle_ = SDL_LoadObject(libName.c_str());
}

Library::~Library()
{
	SDL_UnloadObject(libraryHandle_);
}
