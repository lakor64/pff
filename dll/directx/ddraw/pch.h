/*
 * PROJECT:     SupernovaX 2D Draw
 * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later.html)
 * PURPOSE:     Precompiled header
 * COPYRIGHT:   Copyright 2024 Christian Rendina <pizzaiolo100@proton.me>
 */

#pragma once

#define WIN32_LEAN_AND_MEAN 1
#define STRICT 1

#define DDSCL_HOOKWINDOW 0x20 // TODO: move this to ddrawi.h

#define _ATL_APARTMENT_THREADED 1
#define _ATL_NO_AUTOMATIC_NAMESPACE 1
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS 1	// explicit CString
#define ATL_NO_ASSERT_ON_DESTROY_NONEXISTENT_WINDOW 1
#define _ANONYMOUS_UNION

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x500 // Windows 2000+
#endif

#ifdef __GNUC__
// TODO: This error should be removed when GCC supports __declspec(novtable) (never)
#define _ATL_DISABLE_NO_VTABLE 1 // fix error
#endif

 // ATL
#include <atlbase.h>
#include <atlcom.h>
#undef STATUS_NO_MEMORY

// NDK
/*#ifndef __REACTOS__
#include <winternl.h>
#else
#define NTOS_MODE_USER
#include <ndk/umtypes.h>
#endif*/

// C++
#include <cstdint>
#include <vector>

// DDRAW
#include <ddraw.h>
//#include <dvp.h>
//#include <ddrawi.h> // DDK
#include <ddrawgdi.h>
//#include <d3dhal.h> // DDK
#include <dxutils.h> // Library utilities

/// ATL Object root typedef
using DDModelRoot = ATL::CComMultiThreadModelNoCS;
using DDObjRoot = ATL::CComObjectRootEx<DDModelRoot>;

// Project
#include "dllimports.h"
#include "ddrawiatl.h"

static constexpr const char* REGISTER_PATH_DDSW = "Software\\Microsoft\\DirectDraw\\";
static constexpr const char* PRIMARY_DISPLAY_NAME = "display";

