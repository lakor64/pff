/*
 * Copyright 2016 Henri Verbeet for CodeWeavers
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

#ifndef __WINE_D3DUKMDT_H
#define __WINE_D3DUKMDT_H

/* DXGKRNL targetting information */
#define DXGKDDI_INTERFACE_VERSION_VISTA_SP1  0x1053
#define DXGKDDI_INTERFACE_VERSION_WIN7       0x2005
#define DXGKDDI_INTERFACE_VERSION_WIN8       0x300E
#define DXGKDDI_INTERFACE_VERSION_WDDM1_3    0x4002
#define DXGKDDI_INTERFACE_VERSION_WDDM2_0    0x5023
#define DXGKDDI_INTERFACE_VERSION_WDDM2_2    0x700A
#define DXGKDDI_INTERFACE_VERSION_WDDM2_3    0x8001
#define DXGKDDI_INTERFACE_VERSION_WDDM2_4    0x9006
#define DXGKDDI_INTERFACE_VERSION_WDDM2_5    0xA00B
#define DXGKDDI_INTERFACE_VERSION_WDDM2_6    0xB004
#define DXGKDDI_INTERFACE_VERSION_WDDM2_7    0xC004
#define DXGKDDI_INTERFACE_VERSION_WDDM2_8    0xD001
#define DXGKDDI_INTERFACE_VERSION_WDDM2_9    0xE003
#define DXGKDDI_INTERFACE_VERSION_WDDM3_0    0xF003

/* Isn't used in ReactOS much yet */
#define D3D_UMD_INTERFACE_VERSION_VISTA         0x000C
#define D3D_UMD_INTERFACE_VERSION_WIN7          0x2003
#define D3D_UMD_INTERFACE_VERSION_WDDM2_0       0x5002

#if !defined(DXGKDDI_INTERFACE_VERSION)
#define DXGKDDI_INTERFACE_VERSION           DXGKDDI_INTERFACE_VERSION_VISTA_SP1
#endif

#if !defined(D3D_UMD_INTERFACE_VERSION)
#define D3D_UMD_INTERFACE_VERSION           D3D_UMD_INTERFACE_VERSION_VISTA
#endif

typedef UINT D3DKMT_HANDLE;
typedef UINT  D3DDDI_VIDEO_PRESENT_SOURCE_ID;
typedef ULONGLONG D3DGPU_VIRTUAL_ADDRESS;
typedef ULONGLONG D3DGPU_SIZE_T;

#ifdef _WIN32
#define D3DKMT_ALIGN64
#define D3DKMT_PTR_HELPER(Name)
#define D3DKMT_PTR(Type, Name) Type Name
#define D3DKMT_PTR_INIT(x) (x)
typedef SIZE_T D3DKMT_SIZE_T;
typedef UINT_PTR D3DKMT_UINT_PTR;
typedef ULONG_PTR D3DKMT_ULONG_PTR;
typedef HANDLE D3DKMT_PTR_TYPE;
#else
#define D3DKMT_ALIGN64 alignas(8)
#define D3DKMT_PTR_HELPER(Name) D3DKMT_ALIGN64 UINT64 Name;

#define D3DKMT_PTR(Type, Name)       \
union D3DKMT_ALIGN64                 \
{                                    \
    D3DKMT_PTR_HELPER(Name##_Align)  \
    Type Name;                       \
}

#define D3DKMT_PTR_INIT(x) {
    (UINT64)(SIZE_T)(x)
}

typedef UINT64 D3DKMT_SIZE_T, D3DKMT_UINT_PTR, D3DKMT_ULONG_PTR;
typedef union _D3DKMT_PTR_TYPE
{
    D3DKMT_PTR_HELPER(Ptr_Align);
    HANDLE Ptr;
} D3DKMT_PTR_TYPE;
#endif

#ifndef MAKEFOURCC
#define MAKEFOURCC(ch0, ch1, ch2, ch3) \
        ((DWORD)(BYTE)(ch0) | ((DWORD)(BYTE)(ch1) << 8) | \
        ((DWORD)(BYTE)(ch2) << 16) | ((DWORD)(BYTE)(ch3) << 24))
#endif /* MAKEFOURCC */

#define D3DDDI_MAX_OBJECT_WAITED_ON 32
#define D3DDDI_MAX_OBJECT_SIGNALED  32
#define D3DDDI_MAX_BROADCAST_CONTEXT        64

