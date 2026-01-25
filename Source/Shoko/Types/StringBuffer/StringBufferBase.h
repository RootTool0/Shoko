#pragma once

#include "Core/Aliases.h"

namespace Shoko
{
    class FStringBufferBase
    {
        
    public:
        FStringBufferBase() = delete;
        
        char* GetData() { return reinterpret_cast<char*>(this + 1); }
        const char* GetData() const { return reinterpret_cast<const char*>(this + 1); }
        
        void Append(char InChar)
        {
            if(Length >= Capacity - 1) return;
            
            char* Data = GetData();
            Data[Length] = InChar;
            ++Length;
            Data[Length] = '\0';
        }
        
        void Pop()
        {
            if(Length == 0) return;
            
            --Length;
            GetData()[Length] = '\0';
        }
        
        uint8 Len() const { return Length; }
        bool IsEmpty() const { return Length == 0; }
        uint8 GetCapacity() const { return Capacity; }
        
    protected:
        uint8 Capacity = 0;
        uint8 Length = 0;
        
        constexpr FStringBufferBase(uint16 InCapacity) : Capacity(InCapacity) {}
    };
}
