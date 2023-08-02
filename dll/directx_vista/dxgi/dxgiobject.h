/*
 * PROJECT:     ReactX Graphics Infrastructure
 * COPYRIGHT:   See COPYING in the top level directory
 * PURPOSE:     Basic DXGI object
 * COPYRIGHT:   Copyright 2023 Christian Rendina <christian.rendina@gmail.com>
 */

#pragma once

#include <vector>

/** Manages the private data of a DXGIObject */
struct DXGIPrivateData
{
	/**
		NULL -> there is no RAW data
		Valid and isCOM == false -> RAW data
		Valid and isCOM == true -> A IUnknown** pointer
		Note that IUnknown** pointer value CAN BE NULL, this does not mean that the private data is invalid
	*/
	union
	{
		LPVOID raw;
		IUnknown** com;
	} pData;

	/** Size of the private data */
	UINT nSize;

	/** True if it's a COM object */
	bool isCOM;

	/** GUID identificator */
	GUID Guid;

	DXGIPrivateData() : nSize(0), isCOM(false)
	{
		pData.raw = nullptr;
	}

	~DXGIPrivateData() = default;

	void Release()
	{
		if (pData.raw)
		{
			if (isCOM && *pData.com)
				(*pData.com)->Release();

			free(pData.raw);
			pData.raw = nullptr;
			nSize = 0;
		}
	}

	/** Sets custom data */
	bool Set(GUID guid, LPCVOID pData, UINT nSize, bool com)
	{
		Release();

		Guid = guid;
		this->nSize = nSize;
		isCOM = com;

		this->pData.raw = malloc(nSize);

		if (!this->pData.raw)
			return false;

		memcpy(this->pData.raw, pData, nSize);

		if (com && (*this->pData.com))
			(*this->pData.com)->AddRef();

		return true;
	}
};

/** template DXGI object */
template <typename T>
class ATL_NO_VTABLE CDXGIObject : 
	public T
{
public:
	using PrivateDataMap = std::vector<DXGIPrivateData>;

	STDMETHODIMP SetPrivateData(_In_ REFGUID Name, _In_ UINT DataSize, _In_opt_ const void* pData) override
	{
		return SetPrivateDataReal(Name, DataSize, pData, false);
	}

	STDMETHODIMP GetPrivateData(_In_ REFGUID Name, _Inout_ UINT* DataSize, _Out_ void* pData) override
	{
		auto it = m_vData.begin();

		for (; it != m_vData.end(); it++)
		{
			if (IsEqualGUID(it->Guid, Name))
			{
				if (*DataSize < it->nSize)
				{
					*DataSize = it->nSize;
					return DXGI_ERROR_MORE_DATA;
				}

				*DataSize = it->nSize;

				if (pData)
				{
					memcpy(pData, it->pData.raw, it->nSize);

					if (it->isCOM && *it->pData.com)
					{
						(*it->pData.com)->AddRef();
					}
				}

				return S_OK;
			}
		}

		*DataSize = 0;
		return DXGI_ERROR_NOT_FOUND;
	}

	STDMETHODIMP GetParent(_In_ REFIID Id, _Out_ void** pParent) override
	{
		if (!m_pParent)
			return E_NOINTERFACE;

		if (IsEqualIID(IID_IUnknown, Id) || IsEqualIID(IID_IDXGIObject, Id) || IsEqualIID(IID_IDXGIDeviceSubObject, Id)) // block invalid types
			return DXGI_ERROR_NOT_FOUND;

		auto hr = m_pParent->QueryInterface(Id, pParent);
		if (FAILED(hr))
			return hr;

		return S_OK;
	}

	STDMETHODIMP SetPrivateDataInterface(_In_ REFGUID Name, _In_opt_ const IUnknown* pUnknown) override
	{
		return SetPrivateDataReal(Name, sizeof(pUnknown), &pUnknown, true);
	}

protected:
	CDXGIObject() : m_pParent(nullptr) {}
	~CDXGIObject()
	{
		for (auto it = m_vData.begin(); it != m_vData.end(); it++)
		{
			it->Release();
		}

		if (m_pParent)
			m_pParent->Release();

		m_pParent = nullptr;
		m_vData.clear();
	}

	STDMETHODIMP_(void) SetParent(IUnknown* pParent)
	{
		if (m_pParent)
			m_pParent->Release();

		pParent->AddRef();
		m_pParent = pParent;
	}

	/** Parent of this object */
	IUnknown* m_pParent;

private:
	STDMETHODIMP SetPrivateDataReal(_In_ REFGUID Name, _In_ UINT DataSize, _In_opt_ const void* pData, _In_ bool com)
	{
		if (!pData)
			return DeletePD(Name);

		auto p = FindPD(Name);
		if (p == m_vData.end())
		{
			DXGIPrivateData data;
			if (!data.Set(Name, pData, DataSize, com))
				return E_OUTOFMEMORY;

			m_vData.push_back(data);
		}
		else
			p->Set(Name, pData, DataSize, com);

		return S_OK;
	}

	/** Delete private data */
	STDMETHODIMP DeletePD(_In_ REFGUID Name)
	{
		for (auto it = m_vData.begin(); it != m_vData.end(); it++)
		{
			if (IsEqualGUID(Name, it->Guid))
			{
				it->Release();
				m_vData.erase(it);
				break;
			}
		}

		return S_OK;
	}

	/** Find private data */
	inline PrivateDataMap::iterator FindPD(_In_ REFGUID Name)
	{
		auto it = m_vData.begin();
		for (; it != m_vData.end(); it++)
		{
			if (IsEqualGUID(Name, it->Guid))
				break;
		}

		return it;
	}

	/** Private data container */
	PrivateDataMap m_vData;
};