
/*-----------------------------------------------------------------------------------------------*/
/* Based on innovaphone App template                                                             */
/* copyright (c) innovaphone 2018                                                                */
/*                                                                                               */
/*-----------------------------------------------------------------------------------------------*/

#include "platform/platform.h"
#include "common/os/iomux.h"
#include "common/interface/task.h"
#include "common/interface/socket.h"
#include "common/interface/webserver_plugin.h"
#include "common/interface/database.h"
#include "common/interface/json_api.h"
#include "common/ilib/str.h"
#include "common/ilib/json.h"
#include "common/lib/appservice.h"
#include "common/lib/config.h"
#include "common/lib/tasks_postgresql.h"
#include "common/lib/appwebsocket.h"
#include "common/lib/app_updates.h"
#include "common/lib/badgecount_signaling.h"

#include "SampleApp_tasks.h"
#include "SampleApp.h"

#define DBG(x) //debug->printf x

/*-----------------------------------------------------------------------------------------------*/
/* class SampleAppService                                                                        */
/*-----------------------------------------------------------------------------------------------*/

SampleAppService::SampleAppService(class IIoMux * const iomux, class ISocketProvider * localSocketProvider, class IWebserverPluginProvider * const webserverPluginProvider, class IDatabaseProvider * databaseProvider, AppServiceArgs * args) : AppService(iomux, localSocketProvider, args)
{
    this->iomux = iomux;
    this->localSocketProvider = localSocketProvider;
    this->webserverPluginProvider = webserverPluginProvider;
    this->databaseProvider = databaseProvider;
}

SampleAppService::~SampleAppService()
{

}

void SampleAppService::AppServiceApps(istd::list<AppServiceApp> * appList)
{
    appList->push_back(new AppServiceApp("reinforce-sampleapp"));
    appList->push_back(new AppServiceApp("reinforce-sampleappadmin"));
    appList->push_back(new AppServiceApp("contact-exporter"));
}

void SampleAppService::AppInstancePlugins(istd::list<AppInstancePlugin> * pluginList)
{
    pluginList->push_back(new AppInstancePlugin("reinforce.sampleappmanager", "reinforce-sampleapp.png", "reinforce.sampleappmanagertexts"));
}

class AppInstance * SampleAppService::CreateInstance(AppInstanceArgs * args)
{
    return new SampleApp(iomux, this, args);
}

/*-----------------------------------------------------------------------------------------------*/
/* class SampleApp                                                                               */
/*-----------------------------------------------------------------------------------------------*/

SampleApp::SampleApp(IIoMux * const iomux, class SampleAppService * service, AppInstanceArgs * args) : AppInstance(service, args), AppUpdates(iomux), ConfigContext(nullptr, this)
{
    this->stopping = false;
    this->iomux = iomux;
    this->service = service;
    this->webserverPlugin = service->webserverPluginProvider->CreateWebserverPlugin(iomux, service->localSocketProvider, this, args->webserver, args->webserverPath, this);
    this->database = service->databaseProvider->CreateDatabase(iomux, this, this);
    this->database->Connect(args->dbHost, args->dbName, args->dbUser, args->dbPassword);
    this->logFlags |= LOG_APP;
    this->logFlags |= LOG_APP_WEBSOCKET;
    this->logFlags |= LOG_DATABASE;
	this->currentTask = nullptr;
	this->currentId = 0;
	this->count = 0;

    RegisterJsonApi(this);

    Log("App instance started");
}

SampleApp::~SampleApp()
{
    debug->printf("aa");
}

void SampleApp::DatabaseConnectComplete(IDatabase * const database)
{
    currentTask = new DatabaseInit(this, database);
}

void SampleApp::DatabaseInitComplete()
{
    delete currentTask;
    currentTask = new CountInit(this);
}

void SampleApp::CountInitComplete()
{
    delete currentTask;
    currentTask = new ConfigInit(this, database);
}

void SampleApp::ConfigInitComplete()
{
    delete currentTask;
    currentTask = nullptr;

    webserverPlugin->HttpListen(nullptr, nullptr, nullptr, nullptr, _BUILD_STRING_);
    webserverPlugin->WebsocketListen();
    Log("App instance initialized");
}

void SampleApp::SampleAppSessionClosed(class SampleAppSession * session)
{
    sessionList.remove(session);
    delete session;
    if (stopping) {
        TryStop();
    }
}

