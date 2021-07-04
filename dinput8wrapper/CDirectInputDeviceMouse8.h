#pragma once

class CDirectInputDeviceMouse8
{
private:
	DIDATAFORMAT dataFormat;
	int refCount;

public:

	DWORD dwDevType;

	CDirectInputDeviceMouse8()
	{
		ZeroMemory(&dataFormat, sizeof(DIDATAFORMAT));
		refCount = 1;
	}

	HRESULT STDMETHODCALLTYPE Base_QueryInterface(GUID* riid, LPVOID* ppvObj)
	{
		diGlobalsInstance->LogA("MouseDevice->QueryInterface()", __FILE__, __LINE__);

		return S_OK;
	};

	ULONG __stdcall Base_AddRef()
	{
		diGlobalsInstance->LogA("MouseDevice->AddRef()", __FILE__, __LINE__);
		refCount++;

		return refCount;
	}

	ULONG __stdcall Base_Release()
	{
		diGlobalsInstance->LogA("MouseDevice->Release()", __FILE__, __LINE__);

		refCount--;

		return refCount;
	}


	HRESULT STDMETHODCALLTYPE Base_GetCapabilities(LPDIDEVCAPS lpDIDevCaps) {
		diGlobalsInstance->LogA("MouseDevice->GetCapabilities()", __FILE__, __LINE__);

		lpDIDevCaps->dwFlags = DIDC_ATTACHED | DIDC_EMULATED;
		lpDIDevCaps->dwDevType = this->dwDevType;
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

	HRESULT STDMETHODCALLTYPE Base_GetProperty(GUID* rguidProp, LPDIPROPHEADER pdiph) {
		diGlobalsInstance->LogA("MouseDevice->GetProperty()", __FILE__, __LINE__);

		return E_NOTIMPL;
	}

	HRESULT STDMETHODCALLTYPE Base_SetProperty(GUID* rguidProp, LPCDIPROPHEADER pdiph) {
		diGlobalsInstance->LogA("MouseDevice->SetProperty()", __FILE__, __LINE__);

		return E_NOTIMPL;
	}

	HRESULT STDMETHODCALLTYPE Base_Acquire() {
		//diGlobalsInstance->LogA("MouseDevice->Acquire()", __FILE__, __LINE__);

		HWND hWnd = GetForegroundWindow();
		SetCapture(hWnd);

		return DI_OK;
	}

	HRESULT STDMETHODCALLTYPE Base_Unacquire() {
		//diGlobalsInstance->LogA("MouseDevice->Unacquire()", __FILE__, __LINE__);

		ReleaseCapture();

		return DI_OK;
	}

	HRESULT STDMETHODCALLTYPE Base_GetDeviceState(DWORD cbData, LPVOID lpvData) {
		//diGlobalsInstance->LogA("MouseDevice->GetDeviceState()");

		diGlobalsInstance->Lock();
		{
			// Copy current state to lpvData
			memcpy(lpvData, diGlobalsInstance->mouseState, sizeof(DIMOUSESTATE));

			// Reset current state:
			diGlobalsInstance->mouseState->lX = 0;
			diGlobalsInstance->mouseState->lY = 0;
			diGlobalsInstance->mouseState->lZ = 0;
		}
		diGlobalsInstance->Unlock();

		return DI_OK;
	}

	HRESULT STDMETHODCALLTYPE Base_GetDeviceData(DWORD cbObjectData, LPDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD dwFlags) {
		diGlobalsInstance->LogA("MouseDevice->GetDeviceData()", __FILE__, __LINE__);

		*pdwInOut = 0;

		return DI_OK;
	}

	HRESULT STDMETHODCALLTYPE Base_SetDataFormat(LPCDIDATAFORMAT lpdf)
	{
		diGlobalsInstance->LogA("MouseDevice->SetDataFormat()", __FILE__, __LINE__);
		memcpy(&dataFormat, lpdf, sizeof(DIDATAFORMAT));
		return DI_OK;
	}

	HRESULT STDMETHODCALLTYPE Base_SetEventNotification(HANDLE hEvent)
	{
		diGlobalsInstance->LogA("MouseDevice->SetEventNotification()", __FILE__, __LINE__);

		return E_NOTIMPL;
	}

	HRESULT STDMETHODCALLTYPE Base_SetCooperativeLevel(HWND hwnd, DWORD dwFlags)
	{
		if (dwFlags & DISCL_EXCLUSIVE)
		{
			ShowCursor(false);
		}
		else {
			ShowCursor(true);
		}

		diGlobalsInstance->LogA("MouseDevice->SetCooperativeLevel()", __FILE__, __LINE__);
		return DI_OK;
	}

	HRESULT STDMETHODCALLTYPE Base_RunControlPanel(HWND hwndOwner, DWORD dwFlags)
	{
		diGlobalsInstance->LogA("MouseDevice->RunControlPanel()", __FILE__, __LINE__);

		return E_NOTIMPL;
	}

	HRESULT STDMETHODCALLTYPE Base_Initialize(HINSTANCE hInst, DWORD dwVersion, GUID* rguid)
	{
		diGlobalsInstance->LogA("MouseDevice->Initialize()", __FILE__, __LINE__);

		return DI_OK;
	}

	HRESULT STDMETHODCALLTYPE Base_CreateEffect(GUID* rguid, LPCDIEFFECT lpeff, LPDIRECTINPUTEFFECT* ppdeff, LPUNKNOWN punkOuter)
	{
		diGlobalsInstance->LogA("MouseDevice->CreateEffect()", __FILE__, __LINE__);

		return E_NOTIMPL;
	}

	HRESULT STDMETHODCALLTYPE Base_GetForceFeedbackState(LPDWORD pdwOut)
	{
		diGlobalsInstance->LogA("MouseDevice->GetForceFeedbackState()", __FILE__, __LINE__);

		return E_NOTIMPL;
	}

	HRESULT STDMETHODCALLTYPE Base_SendForceFeedbackCommand(DWORD dwFlags)
	{
		diGlobalsInstance->LogA("MouseDevice->SendForceFeedbackCommand()", __FILE__, __LINE__);

		return E_NOTIMPL;
	}

	HRESULT STDMETHODCALLTYPE Base_EnumCreatedEffectObjects(LPDIENUMCREATEDEFFECTOBJECTSCALLBACK lpCallback, LPVOID pvRef, DWORD fl)
	{
		diGlobalsInstance->LogA("MouseDevice->EnumCreatedEffectObjects()", __FILE__, __LINE__);

		return E_NOTIMPL;
	}

	HRESULT STDMETHODCALLTYPE Base_Escape(LPDIEFFESCAPE pesc)
	{
		diGlobalsInstance->LogA("MouseDevice->Escape()", __FILE__, __LINE__);

		return E_NOTIMPL;
	}

	HRESULT STDMETHODCALLTYPE Base_Poll() {
		//diGlobalsInstance->LogA("MouseDevice->Poll()", __FILE__, __LINE__);

		return DI_NOEFFECT;
	}

	HRESULT STDMETHODCALLTYPE Base_SendDeviceData(DWORD cbObjectData, LPCDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD fl) {
		diGlobalsInstance->LogA("MouseDevice->SendDeviceData()", __FILE__, __LINE__);

		return E_NOTIMPL;
	}
};