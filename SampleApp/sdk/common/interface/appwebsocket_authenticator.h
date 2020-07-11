/*---------------------------------------------------------------------------*/
/* appwebsocket_authenticator.h                                              */
/* copyright (c) innovaphone 2018                                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/

class IAppWebsocketAuthenticator {
public:
    virtual ~IAppWebsocketAuthenticator() {};
    virtual void SetUser(class UAppWebsocketAuthenticator * user) = 0;
    virtual void GetLogin(const char * app, const char * challenge) = 0;
};

class UAppWebsocketAuthenticator {
public:
    virtual void AppWebsocketAuthenticatorClosed(class IAppWebsocketAuthenticator * authenticator) = 0;
    virtual void AppWebsocketAuthenticatorGetLoginResult(class IAppWebsocketAuthenticator * authenticator, const char * domain, const char * sip, const char * guid, const char * dn, const char * pbxObj, const char * app, const char * info, const char * digest, const char * salt, const char * key) = 0;
    virtual void AppWebsocketAuthenticatorGetLoginError(class IAppWebsocketAuthenticator * authenticator) = 0;
};
