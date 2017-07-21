#include "..\include\GLContext.h"
#include <SDL_video.h>
#include "..\include\SDLError.h"

static void glContextDeleter(SDL_GLContext hnd)
{
	SDL_GL_DeleteContext(hnd);
}

SDL::GLContext::GLContext(SDL::Handler& windowHandler):
	contextHandler_(
		SDL_GL_CreateContext(windowHandler),
		glContextDeleter
	)
{
	if (static_cast<void*>(contextHandler_) == nullptr)
		throw SDLError();
}