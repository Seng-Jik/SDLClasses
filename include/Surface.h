#pragma once
#include <functional>
#include <vector>

namespace SDL
{
	struct Vector4U8;
	struct Vector4S32;
	struct ColorU8;
	struct Rect;
	struct Vector2S32;

	class Surface
	{
	public:
		Surface(void* surfaceStruct,bool destoryByClass);
		Surface(const char* bmpFile);
		Surface(void* bmpFileInMemory,size_t size);
		Surface(int width, int height, int depth, int pitch, uint32_t Rm, uint32_t Gm, uint32_t Bm, uint32_t Am);
		Surface(const Surface&) = delete;
		Surface(Surface&&);
		~Surface();
		Surface& operator = (Surface&&);
		Surface& operator = (const Surface&) = delete;

		inline bool Available() { return surfaceHandle_ != nullptr; }

		void Shade(std::function<ColorU8(int x,int y,Surface& thisSurface,ColorU8 nowColor)>);
		void Fill(const Rect&, ColorU8);
		void Fill(const std::vector<Rect>&, ColorU8);
		void Clear(ColorU8);
		void SetRLE(bool);
		void BlitFrom(const Surface& from, const Rect& fromRect, const Rect& toRect);
		Vector2S32 GetSize();
	private:
		void clear();
		void* surfaceHandle_;
		bool destoryByClass_;
	};
}
