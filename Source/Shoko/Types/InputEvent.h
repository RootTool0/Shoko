#pragma once

#include "Core/Aliases.h"

namespace Shoko
{
    enum class EKey : uint8
    {
        None,
        
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
        
        Mouse_Left,
        Mouse_Right,
        Mouse_Middle,
        
        Window_Close
    };
    
    struct FInputEvent
    {
        EKey Key;
        
        uint8 bLeftShift : 1;
        uint8 bRightShift : 1;
        uint8 bLeftAlt  : 1;
        uint8 bRightAlt : 1;
        uint8 bLeftCtrl : 1;
        uint8 bRightCtrl : 1;
        uint8 bLeftCmd : 1;
        uint8 bRightCmd : 1;
        
        bool bShift() const { return bLeftShift || bRightShift; }
        bool bAlt()   const { return bLeftAlt   || bRightAlt;   }
        bool bCtrl()  const { return bLeftCtrl  || bRightCtrl;  }
        bool bCmd()   const { return bLeftCmd   || bRightCmd;   }
    };
}
