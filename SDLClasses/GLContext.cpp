#include "..\include\GLContext.h"
#include <SDL_video.h>
#include "..\include\SDLError.h"

SDL::GLContext::GLContext(void* windowHandler):
	contextHandler_(
		SDL_GL_CreateContext(static_cast<SDL_Window*>(windowHandler))
		, [](void* p) {
			SDL_GL_DeleteContext(p);
})
{
	if (contextHandler_.Get() == nullptr)
		throw SDLError();
}