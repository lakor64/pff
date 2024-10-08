/*
 * PROJECT:     SupernovaX 2D Draw
 * LICENSE:     LGPL-2.1-or-later (https://spdx.org/licenses/LGPL-2.1-or-later.html)
 * PURPOSE:     IDirectDrawColorControl object
 * COPYRIGHT:   Copyright 2024 Christian Rendina <pizzaiolo100@proton.me>
 */

#pragma once

class ATL_NO_VTABLE CDirectDrawColorControl :
    public IDirectDrawColorControl,
    public DDObjRoot
{
public:
    BEGIN_COM_MAP(CDirectDrawColorControl)
        COM_INTERFACE_ENTRY_IID(IID_IDirectDrawColorControl, IDirectDrawColorControl)
    END_COM_MAP()

    STDMETHODIMP GetColorControls(_Out_ LPDDCOLORCONTROL lpColorControl) override;
    STDMETHODIMP SetColorControls(_In_ LPDDCOLORCONTROL lpColorControl) override;
};
