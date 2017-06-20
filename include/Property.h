#pragma once

#include <functional>

namespace SDL
{
	using std::function;

	template<typename T>
	class Auto
	{
	public:
		Auto() = default;
		Auto(const T&);
		Auto(T&&);

		Auto(const Auto<T>&) = delete;
		Auto(Auto<T>&&) = delete;
		const Auto<T>& operator = (const Auto<T>&) = delete;
		const Auto<T>& operator = (Auto<T>&&) = delete;

		T& GetValue();
		operator T&();

		void SetValue(const T&);
		void SetValue(T&&);
		const T& operator = (const T&);
		const T& operator = (T&&);

	private:
		T value_;
	};

	template<typename T>
	class Get
	{
	public:
		Get(T&);
		Get(const function<T&()>& getter);

		Get(const Get<T>&) = delete;
		Get(Get<T>&&) = delete;
		const Get<T>& operator = (const Get<T>&) = delete;
		const Get<T>& operator = (Get<T>&&) = delete;

		T& GetValue();
		operator T&();
	private:
		function<T&()> getter_;
	};

	template<typename T>
	class Set
	{
	public:
		Set(T&);
		Set(function<void(const T&)> copySetter);
		Set(function<void(const T&)> copySetter, function<void(T&&)> moveSetter);

		Set(const Set<T>&) = delete;
		Set(Set<T>&&) = delete;
		const Set<T>& operator = (const Set<T>&) = delete;
		const Set<T>& operator = (Set<T>&&) = delete;

		void SetValue(const T&);
		void SetValue(T&&);
		const T& operator = (const T&);
		const T& operator = (T&&);
	private:
		function<void(const T&)> copySetter_;
		function<void(T&&)> moveSetter_;
	};

	template<typename T>
	class GetSet :
		public Get<T>,
		public Set<T>
	{
	public:
		GetSet(T&);
		GetSet(const function<T&()>& getter, function<void(const T&)> copySetter);
		GetSet(const function<T&()>& getter, function<void(const T&)> copySetter, function<void(T&&)> moveSetter);

		GetSet(const GetSet<T>&) = delete;
		GetSet(GetSet<T>&&) = delete;
		const GetSet<T>& operator = (const GetSet<T>&) = delete;
		const GetSet<T>& operator = (GetSet<T>&&) = delete;

		using Set<T>::operator=;
	};


	/* Propterty */
	template<typename T>
	inline Auto<T>::Auto(const T & value)
	{
		SetValue(value);
	}

	template<typename T>
	inline Auto<T>::Auto(T && value)
	{
		SetValue(value);
	}

	template<typename T>
	inline Auto<T>::operator T&()
	{
		return GetValue();
	}

	template<typename T>
	inline void Auto<T>::SetValue(const T & value)
	{
		value_ = value;
	}

	template<typename T>
	inline void Auto<T>::SetValue(T && value)
	{
		value_ = value;
	}

	template<typename T>
	inline T & Auto<T>::GetValue()
	{
		return value_;
	}

	template<typename T>
	inline const T& Auto<T>::operator = (const T& value)
	{
		SetValue(value);
		return GetValue();
	}

	template<typename T>
	inline const T& Auto<T>::operator = (T&& value)
	{
		SetValue(value);
		return GetValue();
	}

	/* Property Get Only */

	template<typename T>
	inline Get<T>::Get(T & value)
		:Get([&value]() -> T& { return value; })
	{
	}

	template<typename T>
	inline Get<T>::Get(const function<T&()>& getter)
	{
		getter_ = getter;
	}

	template<typename T>
	inline T & Get<T>::GetValue()
	{
		return getter_();
	}
	template<typename T>
	inline Get<T>::operator T&()
	{
		return GetValue();
	}

	/* Property Set Only */
	template<typename T>
	inline Set<T>::Set(T & ref)
		:Set([&ref](const T& value) -> void { ref = value; })
	{
	}

	template<typename T>
	inline Set<T>::Set(function<void(const T&)> copySetter)
		: Set(copySetter, [this](T&& t) { copySetter_(t); })
	{
	}

	template<typename T>
	inline Set<T>::Set(function<void(const T&)> copySetter, function<void(T&&)> moveSetter)
	{
		copySetter_ = copySetter;
		moveSetter_ = moveSetter;
	}

	template<typename T>
	inline void Set<T>::SetValue(const T & value)
	{
		copySetter_(value);
	}

	template<typename T>
	inline void Set<T>::SetValue(T && value)
	{
		moveSetter_(value);
	}

	template<typename T>
	inline const T & Set<T>::operator=(const T & value)
	{
		SetValue(value);
		return value;
	}

	template<typename T>
	inline const T & Set<T>::operator=(T && value)
	{
		SetValue(value);
		return value;
	}

	/* Property Get Set */

	template<typename T>
	inline GetSet<T>::GetSet(T & ref)
		:Get(ref), Set(ref)
	{
	}

	template<typename T>
	inline GetSet<T>::GetSet(const function<T&()>& getter, function<void(const T&)> copySetter)
		: Get(getter), Set(copySetter)
	{
	}

	template<typename T>
	inline GetSet<T>::GetSet(const function<T&()>& getter, function<void(const T&)> copySetter, function<void(T&&)> moveSetter)
		: Get(getter), Set(copySetter, moveSetter)
	{
	}
}
