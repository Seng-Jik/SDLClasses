#pragma once
#include <functional>
#include <utility>
#include <exception>
#include <typeinfo>
#include <typeindex>

namespace SDL
{
	class Handler final
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

#ifdef _DEBUG
		std::type_index typeInfo_;
#endif
	};

	template<typename T>
	Handler::Handler(T * ptr, Deleter deleter) :
		ptr_(ptr),
		deleter_(deleter)
#ifdef _DEBUG
		,typeInfo_(typeid(T*))
#endif
	{
	}

	template<typename T>
	Handler::operator T() const
	{
#ifdef _DEBUG
		if (std::type_index(typeid(T)) != typeInfo_)
			throw std::bad_cast();
#endif
		return static_cast<T>(ptr_);
	}
}


