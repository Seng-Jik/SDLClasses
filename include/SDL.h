#pragma once
#include <cstdint>
#include <functional>
#include <string>

namespace SDL
{
	using std::string;
	template<typename T> struct Vector3;
	struct MouseState;

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
		Vector3<uint8_t> GetVersion() const;

		void ProcessEvents();
		bool KeyPressed(const string&) const;
		MouseState GetMouseState() const;
		bool QuitRequested() const;

		uint64_t GetTicks() const;
		uint64_t GetPerformanceFrequency() const;
		uint64_t GetPerformanceCounter() const;
		void SetMouseCursorShow(bool);
		void Delay(uint32_t) const;
		void EnableScreenSaver(bool);

	private:
	};
}
