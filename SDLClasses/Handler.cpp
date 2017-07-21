#include "..\include\Handler.h"


SDL::Handler::Handler(Handler && r):
	typeInfo_(std::move(r.typeInfo_))
{
	*this = std::move(r);
}

const SDL::Handler& SDL::Handler::operator=(Handler && r)
{
	ptr_ = r.ptr_;
	deleter_ = r.deleter_;

	r.ptr_ = nullptr;
	r.deleter_ = [](void*) {};

	typeInfo_ = std::move(r.typeInfo_);

	return *this;
}

SDL::Handler::~Handler()
{
	deleter_(*this);
}
