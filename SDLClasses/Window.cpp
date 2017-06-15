#include <SDL.h>
#include "..\include\Window.h"


SDL::Window::Window(const string & title, Rect r, WindowFlag flags)
	:
	windowHandler_(
		SDL_CreateWindow(
			title.c_str(),
			r.x == Center ? SDL_WINDOWPOS_CENTERED : r.x,
			r.y == Center ? SDL_WINDOWPOS_CENTERED : r.y,
			r.w, r.h, 
			static_cast<uint32_t>(flags)
		)
	),
	windowSurface_(
		SDL_GetWindowSurface(
			static_cast<SDL_Window*>(windowHandler_)
		),
		false
	)
{
}

SDL::Window::~Window()
{
	SDL_DestroyWindow(static_cast<SDL_Window*>(windowHandler_));
}

void SDL::Window::UpdateWindowSurface() const
{
	SDL_UpdateWindowSurface(static_cast<SDL_Window*>(windowHandler_));
}

void SDL::Window::ShowSimpleMessageBox(const string & title, const string & msg) const
{
	SDL_ShowSimpleMessageBox(0, title.c_str(), msg.c_str(), static_cast<SDL_Window*>(windowHandler_));
}
