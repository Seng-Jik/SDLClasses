#include "..\include\Surface.h"
#include "..\include\Vector2.h"
#include "..\include\Vector4.h"
#include "..\include\SDLError.h"
#include <SDL.h>
#include "..\include\Guard.h"

SDL::Surface::Surface(const std::string& bmpFile)
{
	surfaceHandle_ = SDL_LoadBMP(bmpFile.c_str());
	if (!Available()) throw SDLError();
	destoryByClass_ = true;
}

SDL::Surface::Surface(void * bmpFileInMemory, size_t size)
{
	auto rw = SDL_RWFromConstMem(bmpFileInMemory, static_cast<int>(size));
	if (rw == nullptr) throw SDLError();
	surfaceHandle_ = SDL_LoadBMP_RW(rw, static_cast<int>(size));
	if (!Available()) throw SDLError();
	destoryByClass_ = true;
	SDL_RWclose(rw);
}

SDL::Surface::Surface(int width, int height, int depth, int pitch, uint32_t Rm, uint32_t Gm, uint32_t Bm, uint32_t Am)
{
	surfaceHandle_ = SDL_CreateRGBSurface(0, width, height, depth, Rm, Gm, Bm, Am);
	if (!Available()) throw SDLError();
	destoryByClass_ = true;
}

SDL::Surface::~Surface()
{
	clear();
}

bool SDL::Surface::Available()
{
	return static_cast<SDL_Surface*>(surfaceHandle_) != nullptr;
}

void SDL::Surface::SaveBMP(const std::string & file)
{
	SDL_SaveBMP(static_cast<SDL_Surface*>(surfaceHandle_), file.c_str());
}

void SDL::Surface::Shade(std::function<Color<uint8_t>(int x, int y, Surface&thisSurface, Color<uint8_t> nowColor)> f)
{
	auto sur = static_cast<SDL_Surface*>(surfaceHandle_);
	const bool lock = SDL_MUSTLOCK(sur);

	if (lock) SDL_LockSurface(sur);
	Guard g([sur, lock]() {if (lock) SDL_UnlockSurface(sur); });

	for (int y = 0; y < sur->h; ++y) {
		for (int x = 0; x < sur->w; ++x) {
			auto px = static_cast<Uint8*>(sur->pixels);
			px += sur->pitch * y;
			px += sur->format->BytesPerPixel * x;
			auto pxUint32 = reinterpret_cast<Uint32*>(px);

			Color<uint8_t> oldCol;
			SDL_GetRGBA(*pxUint32, sur->format, &oldCol.r, &oldCol.g, &oldCol.b, &oldCol.a);

			auto newCol = f(x, y, *this, oldCol);
			*pxUint32 = SDL_MapRGBA(sur->format, newCol.r, newCol.g, newCol.b, newCol.a);
		}
	}
}

void SDL::Surface::Fill(const Rect<int32_t> & rect, Color<uint8_t> col)
{
	auto frect = reinterpret_cast<const SDL_Rect&>(rect);
	auto color = SDL_MapRGBA(
		static_cast<SDL_Surface*>(surfaceHandle_)->format,
		col.r,
		col.g,
		col.b,
		col.a);

	SDL_FillRect(static_cast<SDL_Surface*>(surfaceHandle_), &frect, color);
}

void SDL::Surface::Fill(const std::vector<Rect<int32_t>>& rectSet, Color<uint8_t> col)
{
	auto rects = reinterpret_cast<const SDL_Rect*>(rectSet.data());
	auto color = SDL_MapRGBA(
		static_cast<SDL_Surface*>(surfaceHandle_)->format,
		col.r,
		col.g,
		col.b,
		col.a);

	SDL_FillRects(static_cast<SDL_Surface*>(surfaceHandle_), rects, static_cast<int>(rectSet.size()), color);
}

void SDL::Surface::Clear(Color<uint8_t> col)
{
	auto color = SDL_MapRGBA(
		static_cast<SDL_Surface*>(surfaceHandle_)->format,
		col.r,
		col.g,
		col.b,
		col.a);

	SDL_FillRect(static_cast<SDL_Surface*>(surfaceHandle_), nullptr, color);
}

void SDL::Surface::SetRLE(bool b)
{
	SDL_SetSurfaceRLE(static_cast<SDL_Surface*>(surfaceHandle_), b);
}

void SDL::Surface::BlitFrom(const Surface & from, const Rect<int32_t> & fromRect, const Rect<int32_t> & toRect)
{
	auto srcRect = reinterpret_cast<const SDL_Rect&>(fromRect);
	auto dstRect = reinterpret_cast<const SDL_Rect&>(toRect);
	SDL_BlitSurface(static_cast<SDL_Surface*>(from.surfaceHandle_), &srcRect, static_cast<SDL_Surface*>(surfaceHandle_), &dstRect);
}

SDL::Vector2<int32_t> SDL::Surface::GetSize()
{
	auto sur = static_cast<SDL_Surface*>(surfaceHandle_);
	return Vector2<int32_t>{sur->w, sur->h};
}

SDL::Surface::Surface(void * sur, bool des)
{
	surfaceHandle_ = sur;
	destoryByClass_ = des;
}

void SDL::Surface::clear()
{
	if (destoryByClass_ && surfaceHandle_ != nullptr)
		SDL_FreeSurface(static_cast<SDL_Surface*>(surfaceHandle_));
	surfaceHandle_ = nullptr;
	destoryByClass_ = false;
}