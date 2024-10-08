/*
 * PROJECT:     SupernovaX Graphics Infrastructure
 * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later.html)
 * PURPOSE:     Render device
 * COPYRIGHT:   Copyright 2023 Christian Rendina <pizzaiolo100@proton.me>
 */

#pragma once

#include "dxgiobject.h"

class ATL_NO_VTABLE CDXGIDevice : 
	public DXGIObjRoot,
	public CDXGIObject<DXGIDeviceType>,
	public IDXGIDebugProducer
	//, public IDXGIDeviceInternal3
	//, public IDXGISwapChainInternal
	//, public IDXGIDeviceXAML
	//, public IDXGIDeviceDWM
	//, public IDXGIDeviceTest
{
public:
	BEGIN_COM_MAP(CDXGIDevice)
#if DXGI_VERSION >= 1
		COM_INTERFACE_ENTRY_IID(IID_IDXGIDevice1, IDXGIDevice1)
#endif
		COM_INTERFACE_ENTRY_IID(IID_IDXGIDevice, IDXGIDevice)
		COM_INTERFACE_ENTRY_IID(IID_IDXGIObject, IDXGIObject)
	END_COM_MAP()

	// IDXGIDevice	
	STDMETHODIMP CreateSurface(_In_ const DXGI_SURFACE_DESC* pDesc, _In_ UINT NumSurfaces, _In_ DXGI_USAGE Usage, _In_opt_ const DXGI_SHARED_RESOURCE* pSharedResource, _COM_Outptr_ IDXGISurface** ppSurface) override;
	STDMETHODIMP GetAdapter(_COM_Outptr_ IDXGIAdapter** pAdapter) override;
	STDMETHODIMP GetGPUThreadPriority(_Out_ INT* pPriority) override;
	STDMETHODIMP QueryResourceResidency(_In_ IUnknown* const* ppResources, _Out_ DXGI_RESIDENCY *pResidencyStatus, _In_ UINT NumResources) override;
	STDMETHODIMP SetGPUThreadPriority(_In_ INT Priority) override;
#if DXGI_VERSION >= 1
	// IDXGIDevice1
	STDMETHODIMP GetMaximumFrameLatency(_Out_ UINT* pMaxLatency) override;
#endif
};
