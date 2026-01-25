#pragma once

public:

static bool Initialize();
static void Deinitialize();
static void PullEvents();

static uint8 GetKey();

static bool GetLeftShift();
static bool GetRightShift();
static bool GetLeftAlt();
static bool GetRightAlt();
static bool GetLeftCtrl();
static bool GetRightCtrl();
static bool GetLeftCmd();
static bool GetRightCmd();

static FLocation GetMousePosition();
static bool GetMouseLeftButton();
static bool GetMouseRightButton();
static bool GetMouseMiddleButton();

private:
