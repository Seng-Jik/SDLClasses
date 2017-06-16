#include "..\include\Surface.h"
#include "..\include\Vector2S32.h"
#include "..\include\Vector4S32.h"
#include "..\include\SDLError.h"
#include "..\include\Vector4U8.h"
#include <SDL.h>
#include "..\include\Guard.h"
SDL::Surface::Surface(std::any&& surfaceStruct, bool destoryByClass)
{
	surfaceHandle_ = surfaceStruct;
	if (!Available()) throw SDLError();
	destoryByClass_ = destoryByClass;
}

SDL::Surface::Surface(const char * bmpFile)
{
	surfaceHandle_ = SDL_LoadBMP(bmpFile);
	if (!Available()) throw SDLError();
	destoryByClass_ = true;
}

SDL::Surface::Surface(void * bmpFileInMemory, size_t size)
{
	auto rw = SDL_RWFromConstMem(bmpFileInMemory, size);
	if(rw == nullptr) throw SDLError();
	surfaceHandle_ = SDL_LoadBMP_RW(rw,size);
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

SDL::Surface::Surface(Surface && other)
{
	*this=(std::move(other));
}

SDL::Surface::~Surface()
{
	clear();
}

SDL::Surface & SDL::Surface::operator=(Surface && other)
{
	clear();
	destoryByClass_ = other.destoryByClass_;
	surfaceHandle_ = other.surfaceHandle_;
	other.destoryByClass_ = false;
	other.surfaceHandle_.reset();
	return *this;
}

bool SDL::Surface::Available() 
{ 
	if (surfaceHandle_.has_value())
		return std::any_cast<SDL_Surface*>(surfaceHandle_) != nullptr;
	return false;
}

void SDL::Surface::SaveBMP(const std::string & file)
{
	SDL_SaveBMP(std::any_cast<SDL_Surface*>(surfaceHandle_),file.c_str());
}

void SDL::Surface::Shade(std::function<ColorU8(int x, int y, Surface&thisSurface,ColorU8 nowColor)> f)
{
	auto sur = std::any_cast<SDL_Surface*>(surfaceHandle_);
	const bool lock = SDL_MUSTLOCK(sur);

	if (lock) SDL_LockSurface(sur);
	Guard g([sur,lock]() {if (lock) SDL_UnlockSurface(sur); });

	for (int y = 0; y < sur->h; ++y) {
		for (int x = 0; x < sur->w; ++x) {
			auto px = static_cast<Uint8*>(sur->pixels);
			px += sur->pitch * y;
			px += sur->format->BytesPerPixel * x;
			auto pxUint32 = reinterpret_cast<Uint32*>(px);

			ColorU8 oldCol;
			SDL_GetRGBA(*pxUint32, sur->format, &oldCol.r, &oldCol.g, &oldCol.b, &oldCol.a);

			auto newCol = f(x, y, *this, oldCol);
			*pxUint32 = SDL_MapRGBA(sur->format, newCol.r, newCol.g, newCol.b, newCol.a);
		}
	}
}

void SDL::Surface::Fill(const Rect & rect, ColorU8 col)
{
	auto frect = reinterpret_cast<const SDL_Rect&>(rect);
	auto color = SDL_MapRGBA(
		std::any_cast<SDL_Surface*>(surfaceHandle_)->format,
		col.r,
		col.g,
		col.b,
		col.a);

	SDL_FillRect(std::any_cast<SDL_Surface*>(surfaceHandle_), &frect, color);
}

void SDL::Surface::Fill(const std::vector<Rect>& rectSet, ColorU8 col)
{
	auto rects = reinterpret_cast<const SDL_Rect*>(rectSet.data());
	auto color = SDL_MapRGBA(
		std::any_cast<SDL_Surface*>(surfaceHandle_)->format,
		col.r,
		col.g,
		col.b,
		col.a);

	SDL_FillRects(std::any_cast<SDL_Surface*>(surfaceHandle_), rects, rectSet.size(), color);
}

void SDL::Surface::Clear(ColorU8 col)
{
	auto color = SDL_MapRGBA(
		std::any_cast<SDL_Surface*>(surfaceHandle_)->format,
		col.r,
		col.g,
		col.b,
		col.a);

	SDL_FillRect(std::any_cast<SDL_Surface*>(surfaceHandle_), nullptr, color);
}

void SDL::Surface::SetRLE(bool b)
{
	SDL_SetSurfaceRLE(std::any_cast<SDL_Surface*>(surfaceHandle_),b);
}

void SDL::Surface::BlitFrom(const Surface & from, const Rect & fromRect, const Rect & toRect)
{
	auto srcRect = reinterpret_cast<const SDL_Rect&>(fromRect);
	auto dstRect = reinterpret_cast<const SDL_Rect&>(toRect);
	SDL_BlitSurface(std::any_cast<SDL_Surface*>(from.surfaceHandle_), &srcRect, std::any_cast<SDL_Surface*>(surfaceHandle_), &dstRect);
}

SDL::Vector2S32 SDL::Surface::GetSize()
{
	auto sur = std::any_cast<SDL_Surface*>(surfaceHandle_);
	return Vector2S32{sur->w,sur->h};
}

void SDL::Surface::clear()
{
	if (destoryByClass_)
		SDL_FreeSurface(std::any_cast<SDL_Surface*>(surfaceHandle_));
	surfaceHandle_.reset();
	destoryByClass_ = false;
}
