#pragma once

#include "Core/Aliases.h"
#include "Core/Macros.h"
#include "Types/StaticPool/StaticPool.h"

namespace Shoko
{
    template<typename TWidget>
    class SWidgetPoolView : public SWidget<SWidgetPoolView<TWidget>>
    {
        SHOKO_GENERATED_TEMPLATE_BODY()
        using Super = SWidget<SWidgetPoolView<TWidget>>;
        
    public:
        constexpr SWidgetPoolView() = default;

        template<uint16 InCapacity>
        constexpr SWidgetPoolView& Bind(TStaticPool<TWidget, InCapacity>& InPool)
        {
            PoolPtr = &InPool;
            return *this;
        }
    
        void Render() const
        {
            if(!PoolPtr) return;
            
            for(uint16 i = 0; i < PoolPtr->GetCapacity(); ++i)
                if(PoolPtr->CheckElement(i))
                    PoolPtr->Cast<TWidget>(i)->Render();
        }
        
        const FWidgetBase* HitTest(FLocation InMouseLocation) const
        {
            if(!PoolPtr) return nullptr;
            
            for(size_t i = 0; i < PoolPtr->GetCapacity(); ++i)
                if(PoolPtr->CheckElement(i))
                    if(const FWidgetBase* FoundWidget = PoolPtr->Cast<TWidget>(i)->HitTest(InMouseLocation))
                        return FoundWidget;

            return nullptr;
        }
        
    private:
        FStaticPoolBase* PoolPtr = nullptr;
    };
}
