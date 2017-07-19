#pragma once
#include <string>
#include <cstdint>

namespace SDL
{
	using std::string;

	class RWops final
	{
		friend class Surface;
	public:
		RWops(void* mem, int size);
		RWops(const void* mem, int size);
		RWops(const string& filePath, const string& mode);
		~RWops();

		RWops(const RWops&) = delete;
		RWops(RWops&&);
		RWops& operator = (RWops&&) = delete;
		RWops& operator = (const RWops&) = delete;

		bool Available() const;
		
		size_t Read(void* ptr, size_t size, size_t maxnum);
		size_t Write(const void* ptr, size_t size, size_t num);
		int64_t Tell();
	private:
		void* rwopsHandle_;
	};
}