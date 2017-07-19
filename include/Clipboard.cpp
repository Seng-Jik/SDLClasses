#include "Clipboard.h"
#include "SDLError.h"
#include <SDL.h>
std::string SDL::Clipboard::GetText()
{
	char* text = SDL_GetClipboardText();
	if (text == nullptr) throw SDLError();
	string ret(text);
	SDL_free(text);
	return ret;
}

bool SDL::Clipboard::HasText()
{
	return SDL_HasClipboardText();
}

void SDL::Clipboard::SetText(const string & text)
{
	if (SDL_SetClipboardText(text.c_str())) throw SDLError();
}
