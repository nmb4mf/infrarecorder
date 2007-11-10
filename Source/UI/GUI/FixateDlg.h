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
#include "resource.h"
#include "DeviceManager.h"

class CFixateDlg : public CDialogImpl<CFixateDlg>
{
private:
	bool m_bAppMode;
	CComboBox m_RecorderCombo;

	bool Translate();

public:
	enum { IDD = IDD_FIXATEDLG };

	CFixateDlg(bool bAppMode);
	~CFixateDlg();

	BEGIN_MSG_MAP(CFixateDlg)
		MESSAGE_HANDLER(WM_INITDIALOG,OnInitDialog)
		COMMAND_HANDLER(IDC_RECORDERCOMBO,CBN_SELCHANGE,OnRecorderChange)

		COMMAND_ID_HANDLER(IDOK,OnOK)
		COMMAND_ID_HANDLER(IDCANCEL,OnCancel)
		COMMAND_HANDLER(IDC_HELPBUTTON,BN_CLICKED,OnHelp)
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL &bHandled);
	LRESULT OnRecorderChange(WORD wNotifyCode,WORD wID,HWND hWndCtl,BOOL &bHandled);

	LRESULT OnOK(WORD wNotifyCode,WORD wID,HWND hWndCtl,BOOL &bHandled);
	LRESULT OnCancel(WORD wNotifyCode,WORD wID,HWND hWndCtl,BOOL &bHandled);
	LRESULT OnHelp(WORD wNotifyCode,WORD wID,HWND hWndCtl,BOOL &bHandled);
};
