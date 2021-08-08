#pragma once

class CDirectInputDeviceKeyboard8A : public IDirectInputDevice8A, public CDirectInputDeviceKeyboard8
{
private:
	DIDEVICEINSTANCEA* keyboardDeviceInfo;	

public:

	CDirectInputDeviceKeyboard8A() : CDirectInputDeviceKeyboard8()
	{		
		keyboardDeviceInfo = new DIDEVICEINSTANCEA();
		ZeroMemory(keyboardDeviceInfo, sizeof(DIDEVICEINSTANCEA));
		keyboardDeviceInfo->dwSize = sizeof(DIDEVICEINSTANCEA);
		keyboardDeviceInfo->guidInstance = GUID_SysKeyboard;
		keyboardDeviceInfo->guidProduct = GUID_SysKeyboard;
		keyboardDeviceInfo->dwDevType = DI8DEVTYPE_KEYBOARD | (DIDEVTYPEKEYBOARD_PCENH << 8);
		StringCbCopyA(keyboardDeviceInfo->tszInstanceName, 260, "Keyboard");
		StringCbCopyA(keyboardDeviceInfo->tszProductName, 260, "Keyboard");

		this->dwDevType = keyboardDeviceInfo->dwDevType;
	}


	virtual HRESULT STDMETHODCALLTYPE QueryInterface(GUID* riid, LPVOID* ppvObj)
	{
		return Base_QueryInterface(riid, ppvObj);
	};

	virtual ULONG STDMETHODCALLTYPE AddRef()
	{
		return Base_AddRef();
	}

	virtual ULONG STDMETHODCALLTYPE Release()
	{
		return Base_Release();
	}


	virtual HRESULT STDMETHODCALLTYPE GetCapabilities(LPDIDEVCAPS lpDIDevCaps) {
		return Base_GetCapabilities(lpDIDevCaps);
	}

	virtual HRESULT STDMETHODCALLTYPE GetProperty(GUID* rguidProp, LPDIPROPHEADER pdiph) {

		return Base_GetProperty(rguidProp, pdiph);
	}

	virtual HRESULT STDMETHODCALLTYPE SetProperty(GUID* rguidProp, LPCDIPROPHEADER pdiph) {
		return Base_SetProperty(rguidProp, pdiph);
	}

	virtual HRESULT STDMETHODCALLTYPE Acquire() {
		return Base_Acquire();
	}

	virtual HRESULT STDMETHODCALLTYPE Unacquire() {
		return Base_Unacquire();
	}

	virtual HRESULT STDMETHODCALLTYPE GetDeviceState(DWORD cbData, LPVOID lpvData) {
		return Base_GetDeviceState(cbData, lpvData);
	}

	virtual HRESULT STDMETHODCALLTYPE GetDeviceData(DWORD cbObjectData, LPDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD dwFlags)
	{
		return Base_GetDeviceData(cbObjectData, rgdod, pdwInOut, dwFlags);
	}

	virtual HRESULT STDMETHODCALLTYPE SetDataFormat(LPCDIDATAFORMAT lpdf)
	{
		return Base_SetDataFormat(lpdf);
	}

	virtual HRESULT STDMETHODCALLTYPE SetEventNotification(HANDLE hEvent)
	{
		return Base_SetEventNotification(hEvent);
	}

	virtual HRESULT STDMETHODCALLTYPE SetCooperativeLevel(HWND hwnd, DWORD dwFlags)
	{
		return Base_SetCooperativeLevel(hwnd, dwFlags);
	}

	virtual HRESULT STDMETHODCALLTYPE RunControlPanel(HWND hwndOwner, DWORD dwFlags)
	{
		return Base_RunControlPanel(hwndOwner, dwFlags);
	}

	virtual HRESULT STDMETHODCALLTYPE Initialize(HINSTANCE hinst, DWORD dwVersion, GUID* rguid)
	{
		return Base_Initialize(hinst, dwVersion, rguid);
	}

	virtual HRESULT STDMETHODCALLTYPE CreateEffect(GUID* rguid, LPCDIEFFECT lpeff, LPDIRECTINPUTEFFECT* ppdeff, LPUNKNOWN punkOuter)
	{
		return Base_CreateEffect(rguid, lpeff, ppdeff, punkOuter);
	}

	virtual HRESULT STDMETHODCALLTYPE GetForceFeedbackState(LPDWORD pdwOut)
	{
		return Base_GetForceFeedbackState(pdwOut);
	}

	virtual HRESULT STDMETHODCALLTYPE SendForceFeedbackCommand(DWORD dwFlags)
	{
		return Base_SendForceFeedbackCommand(dwFlags);
	}

	virtual HRESULT STDMETHODCALLTYPE EnumCreatedEffectObjects(LPDIENUMCREATEDEFFECTOBJECTSCALLBACK lpCallback, LPVOID pvRef, DWORD fl)
	{
		return Base_EnumCreatedEffectObjects(lpCallback, pvRef, fl);
	}

