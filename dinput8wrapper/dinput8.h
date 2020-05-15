#pragma once

#define DEFINE_GUID2(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
        const GUID name \
                = { l, w1, w2, { b1, b2,  b3,  b4,  b5,  b6,  b7,  b8 } }

DEFINE_GUID2(GUID_Key, 0x55728220, 0xD33C, 0x11CF, 0xBF, 0xC7, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00);
DEFINE_GUID2(GUID_SysMouse, 0x6F1D2B60, 0xD5A0, 0x11CF, 0xBF, 0xC7, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00);
DEFINE_GUID2(GUID_SysKeyboard, 0x6F1D2B61, 0xD5A0, 0x11CF, 0xBF, 0xC7, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00);

#define DIPH_DEVICE             0
#define DIPH_BYOFFSET           1

#define DIGFFS_POWEROFF     0x00000080
#define DIGFFS_EMPTY        0x00000001

#define IS_DIPROP(x)    (((ULONG_PTR)(x) >> 16) == 0)

#define MAKEDIPROP(prop)    (*(const GUID *)(prop))
#define DIPROP_BUFFERSIZE   MAKEDIPROP(1)
#define DIPROP_AXISMODE     MAKEDIPROP(2)

#define DIPROPAXISMODE_ABS  0
#define DIPROPAXISMODE_REL  1

#define DIPROP_GRANULARITY  MAKEDIPROP(3)
#define DIPROP_RANGE        MAKEDIPROP(4)
#define DIPROP_DEADZONE     MAKEDIPROP(5)
#define DIPROP_SATURATION   MAKEDIPROP(6)
#define DIPROP_FFGAIN       MAKEDIPROP(7)
#define DIPROP_FFLOAD       MAKEDIPROP(8)
#define DIPROP_AUTOCENTER   MAKEDIPROP(9)

#define DIPROPAUTOCENTER_OFF    0
#define DIPROPAUTOCENTER_ON 1

#define DIPROP_CALIBRATIONMODE  MAKEDIPROP(10)

#define DIPROPCALIBRATIONMODE_COOKED    0
#define DIPROPCALIBRATIONMODE_RAW   1

#define DIPROP_CALIBRATION  MAKEDIPROP(11)
#define DIPROP_GUIDANDPATH  MAKEDIPROP(12)

#define DIPROP_INSTANCENAME     MAKEDIPROP(13)
#define DIPROP_PRODUCTNAME      MAKEDIPROP(14)
#define DIPROP_JOYSTICKID       MAKEDIPROP(15)

#define DIPROP_KEYNAME     MAKEDIPROP(20)
#define DIPROP_CPOINTS     MAKEDIPROP(21)
#define DIPROP_APPDATA     MAKEDIPROP(22)
#define DIPROP_SCANCODE    MAKEDIPROP(23)
#define DIPROP_VIDPID      MAKEDIPROP(24)
#define DIPROP_USERNAME    MAKEDIPROP(25)
#define DIPROP_TYPENAME    MAKEDIPROP(26)

