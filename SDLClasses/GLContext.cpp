#include "..\include\GLContext.h"
#include <SDL.h>
#include "..\include\SDLError.h"

SDL::GLContext::~GLContext()
{
	SDL_GL_DeleteContext(contextHandler_);
}

SDL::GLContext::GLContext(void* windowHandler)
{
	contextHandler_ = SDL_GL_CreateContext(static_cast<SDL_Window*>(windowHandler));
	if (contextHandler_ == nullptr)
		throw SDLError();
}