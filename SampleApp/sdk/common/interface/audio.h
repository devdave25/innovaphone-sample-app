/*---------------------------------------------------------------------------*/
/* audio.h                                                                   */
/* copyright (c) innovaphone 2017                                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/

enum AudioDeviceType {
    DeviceTypeUnknown,
    HandsetDevice,
    HeadsetDevice,
    HandsfreeDevice,
};

enum AudioDeviceMode {
    AudioModeRecord,
    AudioModePlayback,
    AudioModeCommunication,
};

#define AUDIO_CAPABILITY_RECORD         0x00000001
#define AUDIO_CAPABILITY_PLAYBACK       0x00000002
#define AUDIO_CAPABILITY_COMMUNICATION  0x00000004
#define AUDIO_CAPABILITY_MONITORING     0x00000008
#define AUDIO_CAPABILITY_HOOK_DEVICE    0x00000010

#define KEY_EHS_TALK	0x81		// Talk button pressed
#define KEY_EHS_FLASH	0x82		// accept knocking call, toggle calls (if any)
#define KEY_EHS_REDIAL	0x83		// redial last number dialled (if any)
#define KEY_OFFHOOK     0x93		// handset up
#define KEY_ONHOOK      0x94		// handset down
#define KEY_DISC	    0x8E		// Disconnect
#define KEY_MIC         0x8F        // toggle microphone
#define KEY_INCALL      0xFE        // from softphone
#define KEY_HOLD        0xFD        // from softphone
#define KEY_RETRIEVE      0xFC        // from softphone


NAMESPACE_BEGIN
#if defined(__cplusplus)


class IAudioExec {
public:
    virtual ~IAudioExec() {};
    virtual unsigned ExecJitter8khz() = 0;
};

class IAudioProcessor : public IAudioExec {
public:
    static class IAudioProcessor * Create(class IIoMux * const iomux, class IInstanceLog * log, unsigned execInterval8khz) ;

    virtual void Initialize(class UAudioProcessor * const user) = 0;
};

class UAudioExec {
public:
    virtual void AudioExec(class IAudioExec *audioExec) = 0;
};

class UAudioProcessor : public UAudioExec {
public:
 
};



class UAudioPhone : public UAudioExec {
public:
    virtual void AudioDeviceList(void * context) = 0;
    virtual void HookKeyReceived(const char *deviceId, byte key) = 0;
    virtual void CloseAudioPhoneComplete() = 0;
};

class IAudioPhone : public IAudioExec {
public:
    static class IAudioPhone * Create(class IIoMux * const iomux, class IInstanceLog * log, unsigned execInterval8khz/*125us*/);
    virtual ~IAudioPhone() {};

    virtual void Initialize(class UAudioPhone * const user) = 0;

    virtual void QueryDevices(void * context) = 0;
    virtual unsigned DeviceCount() = 0;
    virtual const char * DeviceId(unsigned deviceNumber) = 0;
    virtual enum AudioDeviceType DeviceType(unsigned deviceNumber) = 0;
    virtual unsigned DeviceCapabilities(unsigned deviceNumber) = 0;
    virtual const char * DeviceName(unsigned deviceNumber) = 0;
    virtual void StartDevice(const char *deviceId, enum AudioDeviceMode deviceMode, unsigned microphoneSampleRate/*Hz*/, unsigned speakerSampleRate/*Hz*/) = 0;
    virtual void StopDevice(const char *deviceId) = 0;
    virtual unsigned AudioDelay8khz() = 0;
    virtual const short * MicrophoneSamplePtr() = 0;
    virtual short * SpeakerSamplePtr() = 0;
    virtual void StartMonitoring(const char *deviceId, enum AudioDeviceMode deviceMode) = 0;
    virtual void StopMonitoring(const char *deviceId) = 0;
    virtual void StartHookDevice(const char *deviceId) = 0;
    virtual void StopHookDevice(const char *deviceId) = 0;
    virtual void SendHookKey(const char *deviceId, byte key, byte callId) = 0;
    virtual void SetMicrophoneMute(bool mute) {};

    virtual void Close() = 0;
};

#endif /* defined(__cplusplus) */
NAMESPACE_END