typedef enum _D3DDDIFORMAT
{
    D3DDDIFMT_UNKNOWN                 = 0,
    D3DDDIFMT_R8G8B8                  = 0x14,
    D3DDDIFMT_A8R8G8B8                = 0x15,
    D3DDDIFMT_X8R8G8B8                = 0x16,
    D3DDDIFMT_R5G6B5                  = 0x17,
    D3DDDIFMT_X1R5G5B5                = 0x18,
    D3DDDIFMT_A1R5G5B5                = 0x19,
    D3DDDIFMT_A4R4G4B4                = 0x1a,
    D3DDDIFMT_R3G3B2                  = 0x1b,
    D3DDDIFMT_A8                      = 0x1c,
    D3DDDIFMT_A8R3G3B2                = 0x1d,
    D3DDDIFMT_X4R4G4B4                = 0x1e,
    D3DDDIFMT_A2B10G10R10             = 0x1f,
    D3DDDIFMT_A8B8G8R8                = 0x20,
    D3DDDIFMT_X8B8G8R8                = 0x21,
    D3DDDIFMT_G16R16                  = 0x22,
    D3DDDIFMT_A2R10G10B10             = 0x23,
    D3DDDIFMT_A16B16G16R16            = 0x24,
    D3DDDIFMT_A8P8                    = 0x28,
    D3DDDIFMT_P8                      = 0x29,
    D3DDDIFMT_L8                      = 0x32,
    D3DDDIFMT_A8L8                    = 0x33,
    D3DDDIFMT_A4L4                    = 0x34,
    D3DDDIFMT_V8U8                    = 0x3c,
    D3DDDIFMT_L6V5U5                  = 0x3d,
    D3DDDIFMT_X8L8V8U8                = 0x3e,
    D3DDDIFMT_Q8W8V8U8                = 0x3f,
    D3DDDIFMT_V16U16                  = 0x40,
    D3DDDIFMT_W11V11U10               = 0x41,
    D3DDDIFMT_A2W10V10U10             = 0x43,
    D3DDDIFMT_D16_LOCKABLE            = 0x46,
    D3DDDIFMT_D32                     = 0x47,
    D3DDDIFMT_S1D15                   = 0x48,
    D3DDDIFMT_D15S1                   = 0x49,
    D3DDDIFMT_S8D24                   = 0x4a,
    D3DDDIFMT_D24S8                   = 0x4b,
    D3DDDIFMT_X8D24                   = 0x4c,
    D3DDDIFMT_D24X8                   = 0x4d,
    D3DDDIFMT_X4S4D24                 = 0x4e,
    D3DDDIFMT_D24X4S4                 = 0x4f,
    D3DDDIFMT_D16                     = 0x50,
    D3DDDIFMT_L16                     = 0x51,
    D3DDDIFMT_D32F_LOCKABLE           = 0x52,
    D3DDDIFMT_D24FS8                  = 0x53,
    D3DDDIFMT_D32_LOCKABLE            = 0x54,
    D3DDDIFMT_S8_LOCKABLE             = 0x55,
    D3DDDIFMT_G8R8                    = 0x5b,
    D3DDDIFMT_R8                      = 0x5c,
    D3DDDIFMT_VERTEXDATA              = 0x64,
    D3DDDIFMT_INDEX16                 = 0x65,
    D3DDDIFMT_INDEX32                 = 0x66,
    D3DDDIFMT_Q16W16V16U16            = 0x6e,
    D3DDDIFMT_R16F                    = 0x6f,
    D3DDDIFMT_G16R16F                 = 0x70,
    D3DDDIFMT_A16B16G16R16F           = 0x71,
    D3DDDIFMT_R32F                    = 0x72,
    D3DDDIFMT_G32R32F                 = 0x73,
    D3DDDIFMT_A32B32G32R32F           = 0x74,
    D3DDDIFMT_CxV8U8                  = 0x75,
    D3DDDIFMT_A1                      = 0x76,
    D3DDDIFMT_A2B10G10R10_XR_BIAS     = 0x77,
    D3DDDIFMT_DXVACOMPBUFFER_BASE     = 0x96,
    D3DDDIFMT_PICTUREPARAMSDATA       = D3DDDIFMT_DXVACOMPBUFFER_BASE + 0,
    D3DDDIFMT_MACROBLOCKDATA          = D3DDDIFMT_DXVACOMPBUFFER_BASE + 0x01,
    D3DDDIFMT_RESIDUALDIFFERENCEDATA  = D3DDDIFMT_DXVACOMPBUFFER_BASE + 0x02,
    D3DDDIFMT_DEBLOCKINGDATA          = D3DDDIFMT_DXVACOMPBUFFER_BASE + 0x03,
    D3DDDIFMT_INVERSEQUANTIZATIONDATA = D3DDDIFMT_DXVACOMPBUFFER_BASE + 0x04,
    D3DDDIFMT_SLICECONTROLDATA        = D3DDDIFMT_DXVACOMPBUFFER_BASE + 0x05,
    D3DDDIFMT_BITSTREAMDATA           = D3DDDIFMT_DXVACOMPBUFFER_BASE + 0x06,
    D3DDDIFMT_MOTIONVECTORBUFFER      = D3DDDIFMT_DXVACOMPBUFFER_BASE + 0x07,
    D3DDDIFMT_FILMGRAINBUFFER         = D3DDDIFMT_DXVACOMPBUFFER_BASE + 0x08,
    D3DDDIFMT_DXVA_RESERVED9          = D3DDDIFMT_DXVACOMPBUFFER_BASE + 0x09,
    D3DDDIFMT_DXVA_RESERVED10         = D3DDDIFMT_DXVACOMPBUFFER_BASE + 0x0a,
    D3DDDIFMT_DXVA_RESERVED11         = D3DDDIFMT_DXVACOMPBUFFER_BASE + 0x0b,
    D3DDDIFMT_DXVA_RESERVED12         = D3DDDIFMT_DXVACOMPBUFFER_BASE + 0x0c,
    D3DDDIFMT_DXVA_RESERVED13         = D3DDDIFMT_DXVACOMPBUFFER_BASE + 0x0d,
    D3DDDIFMT_DXVA_RESERVED14         = D3DDDIFMT_DXVACOMPBUFFER_BASE + 0x0e,
    D3DDDIFMT_DXVA_RESERVED15         = D3DDDIFMT_DXVACOMPBUFFER_BASE + 0x0f,
    D3DDDIFMT_DXVA_RESERVED16         = D3DDDIFMT_DXVACOMPBUFFER_BASE + 0x10,
    D3DDDIFMT_DXVA_RESERVED17         = D3DDDIFMT_DXVACOMPBUFFER_BASE + 0x11,
    D3DDDIFMT_DXVA_RESERVED18         = D3DDDIFMT_DXVACOMPBUFFER_BASE + 0x12,
    D3DDDIFMT_DXVA_RESERVED19         = D3DDDIFMT_DXVACOMPBUFFER_BASE + 0x13,
    D3DDDIFMT_DXVA_RESERVED20         = D3DDDIFMT_DXVACOMPBUFFER_BASE + 0x14,
    D3DDDIFMT_DXVA_RESERVED21         = D3DDDIFMT_DXVACOMPBUFFER_BASE + 0x15,
    D3DDDIFMT_DXVA_RESERVED22         = D3DDDIFMT_DXVACOMPBUFFER_BASE + 0x16,
    D3DDDIFMT_DXVA_RESERVED23         = D3DDDIFMT_DXVACOMPBUFFER_BASE + 0x17,
    D3DDDIFMT_DXVA_RESERVED24         = D3DDDIFMT_DXVACOMPBUFFER_BASE + 0x18,
    D3DDDIFMT_DXVA_RESERVED25         = D3DDDIFMT_DXVACOMPBUFFER_BASE + 0x19,
    D3DDDIFMT_DXVA_RESERVED26         = D3DDDIFMT_DXVACOMPBUFFER_BASE + 0x1a,
    D3DDDIFMT_DXVA_RESERVED27         = D3DDDIFMT_DXVACOMPBUFFER_BASE + 0x1b,
    D3DDDIFMT_DXVA_RESERVED28         = D3DDDIFMT_DXVACOMPBUFFER_BASE + 0x1c,
    D3DDDIFMT_DXVA_RESERVED29         = D3DDDIFMT_DXVACOMPBUFFER_BASE + 0x1d,
    D3DDDIFMT_DXVA_RESERVED30         = D3DDDIFMT_DXVACOMPBUFFER_BASE + 0x1e,
    D3DDDIFMT_DXVA_RESERVED31         = D3DDDIFMT_DXVACOMPBUFFER_BASE + 0x1f,
    D3DDDIFMT_DXVACOMPBUFFER_MAX      = D3DDDIFMT_DXVA_RESERVED31,
    D3DDDIFMT_BINARYBUFFER            = 0xc7,
    D3DDDIFMT_DXT1                    = MAKEFOURCC('D', 'X', 'T', '1'),
    D3DDDIFMT_DXT2                    = MAKEFOURCC('D', 'X', 'T', '2'),
    D3DDDIFMT_DXT3                    = MAKEFOURCC('D', 'X', 'T', '3'),
    D3DDDIFMT_DXT4                    = MAKEFOURCC('D', 'X', 'T', '4'),
    D3DDDIFMT_DXT5                    = MAKEFOURCC('D', 'X', 'T', '5'),
    D3DDDIFMT_G8R8_G8B8               = MAKEFOURCC('G', 'R', 'G', 'B'),
    D3DDDIFMT_MULTI2_ARGB8            = MAKEFOURCC('M', 'E', 'T', '1'),
    D3DDDIFMT_R8G8_B8G8               = MAKEFOURCC('R', 'G', 'B', 'G'),
    D3DDDIFMT_UYVY                    = MAKEFOURCC('U', 'Y', 'V', 'Y'),
    D3DDDIFMT_YUY2                    = MAKEFOURCC('Y', 'U', 'Y', '2'),
    D3DDDIFMT_FORCE_UINT              = 0x7fffffff,
} D3DDDIFORMAT;

