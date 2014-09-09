/*
 * SoundDeviceDirectSound.h
 * ------------------------
 * Purpose: DirectSound sound device driver class.
 * Notes  : (currently none)
 * Authors: Olivier Lapicque
 *          OpenMPT Devs
 * The OpenMPT source code is released under the BSD license. Read LICENSE for more details.
 */


#pragma once

#include "SoundDevice.h"
#include "SoundDeviceThread.h"

#ifndef NO_DSOUND
#include <dsound.h>
#endif

OPENMPT_NAMESPACE_BEGIN

namespace SoundDevice {

////////////////////////////////////////////////////////////////////////////////////
//
// DirectSound device
//

#ifndef NO_DSOUND

//================================================
class CDSoundDevice: public CSoundDeviceWithThread
//================================================
{
protected:
	IDirectSound *m_piDS;
	IDirectSoundBuffer *m_pPrimary;
	IDirectSoundBuffer *m_pMixBuffer;
	DWORD m_nDSoundBufferSize;
	BOOL m_bMixRunning;
	DWORD m_dwWritePos;
	DWORD m_dwLatency;

public:
	CDSoundDevice(SoundDevice::ID id, const std::wstring &internalID);
	~CDSoundDevice();

public:
	bool InternalOpen();
	bool InternalClose();
	void InternalFillAudioBuffer();
	void StartFromSoundThread();
	void StopFromSoundThread();
	bool InternalIsOpen() const { return (m_pMixBuffer != NULL); }
	double GetCurrentLatency() const { return 1.0 * m_dwLatency / m_Settings.GetBytesPerSecond(); }
	SoundDevice::Caps InternalGetDeviceCaps();
	SoundDevice::DynamicCaps GetDeviceDynamicCaps(const std::vector<uint32> &baseSampleRates);

public:
	static std::vector<SoundDevice::Info> EnumerateDevices();
};

#endif // NO_DIRECTSOUND


} // namespace SoundDevice


OPENMPT_NAMESPACE_END
