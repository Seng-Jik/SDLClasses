#include "..\include\GLContext.h"
#include <SDL.h>
#include "..\include\SDLError.h"

SDL::GLContext::~GLContext()
{
	SDL_GL_DeleteContext(std::any_cast<SDL_GLContext>(contextHandler_));
}

SDL::GLContext::GLContext(std::any windowHandler)
{
	contextHandler_ = SDL_GL_CreateContext(std::any_cast<SDL_Window*>(windowHandler));
	if (std::any_cast<SDL_GLContext>(contextHandler_) == nullptr)
		throw SDLError();
}