#pragma once

namespace Shoko
{
    class FMath
    {
    public:

        template <typename T> static T Min(T A, T B) { return A < B ? A : B; }
        template <typename T> static T Max(T A, T B) { return A > B ? A : B; }
    };
}
