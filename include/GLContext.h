#pragma once

namespace SDL {
	class GLContext final
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
		GLContext(void* windowHandler);
		void* contextHandler_;
	};
}