typedef struct _D3DDDI_ESCAPEFLAGS
{
    union
    {
        struct
        {
            UINT    HardwareAccess      : 1;
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM1_3)
            UINT    DeviceStatusQuery   : 1;
            UINT    ChangeFrameLatency  : 1;
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)
            UINT    NoAdapterSynchronization    : 1;
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_2)
            UINT    Reserved            : 1;
            UINT    VirtualMachineData  : 1;
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_5)
            UINT    DriverKnownEscape   : 1;    cture
            UINT    DriverCommonEscape  : 1;
            UINT    Reserved2           :24;
#else
            UINT    Reserved2           :26;
#endif
#else
            UINT    Reserved            :28;
#endif
#else
            UINT    Reserved            :29;
#endif
#else
            UINT    Reserved            :31;
#endif
        };
        UINT        Value;
    };
} D3DDDI_ESCAPEFLAGS;


typedef struct _D3DDDICB_LOCKFLAGS {
  union {
    struct {
      UINT ReadOnly : 1;
      UINT WriteOnly : 1;
      UINT DonotWait : 1;
      UINT IgnoreSync : 1;
      UINT LockEntire : 1;
      UINT DonotEvict : 1;
      UINT AcquireAperture : 1;
      UINT Discard : 1;
      UINT NoExistingReference : 1;
      UINT UseAlternateVA : 1;
      UINT IgnoreReadSync : 1;
      UINT Reserved : 21;
    };
    UINT Value;
  };
} D3DDDICB_LOCKFLAGS;

typedef enum _D3DDDI_GAMMARAMP_TYPE
{
    D3DDDI_GAMMARAMP_UNINITIALIZED = 0,
    D3DDDI_GAMMARAMP_DEFAULT       = 1,
    D3DDDI_GAMMARAMP_RGB256x3x16   = 2,
    D3DDDI_GAMMARAMP_DXGI_1        = 3,
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_3)
    D3DDDI_GAMMARAMP_MATRIX_3x4    = 4,
#endif
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_6)
    D3DDDI_GAMMARAMP_MATRIX_V2     = 5,
#endif
} D3DDDI_GAMMARAMP_TYPE;


typedef enum D3DDDI_FLIPINTERVAL_TYPE
{
    D3DDDI_FLIPINTERVAL_IMMEDIATE = 0,
    D3DDDI_FLIPINTERVAL_ONE       = 1,
    D3DDDI_FLIPINTERVAL_TWO       = 2,
    D3DDDI_FLIPINTERVAL_THREE     = 3,
    D3DDDI_FLIPINTERVAL_FOUR      = 4,

    // This value is only valid for the D3D9 runtime PresentCb SyncIntervalOverride field.
    // For this field, IMMEDIATE means the API semantic of sync interval 0, where
    // IMMEDIATE_ALLOW_TEARING is equivalent to the addition of the DXGI ALLOW_TEARING API flags.
    D3DDDI_FLIPINTERVAL_IMMEDIATE_ALLOW_TEARING = 5,
} D3DDDI_FLIPINTERVAL_TYPE;

