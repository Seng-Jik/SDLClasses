#pragma once

namespace SDL {
	class GLContext final
	{
	public:
		GLContext() = delete;
		GLContext(const GLContext&) = delete;
		GLContext(GLContext&&) = delete;
		GLContext& operator = (GLContext&&) = delete;
		GLContext& operator = (const GLContext&) = delete;
		~GLContext();
	private:
		friend class Window;
		GLContext(void* windowHandler);
		void* contextHandler_;
	};
}
