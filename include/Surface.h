#pragma once
#include <functional>
#include <vector>
#include <string>
#include "RWops.h"

namespace SDL
{
	template<typename T> struct Vector4;
	template<typename T> struct Color;
	template<typename T> struct Rect;
	template<typename T> struct Vector2;

	class Surface final
	{
	public:
		Surface(void* ptrSDL_Surface, bool autoDestoryByClass);
		Surface(const std::string& bmpFile);
		Surface(RWops& rw,int size);
		Surface(int width, int height, int depth, int pitch, uint32_t Rm, uint32_t Gm, uint32_t Bm, uint32_t Am);
		Surface(const Surface&) = delete;
		Surface(Surface&&);
		~Surface();
		Surface& operator = (Surface&&);
		Surface& operator = (const Surface&) = delete;

		bool Available() const;
		void SaveBMP(const std::string& file) const;

		void Shade(std::function<Color<uint8_t>(int x, int y, Surface& thisSurface, Color<uint8_t> nowColor)>);
		void Fill(const Rect<int32_t>&, Color<uint8_t>);
		void Fill(const std::vector<Rect<int32_t>>&, Color<uint8_t>);
		void Clear(Color<uint8_t>);
		void SetRLE(bool);
		void BlitFrom(const Surface& from, const Rect<int32_t>& fromRect, const Rect<int32_t>& toRect);
		Vector2<int32_t> GetSize();

		const void* GetPtrToSDL_Surface() const;
	private:
		
		void clear();
		void* surfaceHandle_;
		bool destoryByClass_;
	};
}