typedef struct _D3DKMT_PRESENTFLAGS
{
    union
    {
        struct
        {
            UINT    Blt                         : 1;
            UINT    ColorFill                   : 1;
            UINT    Flip                        : 1;
            UINT    FlipDoNotFlip               : 1;
            UINT    FlipDoNotWait               : 1;
            UINT    FlipRestart                 : 1;
            UINT    DstRectValid                : 1;
            UINT    SrcRectValid                : 1;
            UINT    RestrictVidPnSource         : 1;
            UINT    SrcColorKey                 : 1;
            UINT    DstColorKey                 : 1;
            UINT    LinearToSrgb                : 1;
            UINT    PresentCountValid           : 1;
            UINT    Rotate                      : 1;
            UINT    PresentToBitmap             : 1;
            UINT    RedirectedFlip              : 1;
            UINT    RedirectedBlt               : 1;
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)
            UINT    FlipStereo                  : 1;
            UINT    FlipStereoTemporaryMono     : 1;
            UINT    FlipStereoPreferRight       : 1;
            UINT    BltStereoUseRight           : 1;
            UINT    PresentHistoryTokenOnly     : 1;
            UINT    PresentRegionsValid         : 1;
            UINT    PresentDDA                  : 1;
            UINT    ProtectedContentBlankedOut  : 1;
            UINT    RemoteSession               : 1;
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM1_3)
            UINT    CrossAdapter                : 1;
            UINT    DurationValid               : 1;
            UINT    PresentIndirect             : 1;
            UINT    PresentHMD                  : 1;
            UINT    Reserved                    : 2;
#else
            UINT    Reserved                    : 6;
#endif
#else
            UINT    Reserved                    : 15;
#endif
        };
        UINT    Value;
    };
} D3DKMT_PRESENTFLAGS;

typedef enum _D3DDDI_SYNCHRONIZATIONOBJECT_TYPE {
  D3DDDI_SYNCHRONIZATION_MUTEX,
  D3DDDI_SEMAPHORE,
  D3DDDI_FENCE,
  D3DDDI_CPU_NOTIFICATION,
  D3DDDI_MONITORED_FENCE,
  D3DDDI_PERIODIC_MONITORED_FENCE,
  D3DDDI_NATIVE_FENCE,
  D3DDDI_SYNCHRONIZATION_TYPE_LIMIT
} D3DDDI_SYNCHRONIZATIONOBJECT_TYPE;

typedef enum _D3DDDI_VIDEO_SIGNAL_SCANLINE_ORDERING {
  D3DDDI_VSSLO_UNINITIALIZED,
  D3DDDI_VSSLO_PROGRESSIVE,
  D3DDDI_VSSLO_INTERLACED_UPPERFIELDFIRST,
  D3DDDI_VSSLO_INTERLACED_LOWERFIELDFIRST,
  D3DDDI_VSSLO_OTHER
} D3DDDI_VIDEO_SIGNAL_SCANLINE_ORDERING;

typedef struct _D3DKMT_SETDISPLAYMODE_FLAGS {
   BOOLEAN PreserveVidPn : 1;
   UINT    Reserved : 31;
} D3DKMT_SETDISPLAYMODE_FLAGS;

typedef struct _D3DDDI_GAMMA_RAMP_RGB256x3x16
{
    USHORT  Red[256];
    USHORT  Green[256];
    USHORT  Blue[256];
} D3DDDI_GAMMA_RAMP_RGB256x3x16;

typedef struct D3DDDI_DXGI_RGB
{
    float   Red;
    float   Green;
    float   Blue;
} D3DDDI_DXGI_RGB;

typedef struct _D3DDDI_GAMMA_RAMP_DXGI_1
{
    D3DDDI_DXGI_RGB    Scale;
    D3DDDI_DXGI_RGB    Offset;
    D3DDDI_DXGI_RGB    GammaCurve[1025];
} D3DDDI_GAMMA_RAMP_DXGI_1;

typedef struct _D3DDDI_SEGMENTPREFERENCE
{
    union
    {
        struct
        {
            UINT SegmentId0 : 5;
            UINT Direction0 : 1;
            UINT SegmentId1 : 5;
            UINT Direction1 : 1;
            UINT SegmentId2 : 5;
            UINT Direction2 : 1;
            UINT SegmentId3 : 5;
            UINT Direction3 : 1;
            UINT SegmentId4 : 5;
            UINT Direction4 : 1;
            UINT Reserved   : 2;
        };
        UINT Value;
    };
} D3DDDI_SEGMENTPREFERENCE, DXGK_SEGMENTPREFERENCE, *PD3DDDI_SEGMENTPREFERENCE;

