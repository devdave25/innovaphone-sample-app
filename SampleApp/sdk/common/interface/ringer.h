/*---------------------------------------------------------------------------*/
/* ringer.h                                                                  */
/* copyright (c) innovaphone 2017                                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/

enum RingerDeviceType {
    RingerSpeaker = 64,
	RingerBaseStation
};

enum RingerDeviceMode {
    RingerModeAudioOnly,
    RingerModeAllowVibrate,
    RingerModeOnlyBaseStation,
    RingerModeWithBaseStation,
};


NAMESPACE_BEGIN
#if defined(__cplusplus)

class URinger {
public:
    virtual void RingerList(void * context) = 0;
    virtual void RingtoneList(void * context) = 0;
    virtual void NotificationToneList(void * context) = 0;
    virtual void CloseRingerComplete() = 0;
};

class IRinger {
public:
    static class IRinger * Create(class IIoMux * const iomux, class IInstanceLog * log);
    virtual ~IRinger() {};

    virtual void Initialize(class URinger * const user) = 0;

    virtual void QueryDevices(void * context) = 0;
    virtual unsigned DeviceCount() = 0;
    virtual const char * DeviceId(unsigned deviceNumber) = 0;
    virtual enum RingerDeviceType DeviceType(unsigned deviceNumber) = 0;
    virtual unsigned DeviceCapabilities(unsigned deviceNumber) = 0;
    virtual const char * DeviceName(unsigned deviceNumber) = 0;

    virtual void QueryRingtones(void * context) = 0;
    virtual unsigned RingtoneCount() = 0;
    virtual const char * RingtoneTitle(unsigned ringtoneNumber) = 0;
    virtual const char * RingtoneIdent(unsigned ringtoneNumber) = 0;
    virtual void RingtoneStart(const char *deviceId, enum RingerDeviceMode deviceMode, const char *ident) = 0;
    virtual void RingtoneStop(const char *deviceId) = 0;

    virtual void QueryNotificationTones(void * context) = 0;
    virtual unsigned NotificationToneCount() = 0;
    virtual const char * NotificationToneTitle(unsigned ringtoneNumber) = 0;
    virtual const char * NotificationToneIdent(unsigned ringtoneNumber) = 0;
    virtual void NotificationTonePlay(const char *deviceId, enum RingerDeviceMode deviceMode, const char *ident) = 0;

    virtual void Close() = 0; 
};

#endif /* defined(__cplusplus) */
NAMESPACE_END
