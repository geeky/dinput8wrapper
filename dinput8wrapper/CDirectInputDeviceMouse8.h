#pragma once

class CDirectInputDeviceMouse8
{
private:
	DIDATAFORMAT dataFormat;
	int refCount;
	bool exclusiveMode;
	bool isAquired;
	HWND hWndForegroundWindow;

public:

	DWORD dwDevType;

	CDirectInputDeviceMouse8()
	{
		ZeroMemory(&dataFormat, sizeof(DIDATAFORMAT));
		refCount = 1;
		exclusiveMode = false;
		isAquired = false;
		hWndForegroundWindow = NULL;
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
		diGlobalsInstance->LogA("-> dwHow: %x", __FILE__,__LINE__,pdiph->dwHow);
		diGlobalsInstance->LogA("-> dwObj: %x", __FILE__, __LINE__, pdiph->dwObj);		

		return E_NOTIMPL;
	}

	HRESULT STDMETHODCALLTYPE Base_Acquire() {
		diGlobalsInstance->LogA("MouseDevice->Acquire()", __FILE__, __LINE__);

		this->hWndForegroundWindow = GetForegroundWindow();	
		
		this->Base_AcquireInternal();
		this->isAquired = true;

		return DI_OK;
	}

	void Base_AcquireInternal()
	{
		if (!this->isAquired)
		{
			return;
		}

		// Initial mouse capture
		// (Or capture lost due to 'ALT+TAB'-ing)
		HWND hWndCapture = GetCapture();
		if (hWndCapture != this->hWndForegroundWindow)
		{
			SetCapture(this->hWndForegroundWindow);

			if (this->exclusiveMode)
			{
				ShowCursor(false);
			}
		}
	}

	HRESULT STDMETHODCALLTYPE Base_Unacquire() {
		diGlobalsInstance->LogA("MouseDevice->Unacquire()", __FILE__, __LINE__);

		ReleaseCapture();

		if (this->exclusiveMode)
		{
			ShowCursor(true);
		}

		this->isAquired = false;

		return DI_OK;
	}

	HRESULT STDMETHODCALLTYPE Base_GetDeviceState(DWORD cbData, LPVOID lpvData) {
		diGlobalsInstance->LogA("MouseDevice->GetDeviceState()", __FILE__, __LINE__);

		if (!this->isAquired)
		{
			diGlobalsInstance->LogA("MouseDevice->GetDeviceState(): DIERR_INPUTLOST", __FILE__, __LINE__);
			return DIERR_INPUTLOST;
		}

		this->Base_AcquireInternal();

		diGlobalsInstance->Lock();
		{
			// Copy current state to lpvData
			memcpy(lpvData, diGlobalsInstance->mouseStateDeviceData, sizeof(DIMOUSESTATE));

			// Set axis movement to zero:
			// (=Mark last movement data as fetched)
			diGlobalsInstance->mouseStateDeviceData->lX = 0;
			diGlobalsInstance->mouseStateDeviceData->lY = 0;
			diGlobalsInstance->mouseStateDeviceData->lZ = 0;
		}
		diGlobalsInstance->Unlock();

		return DI_OK;
	}

