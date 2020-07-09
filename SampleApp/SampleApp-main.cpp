
/*-----------------------------------------------------------------------------------------------*/
/* Based on innovaphone App template                                                             */
/* copyright (c) innovaphone 2016                                                                */
/*                                                                                               */
/*-----------------------------------------------------------------------------------------------*/

#include "platform/platform.h"
#include "common/build/release.h"
#include "common/os/iomux.h"
#include "common/interface/task.h"
#include "common/interface/socket.h"
#include "common/interface/webserver_plugin.h"
#include "common/interface/database.h"
#include "common/interface/json_api.h"
#include "common/interface/random.h"
#include "common/lib/appservice.h"
#include "common/lib/config.h"
#include "common/lib/tasks_postgresql.h"
#include "common/lib/appwebsocket.h"
#include "common/lib/app_updates.h"
#include "common/lib/badgecount_signaling.h"
#include "SampleApp/SampleApp_tasks.h"
#include "SampleApp/SampleApp.h"

int main(int argc, char *argv[])
{
    IRandom::Init(time(nullptr));
    class IIoMux * iomux = IIoMux::Create();
	ISocketProvider * localSocketProvider = CreateLocalSocketProvider();
    IWebserverPluginProvider * webserverPluginProvider = CreateWebserverPluginProvider();
    IDatabaseProvider * databaseProvider = CreatePostgreSQLDatabaseProvider();

    AppServiceArgs  serviceArgs;
    serviceArgs.serviceID = "sampleapp";
    serviceArgs.Parse(argc, argv);
    AppInstanceArgs instanceArgs;
    instanceArgs.appName = "sampleapp";
    instanceArgs.appDomain = "example.com";
    instanceArgs.appPassword = "pwd";
    instanceArgs.webserver = "/var/run/webserver/webserver";
    instanceArgs.webserverPath = "/sampleapp";
    instanceArgs.dbHost = "";
    instanceArgs.dbName = "sampleapp";
    instanceArgs.dbUser = "sampleapp";
    instanceArgs.dbPassword = "sampleapp";
    instanceArgs.Parse(argc, argv);
	
    SampleAppService * service = new SampleAppService(iomux, localSocketProvider, webserverPluginProvider, databaseProvider, &serviceArgs);
    if (!serviceArgs.manager) service->AppStart(&instanceArgs);
    iomux->Run();

    delete service;
	delete localSocketProvider;
    delete webserverPluginProvider;
    delete iomux;
    delete debug;
    
    return 0;
}
