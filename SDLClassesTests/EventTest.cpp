#include "stdafx.h"
#include "CppUnitTest.h"
#include <Window.h>
#include <SDL.h>
#include <MouseState.h>
#include <Library.h>
#include <Vector4U8.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SDLClassesTests
{

	TEST_CLASS(EventTest)
	{
	public:
		TEST_METHOD(MouseAndKeyboard)
		{
			using namespace SDL;
			::SDL::SDL sdl;
			Window wnd("Hello", Rect{ Window::Center,Window::Center,800,600 }, Window::WindowFlag::Null);
			auto& sur = wnd.GetWindowSurface();

			bool bRun = true;


			while (bRun) {
				sdl.ProcessEvents();
				
				auto mouse = sdl.GetMouseState();
				ColorU8 col = {
					uint8_t(mouse.leftButton ? 255 : 0),
					uint8_t(mouse.middleButton ? 255 : 0),
					uint8_t(mouse.rightButton ? 255 : 0),
					255
				};

				try {
					sur.Clear(
						ColorU8{
						uint8_t(sdl.KeyPressed("Space") ? 255 : 0),
						uint8_t(sdl.KeyPressed("Return") ? 255 : 0),
						uint8_t(sdl.KeyPressed("A") ? 255 : 0),
						255
					});

					if (sdl.KeyPressed("Escape")) bRun = false;
				}
				catch (std::exception e) {
					Log(e.what());
				}
				sur.Fill(Rect{ mouse.position.x,mouse.position.y,16,16 }, col);
				wnd.UpdateWindowSurface();
			}
		}

	};
}