#define DIK_ESCAPE   0x01
#define DIK_1   0x02
#define DIK_2   0x03
#define DIK_3   0x04
#define DIK_4   0x05
#define DIK_5   0x06
#define DIK_6   0x07
#define DIK_7   0x08
#define DIK_8   0x09
#define DIK_9   0x0A
#define DIK_0   0x0B
#define DIK_MINUS   0x0C
#define DIK_EQUALS   0x0D
#define DIK_BACK   0x0E
#define DIK_TAB   0x0F
#define DIK_Q   0x10
#define DIK_W   0x11
#define DIK_E   0x12
#define DIK_R   0x13
#define DIK_T   0x14
#define DIK_Y   0x15
#define DIK_U   0x16
#define DIK_I   0x17
#define DIK_O   0x18
#define DIK_P   0x19
#define DIK_LBRACKET   0x1A
#define DIK_RBRACKET   0x1B
#define DIK_RETURN   0x1C
#define DIK_LCONTROL   0x1D
#define DIK_A   0x1E
#define DIK_S   0x1F
#define DIK_D   0x20
#define DIK_F   0x21
#define DIK_G   0x22
#define DIK_H   0x23
#define DIK_J   0x24
#define DIK_K   0x25
#define DIK_L   0x26
#define DIK_SEMICOLON   0x27
#define DIK_APOSTROPHE   0x28
#define DIK_GRAVE   0x29
#define DIK_LSHIFT   0x2A
#define DIK_BACKSLASH   0x2B
#define DIK_Z   0x2C
#define DIK_X   0x2D
#define DIK_C   0x2E
#define DIK_V   0x2F
#define DIK_B   0x30
#define DIK_N   0x31
#define DIK_M   0x32
#define DIK_COMMA   0x33
#define DIK_PERIOD   0x34
#define DIK_SLASH   0x35
#define DIK_RSHIFT   0x36
#define DIK_MULTIPLY   0x37
#define DIK_LMENU   0x38
#define DIK_SPACE   0x39
#define DIK_CAPITAL   0x3A
#define DIK_F1   0x3B
#define DIK_F2   0x3C
#define DIK_F3   0x3D
#define DIK_F4   0x3E
#define DIK_F5   0x3F
#define DIK_F6   0x40
#define DIK_F7   0x41
#define DIK_F8   0x42
#define DIK_F9   0x43
#define DIK_F10   0x44
#define DIK_NUMLOCK   0x45
#define DIK_SCROLL   0x46
#define DIK_NUMPAD7   0x47
#define DIK_NUMPAD8   0x48
#define DIK_NUMPAD9   0x49
#define DIK_SUBTRACT   0x4A
#define DIK_NUMPAD4   0x4B
#define DIK_NUMPAD5   0x4C
#define DIK_NUMPAD6   0x4D
#define DIK_ADD   0x4E
#define DIK_NUMPAD1   0x4F
#define DIK_NUMPAD2   0x50
#define DIK_NUMPAD3   0x51
#define DIK_NUMPAD0   0x52
#define DIK_DECIMAL   0x53
#define DIK_F11   0x57
#define DIK_F12   0x58
#define DIK_F13   0x64
#define DIK_F14   0x65
#define DIK_F15   0x66
#define DIK_KANA   0x70
#define DIK_CONVERT   0x79
#define DIK_NOCONVERT   0x7B
#define DIK_YEN   0x7D
#define DIK_NUMPADEQUALS   0x8D
#define DIK_CIRCUMFLEX   0x90
#define DIK_AT   0x91
#define DIK_COLON   0x92
#define DIK_UNDERLINE   0x93
#define DIK_KANJI   0x94
#define DIK_STOP   0x95
#define DIK_AX   0x96
#define DIK_UNLABELED   0x97
#define DIK_NUMPADENTER   0x9C
#define DIK_RCONTROL   0x9D
#define DIK_NUMPADCOMMA   0xB3
#define DIK_DIVIDE   0xB5
#define DIK_SYSRQ   0xB7
#define DIK_RMENU   0xB8
#define DIK_PAUSE   0xC5
#define DIK_HOME   0xC7
#define DIK_UP   0xC8
#define DIK_PRIOR   0xC9
#define DIK_LEFT   0xCB
#define DIK_RIGHT   0xCD
#define DIK_END   0xCF
#define DIK_DOWN   0xD0
#define DIK_NEXT   0xD1
#define DIK_INSERT   0xD2
#define DIK_DELETE   0xD3
#define DIK_LWIN   0xDB
#define DIK_RWIN   0xDC
#define DIK_APPS   0xDD
#define DIK_POWER   0xDE
#define DIK_SLEEP   0xDF

#define DI8DEVTYPE_MOUSE            0x12
#define DI8DEVTYPE_KEYBOARD         0x13

#define DI8DEVTYPEMOUSE_UNKNOWN         1
#define DI8DEVTYPEMOUSE_TRADITIONAL     2

#define DIDEVTYPEKEYBOARD_PCENH         4

#define DIENUM_STOP                     0
#define DIENUM_CONTINUE                 1

#define DI_OK                           S_OK
#define DIERR_INVALIDPARAM              E_INVALIDARG
#define DIERR_UNSUPPORTED               E_NOTIMPL
#define DI_NOEFFECT                     S_FALSE

