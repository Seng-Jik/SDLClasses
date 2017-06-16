#pragma once
#include <cstdint>
#include <string>

namespace SDL 
{
	using std::string;
	struct Vector4U8;

	class SDL
	{
	public:
		
		enum class InitParam : uint32_t 
		{
			Timer = 0x00000001u,
			Audio = 0x00000010u,
			Video = 0x00000020u,
			Joystick = 0x00000200u,
			Haptic = 0x00001000u,
			GameController = 0x00002000u,
			Events = 0x00004000u,
			Everything = 
				Timer | Audio | Video | Joystick | Haptic | GameController | Events,
		};

		SDL(InitParam = InitParam::Everything);
		SDL(const SDL&) = delete;
		SDL(SDL&&) = delete;
		~SDL();
		SDL& operator = (SDL&&) = delete;
		SDL& operator = (const SDL&) = delete;

		void SetHint(const string& hint, const string& value);
		Vector4U8 GetVersion() const;

		static uint64_t GetTicks();
		static void Delay(uint32_t);
		static void EnableScreenSaver(bool);

	private:

	};
}
