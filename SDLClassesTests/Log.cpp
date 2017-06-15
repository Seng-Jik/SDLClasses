#include "stdafx.h"
#include <fstream>
#include <Windows.h>  
#include <tchar.h>  
#include <deque>
#include <CppUnitTestLogger.h>

static Microsoft::VisualStudio::CppUnitTestFramework::Logger logger;
void Log(const char* format, ...)
{
	static char buf[65536];
	va_list args;
	va_start(args, format);
	_vsnprintf_s(buf, sizeof(buf) - 1, format, args);
	va_end(args);

	logger.WriteMessage(buf);
}
