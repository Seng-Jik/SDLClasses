#include "stdafx.h"
#include "CppUnitTest.h"
#include <SDL.h>
#include <Library.h>
#include <Vector4U8.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SDLClassesTests
{

	TEST_CLASS(LibraryTest)
	{
	public:
		TEST_METHOD(LoadObjectAndDoFunction)
		{
			SDL::SDL sdl;
			SDL::Library lib("SDL2.dll");
			auto f = lib.LoadFunction<int()>("SDL_GetCPUCount");
			int cpuCount = f();
			Assert::IsTrue(cpuCount > 0);
		}

	};
}