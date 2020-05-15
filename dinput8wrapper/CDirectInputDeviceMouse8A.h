#pragma once

class CDirectInputDeviceMouse8A : public IDirectInputDevice8A
{
private:
	DIDEVICEINSTANCEA* mouseDeviceInfo;
	DIDATAFORMAT dataFormat;
	int refCount;

public:

	CDirectInputDeviceMouse8A()
	{
		mouseDeviceInfo = new DIDEVICEINSTANCEA();
		ZeroMemory(mouseDeviceInfo, sizeof(DIDEVICEINSTANCEA));
		mouseDeviceInfo->dwSize = sizeof(DIDEVICEINSTANCEA);
		mouseDeviceInfo->guidInstance = GUID_SysMouse;
		mouseDeviceInfo->guidProduct = GUID_SysMouse;
		mouseDeviceInfo->dwDevType = DI8DEVTYPE_MOUSE | (DI8DEVTYPEMOUSE_UNKNOWN << 8);
		StringCbCopyA(mouseDeviceInfo->tszInstanceName, 260, "Mouse");
		StringCbCopyA(mouseDeviceInfo->tszProductName, 260, "Mouse");

		ZeroMemory(&dataFormat, sizeof(DIDATAFORMAT));
		refCount = 1;
	}

	virtual HRESULT STDMETHODCALLTYPE QueryInterface(GUID* riid, LPVOID* ppvObj)
	{
		diGlobalsInstance->Log("MouseDevice->QueryInterface()", __FILE__, __LINE__);

		return S_OK;
	};

	virtual ULONG __stdcall AddRef()
	{
		diGlobalsInstance->Log("MouseDevice->AddRef()", __FILE__, __LINE__);
		refCount++;

		return refCount;
	}

	virtual ULONG __stdcall Release()
	{
		diGlobalsInstance->Log("MouseDevice->Release()", __FILE__, __LINE__);

		refCount--;

		return refCount;
	}


