/*
 * PROJECT:     SupernovaX Graphics Infrastructure
 * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later.html)
 * PURPOSE:     DXGI D3DKMT/UMD stub exports
 * COPYRIGHT:   Copyright 2023 Christian Rendina <pizzaiolo100@proton.me>
 */
#include "pch.h"

/*
	The following stubs are in use in the situation that a D3DKMT API under XDDM mode,
	 will might be called for things like OpenGL ICD Initialization or a replacement UMD driver.

	In a more practical use, DXGI.DLL acts a software adapter implementing various D3DKMT APIs
	 which can potentially open the doors for more support under XDDM mode.

	OpenAdapter is also provided as during XDDM mode, DXGI should reigster itself as a 
	 device driver, I suppose this is done to enable some portion of DXGI to work under XDDM.

	In a better/more realistic approach, this file should be removed and DXGI.DLL should
	 redirect to a proper reimplementation of some of the D3DKMT/UMD APIs (eg. DXGIXDDM.DLL) for XDDM,
	 if someone even wants to do something as strange and as problematic as this.

	 For now, I'll leave this stubs in here just to retrain compatibility with
	  Windows 7 and possible obscure use-cases that I am not aware of that involves
	  DXGI as a software adapter or UMD driver.
*/

#ifdef HAVE_D3D10UUMDI
#include <D3d10umddi.h>
#else
typedef void D3D10DDIARG_OPENADAPTER;
#endif

