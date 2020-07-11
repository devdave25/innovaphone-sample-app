/*---------------------------------------------------------------------------*/
/* appservice.h                                                              */
/* copyright (c) innovaphone 2016                                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/

enum ServiceAlarmSeverity {
    ALARM_SEVERITY_INDETERMINATE,
    ALARM_SEVERITY_MAJOR,
    ALARM_SEVERITY_CRITICAL
};

enum ServiceAlarmType {
    ALARM_TYPE_SET,
    ALARM_TYPE_CLEAR,
    ALARM_TYPE_ERROR
};

struct AppInstanceArgs {
    AppInstanceArgs();
    void Parse(int argc, char ** argv, bool keepDefaults = true);
    const char * appName;
    const char * appDomain;
    const char * appPassword;
    const char * webserver;
    const char * webserverPath;
    const char * dbHost;
    const char * dbName;
    const char * dbUser;
    const char * dbPassword;
    const char * workingPath;
    ulong64 logFlags;
};

struct AppServiceArgs {
    AppServiceArgs();
    void Parse(int argc, char ** argv, bool keepDefaults = true);
    const char * serviceID;
    const char * manager;
    const char * appPlatformDNSName;
    ulong64 logFlags;
    bool segfaulted;
    bool disableHexdumps;
    off_t logFileSize;
};

class AppServiceApp : public istd::listElement<AppServiceApp> {
    char * name;
    bool websocketOnly;

public:
    AppServiceApp(const char * name, bool websocketOnly = false);
    ~AppServiceApp();

    const char * GetName();
    bool IsWebsocketOnly();
};

class AppInstancePlugin : public istd::listElement<AppInstancePlugin> {
    char * plugin;
    char * icon;
    char * langFile;
    char * api;

public:
    AppInstancePlugin(const char * plugin, const char * icon, const char * langFile, bool wildcard = false, const char * api = NULL);
    ~AppInstancePlugin();

    bool wildcard;

    const char * GetIcon();
    const char * GetApi();
    const char * GetPlugin();
    const char * GetLangFile();
};

class AppServiceSocket : public IShutdownHandler, public USocket, public IInstanceLog {
    class IIoMux * const iomux;
    class ISocketProvider * const localSocketProvider;
    class ISocket * socket;
    class UAppServiceSocket * const user;
    bool connected, appServiceClosed, closing;
    char * recvBuffer, *serviceID;

    void AppSocketShutdown();
    void AppSocketMessageSend(class json_io & send, char * buff);
    void SocketRecv(size_t len, bool partial);
    void ShutdownTimeout() override;
    void TryShutdown();

    void SocketConnectComplete(ISocket * const socket) override;
    void SocketShutdown(ISocket * const socket, shutdownreason_t reason) override;
    void SocketSendResult(ISocket * const socket) override;
    void SocketRecvResult(ISocket * const socket, void * buf, size_t len) override;
    void SocketRecvCanceled(ISocket * const socket, void * buf) override;

public:
    AppServiceSocket(class IIoMux * const iomux, class ISocketProvider * const localSocketProvider, class UAppServiceSocket * const user);
    ~AppServiceSocket();

    void Connect(const char * address, const char * serviceID);
    void Shutdown() override;
    void AppSendStatus(const char * appName, const char * appDomain, bool status, const char * webserverPath);
    void AppSendAlarm(ServiceAlarmType type, ServiceAlarmSeverity severity, word code, const char * text, const char * details, const char * serviceID, const char * appName, const char * appDomain);
    void AppServiceShutdownComplete();

    const char * GetAppDomain() const override { return NULL; }
    const char * GetAppName() const override { return NULL; }

};

class UAppServiceSocket {
public:
    ~UAppServiceSocket() {};

    virtual void AppServiceShutdown() = 0;
    virtual void AppServiceShutdownTimeout() = 0;
    virtual void AppStart(AppInstanceArgs * args) = 0;
    virtual void UpdateServerCertificate(const char * cert) = 0;
    virtual void AppServiceApps(istd::list<AppServiceApp> * appList) = 0;
    virtual void AppStop(const char * appName, const char * appDomain) = 0;
    virtual void AppSetLogFlags(const char * appName, const char * appDomain, ulong64 logFlags) = 0;
    virtual void UpdateAppPlatformDNSName(const char * dnsName) {};
    virtual void AppInstancePlugins(istd::list<AppInstancePlugin> * pluginList) {};
    virtual void AppDomain(const char * appName, const char * appDomain, const char * domain, const char * pwd) {};
};

class AppService : public UAppServiceSocket, public IInstanceLog {
    friend class AppInstance;
    class AppServiceSocket serviceSocket;

    bool appsClosed;
    bool closing;
    class btree * appInstances;
    byte * cert;
    size_t certLen;
    char * serviceID;
    char * appPlatformDNSName;

    void AppServiceShutdown() override;
    void AppServiceShutdownTimeout() override;
    void AppStop(const char * appName, const char * appDomain) override;
    void UpdateServerCertificate(const char * cert) override;
    void AppSetLogFlags(const char * appName, const char * appDomain, ulong64 logFlags) override;
    void UpdateAppPlatformDNSName(const char * dnsName) override;
    void AppDomain(const char * appName, const char * appDomain, const char * domain, const char * pwd) override;
    void CloseApps();

    void TryStop();

    const char * GetAppDomain() const override { return NULL; }
    const char * GetAppName() const override { return NULL; }

public:
    AppService(class IIoMux * const iomux, class ISocketProvider * const localSocketProvider, AppServiceArgs * serviceArgs);
    virtual ~AppService();

    void AppStart(AppInstanceArgs * args) override;
    void AppStopped(class AppInstance * instance);
    const char * GetAppServiceId() const;
    const char * GetAppPlatformDNSName() const;
    void SetAllInstancesLogFlags(ulong64 logFlags);

    virtual class AppInstance * CreateInstance(AppInstanceArgs * args) = 0;
    virtual void AppServiceApps(istd::list<AppServiceApp> * appList) = 0;
    virtual void AppInstancePlugins(istd::list<AppInstancePlugin> * pluginList) {};
};

class AppInstance : public btree, public IInstanceLog {
private:
    char * key;

    virtual int btree_compare(void * key);
    virtual int btree_compare(class btree * b);

protected:
    AppInstanceArgs args;
    class AppService * appService;

public:
    AppInstance(class AppService * appService, AppInstanceArgs * args);
    virtual ~AppInstance();

    const char * GetAppServiceId() const { return appService->GetAppServiceId(); };
    const char * GetAppName() const override;
    const char * GetAppDomain() const override;
    const char * GetKey() const;
    void SetLogFlags(ulong64 logFlags) { this->logFlags = logFlags; };
    static char * GenerateKey(const char * appName, const char * appDomain);

    inline void LogV(const char * format, va_list ap)
    {
        // do only trace is LOG_APP is set
        if (this->logFlags & LOG_APP) {
            debug->appPrintfV(this->args.appName, this->args.appDomain, format, ap);
        }
    }

    inline void Log(const char * format, ...)
    {
        // do only trace is LOG_APP is set
        if (this->logFlags & LOG_APP) {
            va_list ap;
            va_start(ap, format);
            debug->appPrintfV(this->args.appName, this->args.appDomain, format, ap);
            va_end(ap);
        }
    }

    inline void HexDump(const void * buffer, size_t size)
    {
        // do only trace is LOG_APP is set
        if (this->logFlags & LOG_APP) {
            debug->appHexdump(this->args.appName, this->args.appDomain, buffer, size);
        }
    }

    virtual void Stop() = 0;
    virtual void ServerCertificateUpdate(const byte * cert, size_t certLen) {};

    void SetAlarm(word code, ServiceAlarmSeverity severity, const char * text, const char * details);
    void ClearAlarm(word code, ServiceAlarmSeverity severity, const char * text, const char * details);
    void SendEvent(word code, ServiceAlarmSeverity severity, const char * text, const char * details);

    virtual void SetAppDomain(const char * domain, const char * pwd) {};
};

