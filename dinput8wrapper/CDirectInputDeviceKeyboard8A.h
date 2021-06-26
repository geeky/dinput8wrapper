#pragma once

class CDirectInputDeviceKeyboard8A : public IDirectInputDevice8A
{
private:
	DIDEVICEINSTANCEA* keyboardDeviceInfo;
	ULONG refCount;

public:

	CDirectInputDeviceKeyboard8A()
	{
		refCount = 1;

		keyboardDeviceInfo = new DIDEVICEINSTANCEA();
		ZeroMemory(keyboardDeviceInfo, sizeof(DIDEVICEINSTANCEA));
		keyboardDeviceInfo->dwSize = sizeof(DIDEVICEINSTANCEA);
		keyboardDeviceInfo->guidInstance = GUID_SysKeyboard;
		keyboardDeviceInfo->guidProduct = GUID_SysKeyboard;
		keyboardDeviceInfo->dwDevType = DI8DEVTYPE_KEYBOARD | (DIDEVTYPEKEYBOARD_PCENH << 8);
		StringCbCopyA(keyboardDeviceInfo->tszInstanceName, 260, "Keyboard");
		StringCbCopyA(keyboardDeviceInfo->tszProductName, 260, "Keyboard");
	}

	virtual HRESULT STDMETHODCALLTYPE QueryInterface(GUID* riid, LPVOID* ppvObj)
	{
		diGlobalsInstance->Log("KeyboardDevice->QueryInterface()", __FILE__, __LINE__);

		return E_NOINTERFACE;
	};

	virtual ULONG STDMETHODCALLTYPE AddRef()
	{
		diGlobalsInstance->Log("KeyboardDevice->AddRef()", __FILE__, __LINE__);

		refCount++;

		return refCount;
	}

	virtual ULONG STDMETHODCALLTYPE Release()
	{
		diGlobalsInstance->Log("KeyboardDevice->Release()", __FILE__, __LINE__);

		refCount--;

		return refCount;
	}