typedef struct _D3DDDIRECT
{
    LONG left;
    LONG top;
    LONG right;
    LONG bottom;
} D3DDDIRECT;

typedef struct _D3DDDI_KERNELOVERLAYINFO
{
    D3DKMT_HANDLE        hAllocation;           // in: Allocation to be displayed
    D3DDDIRECT           DstRect;               // in: Dest rect
    D3DDDIRECT           SrcRect;               // in: Source rect
    D3DKMT_PTR(VOID*,    pPrivateDriverData);   // in: Private driver data
    UINT                 PrivateDriverDataSize; // in: Size of private driver data
} D3DDDI_KERNELOVERLAYINFO;

typedef struct _D3DDDICB_SIGNALFLAGS
{
    union
    {
        struct
        {
            UINT SignalAtSubmission : 1;
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)
            UINT EnqueueCpuEvent    : 1;
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)
            UINT AllowFenceRewind   : 1;
            UINT Reserved           : 28;
            UINT DXGK_SIGNAL_FLAG_INTERNAL0 : 1;
#else
            UINT Reserved           : 30;
#endif
#else
            UINT Reserved           : 31;
#endif
        };
        UINT Value;
    };
} D3DDDICB_SIGNALFLAGS;

typedef struct _D3DDDI_OPENALLOCATIONINFO
{
    D3DKMT_HANDLE   hAllocation;
    D3DKMT_PTR(CONST VOID*, pPrivateDriverData);
    UINT            PrivateDriverDataSize;

} D3DDDI_OPENALLOCATIONINFO;

typedef struct _D3DDDI_RATIONAL
{
    UINT    Numerator;
    UINT    Denominator;
} D3DDDI_RATIONAL;
typedef enum _D3DDDI_ROTATION
{
    D3DDDI_ROTATION_IDENTITY        = 1,
    D3DDDI_ROTATION_90              = 2,
    D3DDDI_ROTATION_180             = 3,
    D3DDDI_ROTATION_270             = 4
} D3DDDI_ROTATION;

typedef struct _D3DDDI_CREATECONTEXTFLAGS
{
    union
    {
        struct
        {
            UINT    NullRendering       : 1;
            UINT    InitialData         : 1;
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_0)
            UINT    DisableGpuTimeout   : 1;
            UINT    SynchronizationOnly : 1;
#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WDDM2_3)
            UINT    HwQueueSupported    : 1;
            UINT    NoKmdAccess         : 1;
            UINT    Reserved            :26;
#else
            UINT    Reserved            :28;
#endif

#else
            UINT    Reserved            :30;
#endif
        };
        UINT Value;
    };
} D3DDDI_CREATECONTEXTFLAGS;

typedef struct _D3DDDI_ALLOCATIONLIST
{
    D3DKMT_HANDLE       hAllocation;
    union
    {
        struct
        {
            UINT                  WriteOperation      : 1;
            UINT                  DoNotRetireInstance : 1;

#if (DXGKDDI_INTERFACE_VERSION >= DXGKDDI_INTERFACE_VERSION_WIN8)
            UINT                  OfferPriority       : 3;
            UINT                  Reserved            :27;
#else
            UINT                  Reserved            :30;
#endif
        };
        UINT                Value;
    };
} D3DDDI_ALLOCATIONLIST;

typedef struct _D3DDDI_PATCHLOCATIONLIST
{
    UINT                AllocationIndex;
    union
    {
        struct
        {
            UINT            SlotId          : 24;
            UINT            Reserved        : 8;
        };
        UINT                Value;
    };
    UINT                DriverId;
    UINT                AllocationOffset;
    UINT                PatchOffset;
    UINT                SplitOffset;
} D3DDDI_PATCHLOCATIONLIST;

typedef struct _D3DDDI_SYNCHRONIZATIONOBJECTINFO {
    D3DDDI_SYNCHRONIZATIONOBJECT_TYPE Type;
    union {
      struct {
        BOOL InitialState;
      } SynchronizationMutex;
      struct {
        UINT MaxCount;
        UINT InitialCount;
      } Semaphore;
      struct {
        UINT Reserved[16];
      } Reserved;
    };
} D3DDDI_SYNCHRONIZATIONOBJECTINFO;
#endif /* __WINE_D3DUKMDT_H */
