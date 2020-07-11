
/*---------------------------------------------------------------------------*/
/* app_updates.h                                                             */
/* copyright (c) innovaphone 2017                                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/

class AppUpdates : public UIoExec {
    friend class AppUpdatesSession;

    void IoExec(void * execContext);
    IIoMux * iomux;
    istd::list<class AppUpdatesSession> sessions;
    istd::list<class AppUpdate> updates;
    class AppUpdatesFilterY * currentFilter;
    ulong64 nextSessionId;

public:
    AppUpdates(IIoMux * const iomux);
    void StartUpdate(class AppUpdate * update);
};

class AppUpdatesSession : public AppWebsocket, public istd::listElement<AppUpdatesSession> {
    friend class AppUpdates;
    friend class AppUpdatesFilterY;

    void AppWebsocketSendResult();
    void virtual ResponseSent() = 0;
    void virtual UpdateSent();

    bool sendingUpdate;
    bool sendingResponse;
    class btree * srcs;
    istd::list<class AppUpdatesQueuedSession> queue;

public:
    AppUpdatesSession(class AppUpdates * app, IWebserverPlugin * plugin, class IInstanceLog * const log, class JsonApiContext * jsonApiContext);
    ~AppUpdatesSession();
    void SendResponse(class json_io & msg, char * buffer);
    void SendUpdate(class json_io & msg, char * buffer);
    void AppFilterClose(istd::list<AppUpdatesFilterY> & filters, const char * src);
    class AppUpdatesFilterY * AppFilterGet(istd::list<AppUpdatesFilterY> & filters, const char * src);

    class AppUpdates * instance;
    ulong64 sessionId;
    unsigned responsePending;
};

class AppUpdate : public istd::listElement<AppUpdate> {
    friend class AppUpdates;
    friend class AppUpdatesQueued;

    unsigned queuedCount;
    class AppUpdatesUser * user;
    istd::list<AppUpdatesFilterY> * filters;

public:
    AppUpdate(class AppUpdatesFilters & filters, const char * sip = 0);
    virtual ~AppUpdate();
};

class AppUpdatesQueuedSession : public istd::listElement<AppUpdatesQueuedSession> {};
class AppUpdatesQueuedFilter : public istd::listElement<AppUpdatesQueuedFilter> {};
class AppUpdatesQueued : public AppUpdatesQueuedSession, public AppUpdatesQueuedFilter {
    friend class AppUpdates;
    friend class AppUpdatesSession;

    AppUpdatesQueued(class AppUpdate * update, class AppUpdatesFilterY * filter);
    ~AppUpdatesQueued();

    class AppUpdate * update;
    class AppUpdatesFilterY * filter;
};

class AppUpdatesUser : public btree {
    friend class AppUpdates;
    friend class AppUpdate;
    friend class AppUpdatesSession;
    friend class AppUpdatesFilterY;

    AppUpdatesUser(class AppUpdatesFilterY * filter, class btree * & tree, const char * sip);
    ~AppUpdatesUser();

    int btree_compare(void * key) { return strcmp((const char *)key, sip); };
    int btree_compare(class btree * b) { return strcmp(((class AppUpdatesUser *)b)->sip, sip); };

    const char * sip;
    class AppUpdatesFilterY * filters;
    class btree * & tree;
    unsigned refCount;
};

struct filters_ctx {
    const char * src;
    void * filters;
    filters_ctx(void * filters, const char * src) { this->filters = filters; this->src = src; };
};
class AppUpdatesFilterY : public istd::listElement<AppUpdatesFilterY>, public btree {
    friend class AppUpdates;
    friend class AppUpdatesSession;

    int btree_compare(void * key) {
        struct filters_ctx * ctx = (struct filters_ctx *)key;
        if (ctx->filters == filters) return strcmp(ctx->src, src);
        else if (ctx->filters > filters) return 1;
        return -1;
    }
    int btree_compare(class btree * b) {
        if (((class AppUpdatesFilterY *)b)->filters == filters) return strcmp(((class AppUpdatesFilterY *)b)->src, src);
        else if (((class AppUpdatesFilterY *)b)->filters > filters) return 1;
        return -1;
    }
    virtual bool Test(class AppUpdate * update) = 0;
    virtual void Send(class AppUpdate * update) = 0;

    class AppUpdatesUser * user;
    istd::list<class AppUpdatesQueuedFilter> queue;
    char * src;
    void * filters;
    class AppUpdatesSession * session;

public:
    AppUpdatesFilterY(istd::list<AppUpdatesFilterY> & filters, class btree * & usersTree, class AppUpdatesSession * session, const char * src, const char * sip);
    virtual ~AppUpdatesFilterY();
    ulong64 GetSessionId() { return session->sessionId; };
    void SendUpdate(class json_io & msg, char * buffer) { session->SendUpdate(msg, buffer); };
    const char * GetSrc() { return src; };
    const char * GetUser() { return user ? user->sip : 0; };
};

class AppUpdatesFilters {
public:
    AppUpdatesFilters() {
        usersTree = 0;
    }
    istd::list<AppUpdatesFilterY> list;
    class btree * usersTree;
};

template <class U> class AppUpdatesFilter : public AppUpdatesFilterY {
    bool Test(class AppUpdate * update) { return Test((U *)update); };
    void Send(class AppUpdate * update) { Send((U *)update); };
    virtual bool Test(U * update) = 0;
    virtual void Send(U * update) = 0;

public:
    AppUpdatesFilter(AppUpdatesFilters & filters, class AppUpdatesSession * session, const char * src, const char * sip = 0) : AppUpdatesFilterY(filters.list, filters.usersTree, session, src, sip) { };
    virtual ~AppUpdatesFilter() {};
};

