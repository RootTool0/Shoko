#pragma once

namespace Shoko
{
    class FShokoNonePlatformWindow
    {
    public:
	    static bool Initialize() { return true; }
	    static void Deinitialize() {}

	    static void SetTitle(const char* NewTitle) {}
	    static void SetSize(FUIntVector2D Size) {}
    };
    
    using FShokoPlatformWindow = FShokoNonePlatformWindow;
}
