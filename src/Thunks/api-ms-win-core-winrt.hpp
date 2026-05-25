#if (YY_Thunks_Target < __WindowsNT6_2)
#include <roapi.h>
#include <inspectable.h>
#include <Activation.h>
#endif

#if (YY_Thunks_Target < __WindowsNT6_2) && !defined(__Comment_Lib_ole32)
#define __Comment_Lib_ole32
#pragma comment(lib, "Ole32.lib")
#endif

MIDL_INTERFACE("277151C3-9E3E-42F6-91A4-5DFDEB232451")
    ILauncherStatics : public IInspectable
{
public:
    virtual HRESULT STDMETHODCALLTYPE TreatAsUntrusted(boolean * value) = 0;
    virtual HRESULT STDMETHODCALLTYPE LaunchFileAsync(void* file,boolean** operation) = 0;
    virtual HRESULT STDMETHODCALLTYPE LaunchFileWithOptionsAsync(void* file, void* options, boolean** operation) = 0;
    virtual HRESULT STDMETHODCALLTYPE LaunchUriAsync(void* uri, boolean** operation) = 0;
    virtual HRESULT STDMETHODCALLTYPE LaunchUriWithOptionsAsync(void* uri, void* options, boolean** operation) = 0;
};

class __declspec(uuid("{44111111-1111-1111-1111-111111111111}")) fakeLauncherStatics1 : public ILauncherStatics
{
public:
    STDMETHODIMP QueryInterface(
        _In_ REFIID riid, 
        _Out_ void** ppv)
    {
        if (NULL == ppv)
            return E_POINTER;
    
        if ((IID_IUnknown == riid)
            || (__uuidof(ILauncherStatics) == riid)
            || (__uuidof(IInspectable) == riid) || (__uuidof(IAgileObject) == riid))
        {
            AddRef();
            *ppv = (ILauncherStatics*)(this);
            return S_OK;
        }
    
        return E_NOINTERFACE;
    };

    STDMETHODIMP_(ULONG) AddRef(void) 
    { 
        return 1; 
    };
    
    STDMETHODIMP_(ULONG) Release(void) 
    { 
        return 1; 
    };

    STDMETHODIMP HRESULT GetIids(
        _Out_ ULONG* iidCount,
        _Out_ IID** iids) 
    {
        IID *Array;
        ULONG Count = 1;
    	Array = (IID *) CoTaskMemAlloc(Count * sizeof(IID));
        
    	if (!Array) {
    		return E_OUTOFMEMORY;
    	}
        
    	Array[0] = __uuidof(ILauncherStatics);
        
    	*iidCount = Count;
        *iids = Array;
    
    	return S_OK;
    };

    STDMETHODIMP HRESULT GetRuntimeClassName(
        _Out_ HSTRING* className)
    {
        PCWSTR Name = L"Windows.System.Launcher";
        return WindowsCreateString(Name, (ULONG) wcslen(Name), className);
    };

    STDMETHODIMP HRESULT GetTrustLevel(
        _Out_ TrustLevel* trustLevel) 
    {
        *trustLevel = BaseTrust;
        return S_OK;
    };

    STDMETHODIMP HRESULT TreatAsUntrusted(
        boolean* value)
    {
        *value = FALSE;
        return S_OK;
    };

    STDMETHODIMP HRESULT LaunchFileAsync(
        _In_ IUnknown* file, 
        _Out_ IAsyncOperation** operation)
    {
        return E_NOTIMPL;
    };

    STDMETHODIMP HRESULT LaunchFileWithOptionsAsync(
        _In_ IUnknown* file, 
        _In_ IUnknown* options, 
        _Out_ IAsyncOperation** operation)
    {
        return LaunchFileAsync(file, operation);
    };

    STDMETHODIMP HRESULT LaunchUriAsync(
        _In_    IUriRuntimeClass*   uri, 
        _Out_   IAsyncOperation**   operation)
    {
        HRESULT Result;
	    HSTRING RawUri;
	    HINSTANCE ShellExecuteResult;
        
        Result = uri->lpVtbl->get_AbsoluteUri(uri, &RawUri);
	    if (FAILED(Result)) {
		    return Result;
	    }

	    ShellExecuteResult = ShellExecute(
		    NULL,
		    L"open",
		    WindowsGetStringRawBuffer(RawUri, NULL),
		    NULL,
		    NULL,
		    SW_SHOW);

	    WindowsDeleteString(RawUri);

	    if (((ULONG) ShellExecuteResult) <= 32) {
		    return E_FAIL;
	    }

	    *operation = nullptr;

	    return S_OK;
    };