HRESULT WINAPI DirectInput8Create(HINSTANCE hinst, DWORD dwVersion, GUID* riidltf, LPVOID* ppvOut, LPUNKNOWN punkOuter);

#define DIRECTINPUT_VERSION 0x0800

#define DIDC_ATTACHED   1
#define DIDC_EMULATED   4 

#define DIDFT_OPTIONAL		0x80000000
#define DIDFT_ABSAXIS       0x00000002
#define DIDFT_ALIAS		0x08000000
#define DIDFT_ALL           0x00000000
#define DIDFT_AXIS          0x00000003
#define DIDFT_BUTTON        0x0000000C
#define DIDFT_COLLECTION	0x00000040
#define DIDFT_ENUMCOLLECTION(n)	((WORD)(n) << 8)
#define DIDFT_FFACTUATOR	0x01000000
#define DIDFT_FFEFFECTTRIGGER	0x02000000
#define DIDFT_NOCOLLECTION	0x00FFFF00
#define DIDFT_NODATA	0x00000080
#define DIDFT_OUTPUT	0x10000000
#define DIDFT_POV	0x00000010
#define DIDFT_PSHBUTTON	0x00000004
#define DIDFT_RELAXIS	0x00000001
#define DIDFT_TGLBUTTON	0x00000008
#define DIDFT_VENDORDEFINED	0x04000000

typedef struct DIMOUSESTATE {
	LONG lX;
	LONG lY;
	LONG lZ;
	BYTE rgbButtons[4];
} DIMOUSESTATE, * LPDIMOUSESTATE;

typedef struct DIDEVCAPS {
	DWORD   dwSize;
	DWORD   dwFlags;
	DWORD   dwDevType;
	DWORD   dwAxes;
	DWORD   dwButtons;
	DWORD   dwPOVs;
	DWORD   dwFFSamplePeriod;
	DWORD   dwFFMinTimeResolution;
	DWORD   dwFirmwareRevision;
	DWORD   dwHardwareRevision;
	DWORD   dwFFDriverVersion;
} DIDEVCAPS, * LPDIDEVCAPS;

typedef struct DIDEVICEOBJECTINSTANCEA {
	DWORD   dwSize;
	GUID    guidType;
	DWORD   dwOfs;
	DWORD   dwType;
	DWORD   dwFlags;
	CHAR    tszName[MAX_PATH];
	DWORD   dwFFMaxForce;
	DWORD   dwFFForceResolution;
	WORD    wCollectionNumber;
	WORD    wDesignatorIndex;
	WORD    wUsagePage;
	WORD    wUsage;
	DWORD   dwDimension;
	WORD    wExponent;
	WORD    wReportId;
} DIDEVICEOBJECTINSTANCEA, * LPDIDEVICEOBJECTINSTANCEA;

typedef struct DIPROPHEADER {
	DWORD   dwSize;
	DWORD   dwHeaderSize;
	DWORD   dwObj;
	DWORD   dwHow;
} DIPROPHEADER, * LPDIPROPHEADER;
typedef const DIPROPHEADER* LPCDIPROPHEADER;

typedef struct DIPROPDWORD {
	DIPROPHEADER    diph;
	DWORD       dwData;
} DIPROPDWORD, * LPDIPROPDWORD;
typedef const DIPROPDWORD* LPCDIPROPDWORD;

typedef struct DIPROPSTRING {
	DIPROPHEADER diph;
	WCHAR        wsz[MAX_PATH];
} DIPROPSTRING, * LPDIPROPSTRING;
typedef const DIPROPSTRING* LPCDIPROPSTRING;

typedef const DIDEVICEOBJECTINSTANCEA* LPCDIDEVICEOBJECTINSTANCEA;
typedef BOOL(FAR PASCAL* LPDIENUMDEVICEOBJECTSCALLBACKA)(LPCDIDEVICEOBJECTINSTANCEA, LPVOID);

typedef struct DIDEVICEOBJECTDATA {
	DWORD       dwOfs;
	DWORD       dwData;
	DWORD       dwTimeStamp;
	DWORD       dwSequence;
	UINT_PTR    uAppData;
} DIDEVICEOBJECTDATA, * LPDIDEVICEOBJECTDATA;
typedef const DIDEVICEOBJECTDATA* LPCDIDEVICEOBJECTDATA;