void SampleApp::DatabaseShutdown(IDatabase * const database, db_error_t reason)
{
    this->database = nullptr;
    TryStop();
}

void SampleApp::DatabaseError(IDatabase * const database, db_error_t error)
{

}

void SampleApp::ServerCertificateUpdate(const byte * cert, size_t certLen)
{
    Log("SampleApp::ServerCertificateUpdate cert:%x certLen:%u", cert, certLen);
}

void SampleApp::WebserverPluginWebsocketListenResult(IWebserverPlugin * plugin, const char * path, const char * registeredPathForRequest, const char * host)
{
    if (!this->stopping) {
        class SampleAppSession * session = new SampleAppSession(this);
        this->sessionList.push_back(session);
    }
    else {
        plugin->Cancel(wsr_cancel_type_t::WSP_CANCEL_UNAVAILABLE);
    }
}

void SampleApp::WebserverPluginHttpListenResult(IWebserverPlugin * plugin, ws_request_type_t requestType, char * resourceName, const char * registeredPathForRequest, size_t dataSize)
{
    if (requestType == WS_REQUEST_GET) {
        if (plugin->BuildRedirect(resourceName, _BUILD_STRING_, strlen(_BUILD_STRING_))) {
            return;
        }
    }
    plugin->Cancel(WSP_CANCEL_NOT_FOUND);
}

void SampleApp::WebserverPluginClose(IWebserverPlugin * plugin, wsp_close_reason_t reason, bool lastUser)
{
    Log("WebserverPlugin closed");
    if (lastUser) {
        delete webserverPlugin;
        webserverPlugin = nullptr;
        TryStop();
    }
}

void SampleApp::Stop()
{
    TryStop();
}

void SampleApp::TryStop()
{
    if (!stopping) {
        Log("App instance stopping");
        stopping = true;
        if (webserverPlugin) webserverPlugin->Close();
        if (database) database->Shutdown();
        for (std::list<SampleAppSession *>::iterator it = sessionList.begin(); it != sessionList.end(); ++it) {
            (*it)->Close();
        }
    }
    
    if (!webserverPlugin && !database && sessionList.empty()) appService->AppStopped(this);
}

void SampleApp::CreateBadgeCountPresenceMonitor(class BadgeCountSignaling * signaling, int call, const char * cg, const char * cd)
{
    new SampleAppBadgeCountPresenceMonitor(this, signaling, call, cg, cd);
}

/*-----------------------------------------------------------------------------------------------*/
/* class SampleAppSession                                                                        */
/*-----------------------------------------------------------------------------------------------*/

SampleAppSession::SampleAppSession(class SampleApp * instance) : AppUpdatesSession(instance, instance->webserverPlugin, instance, instance)
{
    this->instance = instance;

    this->badgecount = nullptr;

    this->currentTask = nullptr;
    this->currentSrc = nullptr;
    this->closed = false;
    this->closing = false;

    this->admin = false;
    this->adminApp = false;
}

SampleAppSession::~SampleAppSession()
{
    if (badgecount) delete badgecount;
}

void SampleAppSession::AppWebsocketMessage(class json_io & msg, word base, const char * mt, const char * src)
{
    if (currentSrc) free(currentSrc);
    currentSrc = src ? _strdup(src) : nullptr;
    if (!strcmp(mt, "MonitorCount")) {
        currentTask = new MonitorCount(this, instance->database, sip, dn);
    }
    else if (!strcmp(mt, "IncrementCount")) {
        currentTask = new IncrementCount(this, instance->database, sip, dn);
    }
    else if (!strcmp(mt, "PutContacts")) {
        debug->printf("HERE PutContacts ------------------------------------");

        /*instance->service

        class IService* service = services.GetService("com.innovaphone.provisioning");
        if (service) {
            appWebsocketClient->Connect(service->GetWebsocketUrl(), service->GetName(), servicesApi->CreateAuthenticator());
        }*/

    }
    else if (!strcmp(mt, "ResetCount")) {
        if (adminApp) currentTask = new ResetCount(this, instance->database, sip, dn);
        else AppWebsocketClose();
    }
    else if (!strcmp(mt, "PbxInfo")) {
        badgecount = new BadgeCountSignaling(instance, this);
        AppWebsocketMessageComplete();
    }
    else {
        AppWebsocketMessageComplete();
    }
}

