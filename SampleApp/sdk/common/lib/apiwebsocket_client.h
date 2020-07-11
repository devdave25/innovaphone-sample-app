
/*---------------------------------------------------------------------------*/
/* apiwebsocket_client.h                                                     */
/* copyright (c) innovaphone 2017                                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/

class ApiWebsocketProviderRef : public btree {
    friend class ApiWebsocketClient;

    int btree_compare(void * key) override { return strcmp(api, (char *)key); }
    int btree_compare(class btree * b) override { return strcmp(api, ((class ApiWebsocketProviderRef *)b)->api); }

    char * api;
    unsigned refCount;

public:
    ApiWebsocketProviderRef(const char * api) { this->api = _strdup(api); refCount = 0; }
    ~ApiWebsocketProviderRef() { free(api); }
};

class ApiWebsocketBacklogBuffer : public istd::listElement<class ApiWebsocketBacklogBuffer> {
public:
    ApiWebsocketBacklogBuffer(const void * data, size_t len, class ApiProvider * provider, class ApiConsumer * consumer) {
        if (data && (len != 0)) {
            buffer = malloc(len);
            memcpy(buffer, data, len);
        }
        length = len;
        this->provider = provider;
        this->consumer = consumer;
    }
    ~ApiWebsocketBacklogBuffer() {
        if (buffer) free(buffer);
    }

    void * buffer;
    size_t length;
    class ApiProvider * provider;
    class ApiConsumer * consumer;
};

class ApiWebsocketClient : public UWebsocketClient, public UTimer, public USocket {
    friend class ApiProvider;
    friend class ApiConsumer;
    void WebsocketConnectComplete(IWebsocketClient * const websocket) override;
    void WebsocketCloseComplete(IWebsocketClient * const websocket, closereason_t reason) override;
    void WebsocketSendResult(IWebsocketClient * const websocket) override;
    void WebsocketRecvResult(IWebsocketClient * const websocket, void * buf, size_t len, bool text, bool isFragment) override;
    void * WebsocketRecvBuffer(size_t len) override;
    void WebsocketRecvCanceled(IWebsocketClient * const websocket, void * buf) override;
    void TimerOnTimeout(ITimer * timer) override;

    ISocket * localSocket;
    char recvBuf[WS_MAX_DATA_SIZE];
    unsigned recvLen;
    unsigned jsonLevel;
    bool jsonQuotes;
    bool jsonEsc;

    void SocketConnectComplete(ISocket * const socket) override;
    void SocketShutdown(ISocket * const socket, shutdownreason_t reason) override;
    void SocketSendResult(ISocket * const socket) override;
    void SocketRecvResult(ISocket * const socket, void * buf, size_t len) override;
    void SocketRecvCanceled(ISocket * const socket, void * buf) override {};

    void TryClose();
    void ApiProviderClosed(class ApiProvider * provider);
    void ApiConsumerClosed(class ApiConsumer * consumer);

    bool up;
    bool closing;
    class IIoMux * iomux;
    class ISocketProvider * localSocketProvider;
    class ISocketProvider * tcp;
    class ISocketProvider * tls;
    class IDns * dns;
    class IWebsocketClient * websocket;
    class IInstanceLog * log;
    class ITimer reconnectTimer;
    dword timeoutTime;
    class btree * providers;
    class btree * consumers;
    char * name;
    char * uri;
    char * dn;
    char * pwd;
    char * localSocketPath;
    class btree * providerRefs;
    unsigned sendCount;
    unsigned backlogSend;
    istd::list<ApiWebsocketBacklogBuffer> backlogQueue;
    class ITimer backlogTimer;
    void SendBacklog();

public:
    ApiWebsocketClient(class IIoMux * const iomux, class ISocketProvider * localSocketProvider, class ISocketProvider * const tcp, class ISocketProvider * const tls, class IDns * const dns, class IInstanceLog * const log, const char * uri, const char * pwd, const char * dn, const char * localSocketPath = nullptr);
    virtual ~ApiWebsocketClient();

    bool ApiWebsocketClientIsConnected();
    void ApiWebsocketClientClose();
    void ApiWebsocketClientSend(const void * buf, size_t len);
    void ApiWebsocketClientSend(const void * buf, size_t len, class ApiProvider * provider);
    void ApiWebsocketClientSend(const void * buf, size_t len, class ApiConsumer * consumer);

    virtual void ApiWebsocketClientCloseComplete() = 0;
    virtual void ApiWebsocketClientConnected() {};
    virtual void ApiWebsocketClientDisconnected() {};
};

class ApiProvider : public btree, public UIoExec {
    friend class ApiWebsocketClient;

    int btree_compare(void * key) override;
    int btree_compare(class btree * b) override;
    void IoExec(void * execContext) override;

    class ApiWebsocketClient * client;

protected:
    virtual ~ApiProvider();
    void ApiProviderClosed();
    void SendRegisterApi();
    void SendApiModel();

    char * api;
    char * model;

public:
    ApiProvider(class ApiWebsocketClient * const client, const char * api);

    void ApiProviderSend(const char * client, const char * consumer, const char * src, class json_io & msg, word base, char * buffer);
    void ApiProviderUpdate(class json_io & json, word base, char * buffer);

    virtual void ApiProviderRecv(const char * client, const char * consumer, const char * src, class json_io & msg, word base) = 0;
    virtual void ApiProviderConsumerClosed(const char * client, const char * consumer) {}
    virtual void ApiProviderClose() { ApiProviderClosed(); }
    virtual void ApiProviderConnected() {}
    virtual void ApiProviderDisconnected() {}
};

class ApiConsumer : public btree, public UIoExec {
    friend class ApiWebsocketClient;

    int btree_compare(void * key) override;
    int btree_compare(class btree * b) override;
    void IoExec(void * execContext) override;

    class ApiWebsocketClient * client;

protected:
    virtual ~ApiConsumer();
    void ApiConsumerClosed();
    void SendConsumeApi();

    char * api;

public:
    ApiConsumer(class ApiWebsocketClient * const client, const char * api);

    void ApiConsumerSend(const char * provider, const char * src, class json_io & msg, word base, char * buffer);

    virtual void ApiConsumerRecv(const char * provider, const char * src, class json_io & msg, word base) {};
    virtual void ApiConsumerUpdate(class json_io & model, word base) {};
    virtual void ApiConsumerObsolete(class json_io & model, word base) {};
    virtual void ApiConsumerClose() { ApiConsumerClosed(); }
    virtual void ApiConsumerConnected() {}
    virtual void ApiConsumerDisconnected() {}
};
