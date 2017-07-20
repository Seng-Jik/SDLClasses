#pragma once
#include "Handler.h"
// Comming soon
namespace SDL 
{
	struct AudioFormat
	{};

	struct AudioSpec
	{
		AudioFormat format;
		uint8_t channels;
	};

	class Audio
	{
	public:
		Audio();
		~Audio();

	private:
		Handler audioDevice_;
	};
}