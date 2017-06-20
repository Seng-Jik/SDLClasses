#pragma once
#include <functional>
namespace SDL
{
	using std::function;

	template<typename T>
	class Property
	{
	public:
		Property() = default;
		Property(const T&);
		
		Property(const Property<T>&) = delete;
		Property(Property<T>&&) = delete;
		const Property<T>& operator = (const Property<T>&) = delete;
		const Property<T>& operator = (Property<T>&&) = delete;

		T& Get();
		operator T&();

		void Set(const T&);
		void Set(T&&);
		const T& operator = (const T&);
		const T& operator = (T&&);

	private:
		T value_;
	};

	template<typename T>
	class PropertyGetOnly
	{
	public:
		PropertyGetOnly(T&);
		PropertyGetOnly(const function<T&()>& getter);

		PropertyGetOnly(const PropertyGetOnly<T>&) = delete;
		PropertyGetOnly(PropertyGetOnly<T>&&) = delete;
		const PropertyGetOnly<T>& operator = (const PropertyGetOnly<T>&) = delete;
		const PropertyGetOnly<T>& operator = (PropertyGetOnly<T>&&) = delete;

		T& Get();
		operator T&();
	private:
		function<T&()> getter_;
	};

	template<typename T>
	class PropertySetOnly
	{
	public:
		PropertySetOnly(T&);
		PropertySetOnly(function<void(const T&)> copySetter);
		PropertySetOnly(function<void(const T&)> copySetter, function<void(T&&)> moveSetter);

		PropertySetOnly(const PropertySetOnly<T>&) = delete;
		PropertySetOnly(PropertySetOnly<T>&&) = delete;
		const PropertySetOnly<T>& operator = (const PropertySetOnly<T>&) = delete;
		const PropertySetOnly<T>& operator = (PropertySetOnly<T>&&) = delete;

		void Set(const T&);
		void Set(T&&);
		const T& operator = (const T&);
		const T& operator = (T&&);
	private:
		function<void(const T&)> copySetter_;
		function<void(T&&)> moveSetter_;
	};

	template<typename T>
	class PropertyGetSet:
		public PropertyGetOnly<T>,
		public PropertySetOnly<T>
	{
	public:
		PropertyGetSet(T&);
		PropertyGetSet(const function<T&()>& getter, function<void(const T&)> copySetter);
		PropertyGetSet(const function<T&()>& getter, function<void(const T&)> copySetter, function<void(T&&)> moveSetter);

		PropertyGetSet(const PropertyGetSet<T>&) = delete;
		PropertyGetSet(PropertyGetSet<T>&&) = delete;
		const PropertyGetSet<T>& operator = (const PropertyGetSet<T>&) = delete;
		const PropertyGetSet<T>& operator = (PropertyGetSet<T>&&) = delete;

		using PropertySetOnly<T>::operator=;
	};

	
	/* Propterty */
	template<typename T>
	inline Property<T>::Property(const T & value)
	{
		Set(value);
	}

	template<typename T>
	inline Property<T>::operator T&()
	{
		return Get();
	}

	template<typename T>
	inline void Property<T>::Set(const T & value)
	{
		value_ = value;
	}

	template<typename T>
	inline void Property<T>::Set(T && value)
	{
		value_ = value;
	}

	template<typename T>
	inline T & Property<T>::Get()
	{
		return value_;
	}

	template<typename T>
	inline const T& Property<T>::operator = (const T& value)
	{
		Set(value);
		return Get();
	}

	template<typename T>
	inline const T& Property<T>::operator = (T&& value)
	{
		Set(value);
		return Get();
	}

	/* Property Get Only */

	template<typename T>
	inline PropertyGetOnly<T>::PropertyGetOnly(T & value)
		:PropertyGetOnly([&value]() -> T& { return value; })
	{
	}

	template<typename T>
	inline PropertyGetOnly<T>::PropertyGetOnly(const function<T&()>& getter)
	{
		getter_ = getter;
	}

	template<typename T>
	inline T & PropertyGetOnly<T>::Get()
	{
		return getter_();
	}
	template<typename T>
	inline PropertyGetOnly<T>::operator T&()
	{
		return Get();
	}

	/* Property Set Only */
	template<typename T>
	inline PropertySetOnly<T>::PropertySetOnly(T & ref)
		:PropertySetOnly([&ref](const T& value) -> void { ref = value; })
	{
	}

	template<typename T>
	inline PropertySetOnly<T>::PropertySetOnly(function<void(const T&)> copySetter)
		:PropertySetOnly(copySetter, [this](T&& t) { copySetter_(t); })
	{
	}

	template<typename T>
	inline PropertySetOnly<T>::PropertySetOnly(function<void(const T&)> copySetter, function<void(T&&)> moveSetter)
	{
		copySetter_ = copySetter;
		moveSetter_ = moveSetter;
	}

	template<typename T>
	inline void PropertySetOnly<T>::Set(const T & value)
	{
		copySetter_(value);
	}

	template<typename T>
	inline void PropertySetOnly<T>::Set(T && value)
	{
		moveSetter_(value);
	}

	template<typename T>
	inline const T & SDL::PropertySetOnly<T>::operator=(const T & value)
	{
		Set(value);
		return value;
	}

	template<typename T>
	inline const T & SDL::PropertySetOnly<T>::operator=(T && value)
	{
		Set(value);
		return value;
	}

	/* Property Get Set */

	template<typename T>
	inline PropertyGetSet<T>::PropertyGetSet(T & ref)
		:PropertyGetOnly(ref), PropertySetOnly(ref)
	{
	}

	template<typename T>
	inline PropertyGetSet<T>::PropertyGetSet(const function<T&()>& getter, function<void(const T&)> copySetter)
		: PropertyGetOnly(getter), PropertySetOnly(copySetter)
	{
	}

	template<typename T>
	inline PropertyGetSet<T>::PropertyGetSet(const function<T&()>& getter, function<void(const T&)> copySetter, function<void(T&&)> moveSetter)
		: PropertyGetOnly(getter), PropertySetOnly(copySetter,moveSetter)
	{
	}
}
