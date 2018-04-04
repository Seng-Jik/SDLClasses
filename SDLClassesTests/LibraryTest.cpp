#include "stdafx.h"
#include "CppUnitTest.h"
#include <SDLInstance.h>
#include <Library.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SDLClassesTests
{

	TEST_CLASS(LibraryTest)
	{
	public:
		TEST_METHOD(LoadObjectAndDoFunction)
		{
			SDL::SDLInstance sdl;
			SDL::Library lib("SDL2.dll");
			auto f = lib.LoadFunction<int()>("SDL_GetCPUCount");
			int cpuCount = f();
			Assert::IsTrue(cpuCount > 0);
		}

	};
}