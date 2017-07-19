#pragma once
#include "MouseState.h"

namespace SDL
{
	class Mouse final
	{
	public:
		MouseState GetMouseState() const;
		void SetMouseCursorShow(bool);
	};
}