	virtual HRESULT STDMETHODCALLTYPE GetCapabilities(LPDIDEVCAPS lpDIDevCaps) {
		diGlobalsInstance->Log("MouseDevice->GetCapabilities()", __FILE__, __LINE__);

		lpDIDevCaps->dwFlags = DIDC_ATTACHED | DIDC_EMULATED;
		lpDIDevCaps->dwDevType = mouseDeviceInfo->dwDevType;
		lpDIDevCaps->dwAxes = 3;
		lpDIDevCaps->dwButtons = 3;
		lpDIDevCaps->dwPOVs = 0;
		lpDIDevCaps->dwFFSamplePeriod = 0;
		lpDIDevCaps->dwFFMinTimeResolution = 0;
		lpDIDevCaps->dwFirmwareRevision = 0;
		lpDIDevCaps->dwHardwareRevision = 0;
		lpDIDevCaps->dwFFDriverVersion = 0;

		return DI_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE EnumObjects(LPDIENUMDEVICEOBJECTSCALLBACKA lpCallback, LPVOID pvRef, DWORD dwFlags) {

		diGlobalsInstance->Log("MouseDevice->EnumObjects()", __FILE__, __LINE__);

		return DI_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE GetProperty(GUID* rguidProp, LPDIPROPHEADER pdiph) {
		diGlobalsInstance->Log("MouseDevice->GetProperty()", __FILE__, __LINE__);

		return E_NOTIMPL;
	}

	virtual HRESULT STDMETHODCALLTYPE SetProperty(GUID* rguidProp, LPCDIPROPHEADER pdiph) {
		diGlobalsInstance->Log("MouseDevice->SetProperty()", __FILE__, __LINE__);

		return E_NOTIMPL;
	}

	virtual HRESULT STDMETHODCALLTYPE Acquire() {
		//diGlobalsInstance->Log("MouseDevice->Acquire()", __FILE__, __LINE__);

		HWND hWnd = GetForegroundWindow();
		SetCapture(hWnd);

		return DI_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE Unacquire() {
		//diGlobalsInstance->Log("MouseDevice->Unacquire()", __FILE__, __LINE__);

		ReleaseCapture();

		return DI_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE GetDeviceState(DWORD cbData, LPVOID lpvData) {
		//diGlobalsInstance->Log("MouseDevice->GetDeviceState()");

		diGlobalsInstance->Lock();
		{
			memcpy(lpvData, diGlobalsInstance->mouseState, sizeof(DIMOUSESTATE));

			diGlobalsInstance->mouseState->lX = 0;
			diGlobalsInstance->mouseState->lY = 0;
			diGlobalsInstance->mouseState->lZ = 0;
		}
		diGlobalsInstance->Unlock();

		return DI_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE GetDeviceData(DWORD cbObjectData, LPDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD dwFlags) {
		diGlobalsInstance->Log("MouseDevice->GetDeviceData()", __FILE__, __LINE__);

		*pdwInOut = 0;

		return DI_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE SetDataFormat(LPCDIDATAFORMAT lpdf)
	{
		diGlobalsInstance->Log("MouseDevice->SetDataFormat()", __FILE__, __LINE__);
		memcpy(&dataFormat, lpdf, sizeof(DIDATAFORMAT));
		return DI_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE SetEventNotification(HANDLE hEvent)
	{
		diGlobalsInstance->Log("MouseDevice->SetEventNotification()", __FILE__, __LINE__);

		return E_NOTIMPL;
	}

	virtual HRESULT STDMETHODCALLTYPE SetCooperativeLevel(HWND hwnd, DWORD dwFlags)
	{
		diGlobalsInstance->Log("MouseDevice->SetCooperativeLevel()", __FILE__, __LINE__);
		return DI_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE GetObjectInfo(LPDIDEVICEOBJECTINSTANCEA pdidoi, DWORD dwObj, DWORD dwHow)
	{
		diGlobalsInstance->Log("MouseDevice->GetObjectInfo()", __FILE__, __LINE__);

		return E_NOTIMPL;
	}

	virtual HRESULT STDMETHODCALLTYPE GetDeviceInfo(LPDIDEVICEINSTANCEA pdidi)
	{
		diGlobalsInstance->Log("MouseDevice->GetDeviceInfo()", __FILE__, __LINE__);
		memcpy(pdidi, mouseDeviceInfo, sizeof(DIDEVICEINSTANCEA));

		return DI_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE RunControlPanel(HWND hwndOwner, DWORD dwFlags)
	{
		diGlobalsInstance->Log("MouseDevice->RunControlPanel()", __FILE__, __LINE__);

		return E_NOTIMPL;
	}

	virtual HRESULT STDMETHODCALLTYPE Initialize(HINSTANCE hInst, DWORD dwVersion, GUID* rguid)
	{
		diGlobalsInstance->Log("MouseDevice->Initialize()", __FILE__, __LINE__);

		return DI_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE CreateEffect(GUID* rguid, LPCDIEFFECT lpeff, LPDIRECTINPUTEFFECT* ppdeff, LPUNKNOWN punkOuter)
	{
		diGlobalsInstance->Log("MouseDevice->CreateEffect()", __FILE__, __LINE__);

		return E_NOTIMPL;
	}

	virtual HRESULT STDMETHODCALLTYPE EnumEffects(LPDIENUMEFFECTSCALLBACKA lpCallback, LPVOID pvRef, DWORD dwEffType)
	{
		diGlobalsInstance->Log("MouseDevice->EnumEffects()", __FILE__, __LINE__);

		return DI_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE GetEffectInfo(LPDIEFFECTINFOA pdei, GUID* rguid)
	{
		diGlobalsInstance->Log("MouseDevice->GetEffectInfo()", __FILE__, __LINE__);

		return E_NOTIMPL;
	}

	virtual HRESULT STDMETHODCALLTYPE GetForceFeedbackState(LPDWORD pdwOut)
	{
		diGlobalsInstance->Log("MouseDevice->GetForceFeedbackState()", __FILE__, __LINE__);

		return E_NOTIMPL;
	}

	virtual HRESULT STDMETHODCALLTYPE SendForceFeedbackCommand(DWORD dwFlags)
	{
		diGlobalsInstance->Log("MouseDevice->SendForceFeedbackCommand()", __FILE__, __LINE__);

		return E_NOTIMPL;
	}

	virtual HRESULT STDMETHODCALLTYPE EnumCreatedEffectObjects(LPDIENUMCREATEDEFFECTOBJECTSCALLBACK lpCallback, LPVOID pvRef, DWORD fl)
	{
		diGlobalsInstance->Log("MouseDevice->EnumCreatedEffectObjects()", __FILE__, __LINE__);

		return DI_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE Escape(LPDIEFFESCAPE pesc)
	{
		diGlobalsInstance->Log("MouseDevice->Escape()", __FILE__, __LINE__);

		return E_NOTIMPL;
	}

	virtual HRESULT STDMETHODCALLTYPE Poll() {
		//diGlobalsInstance->Log("MouseDevice->Poll()", __FILE__, __LINE__);

		return DI_NOEFFECT;
	}

	virtual HRESULT STDMETHODCALLTYPE SendDeviceData(DWORD cbObjectData, LPCDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD fl) {
		diGlobalsInstance->Log("MouseDevice->SendDeviceData()", __FILE__, __LINE__);

		return E_NOTIMPL;
	}

	virtual HRESULT STDMETHODCALLTYPE EnumEffectsInFile(LPCSTR lpszFileName, LPDIENUMEFFECTSINFILECALLBACK pec, LPVOID pvRef, DWORD dwFlags)
	{
		diGlobalsInstance->Log("MouseDevice->EnumEffectsInFile()", __FILE__, __LINE__);

		return E_NOTIMPL;
	}

	virtual HRESULT STDMETHODCALLTYPE WriteEffectToFile(LPCSTR lpszFileName, DWORD dwEntries, LPDIFILEEFFECT rgDiFileEft, DWORD dwFlags)
	{
		diGlobalsInstance->Log("MouseDevice->WriteEffectToFile()", __FILE__, __LINE__);

		return E_NOTIMPL;
	}

	virtual HRESULT STDMETHODCALLTYPE BuildActionMap(LPDIACTIONFORMATA lpdiaf, LPCSTR lpszUserName, DWORD dwFlags)
	{
		diGlobalsInstance->Log("MouseDevice->BuildActionMap()", __FILE__, __LINE__);

		return E_NOTIMPL;
	}

	virtual HRESULT STDMETHODCALLTYPE SetActionMap(LPDIACTIONFORMATA lpdiaf, LPCSTR lpszUserName, DWORD dwFlags)
	{
		diGlobalsInstance->Log("MouseDevice->SetActionMap()", __FILE__, __LINE__);

		return E_NOTIMPL;
	}

	virtual HRESULT STDMETHODCALLTYPE GetImageInfo(LPDIDEVICEIMAGEINFOHEADERA lpdiDevImageInfoHeader)
	{
		diGlobalsInstance->Log("MouseDevice->GetImageInfo()", __FILE__, __LINE__);

		return E_NOTIMPL;
	}
};