#pragma once

#include <algorithm>

#include "Core/Aliases.h"
#include "Core/Math.h"
#include "Core/Meta.h"
 
namespace Shoko
{
    template<typename T>
    struct TVector2D
    {
        static_assert(Meta::IsArithmetic<T>, "T must be an arithmetic type");
        
        T X, Y;
        
        explicit constexpr TVector2D()             : X(T(0)), Y(T(0)) {}
        explicit constexpr TVector2D(T InScalar)   : X(InScalar), Y(InScalar) {}
        explicit constexpr TVector2D(T InX, T InY) : X(InX), Y(InY) {}

        constexpr TVector2D operator+(const TVector2D& Other) const { return TVector2D(X + Other.X, Y + Other.Y); }
        constexpr TVector2D operator-(const TVector2D& Other) const { return TVector2D(X - Other.X, Y - Other.Y); }
        constexpr TVector2D operator-(T Scalar) const               { return TVector2D(X - Scalar,  Y - Scalar);  }
        constexpr TVector2D operator*(T Scalar) const               { return TVector2D(X * Scalar,  Y * Scalar);  }
        constexpr TVector2D operator/(T Scalar) const               { return TVector2D(X / Scalar,  Y / Scalar);  }
        
        constexpr TVector2D& operator+=(const TVector2D& Other) { X += Other.X; Y += Other.Y; return *this; }
        constexpr TVector2D& operator-=(const TVector2D& Other) { X -= Other.X; Y -= Other.Y; return *this; }
        constexpr TVector2D& operator+=(T Scalar) { X += Scalar; Y += Scalar; return *this; }
        constexpr TVector2D& operator-=(T Scalar) { X -= Scalar; Y -= Scalar; return *this; }
        
        constexpr bool operator==(const TVector2D& Other) const { return X == Other.X && Y == Other.Y; }
        constexpr bool operator!=(const TVector2D& Other) const { return !(*this == Other); }

        T GetMin() const { return FMath::Min(X, Y); }
        T GetMax() const { return FMath::Max(X, Y); }

        // void Print() const { std::cout << "(" << X << ", " << Y << ")\n"; }
    };
    
    using FIntVector2D = TVector2D<int16>;
    using FUIntVector2D = TVector2D<uint16>;

    using FLocation = TVector2D<int16>;
    using FSize = TVector2D<uint16>;

    inline FLocation operator-(const FLocation& Lhs, const FSize& Rhs    ) { return FLocation(static_cast< int16>(Lhs.X - Rhs.X), static_cast< int16>(Lhs.Y - Rhs.Y)); }
    inline FSize     operator-(const FSize& Lhs    , const FLocation& Rhs) { return FSize    (static_cast<uint16>(Lhs.X - Rhs.X), static_cast<uint16>(Lhs.Y - Rhs.Y)); }
    
    using FPadding = TVector2D<uint8>;
}
