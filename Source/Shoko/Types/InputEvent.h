#pragma once

#include "Core/Aliases.h"

namespace Shoko
{
    enum class EKeyboardKey : uint8
    {
        None = 0,
        
        Number_0 = '0',
        Number_1 = '1',
        Number_2 = '2',
        Number_3 = '3',
        Number_4 = '4',
        Number_5 = '5',
        Number_6 = '6',
        Number_7 = '7',
        Number_8 = '8',
        Number_9 = '9',
        
        Letter_A = 'A',
        Letter_B = 'B',
        Letter_C = 'C',
        Letter_D = 'D',
        Letter_E = 'E',
        Letter_F = 'F',
        Letter_G = 'G',
        Letter_H = 'H',
        Letter_I = 'I',
        Letter_J = 'J',
        Letter_K = 'K',
        Letter_L = 'L',
        Letter_M = 'M',
        Letter_N = 'N',
        Letter_O = 'O',
        Letter_P = 'P',
        Letter_Q = 'Q',
        Letter_R = 'R',
        Letter_S = 'S',
        Letter_T = 'T',
        Letter_U = 'U',
        Letter_V = 'V',
        Letter_W = 'W',
        Letter_X = 'X',
        Letter_Y = 'Y',
        Letter_Z = 'Z',

        Special_Space     = ' ',
        Special_Period    = '.',
        Special_Comma     = ',',
        Special_Semicolon = ';',
        Special_Backspace
    };
    
    enum class ESystemKey : uint8
    {
        None = 0,
        
        Window_Close
    };
    
    enum class EModifier : uint8
    {
        None = 0,
        
        LeftShift  = 1 << 0,
        RightShift = 1 << 1,
        
        LeftCtrl  = 1 << 2,
        RightCtrl = 1 << 3,
        
        LeftAlt  = 1 << 4,
        RightAlt = 1 << 5,
        
        LeftCmd  = 1 << 6,
        RightCmd = 1 << 7,
        
        AnyShift = LeftShift | RightShift,
        AnyCtrl  = LeftCtrl  | RightCtrl,
        AnyAlt   = LeftAlt   | RightAlt
    };
    
    enum class EMouseButton : uint8
    {
        None     = 0,
        Left     = 1 << 0,
        Right    = 1 << 1,
        Middle   = 1 << 2
    };
    
    struct FInputEvent
    {
        uint8 Key;
        uint8 Modifiers;
        uint8 MouseButtons;
        bool bRepeat = false;
        
        static bool IsKeyboardKey(uint8 Key) { return Key != 0 && (Key & 0x80) == 0; }
        
        static uint8 GetKey(EKeyboardKey KeyboardKey) { return static_cast<uint8>(KeyboardKey) & ~0x80; }
        static uint8 GetKey(ESystemKey SystemKey)     { return static_cast<uint8>(SystemKey)   |  0x80; }
    };
}
