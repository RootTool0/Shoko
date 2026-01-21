#pragma once

#include <cmath>

namespace Shoko
{
    class FMath
    {
    public:

        template <typename T> static T Min(T InA, T InB) { return InA < InB ? InA : InB; }
        template <typename T> static T Max(T InA, T InB) { return InA > InB ? InA : InB; }
        template <typename T> static T Clamp(T InValue, T InMin, T InMax) { return Min(Max(InValue, InMin), InMax); }

        static float Sqrt(float InA) { return sqrt(InA); }

        static constexpr float PI = 3.14159265358979323846f;
    };
}