typedef struct _DIOBJECTDATAFORMAT {
	const GUID* pguid;
	DWORD   dwOfs;
	DWORD   dwType;
	DWORD   dwFlags;
} DIOBJECTDATAFORMAT, * LPDIOBJECTDATAFORMAT;
typedef const DIOBJECTDATAFORMAT* LPCDIOBJECTDATAFORMAT;

typedef struct _DIDATAFORMAT {
	DWORD   dwSize;
	DWORD   dwObjSize;
	DWORD   dwFlags;
	DWORD   dwDataSize;
	DWORD   dwNumObjs;
	LPDIOBJECTDATAFORMAT rgodf;
} DIDATAFORMAT, * LPDIDATAFORMAT;
typedef const DIDATAFORMAT* LPCDIDATAFORMAT;

typedef struct DIDEVICEINSTANCEA {
	DWORD   dwSize;
	GUID    guidInstance;
	GUID    guidProduct;
	DWORD   dwDevType;
	CHAR    tszInstanceName[MAX_PATH];
	CHAR    tszProductName[MAX_PATH];
	GUID    guidFFDriver;
	WORD    wUsagePage;
	WORD    wUsage;
} DIDEVICEINSTANCEA, * LPDIDEVICEINSTANCEA;
typedef const DIDEVICEINSTANCEA* LPCDIDEVICEINSTANCEA;

typedef struct DIENVELOPE {
	DWORD dwSize;                   /* sizeof(DIENVELOPE)   */
	DWORD dwAttackLevel;
	DWORD dwAttackTime;             /* Microseconds         */
	DWORD dwFadeLevel;
	DWORD dwFadeTime;               /* Microseconds         */
} DIENVELOPE, * LPDIENVELOPE;
typedef const DIENVELOPE* LPCDIENVELOPE;

typedef struct DIEFFECT {
	DWORD dwSize;                   /* sizeof(DIEFFECT)     */
	DWORD dwFlags;                  /* DIEFF_*              */
	DWORD dwDuration;               /* Microseconds         */
	DWORD dwSamplePeriod;           /* Microseconds         */
	DWORD dwGain;
	DWORD dwTriggerButton;          /* or DIEB_NOTRIGGER    */
	DWORD dwTriggerRepeatInterval;  /* Microseconds         */
	DWORD cAxes;                    /* Number of axes       */
	LPDWORD rgdwAxes;               /* Array of axes        */
	LPLONG rglDirection;            /* Array of directions  */
	LPDIENVELOPE lpEnvelope;        /* Optional             */
	DWORD cbTypeSpecificParams;     /* Size of params       */
	LPVOID lpvTypeSpecificParams;   /* Pointer to params    */
	DWORD  dwStartDelay;            /* Microseconds         */
} DIEFFECT, * LPDIEFFECT;
typedef DIEFFECT DIEFFECT_DX6;
typedef LPDIEFFECT LPDIEFFECT_DX6;
typedef const DIEFFECT* LPCDIEFFECT;

typedef struct DIEFFESCAPE {
	DWORD   dwSize;
	DWORD   dwCommand;
	LPVOID  lpvInBuffer;
	DWORD   cbInBuffer;
	LPVOID  lpvOutBuffer;
	DWORD   cbOutBuffer;
} DIEFFESCAPE, * LPDIEFFESCAPE;

typedef struct BufferedKeyboardEvent
{
	DIDEVICEOBJECTDATA dod;
	BufferedKeyboardEvent* nextPtr;
} BufferedKeyboardEvent;

