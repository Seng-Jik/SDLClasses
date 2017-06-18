#pragma once
#include <functional>

namespace SDL
{
	class Guard
	{
	public:
		inline Guard(std::function<void()> unlock)
			:
			unlock_(unlock) 
		{}

		inline ~Guard()
		{
			unlock_();
		}

		Guard(const Guard&) = delete;
		Guard(Guard&&) = delete;
		Guard& operator = (Guard&&) = delete;
		Guard& operator = (const Guard&) = delete;

	private:
		std::function<void()> unlock_;
	};
}