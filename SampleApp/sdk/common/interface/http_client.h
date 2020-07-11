/*---------------------------------------------------------------------------*/
/* http_client.h                                                             */
/* copyright (c) innovaphone 2015                                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/

#define HTTP_AUTH_NONE      0
#define HTTP_AUTH_NTLM      1
#define HTTP_AUTH_DIGEST    2
#define HTTP_AUTH_BASIC     4
#define HTTP_AUTH_ALL       HTTP_AUTH_NTLM | HTTP_AUTH_DIGEST | HTTP_AUTH_BASIC

typedef enum {
    HTTP_GET,
    HTTP_POST,
    HTTP_PUT
} http_request_type_t;


typedef enum {
    HTTP_SHUTDOWN_NORMAL,
    HTTP_SHUTDOWN_BY_PEER,
    HTTP_SOCKET_LOST,
    HTTP_ADDRESS_INVALID,
    HTTP_SOCKET_ERROR,
    HTTP_CONNECT_FAILED,
    HTTP_BYTE_STREAM_BROKEN,
    HTTP_UNHANDLED_HTTP_RESULT,
    HTTP_FAILURE,
    HTTP_AUTHENTICATION_FAILED,
    HTTP_NOT_FOUND,
    HTTP_BAD_REQUEST,
    HTTP_INTERNAL_SERVER_ERROR
} http_shutdown_reason_t;

inline const char * HTTPShutdownReasonToStr(http_shutdown_reason_t reason)
{
    const char * result = "<unkown reason id>";
    switch (reason) {
    case HTTP_SHUTDOWN_NORMAL: result = "HTTP_SHUTDOWN_NORMAL"; break;
    case HTTP_SHUTDOWN_BY_PEER: result = "HTTP_SHUTDOWN_BY_PEER"; break;
    case HTTP_SOCKET_LOST: result = "HTTP_SOCKET_LOST"; break;
    case HTTP_ADDRESS_INVALID: result = "HTTP_ADDRESS_INVALID"; break;
    case HTTP_SOCKET_ERROR: result = "HTTP_SOCKET_ERROR"; break;
    case HTTP_CONNECT_FAILED: result = "HTTP_CONNECT_FAILED"; break;
    case HTTP_BYTE_STREAM_BROKEN: result = "HTTP_BYTE_STREAM_BROKEN"; break;
    case HTTP_UNHANDLED_HTTP_RESULT: result = "HTTP_UNHANDLED_HTTP_RESULT"; break;
    case HTTP_FAILURE: result = "HTTP_FAILURE"; break;
    case HTTP_AUTHENTICATION_FAILED: result = "HTTP_AUTHENTICATION_FAILED"; break;
    case HTTP_NOT_FOUND: result = "HTTP_NOT_FOUND"; break;
    case HTTP_BAD_REQUEST: result = "HTTP_BAD_REQUEST"; break;
    case HTTP_INTERNAL_SERVER_ERROR: result = "HTTP_INTERNAL_SERVER_ERROR"; break;
    }
    return result;
}


typedef enum {
    HTTP_RESULT_OK,
    HTTP_RESULT_NOT_FOUND,
    HTTP_RESULT_BAD_REQUEST,
    HTTP_RESULT_REDIRECT,
    HTTP_RESULT_INTERNAL_SERVER_ERROR,
} http_result_t;


typedef enum {
    HTTP_CL_ERR_NOT_FOUND           = 0x0001,
    HTTP_CL_ERR_BAD_REQUEST         = 0x0002,
    HTTP_CL_ERR_INTERNAL_SERVER     = 0x0004,
    HTTP_CL_ERR_REDIRECT            = 0x0008
} http_error_t;


#define HTTP_CLIENT_CHUNKED_TRANSFER 0xffffffff

class IHTTPClient {
public:
    virtual ~IHTTPClient() {}

    static IHTTPClient * Create(class IIoMux * const iomux,
                                class ISocketProvider * const tcpSocketProvider,
                                class ISocketProvider * const tlsSocketProvider,
                                class UHTTPClient * const user,
                                class IInstanceLog * const log);

    virtual void Connect(const char * address,
                         const char * user = NULL,
                         const char * pwd = NULL,
                         int authMethods = HTTP_AUTH_ALL) = 0;
    virtual void Recv(byte * buffer, size_t size, bool recvPartitial = false) = 0;
    virtual void Send(const byte * data = NULL, size_t size = 0, bool last = false) = 0;
    virtual void Shutdown() = 0;
    virtual void Reconnect() = 0;
    virtual void PassErrorToUser(http_error_t err) = 0;
    virtual void SendContentForAuthentication(bool doSend) = 0;

    virtual void SetRequestType(http_request_type_t reqType, const char * resourceName, size_t contentLength = 0, const char * contentType = "text/xml; charset=utf-8") = 0;
    virtual void SetCustomHeaderField(const char * field, const char * value) = 0;
    virtual http_result_t GetHTTPResult() = 0;
    virtual size_t GetContentLength(bool & chunked) = 0;
    virtual size_t GetHeaderFieldValueCount(const char * headerField) = 0;
    virtual const char * GetHeaderFieldValue(const char * headerField, size_t index = 0) = 0;

    virtual bool Connected() = 0;
};


class UHTTPClient {
public:
    ~UHTTPClient() {}

    virtual void HTTPClientConnectComplete(IHTTPClient * const httpClient) = 0;
    virtual void HTTPClientShutdown(IHTTPClient * const httpClient, http_shutdown_reason_t reason) = 0;
    virtual void HTTPClientSendResult(IHTTPClient * const httpClient) = 0;
    virtual void HTTPClientRecvResult(IHTTPClient * const httpClient, byte * buffer, size_t len, bool transferComplete) = 0;
    virtual void HTTPClientRecvCanceled(IHTTPClient * const httpClient, byte * buffer) = 0;
    virtual void HTTPClientRequestComplete(IHTTPClient * const httpClient) = 0;
};