DECLARE_INTERFACE(IDirectInputEffect)
{
	/*** IUnknown methods ***/
	STDMETHOD(QueryInterface)(GUID* riid, LPVOID * ppvObj) PURE;
	STDMETHOD_(ULONG, AddRef)() PURE;
	STDMETHOD_(ULONG, Release)() PURE;

	/*** IDirectInputEffect methods ***/
	STDMETHOD(Initialize)(HINSTANCE, DWORD, GUID*) PURE;
	STDMETHOD(GetEffectGuid)(LPGUID) PURE;
	STDMETHOD(GetParameters)(LPDIEFFECT, DWORD) PURE;
	STDMETHOD(SetParameters)(LPCDIEFFECT, DWORD) PURE;
	STDMETHOD(Start)(DWORD, DWORD) PURE;
	STDMETHOD(Stop)() PURE;
	STDMETHOD(GetEffectStatus)(LPDWORD) PURE;
	STDMETHOD(Download)() PURE;
	STDMETHOD(Unload)() PURE;
	STDMETHOD(Escape)(LPDIEFFESCAPE) PURE;
};

typedef struct IDirectInputEffect* LPDIRECTINPUTEFFECT;

typedef struct DIEFFECTINFOA {
	DWORD   dwSize;
	GUID    guid;
	DWORD   dwEffType;
	DWORD   dwStaticParams;
	DWORD   dwDynamicParams;
	CHAR    tszName[MAX_PATH];
} DIEFFECTINFOA, * LPDIEFFECTINFOA;

typedef const DIEFFECTINFOA* LPCDIEFFECTINFOA;
typedef BOOL(FAR PASCAL* LPDIENUMEFFECTSCALLBACKA)(LPCDIEFFECTINFOA, LPVOID);

typedef BOOL(FAR PASCAL* LPDIENUMCREATEDEFFECTOBJECTSCALLBACK)(LPDIRECTINPUTEFFECT, LPVOID);

typedef struct DIFILEEFFECT {
	DWORD       dwSize;
	GUID        GuidEffect;
	LPCDIEFFECT lpDiEffect;
	CHAR        szFriendlyName[MAX_PATH];
}DIFILEEFFECT, * LPDIFILEEFFECT;
typedef const DIFILEEFFECT* LPCDIFILEEFFECT;

typedef const DIFILEEFFECT* LPCDIFILEEFFECT;
typedef BOOL(FAR PASCAL* LPDIENUMEFFECTSINFILECALLBACK)(LPCDIFILEEFFECT, LPVOID);

typedef struct _DIACTIONA {
	UINT_PTR    uAppData;
	DWORD       dwSemantic;
	OPTIONAL    DWORD       dwFlags;
	OPTIONAL    union {
		LPCSTR      lptszActionName;
		UINT        uResIdString;
	};
	OPTIONAL    GUID        guidInstance;
	OPTIONAL    DWORD       dwObjID;
	OPTIONAL    DWORD       dwHow;
} DIACTIONA, * LPDIACTIONA;

typedef struct _DIACTIONFORMATA {
	DWORD       dwSize;
	DWORD       dwActionSize;
	DWORD       dwDataSize;
	DWORD       dwNumActions;
	LPDIACTIONA rgoAction;
	GUID        guidActionMap;
	DWORD       dwGenre;
	DWORD       dwBufferSize;
	OPTIONAL    LONG        lAxisMin;
	OPTIONAL    LONG        lAxisMax;
	OPTIONAL    HINSTANCE   hInstString;
	FILETIME    ftTimeStamp;
	DWORD       dwCRC;
	CHAR        tszActionMap[MAX_PATH];
} DIACTIONFORMATA, * LPDIACTIONFORMATA;

typedef struct _DIDEVICEIMAGEINFOA {
	CHAR        tszImagePath[MAX_PATH];
	DWORD       dwFlags;
	// These are valid if DIDIFT_OVERLAY is present in dwFlags.
	DWORD       dwViewID;
	RECT        rcOverlay;
	DWORD       dwObjID;
	DWORD       dwcValidPts;
	POINT       rgptCalloutLine[5];
	RECT        rcCalloutRect;
	DWORD       dwTextAlign;
} DIDEVICEIMAGEINFOA, * LPDIDEVICEIMAGEINFOA;

typedef struct _DIDEVICEIMAGEINFOHEADERA {
	DWORD       dwSize;
	DWORD       dwSizeImageInfo;
	DWORD       dwcViews;
	DWORD       dwcButtons;
	DWORD       dwcAxes;
	DWORD       dwcPOVs;
	DWORD       dwBufferSize;
	DWORD       dwBufferUsed;
	LPDIDEVICEIMAGEINFOA lprgImageInfoArray;
} DIDEVICEIMAGEINFOHEADERA, * LPDIDEVICEIMAGEINFOHEADERA;

