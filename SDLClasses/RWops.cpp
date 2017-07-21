#include "..\include\RWops.h"
#include <SDL_rwops.h>
#include "..\include\SDLError.h"

static void rwopsDeleter(SDL_RWops* rwops)
{
	SDL_RWclose(rwops);
};

SDL::RWops::RWops(void * ptrSDL_RWops):
	rwopsHandle_(static_cast<SDL_RWops*>(ptrSDL_RWops), rwopsDeleter)
{
	if (!Available()) throw SDLError();
}

SDL::RWops::RWops(void * mem, int size):
	rwopsHandle_(static_cast<SDL_RWops*>(SDL_RWFromMem(mem, size)), rwopsDeleter)
{
	if (!Available()) throw SDLError();
}

SDL::RWops::RWops(const void * mem, int size):
	rwopsHandle_(static_cast<SDL_RWops*>(SDL_RWFromConstMem(mem, size)), rwopsDeleter)
{
	if (!Available()) throw SDLError();
}

SDL::RWops::RWops(const string & filePath, const string& mode):
	rwopsHandle_(static_cast<SDL_RWops*>(SDL_RWFromFile(filePath.c_str(), mode.c_str())),rwopsDeleter)
{
	if (!Available()) throw SDLError();
}

bool SDL::RWops::Available() const
{
	return static_cast<SDL_RWops*>(rwopsHandle_) != nullptr;
}

const SDL::Handler& SDL::RWops::GetPtrToSDL_RWops()
{
	return rwopsHandle_;
}

size_t SDL::RWops::Read(void * ptr, size_t size, size_t maxnum)
{
	return SDL_RWread(static_cast<SDL_RWops*>(rwopsHandle_),ptr, size, maxnum);
}

size_t SDL::RWops::Write(const void * ptr, size_t size, size_t num)
{
	return SDL_RWwrite(static_cast<SDL_RWops*>(rwopsHandle_),ptr, size, num);
}

int64_t SDL::RWops::Tell()
{
	return SDL_RWtell(static_cast<SDL_RWops*>(rwopsHandle_));
}
