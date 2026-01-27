#pragma once

#include "Renderer.h"
#include "Widget.h"
#include "Types/InputEvent.h"
#include "Types/StringBuffer/StringBufferBase.h"

namespace Shoko
{
    SHOKO_CLASS(STextInput)
    class STextInput : public SWidget<STextInput>
    {
        SHOKO_GENERATED_BODY(STextInput)

        using Super = SWidget<STextInput>;
        
    public:
        constexpr STextInput() = default;

        constexpr STextInput& SetTextBuffer(FStringBufferBase* InTextBufferPtr)
        {
            TextBufferPtr = InTextBufferPtr;
            return *this;
        }

        constexpr STextInput& SetTextColor(FColor InTextColor)
        {
            TextColor = InTextColor;
            return *this;
        }
        
        constexpr STextInput& SetBackgroundColor(FColor InBackgroundColor)
        {
            BackgroundColor = InBackgroundColor;
            return *this;
        }
        
        constexpr STextInput& SetTextSize(uint8 InSize)
        {
            Size = InSize;
            return *this;
        }
        
        void CallOnKey(uint8 Key) const
        {
            if(!TextBufferPtr) return;

            if(!FInputEvent::IsKeyboardKey(Key)) return;
            
            if(Key == FInputEvent::GetKey(EKeyboardKey::Special_Backspace)) TextBufferPtr->Pop();
            else TextBufferPtr->Append(static_cast<char>(Key));
        }
        
        void Render() const
        {
            static constexpr uint8 Radius = 5;
            
            FShokoRenderer::DrawRoundedRect(GetGeometry().Location, GetGeometry().Size, Radius, BackgroundColor);
            
            if(TextBufferPtr && !TextBufferPtr->IsEmpty())
                FShokoRenderer::DrawText(GetGeometry().Location + FLocation(Radius), TextBufferPtr->GetData(), TextBufferPtr->Len(), Size, TextColor, false);
        }
        
    private:
        FStringBufferBase* TextBufferPtr = nullptr;
        FColor TextColor = FColor(0);
        FColor BackgroundColor = FColor(255);
        uint8 Size = 20;
    };
}
