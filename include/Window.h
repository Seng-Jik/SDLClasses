#pragma once
#include <string>
#include "Vector4S32.h"
#include "Surface.h"

namespace SDL
{
	using std::string;

	class Window
	{
	public:

		enum class WindowFlag : uint32_t
		{
			Null = 0,
			FullScreen = 0x00000001,
			FullScreenDesktop = FullScreen | 0x00001000,
			OpenGL = 0x00000002
		};

		static const int32_t Center = -1;

		Window(const string& title,Rect rectangle, WindowFlag);
		Window(const Window&) = delete;
		Window(Window&&) = delete;
		~Window();
		Window& operator = (Window&&) = delete;
		Window& operator = (const Window&) = delete;

		void UpdateWindowSurface() const;
		inline Surface& GetWindowSurface() { return windowSurface_; }

		void ShowSimpleMessageBox(const string& title, const string& msg) const;
	private:
		void* windowHandler_;
		Surface windowSurface_;
	};
}

