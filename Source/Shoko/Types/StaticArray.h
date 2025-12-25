#pragma once

namespace Shoko
{
    template<typename T, size_t N>
    class TStaticArray
    {
    private:
        T Data[N];
        
    public:
        constexpr TStaticArray() = default;
        
        template<typename... Args>
        constexpr TStaticArray(Args&&... InArgs) : Data{T(InArgs)...}
        {
            static_assert(sizeof...(Args) == N, "TStaticArray: Wrong number of elements");
        }
        
        constexpr T& operator[](size_t InIndex) { return Data[InIndex]; }
        constexpr const T& operator[](size_t InIndex) const { return Data[InIndex]; }
        
        static constexpr size_t Size() { return N; }
        
        constexpr T* Begin() { return Data; }
        constexpr T* End()   { return Data + N; }
        constexpr const T* Begin() const { return Data; }
        constexpr const T* End()   const { return Data + N; }
        
        constexpr void Fill(const T& InValue)
        {
            for(size_t i = 0; i < N; ++i) Data[i] = InValue;
        }
    };
}
