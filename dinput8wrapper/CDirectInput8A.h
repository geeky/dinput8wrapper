#pragma once

class CDirectInput8A : public IDirectInput8A
{
private:
	ULONG refCount;
	CDirectInputDeviceMouse8A* mouseDevice;
	CDirectInputDeviceKeyboard8A* keyboardDevice;
	CDirectInputDeviceGamepad8A* gamepadDevice;

	DIDEVICEINSTANCEA mouseDeviceInfo = {};
	DIDEVICEINSTANCEA keyboardDeviceInfo = {};
	DIDEVICEINSTANCEA gamepadDeviceInfo = {};

public:		
		

	CDirectInput8A()
	{	
		refCount = 1;

		mouseDevice= new CDirectInputDeviceMouse8A();
		keyboardDevice=new CDirectInputDeviceKeyboard8A();
		gamepadDevice = new CDirectInputDeviceGamepad8A();

		DWORD threadId;
		HANDLE hThread;

		hThread=CreateThread(NULL, 0, ThreadProc, NULL, 0, &threadId);
		if (hThread==NULL)
		{
			MessageBoxA(NULL, "CreateThread() failed", "dinput8.dll", MB_OK);
			return;
		}
	}

	static DWORD WINAPI ThreadProc(LPVOID lpParameter)
	{
		WNDCLASSEXA wcex;
		ZeroMemory(&wcex, sizeof(WNDCLASSEXA));
		wcex.cbSize = sizeof(WNDCLASSEXA);
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = MainWndProc;
		wcex.hInstance = DllHModule;
		wcex.hIcon = LoadIconA(NULL, IDI_APPLICATION);
		wcex.hCursor = LoadCursorA(NULL, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		wcex.lpszClassName = "CDirectInput8A";

		if (!RegisterClassExA(&wcex))
		{
			MessageBoxA(NULL, "RegisterClassExA() failed", "dinput8.dll", MB_OK);
			return 0;
		}

		HWND hWnd = CreateWindowExA(WS_EX_CLIENTEDGE, "CDirectInput8A", "dinput8.dll", WS_OVERLAPPEDWINDOW, 1920, 10, 400, 400, NULL, NULL, DllHModule, NULL);
		if (hWnd==NULL)
		{
			MessageBoxA(NULL, "CreateWindowExA() failed", "dinput8.dll", MB_OK);
			return 0;
		}

		ShowWindow(hWnd, SW_HIDE);
		UpdateWindow(hWnd);

		MSG msg;
		while (GetMessage(&msg, NULL, 0, 0) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		return msg.wParam;
	}	

	static LRESULT HandleWMInput(LPARAM lParam)
	{
		UINT dwSize = 0;

		GetRawInputData((HRAWINPUT)lParam, RID_INPUT, NULL, &dwSize, sizeof(RAWINPUTHEADER));
		LPBYTE lpb = new BYTE[dwSize];
		if (lpb == NULL)
		{
			return 0;
		}

		if (GetRawInputData((HRAWINPUT)lParam, RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER)) != dwSize)
		{
			diGlobalsInstance->Log("GetRawInputData does not return correct size!", __FILE__, __LINE__);
			return 0;
		}

		RAWINPUT* raw = (RAWINPUT*)lpb;

		diGlobalsInstance->HandleRawInput(raw);

		delete[] lpb;
		return 0;
	}

	static LRESULT CALLBACK MainWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
	{
		if (Msg == WM_CREATE)
		{
			RAWINPUTDEVICE Rid[4];

			//
			Rid[0].usUsagePage = HID_USAGE_PAGE_GENERIC;
			Rid[0].usUsage = HID_USAGE_GENERIC_MOUSE;
			Rid[0].dwFlags = 0;		// adds HID mouse and also ignores legacy mouse messages
			Rid[0].hwndTarget = hWnd;			

			Rid[1].usUsagePage = HID_USAGE_PAGE_GENERIC;
			Rid[1].usUsage = HID_USAGE_GENERIC_KEYBOARD;
			Rid[1].dwFlags = 0;		// adds HID keyboard and also ignores legacy keyboard messages
			Rid[1].hwndTarget = hWnd;

			Rid[2].usUsagePage = HID_USAGE_PAGE_GENERIC;
			Rid[2].usUsage = HID_USAGE_GENERIC_JOYSTICK;
			Rid[2].dwFlags = RIDEV_DEVNOTIFY;
			Rid[2].hwndTarget = hWnd;

			Rid[3].usUsagePage = HID_USAGE_PAGE_GENERIC;
			Rid[3].usUsage = HID_USAGE_GENERIC_GAMEPAD;
			Rid[3].dwFlags = RIDEV_DEVNOTIFY;
			Rid[3].hwndTarget = hWnd;

			if (RegisterRawInputDevices(Rid, 4, sizeof(Rid[0])) == FALSE) {
				MessageBoxA(NULL, "RegisterRawInputDevices() failed!", "dinput8.dll", MB_OK | MB_ICONEXCLAMATION);
				//registration failed. Call GetLastError for the cause of the error
			}
		}
		else if (Msg == WM_INPUT)
		{
			return HandleWMInput(lParam);
		}
		else if (Msg == WM_INPUT_DEVICE_CHANGE)
		{
			diGlobalsInstance->CheckRawInputDevices();
		}

		return DefWindowProcA(hWnd, Msg, wParam, lParam);
	}

	virtual HRESULT STDMETHODCALLTYPE QueryInterface(GUID* riid, LPVOID* ppvObj)
	{
		MessageBoxA(NULL, "QueryInterface()", "XXXX", MB_OK);

		return S_OK;
	}

	virtual ULONG __stdcall AddRef()
	{
		diGlobalsInstance->Log("CDirectInput8A->AddRef()", __FILE__, __LINE__);
		refCount++;

		return refCount;
	}

	virtual ULONG __stdcall Release()
	{
		diGlobalsInstance->Log("CDirectInput8A->Release()",__FILE__,__LINE__);

		refCount--;

		return refCount;
	}

	/*** IDirectInput8A methods ***/
	virtual HRESULT STDMETHODCALLTYPE CreateDevice(GUID* rguid, LPDIRECTINPUTDEVICE8A* lplpDirectInputDevice, LPUNKNOWN pUnkOuter)
	{
		if (IsEqualIID(GUID_SysMouse, *rguid))
		{
			diGlobalsInstance->Log("CreateDevice() for GUID_SysMouse",__FILE__,__LINE__);

			*lplpDirectInputDevice = mouseDevice;
			return DI_OK;
		}
		else if (IsEqualIID(GUID_SysKeyboard, *rguid))
		{
			diGlobalsInstance->Log("CreateDevice() for GUID_SysKeyboard",__FILE__,__LINE__);

			*lplpDirectInputDevice = keyboardDevice;
			return DI_OK;
		}

		char tmp[4096];
		wsprintfA(tmp, "[dinput8] CreateDevice() for rguid=%x-%x-%x-%x", rguid->Data1, rguid->Data2, rguid->Data3, rguid->Data4);
		diGlobalsInstance->Log(tmp,__FILE__,__LINE__);		

		return E_ABORT;
	}

	virtual HRESULT STDMETHODCALLTYPE EnumDevices(DWORD dwDevType, LPDIENUMDEVICESCALLBACKA lpCallback, LPVOID pvRef, DWORD dwFlags)
	{
		char tmp[4096];
		wsprintfA(tmp, "[dinput8] EnumDevices() for dwDevType=0x%x, dwFlags=0x0", dwDevType, dwFlags);
		diGlobalsInstance->Log(tmp, __FILE__, __LINE__);

		if ((dwDevType == DI8DEVCLASS_ALL) || (dwDevType == DI8DEVCLASS_POINTER) || (dwDevType == DI8DEVTYPE_MOUSE))
		{	
			diGlobalsInstance->Log("EnumDevices: Returning Mouse-Device", __FILE__, __LINE__);

			mouseDevice->GetDeviceInfo(&mouseDeviceInfo);
			if (lpCallback(&mouseDeviceInfo, pvRef) == DIENUM_STOP)
			{
				diGlobalsInstance->Log("EnumDevices stopped (due to DIENUM_STOP)",__FILE__,__LINE__);
				return DI_OK;
			}
		}

		if ((dwDevType == DI8DEVCLASS_ALL) || (dwDevType == DI8DEVCLASS_KEYBOARD))
		{
			diGlobalsInstance->Log("EnumDevices: Returning Keyboard-Device", __FILE__, __LINE__);

			keyboardDevice->GetDeviceInfo(&keyboardDeviceInfo);
			if (lpCallback(&keyboardDeviceInfo, pvRef) == DIENUM_STOP)
			{
				diGlobalsInstance->Log("EnumDevices stopped (due to DIENUM_STOP)", __FILE__, __LINE__);
				return DI_OK;
			}
		}

		if ((dwDevType == DI8DEVCLASS_ALL) || (dwDevType == DI8DEVCLASS_GAMECTRL))
		{
			diGlobalsInstance->Log("EnumDevices: Returning Gamepad-Device", __FILE__, __LINE__);

			gamepadDevice->GetDeviceInfo(&gamepadDeviceInfo);
			if (lpCallback(&gamepadDeviceInfo, pvRef) == DIENUM_STOP)
			{
				diGlobalsInstance->Log("EnumDevices stopped (due to DIENUM_STOP)", __FILE__, __LINE__);
				return DI_OK;
			}
		}

		return DI_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE GetDeviceStatus(GUID* rguidInstance)
	{
		MessageBoxA(NULL, "GetDeviceStatus", "input8.dll", MB_OK);

		return S_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE RunControlPanel(HWND hwndOwner, DWORD dwFlags)
	{
		MessageBoxA(NULL, "RunControlPanel", "input8.dll", MB_OK);

		return S_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE Initialize(HINSTANCE hinst, DWORD dwVersion)
	{
		MessageBoxA(NULL, "Initialize", "input8.dll", MB_OK);

		return S_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE FindDevice(GUID* rguid, LPCSTR pszName, LPGUID pguidInstance)
	{
		MessageBoxA(NULL, "FindDevice", "input8.dll", MB_OK);

		return S_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE EnumDevicesBySemantics(LPCSTR ptszUserName, LPDIACTIONFORMATA lpdiActionFormat, LPDIENUMDEVICESBYSEMANTICSCBA lpCallback, LPVOID pvRef, DWORD dwFlags)
	{
		MessageBoxA(NULL, "EnumDevicesBySemantics", "input8.dll", MB_OK);

		return S_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE ConfigureDevices(LPDICONFIGUREDEVICESCALLBACK lpdiCallback, LPDICONFIGUREDEVICESPARAMSA lpdiCDParams, DWORD dwFlags, LPVOID pvRefData)
	{
		MessageBoxA(NULL, "ConfigureDevices", "input8.dll", MB_OK);

		return S_OK;
	}
};