#pragma once
#include "Vector2.h"

namespace SDL
{
	struct MouseState
	{
		Vector2<int32_t> position;
		bool leftButton, rightButton, middleButton;
	};
}