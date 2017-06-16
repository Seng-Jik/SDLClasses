#include "stdafx.h"
#include "CppUnitTest.h"
#include <SDL.h>
#include <Vector4U8.h>
#include <Window.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SDLClassesTests
{

	TEST_CLASS(SurfaceTest)
	{
	public:
		TEST_METHOD(SimpleDraw)
		{
			using namespace SDL;
			::SDL::SDL sdl;
			Window wnd("HelloWorld", Rect{ Window::Center,Window::Center,1024,768 }, Window::WindowFlag::Null);
			auto& sur = wnd.GetWindowSurface();
			sur.Clear(ColorU8{ 0,0,255,255 });

			sur.Fill(Rect{ 50,50,150,150 }, ColorU8{ 0,255,0,255 });
			std::vector<Rect> rects = {
				{750,350,200,200},
				{0,350,200,200}
			};
			sur.Fill(rects, ColorU8{ 255,0,0,255 });
			wnd.UpdateWindowSurface();
			sdl.Delay(3000);

			sur.Shade([](int x, int y, Surface& thisSur, ColorU8 oldColor) {
				return ColorU8
				{ 
					static_cast<uint8_t>(x % 255),
					static_cast<uint8_t>(y % 255),
					128,
					255
				};
			});
			wnd.UpdateWindowSurface();
			sdl.Delay(3000);

		}

	};
}