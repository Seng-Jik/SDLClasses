#include "stdafx.h"
#include "CppUnitTest.h"
#include <SDL.h>
#include <Window.h>
#include <Vector4.h>

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
			Window wnd("HelloWorld", Rect<int32_t>{ Window::Center,Window::Center,1024,768 }, Window::WindowFlag::Null);
			auto& sur = wnd.GetWindowSurface();
			sur.Clear(Color<uint8_t>{ 0,0,255,255 });

			sur.Fill(Rect<int32_t>{ 50,50,150,150 }, Color<uint8_t>{ 0,255,0,255 });
			std::vector<Rect<int32_t>> rects = {
				{750,350,200,200},
				{0,350,200,200}
			};
			sur.Fill(rects, Color<uint8_t>{ 255,0,0,255 });
			wnd.UpdateWindowSurface();
			sdl.Delay(500);

			sur.Shade([](int x, int y, Surface& thisSur, Color<uint8_t> oldColor) {
				return Color<uint8_t>
				{ 
					static_cast<uint8_t>(x % 255),
					static_cast<uint8_t>(y % 255),
					128,
					255
				};
			});
			wnd.UpdateWindowSurface();
			sdl.Delay(500);

		}

	};
}