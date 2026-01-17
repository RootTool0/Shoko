#pragma once

#include "Core/Aliases.h"
#include "Core/Meta.h"
 
namespace Shoko
{
    template<typename T>
    struct TVector2D
    {
        static_assert(Meta::IsArithmetic<T>, "T must be an arithmetic type");
        
        T X, Y;
        
        explicit constexpr TVector2D()             : X(T(0)), Y(T(0)) {}
        explicit constexpr TVector2D(T InX, T InY) : X(InX), Y(InY) {}

        constexpr TVector2D operator+(const TVector2D& Other) const { return TVector2D(X + Other.X, Y + Other.Y); }
        constexpr TVector2D operator-(const TVector2D& Other) const { return TVector2D(X - Other.X, Y - Other.Y); }
        constexpr TVector2D operator*(T Scalar) const               { return TVector2D(X * Scalar,  Y * Scalar);  }
        constexpr TVector2D operator/(T Scalar) const               { return TVector2D(X / Scalar,  Y / Scalar);  }
 
        constexpr TVector2D& operator+=(const TVector2D& Other) { X += Other.X; Y += Other.Y; return *this; }
        constexpr TVector2D& operator-=(const TVector2D& Other) { X -= Other.X; Y -= Other.Y; return *this; }
        
        constexpr bool operator==(const TVector2D& Other) const { return X == Other.X && Y == Other.Y; }
        constexpr bool operator!=(const TVector2D& Other) const { return !(*this == Other); }
        
        // void Print() const { std::cout << "(" << X << ", " << Y << ")\n"; }
    };
    
    using FIntVector2D = TVector2D<int16>;
    using FUIntVector2D = TVector2D<uint16>;
}
