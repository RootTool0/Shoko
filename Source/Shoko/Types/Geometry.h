#pragma once

#include "Vector2D.h"
#include "Core/Aliases.h"

namespace Shoko
{
    struct FGeometry
    {
        FLocation Location = FLocation(100, 100);
        FSize Size = FSize(100, 100);

        constexpr FGeometry()                                                      : Location(0, 0), Size(100, 100) {}
        constexpr FGeometry(FLocation InLocation, uint16 InWidth, uint16 InHeight) : Location(InLocation), Size(InWidth, InHeight) {}
        constexpr FGeometry(int16 InX, int16 InY, FSize InSize)                    : Location(InX, InY), Size(InSize) {}
        constexpr FGeometry(FLocation InLocation, FSize InSize)                    : Location(InLocation), Size(InSize) {}
        constexpr FGeometry(int16 InX, int16 InY, uint16 InWidth, uint16 InHeight) : Location(InX, InY), Size(InWidth, InHeight) {}
        
        constexpr int16 Left()   const { return static_cast<int16>(Location.X);          }
        constexpr int16 Right()  const { return static_cast<int16>(Location.X + Size.X); }
        constexpr int16 Top()    const { return static_cast<int16>(Location.Y);          }
        constexpr int16 Bottom() const { return static_cast<int16>(Location.Y + Size.Y); }
        
        constexpr int16 X()       const { return Location.X; }
        constexpr int16 Y()       const { return Location.Y; }
        constexpr uint16 Width()  const { return Size.X; }
        constexpr uint16 Height() const { return Size.Y; }

        constexpr bool Contains(FLocation InLocation) const { return InLocation.X >= Location.X && InLocation.X < Right() && InLocation.Y >= Location.Y && InLocation.Y < Bottom(); }

        constexpr void CenterByParent(const FGeometry& Parent)
        {
            Location.X = static_cast<int16>(Parent.X() + (Parent.Width()  - Width() ) / 2);
            Location.Y = static_cast<int16>(Parent.Y() + (Parent.Height() - Height()) / 2);
        }
        
        constexpr void PaddingByParent(const FGeometry& Parent, FPadding Padding)
        {
            Location.X = static_cast<int16>(Parent.Location.X + Padding.X);
            Location.Y = static_cast<int16>(Parent.Location.Y + Padding.Y);
            
            Size.X = Parent.Size.X - Padding.X * 2;
            Size.Y = Parent.Size.Y - Padding.Y * 2;
        }
    };
}
