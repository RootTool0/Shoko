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
        
        constexpr TColor operator+(const TColor& Other) const
        {
            return {
                static_cast<T>(R + Other.R),
                static_cast<T>(G + Other.G),
                static_cast<T>(B + Other.B),
                static_cast<T>(A + Other.A)
            };
        }
    
        constexpr TColor operator-(const TColor& Other) const
        {
            return {
                static_cast<T>(R - Other.R),
                static_cast<T>(G - Other.G),
                static_cast<T>(B - Other.B),
                static_cast<T>(A - Other.A)
            };
        }
    
        constexpr TColor operator*(float Scalar) const
        {
            return {
                static_cast<T>(R * Scalar),
                static_cast<T>(G * Scalar),
                static_cast<T>(B * Scalar),
                static_cast<T>(A * Scalar)
            };
        }
    
        constexpr TColor operator/(float Scalar) const
        {
            return {
                static_cast<T>(R / Scalar),
                static_cast<T>(G / Scalar),
                static_cast<T>(B / Scalar),
                static_cast<T>(A / Scalar)
            };
        }
    
        constexpr TColor Lerp(const TColor& Other, float Alpha) const
        {
            const float OneMinusAlpha = 1.0f - Alpha;
            return {
                static_cast<T>(R * OneMinusAlpha + Other.R * Alpha),
                static_cast<T>(G * OneMinusAlpha + Other.G * Alpha),
                static_cast<T>(B * OneMinusAlpha + Other.B * Alpha),
                static_cast<T>(A * OneMinusAlpha + Other.A * Alpha)
            };
        }
    
        constexpr bool operator==(const TColor& Other) const { return R == Other.R && G == Other.G && B == Other.B && A == Other.A; }
        constexpr bool operator!=(const TColor& Other) const { return !(*this == Other); }

        float GetNormalizedR() { return static_cast<float>(R) / 255.f; }
        float GetNormalizedG() { return static_cast<float>(G) / 255.f; }
        float GetNormalizedB() { return static_cast<float>(B) / 255.f; }
        float GetNormalizedA() { return static_cast<float>(A) / 255.f; }
    };
    
    struct FColor : TColor<uint8>
    {
        using TColor::TColor;
        
        static FColor Red;
        static FColor Green;
        static FColor Blue;
        static FColor White;
        static FColor Black;
        static FColor Yellow;
        static FColor Cyan;
        static FColor Magenta;
        static FColor Gray;
        
        static FColor Error;
    };
    
    inline FColor FColor::Red     = FColor(255, 0  , 0  );
    inline FColor FColor::Green   = FColor(0  , 255, 0  );
    inline FColor FColor::Blue    = FColor(0  , 0  , 255);
    inline FColor FColor::White   = FColor(255, 255, 255);
    inline FColor FColor::Black   = FColor(0  , 0  , 0  );
    inline FColor FColor::Yellow  = FColor(255, 255, 0  );
    inline FColor FColor::Cyan    = FColor(0  , 255, 255);
    inline FColor FColor::Magenta = FColor(255, 0  , 255);
    inline FColor FColor::Gray    = FColor(128, 128, 128);
    
    inline FColor FColor::Error   = FColor(255, 0  , 255);
}
