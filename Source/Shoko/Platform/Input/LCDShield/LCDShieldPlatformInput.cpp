#include "LCDShieldPlatformInput.h"

#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>
#include <algorithm>

using namespace Shoko;

int FShokoLCDShieldPlatformInput::TouchFD = -1;
FLocation FShokoLCDShieldPlatformInput::CurrentPos = FLocation(0, 0);
bool FShokoLCDShieldPlatformInput::bIsPressed = false;

static constexpr int minX = 150,  maxX = 3965;
static constexpr int minY = 106,  maxY = 3967;
static constexpr int screenW = 480;
static constexpr int screenH = 320;

bool FShokoLCDShieldPlatformInput::Initialize()
{ 
    TouchFD = open("/dev/input/event0", O_RDONLY | O_NONBLOCK);
    return TouchFD >= 0;
}
void FShokoLCDShieldPlatformInput::Deinitialize() { if (TouchFD >= 0) close(TouchFD); }
void FShokoLCDShieldPlatformInput::PullEvents()
{
    if (TouchFD < 0) return;

    input_event ev;
    static int rawX = -1;
    static int rawY = -1;

    while (read(TouchFD, &ev, sizeof(ev)) > 0) 
    {
        if (ev.type == EV_ABS) 
        {
            if (ev.code == ABS_X) rawX = ev.value;
            else if (ev.code == ABS_Y) rawY = ev.value;
            
            if (rawX >= 0 && rawY >= 0) 
            {
                // 1. Сначала калибруем (нормализуем) сырые значения
                // ВАЖНО: Если после поворота X и Y поменялись местами, 
                // мы используем сырой Y для расчета экранного X и наоборот.

                // Вычисляем экранный X на основе сырого Y (инвертированного)
                int16 pixX = static_cast<int16>(screenW - ((rawY - minY) * screenW / (maxY - minY)));
                
                // Вычисляем экранный Y на основе сырого X
                int16 pixY = static_cast<int16>((rawX - minX) * screenH / (maxX - minX));

                // 2. Ограничиваем рамками (Clip)
                pixX = std::max(int16(0), std::min(int16(screenW - 1), pixX));
                pixY = std::max(int16(0), std::min(int16(screenH - 1), pixY));

                CurrentPos = FLocation(screenW - pixX, screenH - pixY);
            }
        }
        else if (ev.type == EV_KEY && ev.code == BTN_TOUCH) 
        {
            bIsPressed = (ev.value == 1);
        }
    }
}

FLocation FShokoLCDShieldPlatformInput::GetMousePosition() { return CurrentPos; }
bool FShokoLCDShieldPlatformInput::GetMouseLeftButton()    { return bIsPressed; }
bool FShokoLCDShieldPlatformInput::GetMouseRightButton()   { return false; }
bool FShokoLCDShieldPlatformInput::GetMouseMiddleButton()  { return false; }

uint8 FShokoLCDShieldPlatformInput::GetKey() { return 0; }
bool FShokoLCDShieldPlatformInput::GetLeftShift()  { return false; }
bool FShokoLCDShieldPlatformInput::GetRightShift() { return false; }
bool FShokoLCDShieldPlatformInput::GetLeftAlt()    { return false; }
bool FShokoLCDShieldPlatformInput::GetRightAlt()   { return false; }
bool FShokoLCDShieldPlatformInput::GetLeftCtrl()   { return false; }
bool FShokoLCDShieldPlatformInput::GetRightCtrl()  { return false; }
bool FShokoLCDShieldPlatformInput::GetLeftCmd()    { return false; }
bool FShokoLCDShieldPlatformInput::GetRightCmd()   { return false; }
