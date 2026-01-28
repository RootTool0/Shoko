#pragma once

#include "Widgets/Base/WidgetContainer.h"
#include "Core/Meta.h"
#include "Core/Macros.h"

namespace Shoko
{
    template<typename... TChildWidgets>
    class SRootBox : public SWidgetContainer<TChildWidgets...>
    {
        SHOKO_GENERATED_TEMPLATE_BODY()
        
        using Super = SWidgetContainer<TChildWidgets...>;
        
    public:
        explicit constexpr SRootBox(TChildWidgets&&... InChildren) : Super(Meta::Move(InChildren)...) { CalculateLayout(); }
        
        constexpr SRootBox& SetSize(FSize InSize)
        {
            Super::SetSize(InSize);
            CalculateLayout();
            return *this;
        }

        constexpr SRootBox& SetLocation(FLocation InLocation)
        {
            Super::SetLocation(InLocation);
            CalculateLayout();
            return *this;
        }
        
    private:
        constexpr void CalculateLayout()
        {
            if(this->ChildWidgetsCount == 0) return;
            
            Meta::Apply(
                [&](auto&... Child)
                {
                    ((
                        Child.SetLocation(Super::GetGeometry().Location),
                        Child.SetSize(Super::GetGeometry().Size)
                    ), ...);
                },
                this->ChildWidgets
            );
        }
    };
}
