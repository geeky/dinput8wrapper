// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    DllHModule = hModule;

    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

extern "C" HRESULT WINAPI DllCanUnloadNow() { return S_FALSE; }

extern "C" HRESULT WINAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv) 
{
    return E_ABORT;
}

extern "C" HRESULT WINAPI DllRegisterServer() {
    return E_ABORT;
}

extern "C" HRESULT WINAPI DllUnregisterServer() {
    return E_ABORT;
}

extern "C" LPCDIDATAFORMAT WINAPI GetdfDIJoystick() {
    return NULL;
}

HRESULT WINAPI DirectInput8Create(HINSTANCE hinst, DWORD dwVersion, GUID* riidltf, LPVOID* ppvOut, LPUNKNOWN punkOuter)
{
    IID IID_IDirectInput8A = { 0xBF798030, 0x483A, 0x4DA2, 0xAA, 0x99, 0x5D, 0x64, 0xED, 0x36, 0x97, 0x00 };

    if (IsEqualIID(IID_IDirectInput8A, *riidltf))
    {
        CDirectInput8A* obj = new CDirectInput8A();

        *ppvOut = obj;

        return DI_OK;
    }
    else
    {
        char tmp[256];
        StringCbPrintfA(tmp, 256, "Unsupported REFIID: %x %x %x %x", riidltf->Data1, riidltf->Data2, riidltf->Data3, riidltf->Data4);
        MessageBoxA(NULL, tmp, "dinput8wrapper", MB_OK);
    }

    return DIERR_INVALIDPARAM;
}