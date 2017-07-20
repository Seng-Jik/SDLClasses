#include "..\include\Mouse.h"
#include <SDL_mouse.h>

SDL::MouseState SDL::Mouse::GetMouseState() const
{
	MouseState state;
	auto buttonStates = SDL_GetMouseState(&state.position.x, &state.position.y);
	state.leftButton = buttonStates & SDL_BUTTON(SDL_BUTTON_LEFT);
	state.rightButton = buttonStates & SDL_BUTTON(SDL_BUTTON_RIGHT);
	state.middleButton = buttonStates & SDL_BUTTON(SDL_BUTTON_MIDDLE);
	return state;
}

void SDL::Mouse::SetMouseCursorShow(bool b)
{
	SDL_ShowCursor(b);
}
