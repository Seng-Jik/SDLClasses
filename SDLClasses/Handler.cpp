#include "..\include\Handler.h"


SDL::Handler::Handler(Handler && r):
	typeInfo_(std::move(r.typeInfo_))
{
	deleter_ = std::move(r.deleter_);
	ptr_ = r.ptr_;
	r.ptr_ = nullptr;
}

const SDL::Handler& SDL::Handler::operator=(Handler && r)
{
	ptr_ = r.ptr_;
	deleter_ = std::move(r.deleter_);

	r.ptr_ = nullptr;

	typeInfo_ = std::move(r.typeInfo_);

	return *this;
}

SDL::Handler::~Handler()
{
	if(deleter_)
		deleter_(*this);
}