	virtual HRESULT STDMETHODCALLTYPE GetCapabilities(LPDIDEVCAPS lpDIDevCaps) {
		diGlobalsInstance->Log("KeyboardDevice->GetCapabilities()", __FILE__, __LINE__);

		lpDIDevCaps->dwFlags = DIDC_ATTACHED | DIDC_EMULATED;
		lpDIDevCaps->dwDevType = keyboardDeviceInfo->dwDevType;
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

	virtual HRESULT STDMETHODCALLTYPE EnumObjects(LPDIENUMDEVICEOBJECTSCALLBACKA lpCallback, LPVOID pvRef, DWORD dwFlags) {

		diGlobalsInstance->Log("KeyboardDevice->EnumObjects()", __FILE__, __LINE__);
		return DI_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE GetProperty(GUID* rguidProp, LPDIPROPHEADER pdiph) {

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
		diGlobalsInstance->Log(tmp, __FILE__, __LINE__);

		return DIERR_UNSUPPORTED;
	}

	virtual HRESULT STDMETHODCALLTYPE SetProperty(GUID* rguidProp, LPCDIPROPHEADER pdiph) {
		char tmp[4096];

		if ((int)rguidProp == 0x01) // DIPROP_BUFFERSIZE
		{
			// Buffer-Size
			LPDIPROPDWORD propDword = (LPDIPROPDWORD)pdiph;

			wsprintfA(tmp, "KeyboardDevice->SetProperty(): DI_BUFFERSIZE (dwData=%u)", propDword->dwData);
			diGlobalsInstance->Log(tmp, __FILE__, __LINE__);

			// Currently ignored

			return DI_OK;
		}

		wsprintfA(tmp, "KeyboardDevice->SetProperty(): %x", rguidProp);
		diGlobalsInstance->Log(tmp, __FILE__, __LINE__);

		return DIERR_UNSUPPORTED;
	}

	virtual HRESULT STDMETHODCALLTYPE Acquire() {
		//diGlobalsInstance->Log("KeyboardDevice->Acquire()", __FILE__, __LINE__);

		diGlobalsInstance->Lock();
		{
			diGlobalsInstance->keyboardAcquired = true;
		}
		diGlobalsInstance->Unlock();

		return DI_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE Unacquire() {
		//diGlobalsInstance->Log("KeyboardDevice->Unacquire()", __FILE__, __LINE__);

		diGlobalsInstance->Lock();
		{
			diGlobalsInstance->keyboardAcquired = false;
		}
		diGlobalsInstance->Unlock();

		return DI_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE GetDeviceState(DWORD cbData, LPVOID lpvData) {
		//diGlobalsInstance->Log("KeyboardDevice->GetDeviceState()", __FILE__, __LINE__);

		if (cbData <= sizeof(diGlobalsInstance->keyStates))
		{
			memcpy(lpvData, diGlobalsInstance->keyStates, cbData);
		}
		else
		{
			diGlobalsInstance->Log("KeyboardDevice->GetDeviceState(): cbData too large", __FILE__, __LINE__);
		}

		return DI_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE GetDeviceData(DWORD cbObjectData, LPDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD dwFlags)
	{
		if (cbObjectData != sizeof(DIDEVICEOBJECTDATA))
		{
			diGlobalsInstance->Log("KeyboardDevice->GetDeviceData(): Unexpected cbObjectData", __FILE__, __LINE__);
			return DIERR_INVALIDPARAM;
		}

		bool peekOnly = false;

		if (dwFlags > 0)
		{
			char tmp[1024];
			wsprintfA(tmp, "KeyboardDevice->GetDeviceData(): dwFlags=%x", dwFlags);
			diGlobalsInstance->Log(tmp, __FILE__, __LINE__);
		}

		int dwOut = 0;

		diGlobalsInstance->Lock();
		{
			if ((*pdwInOut == 0) && (rgdod == NULL))
			{
				diGlobalsInstance->Log("KeyboardDevice->GetDeviceData() checking for overflow", __FILE__, __LINE__);
			}
			else if ((*pdwInOut == INFINITE) && (rgdod == NULL))
			{
				// Flush buffer:
				diGlobalsInstance->Log("KeyboardDevice->GetDeviceData() flushing buffer", __FILE__, __LINE__);

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

							// Determine timestamp:
							__int64 fTime;
							GetSystemTimeAsFileTime((FILETIME*)&fTime);
							fTime = fTime / 1000;

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

	virtual HRESULT STDMETHODCALLTYPE SetDataFormat(LPCDIDATAFORMAT lpdf)
	{
		diGlobalsInstance->Log("KeyboardDevice->SetDataFormat()", __FILE__, __LINE__);
		return DI_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE SetEventNotification(HANDLE hEvent)
	{
		diGlobalsInstance->Log("KeyboardDevice->SetEventNotification()", __FILE__, __LINE__);

		return DIERR_INVALIDPARAM;
	}

	virtual HRESULT STDMETHODCALLTYPE SetCooperativeLevel(HWND hwnd, DWORD dwFlags)
	{
		diGlobalsInstance->Log("KeyboardDevice->SetCooperativeLevel()", __FILE__, __LINE__);
		return DI_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE GetObjectInfo(LPDIDEVICEOBJECTINSTANCEA pdidoi, DWORD dwObj, DWORD dwHow)
	{
		diGlobalsInstance->Log("KeyboardDevice->GetObjectInfo()", __FILE__, __LINE__);

		return DIERR_UNSUPPORTED;
	}

	virtual HRESULT STDMETHODCALLTYPE GetDeviceInfo(LPDIDEVICEINSTANCEA pdidi)
	{
		diGlobalsInstance->Log("KeyboardDevice->GetDeviceInfo()", __FILE__, __LINE__);
		memcpy(pdidi, keyboardDeviceInfo, sizeof(DIDEVICEINSTANCEA));

		return DI_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE RunControlPanel(HWND hwndOwner, DWORD dwFlags)
	{
		diGlobalsInstance->Log("KeyboardDevice->RunControlPanel()", __FILE__, __LINE__);

		return DI_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE Initialize(HINSTANCE hinst, DWORD dwVersion, GUID* rguid)
	{
		diGlobalsInstance->Log("KeyboardDevice->Initialize()", __FILE__, __LINE__);

		return DI_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE CreateEffect(GUID* rguid, LPCDIEFFECT lpeff, LPDIRECTINPUTEFFECT* ppdeff, LPUNKNOWN punkOuter)
	{
		diGlobalsInstance->Log("KeyboardDevice->CreateEffect()", __FILE__, __LINE__);

		return DIERR_UNSUPPORTED;
	}

	virtual HRESULT STDMETHODCALLTYPE EnumEffects(LPDIENUMEFFECTSCALLBACKA lpCallback, LPVOID pvRef, DWORD dwEffType)
	{
		diGlobalsInstance->Log("KeyboardDevice->EnumEffects()", __FILE__, __LINE__);

		return DI_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE GetEffectInfo(LPDIEFFECTINFOA pdei, GUID* rguid)
	{
		diGlobalsInstance->Log("KeyboardDevice->GetEffectInfo()", __FILE__, __LINE__);

		return DIERR_UNSUPPORTED;
	}

	virtual HRESULT STDMETHODCALLTYPE GetForceFeedbackState(LPDWORD pdwOut)
	{
		*pdwOut = DIGFFS_POWEROFF | DIGFFS_EMPTY;

		diGlobalsInstance->Log("[dinput8] KeyboardDevice->GetForceFeedbackState()", __FILE__, __LINE__);

		return DI_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE SendForceFeedbackCommand(DWORD dwFlags)
	{
		diGlobalsInstance->Log("[dinput8] KeyboardDevice->SendForceFeedbackCommand()", __FILE__, __LINE__);

		return DI_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE EnumCreatedEffectObjects(LPDIENUMCREATEDEFFECTOBJECTSCALLBACK lpCallback, LPVOID pvRef, DWORD fl)
	{
		diGlobalsInstance->Log("[dinput8] KeyboardDevice->EnumCreatedEffectObjects()", __FILE__, __LINE__);

		return DI_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE Escape(LPDIEFFESCAPE pesc)
	{
		diGlobalsInstance->Log("[dinput8] KeyboardDevice->Escape()", __FILE__, __LINE__);

		return DIERR_UNSUPPORTED;
	}

	virtual HRESULT STDMETHODCALLTYPE Poll() {
		diGlobalsInstance->Log("[dinput8] KeyboardDevice->Poll()" , __FILE__, __LINE__);

		return DIERR_UNSUPPORTED;
	}

	virtual HRESULT STDMETHODCALLTYPE SendDeviceData(DWORD cbObjectData, LPCDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD fl) {
		diGlobalsInstance->Log("[dinput8] KeyboardDevice->SendDeviceData()", __FILE__, __LINE__);

		return DIERR_UNSUPPORTED;
	}

	virtual HRESULT STDMETHODCALLTYPE EnumEffectsInFile(LPCSTR lpszFileName, LPDIENUMEFFECTSINFILECALLBACK pec, LPVOID pvRef, DWORD dwFlags)
	{
		diGlobalsInstance->Log("[dinput8] KeyboardDevice->EnumEffectsInFile()", __FILE__, __LINE__);

		return DIERR_UNSUPPORTED;
	}

	virtual HRESULT STDMETHODCALLTYPE WriteEffectToFile(LPCSTR lpszFileName, DWORD dwEntries, LPDIFILEEFFECT rgDiFileEft, DWORD dwFlags)
	{
		diGlobalsInstance->Log("[dinput8] KeyboardDevice->WriteEffectToFile()", __FILE__, __LINE__);

		return DIERR_UNSUPPORTED;
	}

	virtual HRESULT STDMETHODCALLTYPE BuildActionMap(LPDIACTIONFORMATA lpdiaf, LPCSTR lpszUserName, DWORD dwFlags)
	{
		diGlobalsInstance->Log("[dinput8] KeyboardDevice->BuildActionMap()", __FILE__, __LINE__);

		return DIERR_UNSUPPORTED;
	}

	virtual HRESULT STDMETHODCALLTYPE SetActionMap(LPDIACTIONFORMATA lpdiaf, LPCSTR lpszUserName, DWORD dwFlags)
	{
		diGlobalsInstance->Log("[dinput8] KeyboardDevice->SetActionMap()", __FILE__, __LINE__);

		return DIERR_UNSUPPORTED;
	}

	virtual HRESULT STDMETHODCALLTYPE GetImageInfo(LPDIDEVICEIMAGEINFOHEADERA lpdiDevImageInfoHeader)
	{
		diGlobalsInstance->Log("[dinput8] KeyboardDevice->GetImageInfo()", __FILE__, __LINE__);

		return DIERR_UNSUPPORTED;
	}
};