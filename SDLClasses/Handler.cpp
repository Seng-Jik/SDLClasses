#include "..\include\Handler.h"

SDL::Handler::Handler(void * ptr, Deleter deleter):
	ptr_(ptr),
	deleter_(deleter)
{
}

SDL::Handler::Handler(Handler && r)
{
	*this = std::move(r);
}

SDL::Handler& SDL::Handler::operator=(Handler && r)
{
	ptr_ = r.ptr_;
	deleter_ = r.deleter_;

	r.ptr_ = nullptr;
	r.deleter_ = [](void*) {};

	return *this;
}

SDL::Handler::~Handler()
{
	deleter_(ptr_);
}

void * SDL::Handler::Get() const
{
	return ptr_;
}
