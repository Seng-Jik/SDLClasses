#include "..\include\Library.h"
#include "..\include\SDLError.h"
#include <SDL_loadso.h>

using namespace SDL;

static void libraryDeleter(void* hnd)
{
	SDL_UnloadObject(hnd);
}

void * SDL::Library::loadFunction(const std::string & funcName) const
{
	auto p = SDL_LoadFunction(static_cast<void*>(libraryHandle_), funcName.c_str());
	if (p == nullptr) throw SDLError();
	return p;
}

SDL::Library::Library(const std::string & libName):
	libraryHandle_(SDL_LoadObject(libName.c_str()), libraryDeleter)
{
	if (static_cast<void*>(libraryHandle_) == nullptr) throw SDLError();
}
