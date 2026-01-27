#pragma once

#include "StaticPoolBase.h"
#include "Core/Meta.h"

namespace Shoko
{
    template<typename TWidget, uint16 InCapacity>
    struct TStaticPool : FStaticPoolBase
    {
        static_assert(Meta::IsWidget<TWidget>, "T must be a Widget type");
        
    public:
        constexpr TStaticPool() : FStaticPoolBase(sizeof(TWidget), InCapacity) { Clear(); }
        
        TStaticPool(const TStaticPool&) = delete;
        TStaticPool& operator=(const TStaticPool&) = delete;
        
        constexpr       TWidget& operator[](uint16 Index)       { return *GetPtr(Index); }
        constexpr const TWidget& operator[](uint16 Index) const { return *GetPtr(Index); }
        
        static constexpr uint16 Num() { return InCapacity; }
        
        TWidget* Add(TWidget InWidget)
        {
            for(uint16 i = 0; i < InCapacity; ++i)
            {
                TWidget* Ptr = GetPtr(i);
                if(!CheckPtr(Ptr))
                    return CreateByPtr(Ptr, Meta::Move(InWidget));
            }
            return nullptr;
        }
        
        bool Remove(TWidget* InPtr)
        {
            if(!InPtr || InPtr < Begin() || InPtr >= End() || !CheckPtr(InPtr)) return false;
            
            InPtr->~TWidget();
            std::memset(InPtr, 0, sizeof(TWidget));
            return true;
        }
        
        bool RemoveAt(uint16 Index) { return Index < InCapacity ? Remove(GetPtr(Index)) : false; }
        
        bool RemoveFirst()
        {
            for(uint16 i = 0; i < InCapacity; ++i)
                if(CheckPtr(GetPtr(i)))
                {
                    Remove(GetPtr(i));
                    return true;
                }
            
            return false;
        }
        
        bool RemoveLast()
        {
            for(int16 i = static_cast<int16>(InCapacity) - 1; i >= 0; --i)
                if(CheckPtr(GetPtr(i)))
                {
                    Remove(GetPtr(i));
                    return true;
                }
            
            return false;
        }
        
        TWidget* Replace(uint16 Index, TWidget InWidget)
        {
            if(Index >= InCapacity) return nullptr;
            
            TWidget* Ptr = GetPtr(Index);
            Remove(Ptr);
            return CreateByPtr(Ptr, Meta::Move(InWidget));
        }
        
        void Clear() { std::memset(RawData, 0, sizeof(RawData)); }
        
        constexpr TWidget* Begin() { return reinterpret_cast<TWidget*>(RawData); }
        constexpr TWidget* End()   { return reinterpret_cast<TWidget*>(RawData) + InCapacity; }
        constexpr const TWidget* Begin() const { return reinterpret_cast<const TWidget*>(RawData); }
        constexpr const TWidget* End()   const { return reinterpret_cast<const TWidget*>(RawData) + InCapacity; }
        
    private:
        // alignas(TWidget)
        uint8 RawData[InCapacity * sizeof(TWidget)];
        
        TWidget* CreateByPtr(TWidget* InPtr, TWidget&& InWidget) { return new(InPtr) TWidget(Meta::Move(InWidget)); }
        static bool CheckPtr(const TWidget* InPtr) { return *reinterpret_cast<const uint8*>(InPtr) != 0; }
        constexpr TWidget* GetPtr(uint16 Index) { return reinterpret_cast<TWidget*>(RawData + (Index * sizeof(TWidget))); }
    };
}
