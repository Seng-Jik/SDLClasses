#pragma once
#include <functional>
#include <utility>
#include <exception>
#include <typeinfo>
#include <typeindex>

namespace SDL
{
	class Handler
	{
	public:
		using Deleter = std::function<void(Handler&)>;

		template<typename T>
		Handler(T* ptr, Deleter deleter);

		const Handler& operator = (Handler&&);
		Handler(Handler&& r);
		~Handler();

		template<typename T>
		operator T() const;
	private:
		void* ptr_;
		Deleter deleter_;

		std::type_index typeInfo_;
	};

	template<typename T>
	Handler::Handler(T * ptr, Deleter deleter) :
		ptr_(ptr),
		deleter_(deleter),
		typeInfo_(typeid(T*))
	{
	}

	template<typename T>
	Handler::operator T() const
	{
		auto p1 = typeid(T).name();
		auto p2 = typeInfo_.name();
		if (std::type_index(typeid(T)) != typeInfo_)
			throw std::bad_cast();
		return static_cast<T>(ptr_);
	}
}


