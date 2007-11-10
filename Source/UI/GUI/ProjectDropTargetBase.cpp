/*
 * Copyright (C) 2006-2007 Christian Kindahl, christian dot kindahl at gmail dot com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "stdafx.h"
#include "ProjectDropTargetBase.h"
#include "ProjectDataObject.h"

CProjectDropTargetBase::CProjectDropTargetBase()
{
	m_uiClipFormat = ::RegisterClipboardFormat(_T(PROJECT_CF_NAME));

	m_lRefCount = 1;
}

CProjectDropTargetBase::~CProjectDropTargetBase()
{
}

HRESULT __stdcall CProjectDropTargetBase::QueryInterface(REFIID iid,void **ppvObject)
{
	// Check to see what interface has been requested.
    if (iid == IID_IDropTarget || iid == IID_IUnknown)
    {
        AddRef();
        *ppvObject = this;
        return S_OK;
    }
    else
    {
        *ppvObject = 0;
        return E_NOINTERFACE;
    }
}

ULONG __stdcall CProjectDropTargetBase::AddRef()
{
	// Increment object reference count.
    return InterlockedIncrement(&m_lRefCount);
}

ULONG __stdcall CProjectDropTargetBase::Release()
{
	// Decrement object reference count.
	LONG lCount = InterlockedDecrement(&m_lRefCount);
		
	if (lCount == 0)
	{
		delete this;
		return 0;
	}
	else
	{
		return lCount;
	}
}

CProjectDropTargetBase::eDropType CProjectDropTargetBase::QueryDataObject(IDataObject *pDataObject)
{
    FORMATETC fmtetc = { CF_HDROP,0,DVASPECT_CONTENT,-1,TYMED_HGLOBAL };
	if (pDataObject->QueryGetData(&fmtetc) == S_OK)
		return DT_HDROP;

	fmtetc.cfFormat = m_uiClipFormat;
	if (pDataObject->QueryGetData(&fmtetc) == S_OK)
		return DT_IRPROJECT;

	return DT_NONE;
}

HRESULT __stdcall CProjectDropTargetBase::DragEnter(IDataObject *pDataObject,DWORD grfKeyState,
												POINTL pt,DWORD *pdwEffect)
{
    m_ucDropType = QueryDataObject(pDataObject);

	*pdwEffect = DROPEFFECT_NONE;
	return S_OK;
}

HRESULT __stdcall CProjectDropTargetBase::DragOver(DWORD grfKeyState,POINTL pt,DWORD *pdwEffect)
{
	if (m_ucDropType != DT_NONE && OnDragOver(pt))
		*pdwEffect = m_ucDropType == DT_HDROP ? DROPEFFECT_COPY : DROPEFFECT_MOVE;
	else
		*pdwEffect = DROPEFFECT_NONE;

	return S_OK;
}

HRESULT __stdcall CProjectDropTargetBase::DragLeave()
{
	OnDragLeave();
	return S_OK;
}

HRESULT __stdcall CProjectDropTargetBase::Drop(IDataObject *pDataObject,DWORD grfKeyState,
												   POINTL pt,DWORD *pdwEffect)
{
	if (m_ucDropType != DT_NONE && OnDrop(pt,pDataObject))
		*pdwEffect = m_ucDropType == DT_HDROP ? DROPEFFECT_COPY : DROPEFFECT_MOVE;
	else
		*pdwEffect = DROPEFFECT_NONE;

	return S_OK;
}
