#pragma once

public:

static bool Initialize();
static void Deinitialize();
static void PullEvents();

static EKey GetKey();

static bool GetLeftShift();
static bool GetRightShift();
static bool GetLeftAlt();
static bool GetRightAlt();
static bool GetLeftCtrl();
static bool GetRightCtrl();
static bool GetLeftCmd();
static bool GetRightCmd();

static FIntVector2D GetMousePosition();
static bool GetMouseLeftButton();
static bool GetMouseRightButton();
static bool GetMouseMiddleButton();

private:
