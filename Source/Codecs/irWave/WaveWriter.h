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

#define WAVEWRITER_MAXSIZE					4294967040LU

class CWaveWriter
{
private:
	HANDLE m_hFile;

	int m_iNumChannels;
	int m_iSampleRate;
	int m_iBitRate;
	int m_iBitsPerSample;
	unsigned long m_ulNumSamples;

	bool WriteHeader();
	bool WriteExtensibleHeader();

public:
	CWaveWriter();
	~CWaveWriter();

	bool Open(const TCHAR *szFileName,int iNumChannels,
		int iSampleRate,int iBitRate);
	bool Close();
	__int64 Write(unsigned char *pBuffer,__int64 iDataSize);
};
