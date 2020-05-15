#pragma once

class CDirectInput8A : public IDirectInput8A
{
private:
	ULONG refCount;
	CDirectInputDeviceMouse8A* mouseDevice;
	CDirectInputDeviceKeyboard8A* keyboardDevice;

	LPDIDEVICEINSTANCEA mouseDeviceInfo = new DIDEVICEINSTANCEA();
	LPDIDEVICEINSTANCEA keyboardDeviceInfo = new DIDEVICEINSTANCEA();	

public:		
		

	CDirectInput8A()
	{	
		refCount = 1;

		mouseDevice= new CDirectInputDeviceMouse8A();
		keyboardDevice=new CDirectInputDeviceKeyboard8A();

		// Mouse:
		{
			mouseDevice->GetDeviceInfo(mouseDeviceInfo);
		}

		// Keyboard:
		{
			keyboardDevice->GetDeviceInfo(keyboardDeviceInfo);			
		}

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
		UINT dwSize;

		GetRawInputData((HRAWINPUT)lParam, RID_INPUT, NULL, &dwSize,			sizeof(RAWINPUTHEADER));
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
			RAWINPUTDEVICE Rid[2];

			Rid[0].usUsagePage = 0x01;
			Rid[0].usUsage = 0x02;
			Rid[0].dwFlags = 0;// RIDEV_NOLEGACY;   // adds HID mouse and also ignores legacy mouse messages
			Rid[0].hwndTarget = hWnd;			

			Rid[1].usUsagePage = 0x01;
			Rid[1].usUsage = 0x06;
			Rid[1].dwFlags = 0;// RIDEV_NOLEGACY;   // adds HID keyboard and also ignores legacy keyboard messages
			Rid[1].hwndTarget = hWnd;

			if (RegisterRawInputDevices(Rid, 2, sizeof(Rid[0])) == FALSE) {
				//registration failed. Call GetLastError for the cause of the error
			}
		}
		else if (Msg == WM_INPUT)
		{
			return HandleWMInput(lParam);
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
			diGlobalsInstance->Log("[dinput8] CreateDevice() for GUID_SysMouse",__FILE__,__LINE__);

			*lplpDirectInputDevice = mouseDevice;
			return DI_OK;
		}
		else if (IsEqualIID(GUID_SysKeyboard, *rguid))
		{
			diGlobalsInstance->Log("[dinput8] CreateDevice() for GUID_SysKeyboard",__FILE__,__LINE__);

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
		if (lpCallback(mouseDeviceInfo, pvRef) == DIENUM_STOP)
		{
			//diGlobalsInstance->Log("[dinput8] EnumDevices stopped (due to DIENUM_STOP)",__FILE__,__LINE__);
			return DI_OK;
		}
		if (lpCallback(keyboardDeviceInfo, pvRef) == DIENUM_STOP)
		{
			//diGlobalsInstance->Log("[dinput8] EnumDevices stopped (due to DIENUM_STOP)", __FILE__, __LINE__);
			return DI_OK;
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