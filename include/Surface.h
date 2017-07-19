#pragma once
#include <functional>
#include <vector>
#include <string>

namespace SDL
{
	template<typename T> struct Vector4;
	template<typename T> struct Color;
	template<typename T> struct Rect;
	template<typename T> struct Vector2;

	class Surface final
	{
		friend class Window;
	public:
		Surface(const std::string& bmpFile);
		Surface(void* bmpFileInMemory, size_t size);
		Surface(int width, int height, int depth, int pitch, uint32_t Rm, uint32_t Gm, uint32_t Bm, uint32_t Am);
		Surface(const Surface&) = delete;
		Surface(Surface&&) = default;
		~Surface();
		Surface& operator = (Surface&&) = default;
		Surface& operator = (const Surface&) = delete;

		bool Available();
		void SaveBMP(const std::string& file);

		void Shade(std::function<Color<uint8_t>(int x, int y, Surface& thisSurface, Color<uint8_t> nowColor)>);
		void Fill(const Rect<int32_t>&, Color<uint8_t>);
		void Fill(const std::vector<Rect<int32_t>>&, Color<uint8_t>);
		void Clear(Color<uint8_t>);
		void SetRLE(bool);
		void BlitFrom(const Surface& from, const Rect<int32_t>& fromRect, const Rect<int32_t>& toRect);
		Vector2<int32_t> GetSize();
	private:
		Surface(void*,bool);
		void clear();
		void* surfaceHandle_;
		bool destoryByClass_;
	};
}