#ifndef D3DCOLOR_DEFINED
typedef DWORD D3DCOLOR;
#define D3DCOLOR_DEFINED
#endif

typedef struct _DICOLORSET {
	DWORD       dwSize;
	D3DCOLOR    cTextFore;
	D3DCOLOR    cTextHighlight;
	D3DCOLOR    cCalloutLine;
	D3DCOLOR    cCalloutHighlight;
	D3DCOLOR    cBorder;
	D3DCOLOR    cControlFill;
	D3DCOLOR    cHighlightFill;
	D3DCOLOR    cAreaFill;
} DICOLORSET, * LPDICOLORSET;
typedef const DICOLORSET* LPCDICOLORSET;

typedef struct _DICONFIGUREDEVICESPARAMSA {
	DWORD           dwSize;
	DWORD           dwcUsers;
	LPSTR           lptszUserNames;
	DWORD           dwcFormats;
	LPDIACTIONFORMATA   lprgFormats;
	HWND            hwnd;
	DICOLORSET      dics;
	LPUNKNOWN       lpUnkDDSTarget;
} DICONFIGUREDEVICESPARAMSA, * LPDICONFIGUREDEVICESPARAMSA;
typedef const DICONFIGUREDEVICESPARAMSA* LPCDICONFIGUREDEVICESPARAMSA;

typedef BOOL(CALLBACK* LPDICONFIGUREDEVICESCALLBACK)(LPUNKNOWN, LPVOID);

DECLARE_INTERFACE(IDirectInputDevice8A)
{
	/*** IUnknown methods ***/
	STDMETHOD_(HRESULT, QueryInterface)(GUID* riid, void** ppvObject) PURE;
	STDMETHOD_(ULONG, AddRef)() PURE;
	STDMETHOD_(ULONG, Release)() PURE;

	/*** IDirectInputDeviceA methods ***/
	STDMETHOD(GetCapabilities)(LPDIDEVCAPS lpDIDevCaps) PURE;
	STDMETHOD(EnumObjects)(LPDIENUMDEVICEOBJECTSCALLBACKA lpCallback, LPVOID pvRef, DWORD dwFlags) PURE;
	STDMETHOD(GetProperty)(GUID* rguidProp, LPDIPROPHEADER pdiph) PURE;
	STDMETHOD(SetProperty)(GUID* rguidProp, LPCDIPROPHEADER pdiph) PURE;
	STDMETHOD(Acquire)() PURE;
	STDMETHOD(Unacquire)() PURE;
	STDMETHOD(GetDeviceState)(DWORD cbData, LPVOID lpvData) PURE;
	STDMETHOD(GetDeviceData)(DWORD cbObjectData, LPDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD dwFlags) PURE;
	STDMETHOD(SetDataFormat)(LPCDIDATAFORMAT lpdf) PURE;
	STDMETHOD(SetEventNotification)(HANDLE hEvent) PURE;
	STDMETHOD(SetCooperativeLevel)(HWND hwnd, DWORD dwFlags) PURE;
	STDMETHOD(GetObjectInfo)(LPDIDEVICEOBJECTINSTANCEA pdidoi, DWORD dwObj, DWORD dwHow) PURE;
	STDMETHOD(GetDeviceInfo)(LPDIDEVICEINSTANCEA pdidi) PURE;
	STDMETHOD(RunControlPanel)(HWND hwndOwner, DWORD dwFlags) PURE;
	STDMETHOD(Initialize)(HINSTANCE hinst, DWORD dwVersion, GUID* rguid) PURE;

	/*** IDirectInputDevice2A methods ***/
	STDMETHOD(CreateEffect)(GUID* rguid, LPCDIEFFECT lpeff, LPDIRECTINPUTEFFECT* ppdeff, LPUNKNOWN punkOuter) PURE;
	STDMETHOD(EnumEffects)(LPDIENUMEFFECTSCALLBACKA lpCallback, LPVOID pvRef, DWORD dwEffType) PURE;
	STDMETHOD(GetEffectInfo)(LPDIEFFECTINFOA pdei, GUID* rguid) PURE;
	STDMETHOD(GetForceFeedbackState)(LPDWORD pdwOut) PURE;
	STDMETHOD(SendForceFeedbackCommand)(DWORD dwFlags) PURE;
	STDMETHOD(EnumCreatedEffectObjects)(LPDIENUMCREATEDEFFECTOBJECTSCALLBACK lpCallback, LPVOID pvRef, DWORD fl) PURE;
	STDMETHOD(Escape)(LPDIEFFESCAPE pesc) PURE;
	STDMETHOD(Poll)() PURE;
	STDMETHOD(SendDeviceData)(DWORD cbObjectData, LPCDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD fl) PURE;
	/*** IDirectInputDevice7A methods ***/
	STDMETHOD(EnumEffectsInFile)(LPCSTR lpszFileName, LPDIENUMEFFECTSINFILECALLBACK pec, LPVOID pvRef, DWORD dwFlags) PURE;
	STDMETHOD(WriteEffectToFile)(LPCSTR lpszFileName, DWORD dwEntries, LPDIFILEEFFECT rgDiFileEft, DWORD dwFlags) PURE;
	/*** IDirectInputDevice8A methods ***/
	STDMETHOD(BuildActionMap)(LPDIACTIONFORMATA lpdiaf, LPCSTR lpszUserName, DWORD dwFlags) PURE;
	STDMETHOD(SetActionMap)(LPDIACTIONFORMATA lpdiaf, LPCSTR lpszUserName, DWORD dwFlags) PURE;
	STDMETHOD(GetImageInfo)(LPDIDEVICEIMAGEINFOHEADERA lpdiDevImageInfoHeader) PURE;
};

