#pragma once

#include <corecrt_math.h>

namespace Shoko
{
    class FMath
    {
    public:

        template <typename T> static T Min(T A, T B) { return A < B ? A : B; }
        template <typename T> static T Max(T A, T B) { return A > B ? A : B; }

        static float Sqrt(float A) { return sqrtf(A); }

        static constexpr float PI = 3.14159265358979323846f;
    };
}
