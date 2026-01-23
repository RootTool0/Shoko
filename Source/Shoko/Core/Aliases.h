#pragma once

#include <cstdint>
#include <cstddef>

namespace Shoko
{
    using int8 = int8_t;
    using int16 = int16_t;
    using int32 = int32_t;
    using int64 = int64_t;

    using uint8 = uint8_t;
    using uint16 = uint16_t;
    using uint32 = uint32_t;
    using uint64 = uint64_t;

    using float32 = float;
    using float64 = double;

    using size_t = std::size_t;

    using GUTID = uint8_t;

    static_assert(sizeof(int8)    == 1,   "Invalid int8    size");
    static_assert(sizeof(int16)   == 2,   "Invalid int16   size");
    static_assert(sizeof(int32)   == 4,   "Invalid int32   size");
    static_assert(sizeof(int64)   == 8,   "Invalid int64   size");
    static_assert(sizeof(uint8)   == 1,   "Invalid int8    size");
    static_assert(sizeof(uint16)  == 2,   "Invalid int16   size");
    static_assert(sizeof(uint32)  == 4,   "Invalid int32   size");
    static_assert(sizeof(uint64)  == 8,   "Invalid int64   size");
    static_assert(sizeof(float32) == 4,   "Invalid float32 size");
    static_assert(sizeof(float64) == 8,   "Invalid float64 size");
    static_assert(sizeof(GUTID)   == 1,   "Invalid GUTID   size");
}
