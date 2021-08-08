#pragma once

class CDirectInputDeviceGamepad8
{
public:
	DIDATAFORMAT dataFormat;
	ULONG refCount;
	DWORD dwDevType;
	bool isAcquired;

	CDirectInputDeviceGamepad8()
	{
		refCount = 1;
		isAcquired = false;
	}

	virtual HRESULT STDMETHODCALLTYPE Base_QueryInterface(GUID* riid, LPVOID* ppvObj)
	{
		diGlobalsInstance->LogA("GamepadDevice->QueryInterface()", __FILE__, __LINE__);

		return S_OK;
	};

	virtual ULONG __stdcall Base_AddRef()
	{
		diGlobalsInstance->LogA("GamepadDevice->AddRef()", __FILE__, __LINE__);
		refCount++;

		return refCount;
	}

	virtual ULONG __stdcall Base_Release()
	{
		diGlobalsInstance->LogA("GamepadDevice->Release()", __FILE__, __LINE__);

		refCount--;

		return refCount;
	}


	virtual HRESULT STDMETHODCALLTYPE Base_GetCapabilities(LPDIDEVCAPS lpDIDevCaps) {
		diGlobalsInstance->LogA("GamepadDevice->GetCapabilities()", __FILE__, __LINE__);

		lpDIDevCaps->dwFlags = DIDC_ATTACHED | DIDC_EMULATED;
		lpDIDevCaps->dwDevType = this->dwDevType;
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

	virtual HRESULT STDMETHODCALLTYPE Base_GetProperty(GUID* rguidProp, LPDIPROPHEADER pdiph) {
		diGlobalsInstance->LogA("GamepadDevice->GetProperty()", __FILE__, __LINE__);

		return E_NOTIMPL;
	}

	virtual HRESULT STDMETHODCALLTYPE Base_SetProperty(GUID* rguidProp, LPCDIPROPHEADER pdiph) {
		diGlobalsInstance->LogA("GamepadDevice->SetProperty()", __FILE__, __LINE__);

		return E_NOTIMPL;
	}

	virtual HRESULT STDMETHODCALLTYPE Base_Acquire() {
		diGlobalsInstance->LogA("GamepadDevice->Acquire()", __FILE__, __LINE__);		

		this->isAcquired = true;

		return DI_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE Base_Unacquire() {
		diGlobalsInstance->LogA("GamepadDevice->Unacquire()", __FILE__, __LINE__);

		this->isAcquired = false;

		return DI_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE Base_GetDeviceState(DWORD cbData, LPVOID lpvData) {
		diGlobalsInstance->LogA("GamepadDevice->GetDeviceState()", __FILE__, __LINE__);

		if (!this->isAcquired)
		{
			return DIERR_INPUTLOST;
		}

		diGlobalsInstance->Lock();
		{
			ZeroMemory(lpvData, cbData);

			diGlobalsInstance->gamepadState->lX = 0;
			diGlobalsInstance->gamepadState->lY = 0;
			diGlobalsInstance->gamepadState->lZ = 0;
			diGlobalsInstance->gamepadState->lRx = 0;
			diGlobalsInstance->gamepadState->lRy = 0;
			diGlobalsInstance->gamepadState->lRz = 0;
			diGlobalsInstance->gamepadState->rglSlider[0] = 0;
			diGlobalsInstance->gamepadState->rglSlider[1] = 0;
			diGlobalsInstance->gamepadState->rgdwPOV[0] = -1;
			diGlobalsInstance->gamepadState->rgdwPOV[1] = -1;
			diGlobalsInstance->gamepadState->rgdwPOV[2] = -1;
			diGlobalsInstance->gamepadState->rgdwPOV[3] = -1;
			for (int i = 0; i < 32; i++)
			{
				diGlobalsInstance->gamepadState->rgbButtons[i] = 0;
			}

			if (cbData == sizeof(DIJOYSTATE))
			{
				memcpy(lpvData, diGlobalsInstance->gamepadState, sizeof(DIJOYSTATE));
			}
			else if (cbData == sizeof(DIJOYSTATE2))
			{
				memcpy(lpvData, diGlobalsInstance->gamepadState, sizeof(DIJOYSTATE2));
			}
			else {
				diGlobalsInstance->LogA("GamepadDevice->GetDeviceState(): Unsupported cbData: %i", __FILE__, __LINE__,cbData);
				return DIERR_UNSUPPORTED;
			}
		}
		diGlobalsInstance->Unlock();

		return DI_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE Base_GetDeviceData(DWORD cbObjectData, LPDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD dwFlags) {
		diGlobalsInstance->LogA("GamepadDevice->GetDeviceData()", __FILE__, __LINE__);

		*pdwInOut = 0;

		return DI_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE Base_SetDataFormat(LPCDIDATAFORMAT lpdf)
	{
		diGlobalsInstance->LogA("GamepadDevice->SetDataFormat()", __FILE__, __LINE__);
		memcpy(&dataFormat, lpdf, sizeof(DIDATAFORMAT));
		return DI_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE Base_SetEventNotification(HANDLE hEvent)
	{
		diGlobalsInstance->LogA("GamepadDevice->SetEventNotification()", __FILE__, __LINE__);

		return E_NOTIMPL;
	}

	virtual HRESULT STDMETHODCALLTYPE Base_SetCooperativeLevel(HWND hwnd, DWORD dwFlags)
	{
		diGlobalsInstance->LogA("GamepadDevice->SetCooperativeLevel(), dwFlags: %x", __FILE__, __LINE__, dwFlags);
		return DI_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE Base_RunControlPanel(HWND hwndOwner, DWORD dwFlags)
	{
		diGlobalsInstance->LogA("GamepadDevice->RunControlPanel()", __FILE__, __LINE__);

		return E_NOTIMPL;
	}

	virtual HRESULT STDMETHODCALLTYPE Base_Initialize(HINSTANCE hInst, DWORD dwVersion, GUID* rguid)
	{
		diGlobalsInstance->LogA("GamepadDevice->Initialize()", __FILE__, __LINE__);

		return DI_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE Base_CreateEffect(GUID* rguid, LPCDIEFFECT lpeff, LPDIRECTINPUTEFFECT* ppdeff, LPUNKNOWN punkOuter)
	{
		diGlobalsInstance->LogA("GamepadDevice->CreateEffect()", __FILE__, __LINE__);

		return E_NOTIMPL;
	}


	virtual HRESULT STDMETHODCALLTYPE Base_GetForceFeedbackState(LPDWORD pdwOut)
	{
		diGlobalsInstance->LogA("GamepadDevice->GetForceFeedbackState()", __FILE__, __LINE__);

		return E_NOTIMPL;
	}

	virtual HRESULT STDMETHODCALLTYPE Base_SendForceFeedbackCommand(DWORD dwFlags)
	{
		diGlobalsInstance->LogA("GamepadDevice->SendForceFeedbackCommand()", __FILE__, __LINE__);

		return E_NOTIMPL;
	}

	virtual HRESULT STDMETHODCALLTYPE Base_EnumCreatedEffectObjects(LPDIENUMCREATEDEFFECTOBJECTSCALLBACK lpCallback, LPVOID pvRef, DWORD fl)
	{
		diGlobalsInstance->LogA("GamepadDevice->EnumCreatedEffectObjects()", __FILE__, __LINE__);

		return DI_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE Base_Escape(LPDIEFFESCAPE pesc)
	{
		diGlobalsInstance->LogA("GamepadDevice->Escape()", __FILE__, __LINE__);

		return E_NOTIMPL;
	}

	virtual HRESULT STDMETHODCALLTYPE Base_Poll() {
		//diGlobalsInstance->LogA("GamepadDevice->Poll()", __FILE__, __LINE__);

		return DI_NOEFFECT;
	}

	virtual HRESULT STDMETHODCALLTYPE Base_SendDeviceData(DWORD cbObjectData, LPCDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD fl) {
		diGlobalsInstance->LogA("GamepadDevice->SendDeviceData()", __FILE__, __LINE__);

		return E_NOTIMPL;
	}
};