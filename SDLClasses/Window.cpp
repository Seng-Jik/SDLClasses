#include <SDL_video.h>
#include <SDL_messagebox.h>
#include <SDL_syswm.h>
#include "..\include\Vector4.h"
#include "..\include\Window.h"
#include "..\include\GLContext.h"

static void winDeleter(void* p)
{
	SDL_DestroyWindow(static_cast<SDL_Window*>(p));
};

SDL::Window::Window(const string & title, Rect<int32_t> r, WindowFlag flags)
	:
	windowHandler_(
		SDL_CreateWindow(
			title.c_str(),
			r.x == Center ? SDL_WINDOWPOS_CENTERED : r.x,
			r.y == Center ? SDL_WINDOWPOS_CENTERED : r.y,
			r.w, r.h,
			static_cast<uint32_t>(flags)
		),
		winDeleter
	),
	windowSurface_(SDL_GetWindowSurface(static_cast<SDL_Window*>(windowHandler_.Get())),false)
{
}


void SDL::Window::UpdateWindowSurface() const
{
	SDL_UpdateWindowSurface(static_cast<SDL_Window*>(windowHandler_.Get()));
}

void* SDL::Window::GetHWND()
{
	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	if (SDL_GetWindowWMInfo(static_cast<SDL_Window*>(windowHandler_.Get()), &wmInfo))
	{
		if (wmInfo.subsystem == SDL_SYSWM_WINDOWS)
		{
			HWND i = wmInfo.info.win.window;
			return i;
		}
	}
	throw std::runtime_error("Can not get HWND.");
}

void SDL::Window::ShowSimpleMessageBox(const string & title, const string & msg) const
{
	SDL_ShowSimpleMessageBox(0, title.c_str(), msg.c_str(), static_cast<SDL_Window*>(windowHandler_.Get()));
}

void SDL::Window::SetWindowIcon(const Surface & icon)
{
	SDL_SetWindowIcon(static_cast<SDL_Window*>(windowHandler_.Get()), const_cast<SDL_Surface*>(static_cast<const SDL_Surface*>(icon.GetPtrToSDL_Surface())));
}

SDL::GLContext SDL::Window::CreateOpenGLContext()
{
	return GLContext(windowHandler_.Get());
}