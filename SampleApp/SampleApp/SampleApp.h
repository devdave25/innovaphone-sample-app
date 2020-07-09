
/*-----------------------------------------------------------------------------------------------*/
/* Based on innovaphone App template                                                             */
/* copyright (c) innovaphone 2018                                                                */
/*                                                                                               */
/*-----------------------------------------------------------------------------------------------*/

class SampleAppService : public AppService {
    class AppInstance * CreateInstance(AppInstanceArgs * args) override;
    void AppServiceApps(istd::list<AppServiceApp> * appList) override;
    void AppInstancePlugins(istd::list<AppInstancePlugin> * pluginList) override;

public:
    SampleAppService(class IIoMux * const iomux, class ISocketProvider * localSocketProvider, IWebserverPluginProvider * const webserverPluginProvider, IDatabaseProvider * databaseProvider, AppServiceArgs * args);
    ~SampleAppService();

    class IIoMux * iomux;
    class ISocketProvider * localSocketProvider;
    class IWebserverPluginProvider * webserverPluginProvider;
    class IDatabaseProvider * databaseProvider;
};

class SampleApp : public AppInstance, public AppUpdates, public UDatabase, public UWebserverPlugin, public JsonApiContext, public ConfigContext, public UBadgeCountSignaling
{
    void DatabaseConnectComplete(IDatabase * const database) override;
    void DatabaseShutdown(IDatabase * const database, db_error_t reason) override;
    void DatabaseError(IDatabase * const database, db_error_t error) override;

    void WebserverPluginClose(IWebserverPlugin * plugin, wsp_close_reason_t reason, bool lastUser) override;
    void WebserverPluginWebsocketListenResult(IWebserverPlugin * plugin, const char * path, const char * registeredPathForRequest, const char * host) override;
    void WebserverPluginHttpListenResult(IWebserverPlugin * plugin, ws_request_type_t requestType, char * resourceName, const char * registeredPathForRequest, size_t dataSize) override;

    void ServerCertificateUpdate(const byte * cert, size_t certLen) override;
    void Stop() override;

    void CreateBadgeCountPresenceMonitor(class BadgeCountSignaling * signaling, int call, const char * user, const char * topic) override;

    void TryStop();

    bool stopping;
    class ITask * currentTask;
    std::list<class SampleAppSession *> sessionList;

public:
    SampleApp(IIoMux * const iomux, SampleAppService * service, AppInstanceArgs * args);
    ~SampleApp();

    void DatabaseInitComplete();
    void CountInitComplete();
    void ConfigInitComplete();
    void SampleAppSessionClosed(class SampleAppSession * session);

    const char * appPwd() { return args.appPassword; };

    class IIoMux * iomux;
    class SampleAppService * service;
    class IWebserverPlugin * webserverPlugin;
    class IDatabase * database;
    long64 count;

    class AppUpdatesFilters countFilters;
    class AppUpdatesFilters badgeCountFilters;

    ulong64 currentId;
};

class DatabaseInit : public TaskDatabaseInit {
    class SampleApp * instance;
public:
    DatabaseInit(class SampleApp * instance, IDatabase * database) : TaskDatabaseInit(database) {
        this->instance = instance;
        Start(nullptr);
    }
    void Complete() { instance->DatabaseInitComplete(); };
};

class ConfigInit : public ITask, public UTask {
    class SampleApp * instance;
    class ITask * task;
    void Start(class UTask * user) override {};
    void TaskComplete(class ITask * task) override { instance->ConfigInitComplete(); };
    void TaskFailed(class ITask * task) override {};
public:
    ConfigInit(class SampleApp * instance, class IDatabase * database) {
        this->instance = instance;
        task = instance->CreateInitTask(database);
        task->Start(this);
    }
};

class CountInit : public TaskReadWriteCount {
    class SampleApp * instance;
public:
    CountInit(class SampleApp * instance) : TaskReadWriteCount(instance->database, nullptr, nullptr, -1, false) {
        this->instance = instance;
        Start(nullptr);
    }
    void Complete() {
        instance->count = GetCount();
        instance->CountInitComplete();
    }
};

class SampleAppSession : public AppUpdatesSession {
    void AppWebsocketAccept(class UWebsocket * uwebsocket) { instance->webserverPlugin->WebsocketAccept(uwebsocket); };
    char * AppWebsocketPassword() override { return (char *)instance->appPwd(); };
    void AppWebsocketMessage(class json_io & msg, word base, const char * mt, const char * src) override;
    void AppWebsocketAppInfo(const char * app, class json_io & msg, word base) override;
    bool AppWebsocketConnectComplete(class json_io & msg, word info) override;
    void AppWebsocketClosed() override;

    void ResponseSent() override;

    void TryClose();

    bool closed;
    bool closing;
    bool admin;
    bool adminApp;
    class BadgeCountSignaling * badgecount;

public:
    SampleAppSession(class SampleApp * instance);
    ~SampleAppSession();

    bool CheckSession();

    class SampleApp * instance;
    char * currentSrc;
    class ITask * currentTask;
    void Close();
};

class MonitorCount : public TaskReadWriteCount {
    class SampleAppSession * session;
    char * sip;
public:
    MonitorCount(class SampleAppSession * session, IDatabase * database, const char * sip, const char * dn);
    ~MonitorCount();
    void Complete();
    void Failed();
    void Finished();
};

class IncrementCount : public TaskReadWriteCount {
    class SampleAppSession * session;
    char * sip;
public:
    IncrementCount(class SampleAppSession * session, IDatabase * database, const char * sip, const char * dn);
    ~IncrementCount();
    void Complete();
    void Failed();
    void Finished();
};

class ResetCount : public TaskReadWriteCount {
    class SampleAppSession * session;
public:
    ResetCount(class SampleAppSession * session, IDatabase * database, const char * sip, const char * dn);
    void Complete();
    void Failed();
    void Finished();
};

class SampleAppCountUpdate : public AppUpdate {
    class SampleApp * instance;
public:
    SampleAppCountUpdate(class SampleApp * instance, ulong64 originator, ulong64 count);
    ~SampleAppCountUpdate();

    ulong64 originator;
    ulong64 count;
};

class SampleAppCountFilter : public AppUpdatesFilter<SampleAppCountUpdate> {
    bool Test(SampleAppCountUpdate * update) override;
    void Send(SampleAppCountUpdate * update) override;

    class SampleAppSession * session;
public:
    SampleAppCountFilter(class SampleAppSession * session, const char * src);
    ~SampleAppCountFilter();
};

class SampleAppBadgeCountUpdate : public AppUpdate {

public:
    SampleAppBadgeCountUpdate(class SampleApp * instance, const char * dst = nullptr, int delta = 0, unsigned count = 0, const char * originator = nullptr);
    virtual ~SampleAppBadgeCountUpdate();

    ulong64 count;
    int delta;
    char * originator;
};

class SampleAppBadgeCountPresenceMonitor : public BadgeCountPresenceMonitor, public AppUpdatesFilter<SampleAppBadgeCountUpdate>, public TaskReadUserCount {
    bool Test(SampleAppBadgeCountUpdate * update) override;
    void Send(SampleAppBadgeCountUpdate * update) override;

    void Complete() override;

    class SampleApp * instance;
    long64 count;
    int delta;
    bool initialized;
public:
    SampleAppBadgeCountPresenceMonitor(class SampleApp * instance, class BadgeCountSignaling * signaling, int call, const char * cg, const char * cd);
};


