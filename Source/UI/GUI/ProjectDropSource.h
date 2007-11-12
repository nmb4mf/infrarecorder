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

#pragma once

class CProjectDropSource : public IDropSource
{
private:
	long m_lRefCount;

public:
	CProjectDropSource();
	~CProjectDropSource();

	// IUnknown members.
    HRESULT __stdcall QueryInterface(REFIID iid,void ** ppvObject);
    ULONG __stdcall AddRef();
    ULONG __stdcall Release();

	// IDropSource members.
    HRESULT __stdcall QueryContinueDrag(BOOL fEscapePressed,DWORD grfKeyState);
    HRESULT __stdcall GiveFeedback(DWORD dwEffect);
};