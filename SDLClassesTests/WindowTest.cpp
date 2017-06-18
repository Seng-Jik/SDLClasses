#include "stdafx.h"
#include "CppUnitTest.h"
#include <SDL.h>
#include <Window.h>
#include <GLContext.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SDLClassesTests
{

	TEST_CLASS(WindowTest)
	{
	public:
		TEST_METHOD(NewWindowAndWait)
		{
			using namespace SDL;
			::SDL::SDL sdl;
			Window wnd("HelloWorld", Rect<int32_t>{ Window::Center,Window::Center,1024,768 }, Window::WindowFlag::Null);
			sdl.Delay(3000);
		}

		TEST_METHOD(SimpleMessageBox)
		{
			using namespace SDL;
			::SDL::SDL sdl;
			Window wnd("HelloWorld", Rect<int32_t>{ Window::Center,Window::Center,1024,768 }, Window::WindowFlag::OpenGL);
			auto glContext = wnd.CreateOpenGLContext();
			wnd.ShowSimpleMessageBox("Test MsgBox", "Just a Test");
		}
		
	};
}