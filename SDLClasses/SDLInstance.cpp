#include "..\include\SDLInstance.h"
#include <SDL.h>
#include "..\include\MouseState.h"
#include "..\include\SDLError.h"
#include "..\include\Vector3.h"

using std::string;

SDL::SDLInstance::SDLInstance(uint32_t param)
{
	//SDL_SetMainReady();
	int err = SDL_Init(static_cast<Uint32>(param));
	if (err) throw SDLError();
}

SDL::SDLInstance::~SDLInstance()
{
	SDL_Quit();
}

void SDL::SDLInstance::SetHint(const string & hint, const string & value)
{
	if (!SDL_SetHint(hint.c_str(), value.c_str()))
		throw SDLError();
}

SDL::Vector3<uint8_t> SDL::SDLInstance::GetVersion() const
{
	SDL_version ver;
	SDL_GetVersion(&ver);
	return Vector3<uint8_t>{ ver.major, ver.minor, ver.patch };
}

void SDL::SDLInstance::ProcessEvents()
{
	SDL_PumpEvents();
}

bool SDL::SDLInstance::QuitRequested() const
{
	return SDL_QuitRequested();
}

uint64_t SDL::SDLInstance::GetTicks() const
{
	return SDL_GetTicks();
}

uint64_t SDL::SDLInstance::GetPerformanceFrequency() const
{
	return SDL_GetPerformanceFrequency();
}

uint64_t SDL::SDLInstance::GetPerformanceCounter() const
{
	return SDL_GetPerformanceCounter();
}

void SDL::SDLInstance::Delay(uint32_t ms) const
{
	SDL_Delay(ms);
}

void SDL::SDLInstance::EnableScreenSaver(bool b)
{
	b ? SDL_EnableScreenSaver() : SDL_DisableScreenSaver();
}