	virtual HRESULT STDMETHODCALLTYPE Escape(LPDIEFFESCAPE pesc)
	{
		return Base_Escape(pesc);
	}

	virtual HRESULT STDMETHODCALLTYPE Poll() {
		return Base_Poll();
	}

	virtual HRESULT STDMETHODCALLTYPE SendDeviceData(DWORD cbObjectData, LPCDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD fl) {
		return Base_SendDeviceData(cbObjectData, rgdod, pdwInOut, fl);
	}






	virtual HRESULT STDMETHODCALLTYPE EnumObjects(LPDIENUMDEVICEOBJECTSCALLBACKA lpCallback, LPVOID pvRef, DWORD dwFlags) {

		diGlobalsInstance->LogA("KeyboardDevice->EnumObjects()", __FILE__, __LINE__);
		return DI_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE GetObjectInfo(LPDIDEVICEOBJECTINSTANCEA pdidoi, DWORD dwObj, DWORD dwHow)
	{
		diGlobalsInstance->LogA("KeyboardDevice->GetObjectInfo(dwObj: %x, dwHow: %x)", __FILE__, __LINE__,dwObj,dwHow);

		ZeroMemory(pdidoi, sizeof(DIDEVICEOBJECTINSTANCEW));

		// dwHow: 1, dwObj: 200 

		if (dwHow == DIPH_BYOFFSET)
		{
			pdidoi->dwSize = sizeof(DIDEVICEOBJECTINSTANCEW);
			pdidoi->guidType = GUID_Key;
			pdidoi->dwOfs = dwObj;
			pdidoi->dwType = DIDFT_BUTTON;
			diGlobalsInstance->GetKeyNameA(dwObj, pdidoi->tszName);
			return DI_OK;
		}

		return DIERR_UNSUPPORTED;
	}

	virtual HRESULT STDMETHODCALLTYPE GetDeviceInfo(LPDIDEVICEINSTANCEA pdidi)
	{
		diGlobalsInstance->LogA("KeyboardDevice->GetDeviceInfo()", __FILE__, __LINE__);
		memcpy(pdidi, keyboardDeviceInfo, sizeof(DIDEVICEINSTANCEA));

		return DI_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE EnumEffects(LPDIENUMEFFECTSCALLBACKA lpCallback, LPVOID pvRef, DWORD dwEffType)
	{
		diGlobalsInstance->LogA("KeyboardDevice->EnumEffects()", __FILE__, __LINE__);

		return DI_OK;
	}

	virtual HRESULT STDMETHODCALLTYPE GetEffectInfo(LPDIEFFECTINFOA pdei, GUID* rguid)
	{
		diGlobalsInstance->LogA("KeyboardDevice->GetEffectInfo()", __FILE__, __LINE__);

		return DIERR_UNSUPPORTED;
	}

	virtual HRESULT STDMETHODCALLTYPE EnumEffectsInFile(LPCSTR lpszFileName, LPDIENUMEFFECTSINFILECALLBACK pec, LPVOID pvRef, DWORD dwFlags)
	{
		diGlobalsInstance->LogA("KeyboardDevice->EnumEffectsInFile()", __FILE__, __LINE__);

		return DIERR_UNSUPPORTED;
	}

	virtual HRESULT STDMETHODCALLTYPE WriteEffectToFile(LPCSTR lpszFileName, DWORD dwEntries, LPDIFILEEFFECT rgDiFileEft, DWORD dwFlags)
	{
		diGlobalsInstance->LogA("KeyboardDevice->WriteEffectToFile()", __FILE__, __LINE__);

		return DIERR_UNSUPPORTED;
	}

	virtual HRESULT STDMETHODCALLTYPE BuildActionMap(LPDIACTIONFORMATA lpdiaf, LPCSTR lpszUserName, DWORD dwFlags)
	{
		diGlobalsInstance->LogA("KeyboardDevice->BuildActionMap()", __FILE__, __LINE__);

		return DIERR_UNSUPPORTED;
	}

	virtual HRESULT STDMETHODCALLTYPE SetActionMap(LPDIACTIONFORMATA lpdiaf, LPCSTR lpszUserName, DWORD dwFlags)
	{
		diGlobalsInstance->LogA("KeyboardDevice->SetActionMap()", __FILE__, __LINE__);

		return DIERR_UNSUPPORTED;
	}

	virtual HRESULT STDMETHODCALLTYPE GetImageInfo(LPDIDEVICEIMAGEINFOHEADERA lpdiDevImageInfoHeader)
	{
		diGlobalsInstance->LogA("KeyboardDevice->GetImageInfo()", __FILE__, __LINE__);

		return DIERR_UNSUPPORTED;
	}
};