    STDMETHODIMP HRESULT LaunchUriWithOptionsAsync(
        _In_    IUriRuntimeClass* uri, 
        _In_    IUnknown* options,
        _Out_   IAsyncOperation** operation)
    {
        return LaunchUriAsync(uri, operation);
    };
};

static fakeLauncherStatics1 fbridge_launcherstatics;

namespace YY::Thunks
{
#if (YY_Thunks_Target < __WindowsNT6_2)

    //Windows 8 [desktop apps | UWP apps]
    //Windows Server 2012 [desktop apps | UWP apps]
    __DEFINE_THUNK(
    api_ms_win_core_winrt_l1_1_0,
    4,
    HRESULT,
    WINAPI,
    RoInitialize,
        _In_ RO_INIT_TYPE initType
        )
    {
        if (auto const pRoInitialize = try_get_RoInitialize())
        {
            return pRoInitialize(initType);
        }

        if ((unsigned)initType > (unsigned)RO_INIT_MULTITHREADED)
        {
            return E_INVALIDARG;
        }

        return CoInitializeEx(nullptr, initType ? COINIT_MULTITHREADED : COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    }
#endif

#if (YY_Thunks_Target < __WindowsNT6_2)

    //Windows 8 [desktop apps | UWP apps]
    //Windows Server 2012 [desktop apps | UWP apps]
    __DEFINE_THUNK(
    api_ms_win_core_winrt_l1_1_0,
    0,
    void,
    WINAPI,
    RoUninitialize,
        )
    {
        if (auto const pRoUninitialize = try_get_RoUninitialize())
        {
            return pRoUninitialize();
        }

        CoUninitialize();
    }
#endif

#if (YY_Thunks_Target < __WindowsNT6_2)

    //Windows 8 [desktop apps | UWP apps]
    //Windows Server 2012 [desktop apps | UWP apps]
    __DEFINE_THUNK(
    api_ms_win_core_winrt_l1_1_0,
    8,
    HRESULT,
    WINAPI,
    RoActivateInstance,
        _In_ HSTRING activatableClassId,
        _COM_Outptr_ IInspectable** instance
        )
    {
        if (auto const pRoActivateInstance = try_get_RoActivateInstance())
        {
            return pRoActivateInstance(activatableClassId, instance);
        }

        if (instance)
            *instance = nullptr;

        return E_NOTIMPL;
    }
#endif

#if (YY_Thunks_Target < __WindowsNT6_2)

    //Windows 8 [desktop apps | UWP apps]
    //Windows Server 2012 [desktop apps | UWP apps]
    __DEFINE_THUNK(
    api_ms_win_core_winrt_l1_1_0,
    16,
    HRESULT,
    WINAPI,
    RoRegisterActivationFactories,
        _In_reads_(count) HSTRING* activatableClassIds,
        _In_reads_(count) PFNGETACTIVATIONFACTORY* activationFactoryCallbacks,
        _In_ UINT32 count,
        _Out_ RO_REGISTRATION_COOKIE* cookie
        )
    {
        if (auto const pRoRegisterActivationFactories = try_get_RoRegisterActivationFactories())
        {
            return pRoRegisterActivationFactories(activatableClassIds, activationFactoryCallbacks, count, cookie);
        }

        if (cookie)
            *cookie = nullptr;

        return E_NOTIMPL;
    }
#endif


#if (YY_Thunks_Target < __WindowsNT6_2)

    //Windows 8 [desktop apps | UWP apps]
    //Windows Server 2012 [desktop apps | UWP apps]
    __DEFINE_THUNK(
    api_ms_win_core_winrt_l1_1_0,
    4,
    void,
    WINAPI,
    RoRevokeActivationFactories,
        _In_ RO_REGISTRATION_COOKIE cookie
        )
    {
        if (auto const pRoRevokeActivationFactories = try_get_RoRevokeActivationFactories())
        {
            return pRoRevokeActivationFactories(cookie);
        }
    }
#endif

#if (YY_Thunks_Target < __WindowsNT6_2)

    //Windows 8 [desktop apps | UWP apps]
    //Windows Server 2012 [desktop apps | UWP apps]
    __DEFINE_THUNK(
    api_ms_win_core_winrt_l1_1_0,
    12,
    HRESULT,
    WINAPI,
    RoGetActivationFactory,
        _In_ HSTRING activatableClassId,
        _In_ REFIID iid,
        _COM_Outptr_ void** factory
        )
    {
        if (auto const pRoGetActivationFactory = try_get_RoGetActivationFactory())
        {
            return pRoGetActivationFactory(activatableClassId, iid, factory);
        }

        if (factory)
            *factory = nullptr;

        if (IsEqualIID(__uuidof(IActivationFactory), iid))
        {
            *factory = (IActivationFactory*)&fbridge_factory;
        }
        else if (IsEqualIID(__uuidof(ILauncherStatics), iid))
        {
            *factory = (ILauncherStatics*)&fbridge_launcherstatics;
        }
        else if (IsEqualIID(__uuidof(IUIViewSettings), iid))
        {
            *factory = (IUIViewSettings*)&fbridge_uiviewsettings;
        }
        else if (IsEqualIID(__uuidof(IUIViewSettingsInterop), iid))
        {
            *factory = (IUIViewSettingsInterop*)&fbridge_uiviewsettingsinterop;
        }
        else if (IsEqualIID(__uuidof(IGlobalizationPreferencesStatics), iid))
        {
            *factory = (IGlobalizationPreferencesStatics*)&fbridge_globalization;
        }
        else
        {
            return E_NOINTERFACE;
        }
        
        return S_OK;
    }
#endif


#if (YY_Thunks_Target < __WindowsNT6_2)

    //Windows 8 [desktop apps | UWP apps]
    //Windows Server 2012 [desktop apps | UWP apps]
    __DEFINE_THUNK(
    api_ms_win_core_winrt_l1_1_0,
    12,
    HRESULT,
    WINAPI,
    RoRegisterForApartmentShutdown,
        _In_ IApartmentShutdown* callbackObject,
        _Out_ UINT64* apartmentIdentifier,
        _Out_ APARTMENT_SHUTDOWN_REGISTRATION_COOKIE* regCookie
        )
    {
        if (auto const pRoRegisterForApartmentShutdown = try_get_RoRegisterForApartmentShutdown())
        {
            return pRoRegisterForApartmentShutdown(callbackObject, apartmentIdentifier, regCookie);
        }

        if (regCookie)
            *regCookie = nullptr;


        return E_NOTIMPL;

    }
#endif


#if (YY_Thunks_Target < __WindowsNT6_2)

    //Windows 8 [desktop apps | UWP apps]
    //Windows Server 2012 [desktop apps | UWP apps]
    __DEFINE_THUNK(
    api_ms_win_core_winrt_l1_1_0,
    4,
    HRESULT,
    WINAPI,
    RoUnregisterForApartmentShutdown,
        _In_ APARTMENT_SHUTDOWN_REGISTRATION_COOKIE regCookie
        )
    {
        if (auto const pRoUnregisterForApartmentShutdown = try_get_RoUnregisterForApartmentShutdown())
        {
            return pRoUnregisterForApartmentShutdown(regCookie);
        }

        return E_NOTIMPL;

    }
#endif

#if (YY_Thunks_Target < __WindowsNT6_2)

    //Windows 8 [desktop apps | UWP apps]
    //Windows Server 2012 [desktop apps | UWP apps]
    __DEFINE_THUNK(
    api_ms_win_core_winrt_l1_1_0,
    4,
    HRESULT,
    WINAPI,
    RoGetApartmentIdentifier,
        _Out_ UINT64* apartmentIdentifier
        )
    {
        if (auto const pRoGetApartmentIdentifier = try_get_RoGetApartmentIdentifier())
        {
            return pRoGetApartmentIdentifier(apartmentIdentifier);
        }

        return E_NOTIMPL;

    }
#endif
}
