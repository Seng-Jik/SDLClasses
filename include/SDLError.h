#pragma once
#include <exception>
#include <string>

namespace SDL 
{
	class SDLError :
		public std::exception
	{
	public:
		const char* what() const override;
		const std::string What() const;
	};
}
