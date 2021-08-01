#pragma once

class CDirectInput8A : public IDirectInput8A, public CDirectInput8
{
private:	
	CDirectInputDeviceMouse8A* mouseDevice;
	CDirectInputDeviceKeyboard8A* keyboardDevice;
	CDirectInputDeviceGamepad8A* gamepadDevice;

	DIDEVICEINSTANCEA mouseDeviceInfo = {};
	DIDEVICEINSTANCEA keyboardDeviceInfo = {};
	DIDEVICEINSTANCEA gamepadDeviceInfo = {};

public:		
		

	CDirectInput8A() : CDirectInput8()
	{	
		mouseDevice= new CDirectInputDeviceMouse8A();
		keyboardDevice=new CDirectInputDeviceKeyboard8A();
		gamepadDevice = new CDirectInputDeviceGamepad8A();
	}

	virtual HRESULT STDMETHODCALLTYPE QueryInterface(GUID* riid, LPVOID* ppvObj)
	{
		return Base_QueryInterface(riid, ppvObj);
	}

	virtual ULONG __stdcall AddRef()
	{
		return Base_AddRef();
	}

	virtual ULONG __stdcall Release()
	{
		return Base_Release();
	}

	virtual HRESULT STDMETHODCALLTYPE GetDeviceStatus(GUID* rguidInstance)
	{
		return Base_GetDeviceStatus(rguidInstance);
	}

	virtual HRESULT STDMETHODCALLTYPE RunControlPanel(HWND hwndOwner, DWORD dwFlags)
	{
		return Base_RunControlPanel(hwndOwner, dwFlags);
	}

	virtual HRESULT STDMETHODCALLTYPE Initialize(HINSTANCE hinst, DWORD dwVersion)
	{
		return Base_Initialize(hinst, dwVersion);
	}

	
	virtual HRESULT STDMETHODCALLTYPE CreateDevice(GUID* rguid, LPDIRECTINPUTDEVICE8A* lplpDirectInputDevice, LPUNKNOWN pUnkOuter)
	{
		if (IsEqualIID(GUID_SysMouse, *rguid))
		{
			diGlobalsInstance->LogA("CreateDevice() for GUID_SysMouse",__FILE__,__LINE__);

			*lplpDirectInputDevice = mouseDevice;
			return DI_OK;
		}
		else if (IsEqualIID(GUID_SysKeyboard, *rguid))
		{
			diGlobalsInstance->LogA("CreateDevice() for GUID_SysKeyboard",__FILE__,__LINE__);

			*lplpDirectInputDevice = keyboardDevice;
			return DI_OK;
		}
		
		diGlobalsInstance->LogA("CreateDevice() for rguid = % x - % x - % x - % x",__FILE__,__LINE__, rguid->Data1, rguid->Data2, rguid->Data3, rguid->Data4);
		return E_ABORT;
	}

	virtual HRESULT STDMETHODCALLTYPE EnumDevices(DWORD dwDevType, LPDIENUMDEVICESCALLBACKA lpCallback, LPVOID pvRef, DWORD dwFlags)
	{	
		//diGlobalsInstance->LogA("EnumDevices() for dwDevType=%x, dwFlags=%x", __FILE__, __LINE__, dwDevType, dwFlags);

		if ((dwDevType == DI8DEVCLASS_ALL) || (dwDevType == DI8DEVCLASS_POINTER) || (dwDevType == DI8DEVTYPE_MOUSE))
		{	
			diGlobalsInstance->LogA("EnumDevices: Returning Mouse-Device", __FILE__, __LINE__);

			mouseDevice->GetDeviceInfo(&mouseDeviceInfo);
			if (lpCallback(&mouseDeviceInfo, pvRef) == DIENUM_STOP)
			{
				diGlobalsInstance->LogA("EnumDevices stopped (due to DIENUM_STOP)",__FILE__,__LINE__);
				return DI_OK;
			}
		}

		if ((dwDevType == DI8DEVCLASS_ALL) || (dwDevType == DI8DEVCLASS_KEYBOARD))
		{
			diGlobalsInstance->LogA("EnumDevices: Returning Keyboard-Device", __FILE__, __LINE__);

			keyboardDevice->GetDeviceInfo(&keyboardDeviceInfo);
			if (lpCallback(&keyboardDeviceInfo, pvRef) == DIENUM_STOP)
			{
				diGlobalsInstance->LogA("EnumDevices stopped (due to DIENUM_STOP)", __FILE__, __LINE__);
				return DI_OK;
			}
		}

		if (diGlobalsInstance->enableGamepadSupport)
		{
			if ((dwDevType == DI8DEVCLASS_ALL) || (dwDevType == DI8DEVCLASS_GAMECTRL))
			{
				diGlobalsInstance->LogA("EnumDevices: Returning Gamepad-Device", __FILE__, __LINE__);

				gamepadDevice->GetDeviceInfo(&gamepadDeviceInfo);
				if (lpCallback(&gamepadDeviceInfo, pvRef) == DIENUM_STOP)
				{
					diGlobalsInstance->LogA("EnumDevices stopped (due to DIENUM_STOP)", __FILE__, __LINE__);
					return DI_OK;
				}
			}
		}

		return DI_OK;
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