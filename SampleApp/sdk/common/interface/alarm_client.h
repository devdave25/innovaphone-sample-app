
/*---------------------------------------------------------------------------*/
/* alarm_client.h                                                            */
/* copyright (c) innovaphone 2018                                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/

#define FAULT_CODE_APPS       0x00240000

enum AlarmSeverity {
    ALARM_SEVERITY_INDETERMINATE = 0,
    ALARM_SEVERITY_MAJOR,
    ALARM_SEVERITY_CRITICAL
};

enum AlarmType {
    SET_ALARM = 0,
    CLEAR_ALARM,
    ERROR
};

typedef enum {
    AC_SHUTDOWN_NORMAL,
    AC_HTTP_CONNECTION_ERROR
} ac_shutdown_reason;

class IAlarmClient {
public:
    virtual ~IAlarmClient() {};

    static IAlarmClient * Create(class IIoMux * const iomux,
                                class ISocketProvider * const tcpSocketProvider,
                                class ISocketProvider * const tlsSocketProvider,
                                class UAlarmClient * const user,
                                class IInstanceLog * const log,
                                char * url,
                                char * username,
                                char * pwd);

    virtual void SetAlarm(dword code, AlarmSeverity severtiy, ulong64 time, const char * text, const char * details, const char * src) = 0;
    virtual void ClearAlarm(dword code, AlarmSeverity severtiy, ulong64 time, const char * text, const char * details, const char * src) = 0;
    virtual void SendEvent(dword code, AlarmSeverity severtiy, ulong64 time, const char * text, const char * details, const char * src) = 0;
    virtual void ResetConnection(char * url, char * username, char * pwd) = 0;
    virtual void Shutdown() = 0;
    virtual void ChangeAlarmTimeout(unsigned int timeout) = 0;
};

class UAlarmClient {
public:
    ~UAlarmClient() {}
    virtual void AlarmClientShutdown(IAlarmClient * const alarmClient) = 0;    
};