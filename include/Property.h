#pragma once

#include <functional>
#include <type_traits>

namespace SDL
{
	using std::function;

	template<typename T>
	class Auto
	{
	public:
		Auto(T&& value...);

		T& GetVal();
		const T& GetConst() const;
		operator T&();
		operator const T&() const;

		void SetValue(T&&);
		void SetValue(const T&);
		const T& operator = (T&&);
		const T& operator = (const T&);
	private:
		T value_;

		Auto(const Auto&) = delete;
		Auto(Auto&&) = delete;
		const Auto& operator=(Auto&&) = delete;
		const Auto& operator=(const Auto&) = delete;
	};

	template<typename T>
	class Get
	{
	public:
		explicit Get(T& boundObject);
		Get(function<T&()>&& getter);

		T& GetVal();
		const T& GetConst() const;
		operator T&();
		operator const T&() const;
	private:
		function<T&()> getter_;

		Get(const Get&) = delete;
		Get(Get&&) = delete;
		const Get& operator=(Get&&) = delete;
		const Get& operator=(const Get&) = delete;
	};

	template<typename T>
	class Set
	{
	public:
		explicit Set(T& boundObject);
		Set(function<void(const T&)>&& setter);
		Set(function<void(const T&)>&& setter,function<void(T&&)>&& setterForMove);

		void SetValue(T&&);
		void SetValue(const T&);
		const T& operator=(T&&);
		const T& operator=(const T&);
	private:
		function<void(const T&)> copySetter_;
		function<void(T&&)> moveSetter_;

		Set(const Set&) = delete;
		Set(Set&&) = delete;
		const Set& operator=(Set&&) = delete;
		const Set& operator=(const Set&) = delete;
	};

	template<typename T>
	class GetSet:
		public Get<T>,
		public Set<T>
	{
		explicit GetSet(T& boundObject);
		GetSet(function<T&()>&& getter, function<void(const T&)>&& setter);
		GetSet(function<T&()>&& getter, function<void(const T&)>&& setter, function<void(T&&)>&& setterForMove);
	};


	/* Auto */

	template<typename T>
	inline Auto<T>::Auto(T && value...):
		value_(std::move(value))
	{
	}

	template<typename T>
	inline Auto<T>::operator T&()
	{
		return GetVal();
	}

	template<typename T>
	inline Auto<T>::operator const T&() const
	{
		return GetConst();
	}

	template<typename T>
	inline void Auto<T>::SetValue(T && value)
	{
		value_ = std::move(value);
	}

	template<typename T>
	inline T & Auto<T>::GetVal()
	{
		return value_;
	}

	template<typename T>
	inline const T & Auto<T>::GetConst() const
	{
		return value_;
	}

	template<typename T>
	inline const T& Auto<T>::operator = (T&& value)
	{
		SetValue(std::move(value));
		return GetVal();
	}

	template<typename T>
	inline const T& Auto<T>::operator = (const T& value)
	{
		SetValue(value);
		return GetVal();
	}

	template<typename T>
	inline void Auto<T>::SetValue(const T& value)
	{
		value_ = value;
	}

	/* Get */

	template<typename T>
	inline Get<T>::Get(T & boundObject)
		:Get([&boundObject]() -> T& { return boundObject; })
	{
	}

	template<typename T>
	inline Get<T>::Get(function<T&()>&& getter)
	{
		getter_ = getter;
	}

	template<typename T>
	inline T & Get<T>::GetVal()
	{
		return getter_();
	}

	template<typename T>
	inline const T & Get<T>::GetConst() const
	{
		return getter_();
	}
	template<typename T>
	inline Get<T>::operator T&()
	{
		return GetVal();
	}

	template<typename T>
	inline Get<T>::operator const T&() const
	{
		return GetConst();
	}

}
