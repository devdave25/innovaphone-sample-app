/*---------------------------------------------------------------------------*/
/* services.h                                                                */
/* copyright (c) innovaphone 2018                                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/

extern class IServicesApi * CreateServicesApi(class UServicesApi * user, class IJsonApiConnection * conn);

class IService {
public:
    virtual const char * GetName() = 0;
    virtual const char * GetTitle() = 0;
    virtual const char * GetWebsocketUrl() = 0;
    virtual const char * GetApiInfo() = 0;
    virtual class IService * GetNext() = 0;
};

class IServicesApi {
public:
    virtual ~IServicesApi() {};
    virtual class IService * GetService(const char * api) = 0;
    virtual class IAppWebsocketAuthenticator * CreateAuthenticator(class UAppWebsocketAuthenticator * user = 0) = 0;
};

class UServicesApi {
public:
    virtual void ServicesApiUpdated(class IServicesApi * servicesApi) = 0;
    virtual void ServicesApiClosed(class IServicesApi * servicesApi) = 0;
};
