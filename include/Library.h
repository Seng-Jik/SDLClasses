#pragma once
#include <functional>

namespace SDL
{
	class Library
	{
	private:
		void* loadFunction(const std::string& funcName) const;
	public:
		Library(const std::string& libName);
		Library(const Library&) = delete;
		Library(Library&&) = delete;
		~Library();
		Library& operator = (Library&&) = delete;
		Library& operator = (const Library&) = delete;

		template<class FuncType>
		std::function<FuncType> LoadFunction(const std::string& funcName) const
		{
			return static_cast<FuncType*>(loadFunction(funcName));
		}

	private:
		void* libraryHandle_;
	};
}