void SampleAppSession::AppWebsocketAppInfo(const char * app, class json_io & msg, word base)
{

}

bool SampleAppSession::AppWebsocketConnectComplete(class json_io & msg, word info)
{
    const char * appobj = msg.get_string(info, "appobj");
    if (appobj && !strcmp(appobj, sip)) admin = true;
    if (!strcmp(app, "reinforce-sampleappAdmin")) adminApp = true;
    return true;
}

void SampleAppSession::AppWebsocketClosed()
{
    closed = true;
    TryClose();
}

void SampleAppSession::ResponseSent()
{
    if (currentTask) {
        currentTask->Finished();
    }
    else {
        AppWebsocketMessageComplete();
    }
}

void SampleAppSession::TryClose()
{
    closing = true;
    if (!closed) {
        AppWebsocketClose();
        return;
    }
    if (currentTask) {
        currentTask->Stop();
        return;
    }
    if (closed && !currentTask) {
        instance->SampleAppSessionClosed(this);
    }
}

void SampleAppSession::Close()
{
    TryClose();
}

bool SampleAppSession::CheckSession()
{
    if (closing) {
        currentTask = nullptr;
        TryClose();
        return false;
    }
    return true;
}

/*-----------------------------------------------------------------------------------------------*/
/* MonitorCount                                                                                  */
/*-----------------------------------------------------------------------------------------------*/

MonitorCount::MonitorCount(class SampleAppSession * session, IDatabase * database, const char * sip, const char * dn) : TaskReadWriteCount(database, sip, dn, session->instance->count, false)
{
    this->session = session;
    this->sip = _strdup(sip);
    Start(nullptr);
}

MonitorCount::~MonitorCount()
{
    free(sip);
}

void MonitorCount::Complete()
{
    if (session->CheckSession()) {
        char sb[1000];
        char b[100];
        char * tmp = b;
        class json_io send(sb);
        word base = send.add_object(0xffff, nullptr);
        send.add_string(base, "mt", "MonitorCountResult");
        if (session->currentSrc) send.add_string(base, "src", session->currentSrc);
        send.add_ulong64(base, "count", session->instance->count, tmp);
        session->SendResponse(send, sb);

        session->instance->StartUpdate(new SampleAppBadgeCountUpdate(session->instance, sip, 0, 0, nullptr));
    }
}

void MonitorCount::Failed()
{
    Complete();
}

void MonitorCount::Finished()
{
    session->currentTask = nullptr;
    session->AppWebsocketMessageComplete();
    new SampleAppCountFilter(session, session->currentSrc);
    delete this;
}

/*-----------------------------------------------------------------------------------------------*/
/* IncrementCount                                                                                */
/*-----------------------------------------------------------------------------------------------*/

IncrementCount::IncrementCount(class SampleAppSession * session, IDatabase * database, const char * sip, const char * dn) : TaskReadWriteCount(database, sip, dn, ++session->instance->count, true)
{
    this->session = session;
    this->sip = _strdup(sip);
    Start(nullptr);
}

IncrementCount::~IncrementCount()
{
    free(sip);
}

void IncrementCount::Complete()
{
    if (session->CheckSession()) {
        char sb[1000];
        char b[100];
        char * tmp = b;
        class json_io send(sb);
        word base = send.add_object(0xffff, nullptr);
        send.add_string(base, "mt", "IncrementCountResult");
        if (session->currentSrc) send.add_string(base, "src", session->currentSrc);
        send.add_ulong64(base, "count", session->instance->count, tmp);
        session->SendResponse(send, sb);

        session->instance->StartUpdate(new SampleAppCountUpdate(session->instance, session->sessionId, session->instance->count));
        session->instance->StartUpdate(new SampleAppBadgeCountUpdate(session->instance, nullptr, 1, 0, sip));
    }
}

void IncrementCount::Failed()
{
    Complete();
}

void IncrementCount::Finished()
{
    session->currentTask = nullptr;
    session->AppWebsocketMessageComplete();
    delete this;
}

/*-----------------------------------------------------------------------------------------------*/
/* ResetCount                                                                                    */
/*-----------------------------------------------------------------------------------------------*/

ResetCount::ResetCount(class SampleAppSession * session, IDatabase * database, const char * sip, const char * dn) : TaskReadWriteCount(database, sip, dn, (session->instance->count = 0), true)
{
    this->session = session;
    Start(nullptr);
}

