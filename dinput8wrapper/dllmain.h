// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

#include <windows.h>
#include <objbase.h>
#include <strsafe.h>
#include "dinput8.h"

#include "hid.h"

static HMODULE DllHModule;

#include "CDirectInput8Globals.h"

#include "CDirectInputDeviceMouse8.h"
#include "CDirectInputDeviceMouse8A.h"
#include "CDirectInputDeviceMouse8W.h"

#include "CDirectInputDeviceKeyboard8.h"
#include "CDirectInputDeviceKeyboard8A.h"
#include "CDirectInputDeviceKeyboard8W.h"

#include "CDirectInputDeviceGamepad8.h"
#include "CDirectInputDeviceGamepad8A.h"
#include "CDirectInputDeviceGamepad8W.h"

#include "CDirectInput8.h"
#include "CDirectInput8A.h"
#include "CDirectInput8W.h"

#endif //PCH_H