typedef struct IDirectInputDevice8A* LPDIRECTINPUTDEVICE8A;

typedef BOOL(CALLBACK* LPDIENUMDEVICESCALLBACKA)(LPCDIDEVICEINSTANCEA, LPVOID);
typedef BOOL(CALLBACK* LPDIENUMDEVICESBYSEMANTICSCBA)(LPCDIDEVICEINSTANCEA, LPDIRECTINPUTDEVICE8A, DWORD, DWORD, LPVOID);

DECLARE_INTERFACE(IDirectInput8A)
{
	/*** IUnknown methods ***/
	STDMETHOD_(HRESULT, QueryInterface)(GUID* riid, void** ppvObject) PURE;
	STDMETHOD_(ULONG, AddRef)() PURE;
	STDMETHOD_(ULONG, Release)() PURE;

	/*** IDirectInput8A methods ***/
	STDMETHOD(CreateDevice)(GUID* rguid, LPDIRECTINPUTDEVICE8A * lplpDirectInputDevice, LPUNKNOWN pUnkOuter) PURE;
	STDMETHOD(EnumDevices)(DWORD dwDevType, LPDIENUMDEVICESCALLBACKA lpCallback, LPVOID pvRef, DWORD dwFlags) PURE;
	STDMETHOD(GetDeviceStatus)(GUID* rguidInstance) PURE;
	STDMETHOD(RunControlPanel)(HWND hwndOwner, DWORD dwFlags) PURE;
	STDMETHOD(Initialize)(HINSTANCE hinst, DWORD dwVersion) PURE;
	STDMETHOD(FindDevice)(GUID* rguid, LPCSTR pszName, LPGUID pguidInstance) PURE;
	STDMETHOD(EnumDevicesBySemantics)(LPCSTR ptszUserName, LPDIACTIONFORMATA lpdiActionFormat, LPDIENUMDEVICESBYSEMANTICSCBA lpCallback, LPVOID pvRef, DWORD dwFlags) PURE;
	STDMETHOD(ConfigureDevices)(LPDICONFIGUREDEVICESCALLBACK lpdiCallback, LPDICONFIGUREDEVICESPARAMSA lpdiCDParams, DWORD dwFlags, LPVOID pvRefData) PURE;
};

typedef struct IDirectInput8A* LPDIRECTINPUT8A;