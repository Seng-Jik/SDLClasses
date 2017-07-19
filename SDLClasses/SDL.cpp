#include "..\include\SDL.h"
#include <SDL.h>
#include "..\include\MouseState.h"
#include "..\include\SDLError.h"
#include "..\include\Vector3.h"

using std::string;

SDL::SDL::SDL(InitParam param)
{
	//SDL_SetMainReady();
	int err = SDL_Init(static_cast<Uint32>(param));
	if (err) throw SDLError();
}

SDL::SDL::~SDL()
{
	SDL_Quit();
}

void SDL::SDL::SetHint(const string & hint, const string & value)
{
	if (!SDL_SetHint(hint.c_str(), value.c_str()))
		throw SDLError();
}

SDL::Vector3<uint8_t> SDL::SDL::GetVersion() const
{
	SDL_version ver;
	SDL_GetVersion(&ver);
	return Vector3<uint8_t>{ ver.major, ver.minor, ver.patch };
}

void SDL::SDL::ProcessEvents()
{
	SDL_PumpEvents();
}

bool SDL::SDL::QuitRequested() const
{
	return SDL_QuitRequested();
}

uint64_t SDL::SDL::GetTicks() const
{
	return SDL_GetTicks();
}

uint64_t SDL::SDL::GetPerformanceFrequency() const
{
	return SDL_GetPerformanceFrequency();
}

uint64_t SDL::SDL::GetPerformanceCounter() const
{
	return SDL_GetPerformanceCounter();
}

void SDL::SDL::Delay(uint32_t ms) const
{
	SDL_Delay(ms);
}

void SDL::SDL::EnableScreenSaver(bool b)
{
	b ? SDL_EnableScreenSaver() : SDL_DisableScreenSaver();
}