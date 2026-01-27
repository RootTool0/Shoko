#pragma once

#include "Core/Aliases.h"

namespace Shoko
{
    struct FStaticPoolBase
    {
        
    public:
        uint8* GetData() { return reinterpret_cast<uint8*>(this + 1); }
        const uint8* GetData() const { return reinterpret_cast<const uint8*>(this + 1); }

        uint8* GetElement(uint16 Index) { return GetData() + (Index * ElementSize); }
        const uint8* GetElement(uint16 Index) const { return GetData() + (Index * ElementSize); }
        
        bool CheckElement(uint16 Index) const { return *GetElement(Index) != 0; }
        
        uint16 GetCapacity() const { return Capacity; }

        template<typename T>       T* Cast(uint16 Index)       { return reinterpret_cast<      T*>(GetElement(Index)); }
        template<typename T> const T* Cast(uint16 Index) const { return reinterpret_cast<const T*>(GetElement(Index)); }
        
    protected:
        uint16 ElementSize;
        uint16 Capacity;

        constexpr FStaticPoolBase(uint16 InElementSize, uint16 InCapacity) : ElementSize(InElementSize), Capacity(InCapacity) {}
    };
}
