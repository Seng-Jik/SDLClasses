#pragma once
#include <cstdint>

namespace SDL
{
	struct Vector4S32
	{
		int32_t x, y, z, w;
	};

	struct Rect
	{
		int32_t x, y, w, h;
	};
}
