#pragma once

class CDirectInputDeviceGamepad8A : public IDirectInputDevice8A
{
private:
	DIDEVICEINSTANCEA* gamepadDeviceInfo;
	DIDATAFORMAT dataFormat;
	ULONG refCount;

public:

	CDirectInputDeviceGamepad8A()
	{
		refCount = 1;

		gamepadDeviceInfo = new DIDEVICEINSTANCEA();
		ZeroMemory(gamepadDeviceInfo, sizeof(DIDEVICEINSTANCEA));
		gamepadDeviceInfo->dwSize = sizeof(DIDEVICEINSTANCEA);
		gamepadDeviceInfo->guidInstance = GUID_Xbox360Controller;
		gamepadDeviceInfo->guidProduct = GUID_Xbox360Controller;
		gamepadDeviceInfo->dwDevType = DIDEVTYPE_HID | DI8DEVTYPE_GAMEPAD | (DI8DEVTYPEGAMEPAD_STANDARD << 8);
		gamepadDeviceInfo->wUsage = HID_USAGE_GENERIC_GAMEPAD;
		gamepadDeviceInfo->wUsagePage = HID_USAGE_PAGE_GENERIC;
		StringCbCopyA(gamepadDeviceInfo->tszInstanceName, 260, "Controller (Gamepad XBox360)");
		StringCbCopyA(gamepadDeviceInfo->tszProductName, 260, "Controller (Gamepad XBox360)");
	}

	virtual HRESULT STDMETHODCALLTYPE QueryInterface(GUID* riid, LPVOID* ppvObj)
	{
		diGlobalsInstance->Log("GamepadDevice->QueryInterface()", __FILE__, __LINE__);

		return S_OK;
	};

	virtual ULONG __stdcall AddRef()
	{
		diGlobalsInstance->Log("GamepadDevice->AddRef()", __FILE__, __LINE__);
		refCount++;

		return refCount;
	}

	virtual ULONG __stdcall Release()
	{
		diGlobalsInstance->Log("GamepadDevice->Release()", __FILE__, __LINE__);

		refCount--;

		return refCount;
	}


