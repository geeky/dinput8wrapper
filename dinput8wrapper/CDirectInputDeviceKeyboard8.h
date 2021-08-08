#pragma once

class CDirectInputDeviceKeyboard8
{
public:

	ULONG refCount;
	DWORD dwDevType;

	CDirectInputDeviceKeyboard8()
	{
		refCount = 1;
	}

	virtual HRESULT STDMETHODCALLTYPE Base_QueryInterface(GUID* riid, LPVOID* ppvObj)
	{
		diGlobalsInstance->LogA("KeyboardDevice->QueryInterface()", __FILE__, __LINE__);

		return E_NOINTERFACE;
	};

	virtual ULONG STDMETHODCALLTYPE Base_AddRef()
	{
		diGlobalsInstance->LogA("KeyboardDevice->AddRef()", __FILE__, __LINE__);

		refCount++;

		return refCount;
	}

	virtual ULONG STDMETHODCALLTYPE Base_Release()
	{
		diGlobalsInstance->LogA("KeyboardDevice->Release()", __FILE__, __LINE__);

		refCount--;

		return refCount;
	}


	virtual HRESULT STDMETHODCALLTYPE Base_GetCapabilities(LPDIDEVCAPS lpDIDevCaps) {
		diGlobalsInstance->LogA("KeyboardDevice->GetCapabilities()", __FILE__, __LINE__);

		lpDIDevCaps->dwFlags = DIDC_ATTACHED | DIDC_EMULATED;
		lpDIDevCaps->dwDevType = this->dwDevType;
		lpDIDevCaps->dwAxes = 0;
		lpDIDevCaps->dwButtons = 128;
		lpDIDevCaps->dwPOVs = 0;
		lpDIDevCaps->dwFFSamplePeriod = 0;
		lpDIDevCaps->dwFFMinTimeResolution = 0;
		lpDIDevCaps->dwFirmwareRevision = 0;
		lpDIDevCaps->dwHardwareRevision = 0;
		lpDIDevCaps->dwFFDriverVersion = 0;

		return DI_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE Base_GetProperty(GUID* rguidProp, LPDIPROPHEADER pdiph) {

		char tmp[4096];

		int propId = (int)rguidProp;

		if (propId == 0x14) // // 0x14 = DIPROP_PRODUCTNAME
		{
			DIPROPSTRING* strProp = (DIPROPSTRING*)pdiph;

			if (pdiph->dwHow == DIPH_DEVICE)
			{
				lstrcpyW(strProp->wsz, L"Keyboard");
				return DI_OK;
			}
			else if (pdiph->dwHow == DIPH_BYOFFSET)
			{
				diGlobalsInstance->GetKeyNameW(pdiph->dwObj, strProp->wsz);
				return DI_OK;
			}
		}

		wsprintfA(tmp, "KeyboardDevice->GetProperty() unhandled guid: %x, dwHow: %x", propId, pdiph->dwHow);
		diGlobalsInstance->LogA(tmp, __FILE__, __LINE__);

		return DIERR_UNSUPPORTED;
	}

	virtual HRESULT STDMETHODCALLTYPE Base_SetProperty(GUID* rguidProp, LPCDIPROPHEADER pdiph) {
		char tmp[4096];

		if ((int)rguidProp == 0x01) // DIPROP_BUFFERSIZE
		{
			// Buffer-Size
			LPDIPROPDWORD propDword = (LPDIPROPDWORD)pdiph;

			wsprintfA(tmp, "KeyboardDevice->SetProperty(): DI_BUFFERSIZE (dwData=%u)", propDword->dwData);
			diGlobalsInstance->LogA(tmp, __FILE__, __LINE__);

			// Currently ignored

			return DI_OK;
		}

		wsprintfA(tmp, "KeyboardDevice->SetProperty(): %x", rguidProp);
		diGlobalsInstance->LogA(tmp, __FILE__, __LINE__);

		return DIERR_UNSUPPORTED;
	}

	virtual HRESULT STDMETHODCALLTYPE Base_Acquire() {
		//diGlobalsInstance->LogA("KeyboardDevice->Acquire()", __FILE__, __LINE__);

		diGlobalsInstance->Lock();
		{
			diGlobalsInstance->keyboardAcquired = true;
		}
		diGlobalsInstance->Unlock();

		return DI_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE Base_Unacquire() {
		//diGlobalsInstance->LogA("KeyboardDevice->Unacquire()", __FILE__, __LINE__);

		diGlobalsInstance->Lock();
		{
			diGlobalsInstance->keyboardAcquired = false;
		}
		diGlobalsInstance->Unlock();

		return DI_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE Base_GetDeviceState(DWORD cbData, LPVOID lpvData) {
		//diGlobalsInstance->LogA("KeyboardDevice->GetDeviceState()", __FILE__, __LINE__);

		if (cbData <= sizeof(diGlobalsInstance->keyStates))
		{
			memcpy(lpvData, diGlobalsInstance->keyStates, cbData);
		}
		else
		{
			diGlobalsInstance->LogA("KeyboardDevice->GetDeviceState(): cbData too large", __FILE__, __LINE__);
		}

		return DI_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE Base_GetDeviceData(DWORD cbObjectData, LPDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD dwFlags)
	{
		if (cbObjectData != sizeof(DIDEVICEOBJECTDATA))
		{
			diGlobalsInstance->LogA("KeyboardDevice->GetDeviceData(): Unexpected cbObjectData", __FILE__, __LINE__);
			return DIERR_INVALIDPARAM;
		}

		bool peekOnly = false;

		if (dwFlags > 0)
		{
			char tmp[1024];
			wsprintfA(tmp, "KeyboardDevice->GetDeviceData(): dwFlags=%x", dwFlags);
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
				diGlobalsInstance->LogA("KeyboardDevice->GetDeviceData() checking for overflow", __FILE__, __LINE__);
			}
			else if ((*pdwInOut == INFINITE) && (rgdod == NULL))
			{
				// Flush buffer:
				diGlobalsInstance->LogA("KeyboardDevice->GetDeviceData() flushing buffer", __FILE__, __LINE__);

				ZeroMemory(diGlobalsInstance->keyStates, sizeof(diGlobalsInstance->keyStates));
				ZeroMemory(diGlobalsInstance->gameKeyStates, sizeof(diGlobalsInstance->gameKeyStates));
			}
			else
			{
				memset(rgdod, 0, *pdwInOut * sizeof(DIDEVICEOBJECTDATA));

				for (DWORD i = 0; i < *pdwInOut; i++)
				{
					// Check if there is a changed key
					for (int k = 0; k < 256; k++)
					{
						if (diGlobalsInstance->keyStates[k] != diGlobalsInstance->gameKeyStates[k])
						{						

							rgdod[i].dwData = diGlobalsInstance->keyStates[k];
							rgdod[i].dwOfs = k;
							rgdod[i].dwSequence = diGlobalsInstance->dwSequence;
							rgdod[i].dwTimeStamp = (DWORD)fTime;
							rgdod[i].uAppData = NULL;

							diGlobalsInstance->dwSequence++;

							diGlobalsInstance->gameKeyStates[k] = diGlobalsInstance->keyStates[k];

							dwOut++;
							k = 256;
						}
					}
				}
			}
		}
		diGlobalsInstance->Unlock();

		*pdwInOut = dwOut;
		return DI_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE Base_SetDataFormat(LPCDIDATAFORMAT lpdf)
	{
		diGlobalsInstance->LogA("KeyboardDevice->SetDataFormat()", __FILE__, __LINE__);
		return DI_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE Base_SetEventNotification(HANDLE hEvent)
	{
		diGlobalsInstance->LogA("KeyboardDevice->SetEventNotification()", __FILE__, __LINE__);

		return DIERR_INVALIDPARAM;
	}

	virtual HRESULT STDMETHODCALLTYPE Base_SetCooperativeLevel(HWND hwnd, DWORD dwFlags)
	{
		diGlobalsInstance->LogA("KeyboardDevice->SetCooperativeLevel()", __FILE__, __LINE__);
		return DI_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE Base_RunControlPanel(HWND hwndOwner, DWORD dwFlags)
	{
		diGlobalsInstance->LogA("KeyboardDevice->RunControlPanel()", __FILE__, __LINE__);

		return DI_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE Base_Initialize(HINSTANCE hinst, DWORD dwVersion, GUID* rguid)
	{
		diGlobalsInstance->LogA("KeyboardDevice->Initialize()", __FILE__, __LINE__);

		return DI_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE Base_CreateEffect(GUID* rguid, LPCDIEFFECT lpeff, LPDIRECTINPUTEFFECT* ppdeff, LPUNKNOWN punkOuter)
	{
		diGlobalsInstance->LogA("KeyboardDevice->CreateEffect()", __FILE__, __LINE__);

		return DIERR_UNSUPPORTED;
	}

	virtual HRESULT STDMETHODCALLTYPE Base_GetForceFeedbackState(LPDWORD pdwOut)
	{
		*pdwOut = DIGFFS_POWEROFF | DIGFFS_EMPTY;

		diGlobalsInstance->LogA("KeyboardDevice->GetForceFeedbackState()", __FILE__, __LINE__);

		return DI_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE Base_SendForceFeedbackCommand(DWORD dwFlags)
	{
		diGlobalsInstance->LogA("KeyboardDevice->SendForceFeedbackCommand()", __FILE__, __LINE__);

		return DI_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE Base_EnumCreatedEffectObjects(LPDIENUMCREATEDEFFECTOBJECTSCALLBACK lpCallback, LPVOID pvRef, DWORD fl)
	{
		diGlobalsInstance->LogA("KeyboardDevice->EnumCreatedEffectObjects()", __FILE__, __LINE__);

		return DI_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE Base_Escape(LPDIEFFESCAPE pesc)
	{
		diGlobalsInstance->LogA("KeyboardDevice->Escape()", __FILE__, __LINE__);

		return DIERR_UNSUPPORTED;
	}

	virtual HRESULT STDMETHODCALLTYPE Base_Poll() {
		diGlobalsInstance->LogA("KeyboardDevice->Poll()", __FILE__, __LINE__);

		return DIERR_UNSUPPORTED;
	}

	virtual HRESULT STDMETHODCALLTYPE Base_SendDeviceData(DWORD cbObjectData, LPCDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD fl) {
		diGlobalsInstance->LogA("KeyboardDevice->SendDeviceData()", __FILE__, __LINE__);

		return DIERR_UNSUPPORTED;
	}
};