void ResetCount::Complete()
{
    if (session->CheckSession()) {
        char sb[1000];
        char b[100];
        char * tmp = b;
        class json_io send(sb);
        word base = send.add_object(0xffff, nullptr);
        send.add_string(base, "mt", "ResetCountResult");
        if (session->currentSrc) send.add_string(base, "src", session->currentSrc);
        send.add_ulong64(base, "count", GetCount(), tmp);
        session->SendResponse(send, sb);

        session->instance->StartUpdate(new SampleAppCountUpdate(session->instance, session->sessionId, session->instance->count));
    }
}

void ResetCount::Failed()
{
    Complete();
}

void ResetCount::Finished()
{
    session->currentTask = nullptr;
    session->AppWebsocketMessageComplete();
    delete this;
}

/*-----------------------------------------------------------------------------------------------*/
/* SampleAppCountUpdate                                                                          */
/*-----------------------------------------------------------------------------------------------*/

SampleAppCountUpdate::SampleAppCountUpdate(class SampleApp * instance, ulong64 originator, ulong64 count) :
AppUpdate(instance->countFilters, nullptr)
{
    this->instance = instance;
    this->originator = originator;
    this->count = count;
}

SampleAppCountUpdate::~SampleAppCountUpdate()
{
}

/*-----------------------------------------------------------------------------------------------*/

SampleAppCountFilter::SampleAppCountFilter(class SampleAppSession * session, const char * src) : AppUpdatesFilter<SampleAppCountUpdate>(session->instance->countFilters, session, src)
{
    this->session = session;
}

SampleAppCountFilter::~SampleAppCountFilter()
{
}

bool SampleAppCountFilter::Test(SampleAppCountUpdate * update)
{
    if (GetSessionId() == update->originator) return false;
    return true;
}

void SampleAppCountFilter::Send(SampleAppCountUpdate * update)
{
    char sb[1000];
    char b[100];
    char * tmp = b;
    class json_io send(sb);
    word base = send.add_object(0xffff, nullptr);
    send.add_string(base, "mt", "UpdateCount");
    send.add_string(base, "src", GetSrc());
    send.add_ulong64(base, "count", update->count, tmp);

    SendUpdate(send, sb);
    session->instance->StartUpdate(new SampleAppBadgeCountUpdate(session->instance, session->sip, 0, 0, nullptr));
}

/*-----------------------------------------------------------------------------------------------*/
/* SampleAppBadgeCountUpdate                                                                     */
/*-----------------------------------------------------------------------------------------------*/

SampleAppBadgeCountUpdate::SampleAppBadgeCountUpdate(class SampleApp * instance, const char * dst, int delta, unsigned count, const char * originator) : AppUpdate(instance->badgeCountFilters, dst)
{
    this->delta = delta;
    this->count = count;
    this->originator = _strdup(originator);
}

SampleAppBadgeCountUpdate::~SampleAppBadgeCountUpdate()
{

}

/*-----------------------------------------------------------------------------------------------*/

SampleAppBadgeCountPresenceMonitor::SampleAppBadgeCountPresenceMonitor(class SampleApp * instance, class BadgeCountSignaling * signaling, int call, const char * cg, const char * cd) : BadgeCountPresenceMonitor(signaling, call), AppUpdatesFilter<SampleAppBadgeCountUpdate>(instance->badgeCountFilters, signaling->session, nullptr, cg), TaskReadUserCount(instance->database, cg)
{
    this->instance = instance;
    count = -1;
    delta = 0;
    initialized = false;
    Start(nullptr);
}

void SampleAppBadgeCountPresenceMonitor::Complete()
{
    initialized = true;
    if (count == -1) {
        count = GetCount() < instance->count ? instance->count - GetCount() : 0;
    }
    count += delta;
    SendBadge(count);
}

bool SampleAppBadgeCountPresenceMonitor::Test(SampleAppBadgeCountUpdate * update)
{
    if (update->originator && !strcmp(update->originator, GetUser())) return false;
    return true;
}

void SampleAppBadgeCountPresenceMonitor::Send(SampleAppBadgeCountUpdate * update)
{
    if (initialized) {
        if (update->delta) count += update->delta;
        else count = update->count;
        SendBadge(count);
    }
    else {
        if (update->delta) {
            delta += update->delta;
        }
        else {
            count = update->count;
            delta = 0;
        }
    }
}
