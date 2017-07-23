#include "stdafx.h"
#include "CppUnitTest.h"
#include <Vector4.h>
#include <Vector2.h>
#include <Window.h>
#include <SDLInstance.h>
#include <MouseState.h>
#include <Mouse.h>
#include <Library.h>
#include <Keyboard.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SDLClassesTests
{

	TEST_CLASS(EventTest)
	{
	public:
		TEST_METHOD(MouseAndKeyboard)
		{
			using namespace SDL;
			::SDL::SDLInstance sdl;
			::SDL::Mouse mouseDevice;
			::SDL::Keyboard keyboardDevice;
			Window wnd("Hello", Rect<int32_t>{ Window::Center,Window::Center,800,600 }, Window::WindowFlag::Null);
			auto& sur = wnd.GetWindowSurface();

			bool bRun = true;
			int b = 5000;

			while (bRun && b--) {
				sdl.ProcessEvents();
				
				auto mouse = mouseDevice.GetMouseState();
				Color<uint8_t> col = {
					uint8_t(mouse.leftButton ? 255 : 0),
					uint8_t(mouse.middleButton ? 255 : 0),
					uint8_t(mouse.rightButton ? 255 : 0),
					255
				};

				try {
					sur.Clear(
						Color<uint8_t>{
						uint8_t(keyboardDevice.KeyPressed("Space") ? 255 : 0),
						uint8_t(keyboardDevice.KeyPressed("Return") ? 255 : 0),
						uint8_t(keyboardDevice.KeyPressed("A") ? 255 : 0),
						255
					});

					if (keyboardDevice.KeyPressed("Escape") || sdl.QuitRequested()) bRun = false;
				}
				catch (std::exception e) {
					Log(e.what());
				}
				sur.Fill(Rect<int32_t>{ mouse.position.x,mouse.position.y,16,16 }, col);
				wnd.UpdateWindowSurface();
			}
		}

	};
}