	virtual HRESULT STDMETHODCALLTYPE GetCapabilities(LPDIDEVCAPS lpDIDevCaps) {
		diGlobalsInstance->Log("GamepadDevice->GetCapabilities()", __FILE__, __LINE__);

		lpDIDevCaps->dwFlags = DIDC_ATTACHED | DIDC_EMULATED;
		lpDIDevCaps->dwDevType = gamepadDeviceInfo->dwDevType;
		lpDIDevCaps->dwAxes = 5;
		lpDIDevCaps->dwButtons = 10;
		lpDIDevCaps->dwPOVs = 1;
		lpDIDevCaps->dwFFSamplePeriod = 0;
		lpDIDevCaps->dwFFMinTimeResolution = 0;
		lpDIDevCaps->dwFirmwareRevision = 0;
		lpDIDevCaps->dwHardwareRevision = 0;
		lpDIDevCaps->dwFFDriverVersion = 0;

		return DI_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE EnumObjects(LPDIENUMDEVICEOBJECTSCALLBACKA lpCallback, LPVOID pvRef, DWORD dwFlags) {

		diGlobalsInstance->Log("GamepadDevice->EnumObjects()", __FILE__, __LINE__);

		return DI_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE GetProperty(GUID* rguidProp, LPDIPROPHEADER pdiph) {
		diGlobalsInstance->Log("GamepadDevice->GetProperty()", __FILE__, __LINE__);

		return E_NOTIMPL;
	}

	virtual HRESULT STDMETHODCALLTYPE SetProperty(GUID* rguidProp, LPCDIPROPHEADER pdiph) {
		diGlobalsInstance->Log("GamepadDevice->SetProperty()", __FILE__, __LINE__);

		return E_NOTIMPL;
	}

	virtual HRESULT STDMETHODCALLTYPE Acquire() {
		//diGlobalsInstance->Log("GamepadDevice->Acquire()", __FILE__, __LINE__);

		HWND hWnd = GetForegroundWindow();
		SetCapture(hWnd);

		return DI_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE Unacquire() {
		//diGlobalsInstance->Log("GamepadDevice->Unacquire()", __FILE__, __LINE__);

		ReleaseCapture();

		return DI_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE GetDeviceState(DWORD cbData, LPVOID lpvData) {
		diGlobalsInstance->Log("GamepadDevice->GetDeviceState()",__FILE__,__LINE__);		

		return DI_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE GetDeviceData(DWORD cbObjectData, LPDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD dwFlags) {
		diGlobalsInstance->Log("GamepadDevice->GetDeviceData()", __FILE__, __LINE__);

		*pdwInOut = 0;

		return DI_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE SetDataFormat(LPCDIDATAFORMAT lpdf)
	{
		diGlobalsInstance->Log("GamepadDevice->SetDataFormat()", __FILE__, __LINE__);
		memcpy(&dataFormat, lpdf, sizeof(DIDATAFORMAT));
		return DI_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE SetEventNotification(HANDLE hEvent)
	{
		diGlobalsInstance->Log("GamepadDevice->SetEventNotification()", __FILE__, __LINE__);

		return E_NOTIMPL;
	}

	virtual HRESULT STDMETHODCALLTYPE SetCooperativeLevel(HWND hwnd, DWORD dwFlags)
	{
		diGlobalsInstance->Log("GamepadDevice->SetCooperativeLevel()", __FILE__, __LINE__);
		return DI_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE GetObjectInfo(LPDIDEVICEOBJECTINSTANCEA pdidoi, DWORD dwObj, DWORD dwHow)
	{
		diGlobalsInstance->Log("GamepadDevice->GetObjectInfo()", __FILE__, __LINE__);

		return E_NOTIMPL;
	}

	virtual HRESULT STDMETHODCALLTYPE GetDeviceInfo(LPDIDEVICEINSTANCEA pdidi)
	{
		diGlobalsInstance->Log("GamepadDevice->GetDeviceInfo()", __FILE__, __LINE__);
		memcpy(pdidi, gamepadDeviceInfo, sizeof(DIDEVICEINSTANCEA));

		return DI_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE RunControlPanel(HWND hwndOwner, DWORD dwFlags)
	{
		diGlobalsInstance->Log("GamepadDevice->RunControlPanel()", __FILE__, __LINE__);

		return E_NOTIMPL;
	}

	virtual HRESULT STDMETHODCALLTYPE Initialize(HINSTANCE hInst, DWORD dwVersion, GUID* rguid)
	{
		diGlobalsInstance->Log("GamepadDevice->Initialize()", __FILE__, __LINE__);

		return DI_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE CreateEffect(GUID* rguid, LPCDIEFFECT lpeff, LPDIRECTINPUTEFFECT* ppdeff, LPUNKNOWN punkOuter)
	{
		diGlobalsInstance->Log("GamepadDevice->CreateEffect()", __FILE__, __LINE__);

		return E_NOTIMPL;
	}

	virtual HRESULT STDMETHODCALLTYPE EnumEffects(LPDIENUMEFFECTSCALLBACKA lpCallback, LPVOID pvRef, DWORD dwEffType)
	{
		diGlobalsInstance->Log("GamepadDevice->EnumEffects()", __FILE__, __LINE__);

		return DI_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE GetEffectInfo(LPDIEFFECTINFOA pdei, GUID* rguid)
	{
		diGlobalsInstance->Log("GamepadDevice->GetEffectInfo()", __FILE__, __LINE__);

		return E_NOTIMPL;
	}

	virtual HRESULT STDMETHODCALLTYPE GetForceFeedbackState(LPDWORD pdwOut)
	{
		diGlobalsInstance->Log("GamepadDevice->GetForceFeedbackState()", __FILE__, __LINE__);

		return E_NOTIMPL;
	}

	virtual HRESULT STDMETHODCALLTYPE SendForceFeedbackCommand(DWORD dwFlags)
	{
		diGlobalsInstance->Log("GamepadDevice->SendForceFeedbackCommand()", __FILE__, __LINE__);

		return E_NOTIMPL;
	}

	virtual HRESULT STDMETHODCALLTYPE EnumCreatedEffectObjects(LPDIENUMCREATEDEFFECTOBJECTSCALLBACK lpCallback, LPVOID pvRef, DWORD fl)
	{
		diGlobalsInstance->Log("GamepadDevice->EnumCreatedEffectObjects()", __FILE__, __LINE__);

		return DI_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE Escape(LPDIEFFESCAPE pesc)
	{
		diGlobalsInstance->Log("GamepadDevice->Escape()", __FILE__, __LINE__);

		return E_NOTIMPL;
	}

	virtual HRESULT STDMETHODCALLTYPE Poll() {
		//diGlobalsInstance->Log("GamepadDevice->Poll()", __FILE__, __LINE__);

		return DI_NOEFFECT;
	}

	virtual HRESULT STDMETHODCALLTYPE SendDeviceData(DWORD cbObjectData, LPCDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD fl) {
		diGlobalsInstance->Log("GamepadDevice->SendDeviceData()", __FILE__, __LINE__);

		return E_NOTIMPL;
	}

	virtual HRESULT STDMETHODCALLTYPE EnumEffectsInFile(LPCSTR lpszFileName, LPDIENUMEFFECTSINFILECALLBACK pec, LPVOID pvRef, DWORD dwFlags)
	{
		diGlobalsInstance->Log("GamepadDevice->EnumEffectsInFile()", __FILE__, __LINE__);

		return E_NOTIMPL;
	}

	virtual HRESULT STDMETHODCALLTYPE WriteEffectToFile(LPCSTR lpszFileName, DWORD dwEntries, LPDIFILEEFFECT rgDiFileEft, DWORD dwFlags)
	{
		diGlobalsInstance->Log("GamepadDevice->WriteEffectToFile()", __FILE__, __LINE__);

		return E_NOTIMPL;
	}

	virtual HRESULT STDMETHODCALLTYPE BuildActionMap(LPDIACTIONFORMATA lpdiaf, LPCSTR lpszUserName, DWORD dwFlags)
	{
		diGlobalsInstance->Log("GamepadDevice->BuildActionMap()", __FILE__, __LINE__);

		return E_NOTIMPL;
	}

	virtual HRESULT STDMETHODCALLTYPE SetActionMap(LPDIACTIONFORMATA lpdiaf, LPCSTR lpszUserName, DWORD dwFlags)
	{
		diGlobalsInstance->Log("GamepadDevice->SetActionMap()", __FILE__, __LINE__);

		return E_NOTIMPL;
	}

	virtual HRESULT STDMETHODCALLTYPE GetImageInfo(LPDIDEVICEIMAGEINFOHEADERA lpdiDevImageInfoHeader)
	{
		diGlobalsInstance->Log("GamepadDevice->GetImageInfo()", __FILE__, __LINE__);

		return E_NOTIMPL;
	}
};