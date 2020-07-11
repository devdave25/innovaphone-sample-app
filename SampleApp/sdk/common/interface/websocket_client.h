
/*---------------------------------------------------------------------------*/
/* websocketclient.h                                                         */
/* copyright (c) innovaphone 2015                                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/

#define WEBSOCKET_MAX_PAYLOAD_SIZE 16384

class IWebsocketClient {
public:
	static IWebsocketClient * Create(class IIoMux * const iomux,
									 class UWebsocketClient * const user,
									 class ISocketProvider * const tcpSocketProvider,
									 class ISocketProvider * const tlsSocketProvider,
                                     class IDns * const dns,
                                     class IInstanceLog * const log);
	
	virtual ~IWebsocketClient() {};
	virtual void Connect(const char * uri) = 0;
	virtual void Close() = 0;
	virtual void Cancel() = 0;
	virtual void Send(const void * buf, size_t len, bool text = true) = 0;
	virtual void Recv(void * buf = NULL, size_t len = 0) = 0;
    virtual void Ping() = 0;
};


class UWebsocketClient {
public:
    typedef enum {
        WSCR_NORMAL_CLOSE,       // Nachdem die Anwendung Close() gerufen hat
        WSCR_CONNECTION_FAILED, 
        WSCR_URI_INVALID,
        WSCR_BUFFER_OVERFLOW,
        WSCR_PROTOCOL_ERROR,
        WSCR_SOCKET_LOST,
        WSCR_SERVER_CLOSED      // Server hat Close-Handshake initiiert
    } closereason_t;
    
    virtual void WebsocketConnectComplete(IWebsocketClient * const websocket) = 0;
    virtual void WebsocketCloseComplete(IWebsocketClient * const websocket, closereason_t reason) = 0;
	virtual void WebsocketSendResult(IWebsocketClient * const websocket) = 0;
	virtual void WebsocketRecvResult(IWebsocketClient * const websocket, void * buf, size_t len, bool text, bool isFragment) = 0;
    virtual void * WebsocketRecvBuffer(size_t len) { return NULL; }
	virtual void WebsocketRecvCanceled(IWebsocketClient * const websocket, void * buf) = 0;
    virtual void WebsocketPongReceived(IWebsocketClient * const websocket) {}
};