extern "C"
{
	NTSTATUS NTAPI D3DKMTGetDeviceState(_Inout_ D3DKMT_GETDEVICESTATE* ds)
	{
		if (ds->StateType == D3DKMT_DEVICESTATE_EXECUTION)
		{
			ds->ExecutionState = D3DKMT_DEVICEEXECUTION_ACTIVE;
		}
		else if (ds->StateType == D3DKMT_DEVICESTATE_PRESENT)
		{
			memset(&ds->PresentState, 0, sizeof(ds->PresentState));
		}
		else
			return STATUS_NOT_SUPPORTED;

		return STATUS_SUCCESS;
	}

	NTSTATUS NTAPI D3DKMTOpenAdapterFromHdc(_Inout_ D3DKMT_OPENADAPTERFROMHDC* hdc)
	{
		memset(hdc, 0, sizeof(*hdc));
		hdc->hAdapter = 1;
		return STATUS_SUCCESS;
	}

	NTSTATUS NTAPI D3DKMTQueryAdapterInfo(_Inout_ CONST D3DKMT_QUERYADAPTERINFO* ai)
	{
		if (ai->Type == KMTQAITYPE_UMDRIVERNAME)
		{
			if (ai->PrivateDriverDataSize != sizeof(D3DKMT_UMDFILENAMEINFO))
				return STATUS_INVALID_PARAMETER;

			wcscpy_s(((D3DKMT_UMDFILENAMEINFO*)ai->pPrivateDriverData)->UmdFileName, _countof(((D3DKMT_UMDFILENAMEINFO*)ai->pPrivateDriverData)->UmdFileName), L"dxgi.dll");
			((D3DKMT_UMDFILENAMEINFO*)ai->pPrivateDriverData)->Version = KMTUMDVERSION_DX10;
		}
		else if (ai->Type == KMTQAITYPE_UMDRIVERPRIVATE)
		{
			*((DWORD*)ai->pPrivateDriverData) = 0;
		}

		return STATUS_SUCCESS;
	}

	NTSTATUS NTAPI D3DKMTOpenResource(_Inout_ D3DKMT_OPENRESOURCE*)
	{
		return STATUS_SUCCESS;
	}

	NTSTATUS NTAPI D3DKMTPresent(_Inout_ D3DKMT_PRESENT*)
	{
		return STATUS_SUCCESS;
	}

	NTSTATUS NTAPI D3DKMTQueryAllocationResidency(_In_ CONST D3DKMT_QUERYALLOCATIONRESIDENCY*)
	{
		return STATUS_SUCCESS;
	}

	NTSTATUS NTAPI D3DKMTQueryResourceInfo(_Inout_ D3DKMT_QUERYRESOURCEINFO*)
	{
		return STATUS_SUCCESS;
	}

	NTSTATUS NTAPI D3DKMTCloseAdapter(_In_ CONST D3DKMT_CLOSEADAPTER*)
	{
		return STATUS_SUCCESS;
	}

	NTSTATUS NTAPI D3DKMTRender(_Inout_ D3DKMT_RENDER*)
	{
		return STATUS_SUCCESS;
	}

	NTSTATUS NTAPI D3DKMTLock(_Inout_ D3DKMT_LOCK*)
	{
		return STATUS_SUCCESS;
	}

	NTSTATUS NTAPI D3DKMTSetAllocationPriority(_In_ CONST D3DKMT_SETALLOCATIONPRIORITY*)
	{
		return STATUS_SUCCESS;
	}

	NTSTATUS NTAPI D3DKMTSetContextSchedulingPriority(_In_ CONST D3DKMT_SETCONTEXTSCHEDULINGPRIORITY*)
	{
		return STATUS_SUCCESS;
	}

	NTSTATUS NTAPI D3DKMTSetDisplayMode(_In_ CONST D3DKMT_SETDISPLAYMODE*)
	{
		return STATUS_SUCCESS;
	}

	NTSTATUS NTAPI D3DKMTSetDisplayPrivateDriverFormat(_In_ CONST D3DKMT_SETDISPLAYPRIVATEDRIVERFORMAT*)
	{
		return STATUS_SUCCESS;
	}

	NTSTATUS NTAPI D3DKMTSetGammaRamp(_In_ CONST D3DKMT_SETGAMMARAMP*)
	{
		return STATUS_SUCCESS;
	}

	NTSTATUS NTAPI D3DKMTSetVidPnSourceOwner(_In_ CONST D3DKMT_SETVIDPNSOURCEOWNER*)
	{
		return STATUS_SUCCESS;
	}

	NTSTATUS NTAPI D3DKMTSignalSynchronizationObject(_In_ CONST D3DKMT_SIGNALSYNCHRONIZATIONOBJECT*)
	{
		return STATUS_SUCCESS;
	}

	NTSTATUS NTAPI D3DKMTUnlock(_In_ CONST D3DKMT_UNLOCK*)
	{
		return STATUS_SUCCESS;
	}

	NTSTATUS NTAPI D3DKMTWaitForSynchronizationObject(_In_ CONST D3DKMT_WAITFORSYNCHRONIZATIONOBJECT*)
	{
		return STATUS_SUCCESS;
	}

	NTSTATUS NTAPI D3DKMTWaitForVerticalBlankEvent(_In_ CONST D3DKMT_WAITFORVERTICALBLANKEVENT*)
	{
		return STATUS_SUCCESS;
	}

	NTSTATUS NTAPI D3DKMTCreateAllocation(_Inout_ D3DKMT_CREATEALLOCATION*)
	{
		return STATUS_SUCCESS;
	}

	NTSTATUS NTAPI D3DKMTCreateDevice(_Inout_ D3DKMT_CREATEDEVICE*)
	{
		return STATUS_SUCCESS;
	}

	NTSTATUS NTAPI D3DKMTCreateContext(_Inout_ D3DKMT_CREATECONTEXT*)
	{
		return STATUS_SUCCESS;
	}

	NTSTATUS NTAPI D3DKMTCreateSyncrhonizationObject(_Inout_ D3DKMT_CREATESYNCHRONIZATIONOBJECT*)
	{
		return STATUS_SUCCESS;
	}

	NTSTATUS NTAPI D3DKMTDestroyAllocation(_In_ CONST D3DKMT_DESTROYALLOCATION*)
	{
		return STATUS_SUCCESS;
	}

	NTSTATUS NTAPI D3DKMTDestroyContext(_In_ CONST D3DKMT_DESTROYCONTEXT*)
	{
		return STATUS_SUCCESS;
	}

	NTSTATUS NTAPI D3DKMTDestroyDevice(_In_ CONST D3DKMT_DESTROYDEVICE*)
	{
		return STATUS_SUCCESS;
	}

	NTSTATUS NTAPI D3DKMTDestroySynchronizationObject(_In_ CONST D3DKMT_DESTROYSYNCHRONIZATIONOBJECT*)
	{
		return STATUS_SUCCESS;
	}

	NTSTATUS NTAPI D3DKMTGetContextSchedulingPriority(_Inout_ D3DKMT_GETCONTEXTSCHEDULINGPRIORITY*)
	{
		return STATUS_SUCCESS;
	}

	NTSTATUS NTAPI D3DKMTEscape(_Inout_ CONST D3DKMT_ESCAPE*)
	{
		return STATUS_SUCCESS;
	}

	NTSTATUS NTAPI D3DKMTGetDisplayModeList(_Inout_ D3DKMT_GETDISPLAYMODELIST*)
	{
		return STATUS_SUCCESS;
	}

	NTSTATUS NTAPI D3DKMTGetMultisampleMethodList(_Inout_ D3DKMT_GETMULTISAMPLEMETHODLIST*)
	{
		return STATUS_SUCCESS;
	}

	NTSTATUS NTAPI D3DKMTGetRuntimeData(_Inout_ CONST D3DKMT_GETRUNTIMEDATA*)
	{
		return STATUS_SUCCESS;
	}

	NTSTATUS NTAPI D3DKMTGetSharedPrimaryHandle(_Inout_ D3DKMT_GETSHAREDPRIMARYHANDLE*)
	{
		return STATUS_SUCCESS;
	}


	HRESULT WINAPI OpenAdapter10(D3D10DDIARG_OPENADAPTER* pOpenData)
	{
		return DXGI_ERROR_UNSUPPORTED;
	}

	HRESULT WINAPI OpenAdapter10_2(D3D10DDIARG_OPENADAPTER* pOpenData)
	{
		return DXGI_ERROR_UNSUPPORTED;
	}
}
