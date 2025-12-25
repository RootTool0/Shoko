#pragma once

#include "../Core/Aliases.h"
#include "../Core/Meta.h"
 
namespace Shoko
{
    template<typename T>
    struct TColor
    {
        static_assert(Meta::IsArithmetic<T>, "T must be an arithmetic type");
        
        T R, G, B, A;
        
        constexpr TColor() : R(0), G(0), B(0), A(255) {}
        constexpr TColor(const T InR, const T InG, const T InB) : R(InR), G(InG), B(InB), A(255) {}
        constexpr TColor(const T InR, const T InG, const T InB, const T InA) : R(InR), G(InG), B(InB), A(InA) {}
        
        constexpr TColor operator+(const TColor& InOther) const
        {
            return {
                static_cast<T>(R + InOther.R),
                static_cast<T>(G + InOther.G),
                static_cast<T>(B + InOther.B),
                static_cast<T>(A + InOther.A)
            };
        }
    
        constexpr TColor operator-(const TColor& InOther) const
        {
            return {
                static_cast<T>(R - InOther.R),
                static_cast<T>(G - InOther.G),
                static_cast<T>(B - InOther.B),
                static_cast<T>(A - InOther.A)
            };
        }
    
        constexpr TColor operator*(float InScalar) const
        {
            return {
                static_cast<T>(R * InScalar),
                static_cast<T>(G * InScalar),
                static_cast<T>(B * InScalar),
                static_cast<T>(A * InScalar)
            };
        }
    
        constexpr TColor operator/(float InScalar) const
        {
            return {
                static_cast<T>(R / InScalar),
                static_cast<T>(G / InScalar),
                static_cast<T>(B / InScalar),
                static_cast<T>(A / InScalar)
            };
        }
    
        constexpr TColor Lerp(const TColor& InOther, float InAlpha) const
        {
            const float OneMinusAlpha = 1.0f - InAlpha;
            return {
                static_cast<T>(R * OneMinusAlpha + InOther.R * InAlpha),
                static_cast<T>(G * OneMinusAlpha + InOther.G * InAlpha),
                static_cast<T>(B * OneMinusAlpha + InOther.B * InAlpha),
                static_cast<T>(A * OneMinusAlpha + InOther.A * InAlpha)
            };
        }
    
        constexpr bool operator==(const TColor& InOther) const { return R == InOther.R && G == InOther.G && B == InOther.B && A == InOther.A; }
        constexpr bool operator!=(const TColor& InOther) const { return !(*this == InOther); }
    };
    
    struct FColor : TColor<uint8>
    {
        using TColor::TColor;
        
        // РќР° Р±СѓРґСѓС‰РµРµ
    };
}
