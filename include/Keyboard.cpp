#include "Keyboard.h"
#include "SDLError.h"
#include <SDL.h>

const uint8_t * SDL::Keyboard::GetKeyboardState(int& keyCount) const
{
	auto p = SDL_GetKeyboardState(&keyCount);
	if (p == nullptr) throw SDLError();
	return p;
}

uint32_t SDL::Keyboard::GetKeyboardScancode(const string & keyName) const
{
	auto scanCode = SDL_GetScancodeFromName(keyName.c_str());
	if (scanCode == SDL_SCANCODE_UNKNOWN) throw std::exception(("Unknow key:" + keyName).c_str());
	return static_cast<uint32_t>(scanCode);
}

bool SDL::Keyboard::KeyPressed(uint32_t scanCode) const
{
	int numKeys;
	auto map = GetKeyboardState(numKeys);
	if (static_cast<unsigned>(numKeys) > scanCode) return map[scanCode] > 0;
	else throw std::exception("Unknown scancode.");
}

bool SDL::Keyboard::KeyPressed(const string & keyName) const
{
	return KeyPressed(GetKeyboardScancode(keyName));
}
