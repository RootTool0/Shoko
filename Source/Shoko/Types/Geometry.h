#pragma once

#include "Vector2D.h"
#include "../Core/Aliases.h"

namespace Shoko
{
    struct FGeometry
    {
        FIntVector2D Location;
        FUIntVector2D Size;

        constexpr FGeometry()                                                         : Location(0, 0), Size(100, 100) {}
        constexpr FGeometry(FIntVector2D InLocation, uint16 InWidth, uint16 InHeight) : Location(InLocation), Size(InWidth, InHeight) {}
        constexpr FGeometry(int16 InX, int16 InY, FUIntVector2D InSize)               : Location(InX, InY), Size(InSize) {}
        constexpr FGeometry(FIntVector2D InLocation, FUIntVector2D InSize)            : Location(InLocation), Size(InSize) {}
        constexpr FGeometry(int16 InX, int16 InY, uint16 InWidth, uint16 InHeight)    : Location(InX, InY), Size(InWidth, InHeight) {}
        
        constexpr int16 Right()  const { return static_cast<int16>(Location.X + Size.X); }
        constexpr int16 Bottom() const { return static_cast<int16>(Location.Y + Size.Y); }
        
        constexpr bool Contains(FIntVector2D Point) const { return Point.X >= Location.X && Point.Y < Right() && Point.Y >= Location.Y && Point.Y < Bottom(); }
    };
}
