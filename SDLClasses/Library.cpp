#include "..\include\Library.h"
#include "..\include\SDLError.h"
#include <SDL.h>

using namespace SDL;

void * SDL::Library::loadFunction(const std::string & funcName) const
{
	auto p = SDL_LoadFunction(libraryHandle_, funcName.c_str());
	if (p == nullptr) throw SDLError();
	return p;
}

SDL::Library::Library(const std::string & libName)
{
	libraryHandle_ = SDL_LoadObject(libName.c_str());
	if (libraryHandle_ == nullptr) throw SDLError();
}

Library::~Library()
{
	SDL_UnloadObject(libraryHandle_);
}
