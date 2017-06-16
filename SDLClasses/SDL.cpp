#include "..\include\SDL.h"
#include <SDL.h>
#include "..\include\MouseState.h"
#include "..\include\SDLError.h"
#include "..\include\Vector4U8.h"


using std::string;

SDL::SDL::SDL(InitParam param)
{
	SDL_SetMainReady();
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

SDL::Vector4U8 SDL::SDL::GetVersion()
{
	SDL_version ver;
	SDL_GetVersion(&ver);
	return Vector4U8{ ver.major,ver.minor,ver.patch,0 };
}

SDL::MouseState SDL::SDL::GetMouseState()
{
	MouseState state;
	auto buttonStates = SDL_GetMouseState(&state.position.x,&state.position.y);
	state.leftButton = buttonStates & SDL_BUTTON(SDL_BUTTON_LEFT);
	state.rightButton = buttonStates & SDL_BUTTON(SDL_BUTTON_RIGHT);
	state.middleButton = buttonStates & SDL_BUTTON(SDL_BUTTON_MIDDLE);
	return state;
}

uint64_t SDL::SDL::GetTicks()
{
	return SDL_GetTicks();
}

uint64_t SDL::SDL::GetPerformanceFrequency()
{
	return SDL_GetPerformanceFrequency();
}

uint64_t SDL::SDL::GetPerformanceCounter()
{
	return SDL_GetPerformanceCounter();
}

void SDL::SDL::SetMouseCursorShow(bool b)
{
	SDL_ShowCursor(b);
}

void SDL::SDL::Delay(uint32_t ms)
{
	SDL_Delay(ms);
}

void SDL::SDL::EnableScreenSaver(bool b)
{
	b ? SDL_EnableScreenSaver() : SDL_DisableScreenSaver();
}

