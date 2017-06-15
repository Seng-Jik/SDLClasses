#include "stdafx.h"
#include "CppUnitTest.h"
#include <SDL.h>
#include <Vector4U8.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SDLClassesTests
{		

	TEST_CLASS(SDLTest)
	{
	public:
		TEST_METHOD(InitAndQuit)
		{
			SDL::SDL sdl;
			auto ver = sdl.GetVersion();

			Log("SDL Version:%d,%d,%d\n", static_cast<int>(ver.x), static_cast<int>(ver.y), static_cast<int>(ver.z));
		}

	};
}