	HRESULT STDMETHODCALLTYPE Base_GetDeviceData(DWORD cbObjectData, LPDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD dwFlags) {
		//diGlobalsInstance->LogA("MouseDevice->GetDeviceData()", __FILE__, __LINE__);

		if (!this->isAquired)
		{
			diGlobalsInstance->LogA("MouseDevice->GetDeviceData(): DIERR_INPUTLOST", __FILE__, __LINE__);
			return DIERR_INPUTLOST;
		}

		this->Base_AcquireInternal();

		if (cbObjectData != sizeof(DIDEVICEOBJECTDATA))
		{
			diGlobalsInstance->LogA("MouseDevice->GetDeviceData(): Unexpected cbObjectData", __FILE__, __LINE__);
			return DIERR_INVALIDPARAM;
		}

		bool peekOnly = false;

		if (dwFlags > 0)
		{
			char tmp[1024];
			wsprintfA(tmp, "MouseDevice->GetDeviceData(): dwFlags=%x", dwFlags);
			diGlobalsInstance->LogA(tmp, __FILE__, __LINE__);
		}

		int dwOut = 0;

		// Determine timestamp:
		__int64 fTime = 0;
		GetSystemTimeAsFileTime((FILETIME*)&fTime);
		fTime = fTime / 1000;

		diGlobalsInstance->Lock();
		{
			if ((*pdwInOut == 0) && (rgdod == NULL))
			{
				diGlobalsInstance->LogA("MouseDevice->GetDeviceData() checking for overflow", __FILE__, __LINE__);
			}
			else if ((*pdwInOut == INFINITE) && (rgdod == NULL))
			{
				// Flush buffer:
				diGlobalsInstance->LogA("MouseDevice->GetDeviceData() flushing buffer", __FILE__, __LINE__);

				ZeroMemory(diGlobalsInstance->keyStates, sizeof(diGlobalsInstance->keyStates));
				ZeroMemory(diGlobalsInstance->gameKeyStates, sizeof(diGlobalsInstance->gameKeyStates));
			}
			else
			{
				memset(rgdod, 0, *pdwInOut * sizeof(DIDEVICEOBJECTDATA));

				if (true)
				{
					for (DWORD i = 0; i < *pdwInOut; i++)
					{
						if (diGlobalsInstance->mouseStateDeviceData->lX != 0)
						{
							//diGlobalsInstance->LogA("MouseDevice->GetDeviceData() sending DIMOFS_X: %i", __FILE__, __LINE__, diGlobalsInstance->mouseStateDeviceData->lX);

							rgdod[i].dwData = diGlobalsInstance->mouseStateDeviceData->lX;
							rgdod[i].dwOfs = DIMOFS_X;
							rgdod[i].dwSequence = diGlobalsInstance->dwSequence;
							rgdod[i].dwTimeStamp = (DWORD)fTime;
							rgdod[i].uAppData = NULL;

							diGlobalsInstance->dwSequence++;
							diGlobalsInstance->mouseStateDeviceData->lX = 0;
							dwOut++;
						}
						else if (diGlobalsInstance->mouseStateDeviceData->lY != 0)
						{
							//diGlobalsInstance->LogA("MouseDevice->GetDeviceData() sending DIMOFS_Y: %i", __FILE__, __LINE__, diGlobalsInstance->mouseStateDeviceData->lY);

							rgdod[i].dwData = diGlobalsInstance->mouseStateDeviceData->lY;
							rgdod[i].dwOfs = DIMOFS_Y;
							rgdod[i].dwSequence = diGlobalsInstance->dwSequence;
							rgdod[i].dwTimeStamp = (DWORD)fTime;
							rgdod[i].uAppData = NULL;

							diGlobalsInstance->dwSequence++;
							diGlobalsInstance->mouseStateDeviceData->lY = 0;
							dwOut++;
						}
						else if (diGlobalsInstance->mouseStateDeviceData->lZ != 0)
						{
							//diGlobalsInstance->LogA("MouseDevice->GetDeviceData() sending DIMOFS_Z: %i", __FILE__, __LINE__, diGlobalsInstance->mouseStateDeviceData->lZ);

							rgdod[i].dwData = diGlobalsInstance->mouseStateDeviceData->lZ;
							rgdod[i].dwOfs = DIMOFS_Z;
							rgdod[i].dwSequence = diGlobalsInstance->dwSequence;
							rgdod[i].dwTimeStamp = (DWORD)fTime;
							rgdod[i].uAppData = NULL;

							diGlobalsInstance->dwSequence++;
							diGlobalsInstance->mouseStateDeviceData->lZ = 0;
							dwOut++;
						}
						else if (diGlobalsInstance->mouseStateDeviceData->rgbButtons[0] != diGlobalsInstance->mouseStateDeviceDataGame->rgbButtons[0]) {
							//diGlobalsInstance->LogA("MouseDevice->GetDeviceData() sending DIMOFS_BUTTON0: %i", __FILE__, __LINE__, diGlobalsInstance->mouseStateDeviceData->rgbButtons[0]);

							rgdod[i].dwData = diGlobalsInstance->mouseStateDeviceData->rgbButtons[0];
							rgdod[i].dwOfs = DIMOFS_BUTTON0;
							rgdod[i].dwSequence = diGlobalsInstance->dwSequence;
							rgdod[i].dwTimeStamp = (DWORD)fTime;
							rgdod[i].uAppData = NULL;

							diGlobalsInstance->dwSequence++;
							diGlobalsInstance->mouseStateDeviceDataGame->rgbButtons[0] = diGlobalsInstance->mouseStateDeviceData->rgbButtons[0];
							dwOut++;
						}
						else if (diGlobalsInstance->mouseStateDeviceData->rgbButtons[1] != diGlobalsInstance->mouseStateDeviceDataGame->rgbButtons[1]) {
							//diGlobalsInstance->LogA("MouseDevice->GetDeviceData() sending DIMOFS_BUTTON1: %i", __FILE__, __LINE__, diGlobalsInstance->mouseStateDeviceData->rgbButtons[1]);

							rgdod[i].dwData = diGlobalsInstance->mouseStateDeviceData->rgbButtons[1];
							rgdod[i].dwOfs = DIMOFS_BUTTON1;
							rgdod[i].dwSequence = diGlobalsInstance->dwSequence;
							rgdod[i].dwTimeStamp = (DWORD)fTime;
							rgdod[i].uAppData = NULL;

							diGlobalsInstance->dwSequence++;
							diGlobalsInstance->mouseStateDeviceDataGame->rgbButtons[1] = diGlobalsInstance->mouseStateDeviceData->rgbButtons[1];
							dwOut++;
						}
						else if (diGlobalsInstance->mouseStateDeviceData->rgbButtons[2] != diGlobalsInstance->mouseStateDeviceDataGame->rgbButtons[2]) {
							//diGlobalsInstance->LogA("MouseDevice->GetDeviceData() sending DIMOFS_BUTTON2: %i", __FILE__, __LINE__, diGlobalsInstance->mouseStateDeviceData->rgbButtons[2]);

							rgdod[i].dwData = diGlobalsInstance->mouseStateDeviceData->rgbButtons[2];
							rgdod[i].dwOfs = DIMOFS_BUTTON2;
							rgdod[i].dwSequence = diGlobalsInstance->dwSequence;
							rgdod[i].dwTimeStamp = (DWORD)fTime;
							rgdod[i].uAppData = NULL;

							diGlobalsInstance->dwSequence++;
							diGlobalsInstance->mouseStateDeviceDataGame->rgbButtons[2] = diGlobalsInstance->mouseStateDeviceData->rgbButtons[2];
							dwOut++;
						}
					}
				}
			}
		}
		diGlobalsInstance->Unlock();

		*pdwInOut = dwOut;
		return DI_OK;
	}

