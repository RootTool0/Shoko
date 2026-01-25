#pragma once

#include "StringBufferBase.h"
#include "Core/Aliases.h"

namespace Shoko
{
    template<uint16 InCapacity>
    class TStringBuffer : public FStringBufferBase
    {
        
    public:
        constexpr TStringBuffer() : FStringBufferBase(InCapacity + 1) { Buffer[0] = '\0'; }
        
        TStringBuffer(const TStringBuffer&) = delete;
        TStringBuffer& operator=(const TStringBuffer&) = delete;
        
    private:
        char Buffer[InCapacity + 1];
    };
}
