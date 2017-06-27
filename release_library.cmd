md SDLClasses_ReleasePack
md SDLClasses_ReleasePack\include
md SDLClasses_ReleasePack\lib
md SDLClasses_ReleasePack\lib\x86
md SDLClasses_ReleasePack\lib\x64

copy include\*.* SDLClasses_ReleasePack\include\*.*
copy SDLClasses\Release\SDLClasses.lib SDLClasses_ReleasePack\lib\x86\SDLClasses.lib
copy SDLClasses\x64\Release\SDLClasses.lib SDLClasses_ReleasePack\lib\x64\SDLClasses.lib
copy LICENSE SDLClasses_ReleasePack\LICENSE

