/*---------------------------------------------------------------------------*/
/* json_api.h                                                                */
/* copyright (c) innovaphone 2017                                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/

class UJsonApiContext {
public:
    virtual class JsonApi * CreateJsonApi(class IJsonApiConnection * connection, class json_io & msg, word base) = 0;
    virtual class JsonApi * JsonApiRequested(class IJsonApiConnection * connection) { return 0; };
    virtual const char * Name() = 0;
    class UJsonApiContext * next;
};

class JsonApiContext {
public:
    JsonApiContext() {
        providers = 0;
    }
    void RegisterJsonApi(class UJsonApiContext * provider) {
        provider->next = providers;
        providers = provider;
    }
    class JsonApi * CreateJsonApi(const char * name, class IJsonApiConnection * connection, class json_io & msg, word base) {
        for (class UJsonApiContext * p = providers; p; p = p->next) {
            if (!strcmp(name, p->Name())) return p->CreateJsonApi(connection, msg, base);
        }
        return 0;
    }
    class JsonApi * JsonApiRequested(const char * name, class IJsonApiConnection * connection) {
        for (class UJsonApiContext * p = providers; p; p = p->next) {
            if (!strcmp(name, p->Name())) return p->JsonApiRequested(connection);
        }
        return 0;
    }
    class UJsonApiContext * providers;
};

class JsonApi {
public:
    // An JsonApi instance will be managed by an AppWebsocket object. The app must not delete
    // the JsonApi object by itself.
    virtual ~JsonApi() {};
public:
    virtual const char * Name() = 0;
    virtual void JsonApiStart() {};
    virtual void Message(class json_io & msg, word base, const char * mt, const char * src) = 0;
    virtual void JsonApiConnectionClosed() = 0;
};

class IJsonApiConnection {
public:
    virtual ~IJsonApiConnection() {}
    virtual void RegisterJsonApi(class JsonApi * api) = 0;
    virtual void UnRegisterJsonApi(class JsonApi * api) = 0;
    virtual void JsonApiMessage(class json_io & msg, char * buffer) = 0;
    virtual void JsonApiMessageComplete() = 0;
    virtual bool JsonApiPermission(const char * api) = 0;
};
