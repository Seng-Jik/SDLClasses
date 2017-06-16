#pragma once
#include <any>

namespace SDL {
	class GLContext
	{
	public:
		GLContext() = delete;
		GLContext(const GLContext&) = delete;
		GLContext(GLContext&&) = default;
		GLContext& operator = (GLContext&&) = default;
		GLContext& operator = (const GLContext&) = delete;
		~GLContext();
	private:
		friend class Window;
		GLContext(std::any windowHandler);
		std::any contextHandler_;
	};
}

