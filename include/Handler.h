#pragma once
#include <functional>
#include <utility>

namespace SDL
{
	class Handler
	{
	public:
		using Deleter = std::function<void(void* ptr)>;

		const Handler& operator = (Handler&&);
		Handler(void* ptr, Deleter deleter);
		Handler(Handler&& r);
		~Handler();

		void* Get() const;
	private:
		void* ptr_;
		Deleter deleter_;
	};
}