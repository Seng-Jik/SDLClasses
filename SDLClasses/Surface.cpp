#include "..\include\Surface.h"
#include "..\include\Vector2.h"
#include "..\include\Vector4.h"
#include "..\include\SDLError.h"
#include <SDL_surface.h>
#include "..\include\Guard.h"

static void surDeleter(SDL_Surface* sur)
{
	SDL_FreeSurface(sur);
};


SDL::Surface::Surface(const std::string& bmpFile):
	surfaceHandle_(SDL_LoadBMP(bmpFile.c_str()),surDeleter)
{
	if (!Available()) throw SDLError();
}

SDL::Surface::Surface(RWops & rw,int size):
	surfaceHandle_(SDL_LoadBMP_RW(rw.GetPtrToSDL_RWops(), size), surDeleter)
{
	if (!Available()) throw SDLError();
}

SDL::Surface::Surface(int width, int height, int depth, uint32_t Rm, uint32_t Gm, uint32_t Bm, uint32_t Am):
	surfaceHandle_(SDL_CreateRGBSurface(0, width, height, depth, Rm, Gm, Bm, Am), surDeleter)
{
	if (!Available()) throw SDLError();
}

bool SDL::Surface::Available() const
{
	return static_cast<SDL_Surface*>(surfaceHandle_) != nullptr;
}

void SDL::Surface::SaveBMP(const std::string & file) const
{
	SDL_SaveBMP(surfaceHandle_, file.c_str());
}

void SDL::Surface::SaveBMP(RWops & rw,int freedst) const
{
	SDL_SaveBMP_RW(surfaceHandle_, rw, freedst);
}

void SDL::Surface::Shade(
	std::function<Color<uint8_t>(int x, int y, Surface&thisSurface, 
		Color<uint8_t> nowColor)> f
)
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

	SDL_FillRect(surfaceHandle_, &frect, color);
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

	SDL_FillRects(surfaceHandle_, rects, static_cast<int>(rectSet.size()), color);
}

void SDL::Surface::Clear(Color<uint8_t> col)
{
	auto color = SDL_MapRGBA(
		static_cast<SDL_Surface*>(surfaceHandle_)->format,
		col.r,
		col.g,
		col.b,
		col.a);

	SDL_FillRect(surfaceHandle_, nullptr, color);
}

void SDL::Surface::SetRLE(bool b)
{
	SDL_SetSurfaceRLE(surfaceHandle_, b);
}

void SDL::Surface::BlitFrom(
	const Surface & from, 
	const Rect<int32_t> & fromRect,
	const Rect<int32_t> & toRect
)
{
	auto srcRect = reinterpret_cast<const SDL_Rect&>(fromRect);
	auto dstRect = reinterpret_cast<const SDL_Rect&>(toRect);
	SDL_BlitSurface(from.surfaceHandle_, &srcRect, surfaceHandle_, &dstRect);
}

SDL::Vector2<int32_t> SDL::Surface::GetSize()
{
	auto sur = static_cast<SDL_Surface*>(surfaceHandle_);
	return Vector2<int32_t>{sur->w, sur->h};
}

const SDL::Handler& SDL::Surface::GetPtrToSDL_Surface() const
{
	return surfaceHandle_;
}

SDL::Surface::Surface(void * sur, bool des):
	surfaceHandle_(static_cast<SDL_Surface*>(sur), des ? surDeleter : [](SDL_Surface*) {})
{
}
