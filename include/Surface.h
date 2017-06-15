#pragma once
#include "Vector4U8.h"
#include "Vector4S32.h"
#include <functional>
#include <vector>

namespace SDL
{
	class Surface
	{
	public:
		Surface(void* surfaceStruct,bool destoryByClass);
		Surface(const char* bmpFile);
		Surface(void* bmpFileInMemory,size_t size);
		Surface(int width, int height, int depth, int pitch, uint32_t Rm, uint32_t Gm, uint32_t Bm, uint32_t Am);
		Surface(const Surface&);
		Surface(Surface&&);
		~Surface();

		inline bool Available() { return surfaceHandle_ != nullptr; }

		void Shade(std::function<ColorU8(int x,int y,Surface& thisSurface,ColorU8 nowColor)>);
		void Fill(const Rect&, ColorU8);
		void Fill(const std::vector<Rect>&, ColorU8);
		void Clear(ColorU8);
		void SetRLE(bool);
		void BlitFrom(const Surface& from, const Rect& fromRect, const Rect& toRect);

	private:
		void* surfaceHandle_;
		bool destoryByClass_;
	};
}
