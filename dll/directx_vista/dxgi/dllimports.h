/*
 * PROJECT:     SupernovaX Graphics Infrastructure
 * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later.html)
 * PURPOSE:     DLL Imports
 * COPYRIGHT:   Copyright 2023 Christian Rendina <pizzaiolo100@proton.me>
 */

#pragma once

 // gdi32.dll
typedef NTSTATUS(NTAPI* D3DKMTOpenAdapterFromGdiDisplayName_)(_Inout_ D3DKMT_OPENADAPTERFROMGDIDISPLAYNAME* disp);
typedef NTSTATUS(NTAPI* D3DKMTQueryAdapterInfo_)(_Inout_ CONST D3DKMT_QUERYADAPTERINFO* info);
typedef NTSTATUS(NTAPI* D3DKMTCloseAdapter_)(_In_ CONST D3DKMT_CLOSEADAPTER* close);
typedef NTSTATUS(NTAPI* D3DKMTGetDisplayModeList_)(_In_ D3DKMT_GETDISPLAYMODELIST* dmList);
typedef NTSTATUS(NTAPI* D3DKMTWaitForVerticalBlankEvent_)(_In_ CONST D3DKMT_WAITFORVERTICALBLANKEVENT*);
typedef NTSTATUS(NTAPI* D3DKMTGetDeviceState_)(_Inout_ D3DKMT_GETDEVICESTATE*);

#if DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN7
typedef NTSTATUS(NTAPI* D3DKMTCheckSharedResourceAccess_)(_In_ CONST D3DKMT_CHECKSHAREDRESOURCEACCESS*);
#endif
#if DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8
typedef NTSTATUS(NTAPI* D3DKMTEnumAdapters2_)(_Inout_ CONST D3DKMT_ENUMADAPTERS2* adapters);
#endif

// d3d11.dll
typedef HRESULT(NTAPI* D3D11CreateDevice_)(_In_opt_ IDXGIAdapter*, _In_ D3D_DRIVER_TYPE, _In_opt_ HMODULE, _In_ UINT, _In_opt_ const D3D_FEATURE_LEVEL*, _In_ UINT FeatureLevels, _In_ UINT SDKVersion, _Out_opt_ ID3D11Device*, _Out_opt_ D3D_FEATURE_LEVEL*, _Out_opt_ ID3D11DeviceContext*);

// d3d10.dll
typedef HRESULT(NTAPI* D3D10CreateDevice_)(_In_opt_ IDXGIAdapter*, _In_ D3D10_DRIVER_TYPE, _In_ HMODULE, _In_ UINT, _In_ UINT, _Out_ ID3D10Device**);

// dwmapi.dll
typedef HRESULT(WINAPI* DwmDxGetWindowSharedSurface_)(_In_ HWND hwnd, _In_ LUID luidAdapter, _In_opt_ HMONITOR hmonitorAssociation, _In_ DWORD dwFlags, _Inout_ DXGI_FORMAT* pfmtWindow, _Out_ HANDLE* phDxSurface, _Out_ UINT64* puiUpdateId);
typedef HRESULT(WINAPI* DwmDxUpdateWindowSharedSurface_)(_In_ HWND hwnd, _In_ UINT64 uiUpdateId, _In_ DWORD dwFlags, _In_opt_ HMONITOR hmonitorAssociation, _In_ RECT* prc);
typedef HRESULT(WINAPI* DwmIsCompositionEnabled_)(_Out_ BOOL* pfEnabled);

#define DWM_REDIRECTION_FLAG_WAIT 0
#define DWM_REDIRECTION_FLAG_SUPPORT_PRESENT_TO_GDI_SURFACE 0x10

/// Global pointer to DwmDxGetWindowSharedSurface
extern DwmDxGetWindowSharedSurface_ DwmDxGetWindowSharedSurface;

/// Global pointer to DwmDxUpdateWindowSharedSurface
extern DwmDxUpdateWindowSharedSurface_ DwmDxUpdateWindowSharedSurface;

/// Global pointer to DwmIsCompositionEnabled
extern DwmIsCompositionEnabled_ DwmIsCompositionEnabled;

/// Global pointer to GDI32.DLL
extern HMODULE g_GDI32;
