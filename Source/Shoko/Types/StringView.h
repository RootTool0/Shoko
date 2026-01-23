#pragma once

#include "StringFixed.h"
#include "Core/Aliases.h"

namespace Shoko
{
    struct FStringView
    {
        
    public:
        
    public:
        template<uint16 Capacity>
        constexpr FStringView(const TStringFixed<Capacity>& InBuffer) : DataPtr(InBuffer.GetData()) {}
        constexpr FStringView(const char* InPtr)                      : DataPtr(InPtr) {}
        constexpr FStringView()                                       : DataPtr(nullptr) {}
        
        constexpr FStringView& operator=(const char* InPtr)
        {
            DataPtr = InPtr;
            return *this;
        }
        
        constexpr const char* GetData() const { return DataPtr; }
        bool IsEmpty() const { return !DataPtr || DataPtr[0] == '\0'; }

        constexpr uint16 Len() const 
        {
            if(!DataPtr) return 0;
            
            uint16 Count = 0;
            while(DataPtr[Count] != '\0') ++Count;
            return Count;
        }
        
        /*
        constexpr ElementType operator[](SizeType Index) const { return DataPtr[Index]; }
        
        constexpr ElementType* begin() const noexcept { return DataPtr; }
        constexpr ElementType* end()   const noexcept { return DataPtr + Length; }
        */

        /*
        constexpr bool operator==(const FStringView Other) const
        {
            if (Length != Other.Length) return false;
            if (DataPtr == Other.DataPtr) return true;
            for (SizeType i = 0; i < Length; ++i)
            {
                if (DataPtr[i] != Other.DataPtr[i]) return false;
            }
            return true;
        }
        
        constexpr bool operator!=(const FStringView Other) const { return !(*this == Other); }
        */

        
    private:
        const char* DataPtr;
        
        /*
        static constexpr SizeType StrLen(ElementType* Str)
        {
            if(!Str) return 0;
            SizeType Count = 0;
            while (Str[Count] != '\0') ++Count;
            return Count;
        }*/
    };
}
