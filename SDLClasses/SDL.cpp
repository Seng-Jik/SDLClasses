#include "..\include\SDL.h"
#include <SDL.h>
#include "..\include\MouseState.h"
#include "..\include\SDLError.h"
#include "..\include\Vector3.h"


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

SDL::Vector3<uint8_t> SDL::SDL::GetVersion() const
{
	SDL_version ver;
	SDL_GetVersion(&ver);
	return Vector3<uint8_t>{ ver.major,ver.minor,ver.patch };
}

void SDL::SDL::ProcessEvents()
{
	SDL_PumpEvents();
}

bool SDL::SDL::KeyPressed(const string & keyName) const
{
	auto scanCode = SDL_GetScancodeFromName(keyName.c_str());
	if (scanCode == SDL_SCANCODE_UNKNOWN) throw std::exception(("Unknow key:" + keyName).c_str());
	auto states = SDL_GetKeyboardState(nullptr);
	if (states == nullptr) throw SDLError();
	return states[scanCode] != 0;
}

SDL::MouseState SDL::SDL::GetMouseState() const
{
	MouseState state;
	auto buttonStates = SDL_GetMouseState(&state.position.x,&state.position.y);
	state.leftButton = buttonStates & SDL_BUTTON(SDL_BUTTON_LEFT);
	state.rightButton = buttonStates & SDL_BUTTON(SDL_BUTTON_RIGHT);
	state.middleButton = buttonStates & SDL_BUTTON(SDL_BUTTON_MIDDLE);
	return state;
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

void SDL::SDL::SetMouseCursorShow(bool b)
{
	SDL_ShowCursor(b);
}

void SDL::SDL::Delay(uint32_t ms) const
{
	SDL_Delay(ms);
}

void SDL::SDL::EnableScreenSaver(bool b)
{
	b ? SDL_EnableScreenSaver() : SDL_DisableScreenSaver();
}

