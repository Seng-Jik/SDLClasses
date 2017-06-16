#pragma once
#include "Vector2S32.h"

namespace SDL
{
	struct MouseState
	{
		Vector2S32 position;
		bool leftButton, rightButton, middleButton;
	};
}