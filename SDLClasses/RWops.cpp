#include "..\include\RWops.h"
#include <SDL.h>
#include "..\include\SDLError.h"

static SDL::Handler::Deleter rwopsDeleter = [](void* rwops)
{
	SDL_RWclose(static_cast<SDL_RWops*>(rwops));
};

SDL::RWops::RWops(void * ptrSDL_RWops):
	rwopsHandle_(ptrSDL_RWops, rwopsDeleter)
{
	if (!Available()) throw SDLError();
}

SDL::RWops::RWops(void * mem, int size):
	rwopsHandle_(static_cast<void*>(SDL_RWFromMem(mem, size)), rwopsDeleter)
{
	if (!Available()) throw SDLError();
}

SDL::RWops::RWops(const void * mem, int size):
	rwopsHandle_(static_cast<void*>(SDL_RWFromConstMem(mem, size)), rwopsDeleter)
{
	if (!Available()) throw SDLError();
}

SDL::RWops::RWops(const string & filePath, const string& mode):
	rwopsHandle_(static_cast<void*>(SDL_RWFromFile(filePath.c_str(), mode.c_str())),rwopsDeleter)
{
	if (!Available()) throw SDLError();
}

bool SDL::RWops::Available() const
{
	return rwopsHandle_.Get() != nullptr;
}

void * SDL::RWops::GetPtrToSDL_RWops()
{
	return rwopsHandle_.Get();
}

size_t SDL::RWops::Read(void * ptr, size_t size, size_t maxnum)
{
	return SDL_RWread(static_cast<SDL_RWops*>(rwopsHandle_.Get()),ptr, size, maxnum);
}

size_t SDL::RWops::Write(const void * ptr, size_t size, size_t num)
{
	return SDL_RWwrite(static_cast<SDL_RWops*>(rwopsHandle_.Get()),ptr, size, num);
}

int64_t SDL::RWops::Tell()
{
	return SDL_RWtell(static_cast<SDL_RWops*>(rwopsHandle_.Get()));
}
