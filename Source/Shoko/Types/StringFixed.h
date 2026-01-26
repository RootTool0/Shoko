#pragma once

#include "Core/Aliases.h"

#include <ostream>

namespace Shoko
{
    template<uint16 Capacity>
    class TStringFixed
    {
        
    public:
        constexpr TStringFixed() : Buffer{}, Length(0) {}
        
        template<uint16 N>
        constexpr TStringFixed(const char (&InStr)[N]) : Buffer{}, Length(0)
        {
            const uint16 InLen = (N > 0) ? N - 1 : 0;
            Length = (InLen < Capacity) ? InLen : Capacity - 1;
            for (uint16 i = 0; i < Length; ++i)
                Buffer[i] = InStr[i];
            Buffer[Length] = '\0';
        }

        TStringFixed& operator=(const char* InStr)
        {
            uint16 i = 0;
            while(i < Capacity - 1 && InStr[i] != '\0') {
                Buffer[i] = InStr[i];
                ++i;
            }
            Buffer[i] = '\0';
            Length = i;
            return *this;
        }

        TStringFixed& operator+=(const char* InStr)
        {
            if(!InStr) return *this;

            while(Length < Capacity - 1 && *InStr != '\0')
            {
                Buffer[Length] = *InStr;
                ++Length;
                ++InStr;
            }
    
            Buffer[Length] = '\0';
    
            return *this;
        }

        TStringFixed& operator+=(char InChar)
        {
            if(Length < Capacity - 1)
            {
                Buffer[Length] = InChar;
                ++Length;
                Buffer[Length] = '\0';
            }
            return *this;
        }
        
        friend std::ostream& operator<<(std::ostream& os, const TStringFixed& Str)
        {
            os << Str.GetData();
            return os;
        }
        
        constexpr const char* GetData() const { return Buffer; }
        constexpr uint16 Len() const { return Length; }
        
        constexpr void Empty() { Buffer[0] = '\0'; Length = 0; }
        constexpr bool IsEmpty() const { return Length == 0; }
        
    private:
        char Buffer[Capacity];
        uint16 Length;
    };
}
