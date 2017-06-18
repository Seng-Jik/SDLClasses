#pragma once
#include <string>
#include <any>
#include "Surface.h"

namespace SDL
{
	using std::string;

	template<typename T> struct Vector4;
	class GLContext;

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

		Window(const string& title,Rect<int32_t> rectangle, WindowFlag);
		Window(const Window&) = delete;
		Window(Window&&) = delete;
		~Window();
		Window& operator = (Window&&) = delete;
		Window& operator = (const Window&) = delete;

		void UpdateWindowSurface() const;
		inline Surface& GetWindowSurface() { return windowSurface_; }

		void ShowSimpleMessageBox(const string& title, const string& msg) const;

		GLContext CreateOpenGLContext();
	private:
		std::any windowHandler_;
		Surface windowSurface_;
	};
}

