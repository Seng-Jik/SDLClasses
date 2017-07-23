md SDLClasses_ReleasePack
md SDLClasses_ReleasePack\include
md SDLClasses_ReleasePack\lib
md SDLClasses_ReleasePack\lib\Win32Debug
md SDLClasses_ReleasePack\lib\x64Debug
md SDLClasses_ReleasePack\lib\Win32Release
md SDLClasses_ReleasePack\lib\x64Release

copy include\*.* SDLClasses_ReleasePack\include\*.*
copy SDLClasses\Release\SDLClasses.lib SDLClasses_ReleasePack\lib\Win32Release\SDLClasses.lib
copy SDLClasses\x64\Release\SDLClasses.lib SDLClasses_ReleasePack\lib\x64Release\SDLClasses.lib
copy SDLClasses\Debug\SDLClasses.lib SDLClasses_ReleasePack\lib\Win32Debug\SDLClasses.lib
copy SDLClasses\x64\Debug\SDLClasses.lib SDLClasses_ReleasePack\lib\x64Debug\SDLClasses.lib
copy LICENSE SDLClasses_ReleasePack\LICENSE

