#pragma once

#include "Vector2D.h"
#include "Core/Aliases.h"

namespace Shoko
{
    struct FGeometry
    {
        FLocation Location;
        FSize Size;

        constexpr FGeometry()                                                      : Location(0, 0), Size(100, 100) {}
        constexpr FGeometry(FLocation InLocation, uint16 InWidth, uint16 InHeight) : Location(InLocation), Size(InWidth, InHeight) {}
        constexpr FGeometry(int16 InX, int16 InY, FSize InSize)                    : Location(InX, InY), Size(InSize) {}
        constexpr FGeometry(FLocation InLocation, FSize InSize)                    : Location(InLocation), Size(InSize) {}
        constexpr FGeometry(int16 InX, int16 InY, uint16 InWidth, uint16 InHeight) : Location(InX, InY), Size(InWidth, InHeight) {}
        
        constexpr int16 Right()  const { return static_cast<int16>(Location.X + Size.X); }
        constexpr int16 Bottom() const { return static_cast<int16>(Location.Y + Size.Y); }
        
        constexpr bool Contains(FIntVector2D Point) const { return Point.X >= Location.X && Point.X < Right() && Point.Y >= Location.Y && Point.Y < Bottom(); }
    };
}