	HRESULT STDMETHODCALLTYPE Base_SetDataFormat(LPCDIDATAFORMAT lpdf)
	{
		diGlobalsInstance->LogA("MouseDevice->SetDataFormat()", __FILE__, __LINE__);
		memcpy(&dataFormat, lpdf, sizeof(DIDATAFORMAT));
		diGlobalsInstance->LogA("- dwFlags: %x", __FILE__, __LINE__,dataFormat.dwFlags);
		diGlobalsInstance->LogA("- dwNumObjs: %i", __FILE__, __LINE__, dataFormat.dwNumObjs);
		diGlobalsInstance->LogA("- dwSize: %i", __FILE__, __LINE__, dataFormat.dwSize);
		diGlobalsInstance->LogA("- dwDataSize: %i", __FILE__, __LINE__, dataFormat.dwDataSize);
		diGlobalsInstance->LogA("- dwObjSize: %i", __FILE__, __LINE__, dataFormat.dwObjSize);
		return DI_OK;
	}

	HRESULT STDMETHODCALLTYPE Base_SetEventNotification(HANDLE hEvent)
	{
		diGlobalsInstance->LogA("MouseDevice->SetEventNotification(hEvent: %x)", __FILE__, __LINE__,hEvent);
		diGlobalsInstance->Lock();
		{
			diGlobalsInstance->mouseEventHandle = hEvent;
		}
		diGlobalsInstance->Unlock();

		return E_NOTIMPL;
	}

	HRESULT STDMETHODCALLTYPE Base_SetCooperativeLevel(HWND hwnd, DWORD dwFlags)
	{
		diGlobalsInstance->LogA("MouseDevice->SetCooperativeLevel(dwFlags: %x)", __FILE__, __LINE__, dwFlags);
		diGlobalsInstance->LogA("-> DISCL_EXCLUSIVE: %i", __FILE__, __LINE__, (dwFlags & DISCL_EXCLUSIVE) ? 1 :0);
		diGlobalsInstance->LogA("-> DISCL_BACKGROUND: %i", __FILE__, __LINE__, (dwFlags & DISCL_BACKGROUND) ? 1 :0);
		diGlobalsInstance->LogA("-> DISCL_FOREGROUND: %i", __FILE__, __LINE__, (dwFlags & DISCL_FOREGROUND) ? 1 : 0);
		diGlobalsInstance->LogA("-> DISCL_NONEXCLUSIVE: %i", __FILE__, __LINE__, (dwFlags & DISCL_NONEXCLUSIVE) ? 1 : 0);
		diGlobalsInstance->LogA("-> DISCL_NOWINKEY: %i", __FILE__, __LINE__, (dwFlags & DISCL_NOWINKEY) ? 1 : 0);

		this->exclusiveMode = ((dwFlags & DISCL_EXCLUSIVE) > 0);		
		
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
		diGlobalsInstance->LogA("MouseDevice->Poll()", __FILE__, __LINE__);

		return DI_NOEFFECT;
	}

	HRESULT STDMETHODCALLTYPE Base_SendDeviceData(DWORD cbObjectData, LPCDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD fl) {
		diGlobalsInstance->LogA("MouseDevice->SendDeviceData() - unhandled", __FILE__, __LINE__);		

		return E_NOTIMPL;
	}
};