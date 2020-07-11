/*---------------------------------------------------------------------------*/
/* webserverplugin.h                                                         */
/* copyright (c) innovaphone 2015 - 2019                                     */
/*                                                                           */
/*---------------------------------------------------------------------------*/

#define WS_MAX_PATH_LENGTH      8192
#define WS_MAX_DATA_SIZE        65535

// For additional notes to the structure of wsr_cancel_type_t and ws_webdav_result_t, look to
// webserver_internal.h, description to wsr_int_type_t. So before changing anything here, first
// read that description.
typedef enum {
    // Everything from 0 to 15 will be internal types
    WSP_CANCEL_NOT_FOUND = 0x10,
    WSP_CANCEL_BAD_REQUEST,
    WSP_CANCEL_UNAVAILABLE,
    WSP_CANCEL_MISSING_LENGTH,
    WSP_CANCEL_STREAM,
    WSP_CANCEL_ACCESS_DENIED,
    WSP_CANCEL_INTERNAL_ERROR
} wsr_cancel_type_t;


typedef enum {
    WSP_PATH_TYPE_HTTP,
    WSP_PATH_TYPE_WEBSOCKET,
    WSP_PATH_TYPE_PASSTHROUGH
} wsp_path_type_t;


inline const char * WSCancelTypeToStr(wsr_cancel_type_t c)
{
    switch (c)
    {
    case WSP_CANCEL_NOT_FOUND: return "WSP_CANCEL_NOT_FOUND";
    case WSP_CANCEL_BAD_REQUEST: return "WSP_CANCEL_BAD_REQUEST";
    case WSP_CANCEL_UNAVAILABLE: return "WSP_CANCEL_UNAVAILABLE";
    case WSP_CANCEL_MISSING_LENGTH: return "WSP_CANCEL_MISSING_LENGTH";
    case WSP_CANCEL_STREAM: return "WSP_CANCEL_STREAM";
    case WSP_CANCEL_ACCESS_DENIED: return "WSP_CANCEL_ACCESS_DENIED";
    case WSP_CANCEL_INTERNAL_ERROR: return "WSP_CANCEL_INTERNAL_ERROR";
    }
    return "<unkown wsr_cancel_type_t>"; //  Make the compiler happy
}


// Read the above commentar before changing anything here!
typedef enum {
    WEBDAV_RESULT_OK = 0x100,
    WEBDAV_RESULT_CREATED,
    WEBDAV_RESULT_NO_CONTENT,
    WEBDAV_RESULT_MULTIPLE_STATUS,
    WEBDAV_RESULT_FORBIDDEN,
    WEBDAV_RESULT_METHOD_NOT_ALLOWED,
    WEBDAV_RESULT_CONFLICT,
    WEBDAV_RESULT_PRECONDITION_FAILED,
    WEBDAV_RESULT_LOCKED,
    WEBDAV_RESULT_BAD_GATEWAY,
    WEBDAV_RESULT_INSUFFICIENT_STORAGE
} ws_webdav_result_t;


inline const char * WSWebdavResultToStr(ws_webdav_result_t r)
{
    switch (r)
    {
    case WEBDAV_RESULT_OK: return "WEBDAV_RESULT_OK";
    case WEBDAV_RESULT_CREATED: return "WEBDAV_RESULT_CREATED";
    case WEBDAV_RESULT_NO_CONTENT: return "WEBDAV_RESULT_NO_CONTENT";
    case WEBDAV_RESULT_MULTIPLE_STATUS: return "WEBDAV_RESULT_MULTIPLE_STATUS";
    case WEBDAV_RESULT_FORBIDDEN: return "WEBDAV_RESULT_FORBIDDEN";
    case WEBDAV_RESULT_METHOD_NOT_ALLOWED: return "WEBDAV_RESULT_METHOD_NOT_ALLOWED";
    case WEBDAV_RESULT_CONFLICT: return "WEBDAV_RESULT_CONFLICT";
    case WEBDAV_RESULT_PRECONDITION_FAILED: return "WEBDAV_RESULT_PRECONDITION_FAILED";
    case WEBDAV_RESULT_LOCKED: return "WEBDAV_RESULT_LOCKED";
    case WEBDAV_RESULT_BAD_GATEWAY: return "WEBDAV_RESULT_BAD_GATEWAY";
    case WEBDAV_RESULT_INSUFFICIENT_STORAGE: return "WEBDAV_RESULT_INSUFFICIENT_STORAGE";
    }
    return "<unkown ws_webdav_result_t>"; //  Make the compiler happy
}


typedef enum {
    // Start of resource file types
    WSP_RESPONSE_NO_TYPE = 0x100,
    WSP_RESPONSE_BINARY,
    WSP_RESPONSE_JAVA,
    WSP_RESPONSE_WAV,
    WSP_RESPONSE_OGG,
    WSP_RESPONSE_MP3,
    WSP_RESPONSE_GIF,
    WSP_RESPONSE_PNG,
    WSP_RESPONSE_BMP,
    WSP_RESPONSE_ICON,
    WSP_RESPONSE_TTF,
    WSP_RESPONSE_EOT,
    WSP_RESPONSE_PDF,
    WSP_RESPONSE_TEXT,
    WSP_RESPONSE_XML,
    WSP_RESPONSE_CSS,
    WSP_RESPONSE_JAVASCRIPT,
    WSP_RESPONSE_JSON,
    WSP_RESPONSE_HTML,
    WSP_RESPONSE_SVG,
    WSP_RESPONSE_WOFF,
    WSP_RESPONSE_G711,
    WSP_RESPONSE_G722,
    WSP_RESPONSE_G729,
    WSP_RESPONSE_JPEG,
    WSP_RESPONSE_MP4,
    WSP_RESPONSE_WEBM,
    WSP_RESPONSE_PEM,
    WSP_RESPONSE_MOBILECONFIG,
    WSP_RESPONSE_CACHE_MANIFEST,
    WSP_RESPONSE_OPUS,
} wsr_type_t;


typedef enum {
    WSP_FLAG_NONE           =   0x00,
    WSP_FLAG_ENCODING_GZIP  =   0x01,
    WSP_FLAG_SEND_RANGE     =   0x02
    // Note that the values 0x10 and above are used internally and must not be used
} wsr_flags_t;


typedef struct {
    const char * sfx;
    wsr_type_t type;
} ws_type_sfx_t;


static const ws_type_sfx_t suffixes[] = {
    { "html", WSP_RESPONSE_HTML },
    { "htm", WSP_RESPONSE_HTML },
    { "css", WSP_RESPONSE_CSS },
    { "xml", WSP_RESPONSE_XML },
    { "xsl", WSP_RESPONSE_XML },
    { "js", WSP_RESPONSE_JAVASCRIPT },
    { "json", WSP_RESPONSE_JSON },
    { "ico", WSP_RESPONSE_ICON },
    { "bin", WSP_RESPONSE_BINARY },
    { "jar", WSP_RESPONSE_JAVA },
    { "png", WSP_RESPONSE_PNG },
    { "gif", WSP_RESPONSE_GIF },
    { "bmp", WSP_RESPONSE_BMP },
    { "pdf", WSP_RESPONSE_PDF },
    { "wav", WSP_RESPONSE_WAV },
    { "ogg", WSP_RESPONSE_OGG },
    { "mp3", WSP_RESPONSE_MP3 },
    { "txt", WSP_RESPONSE_TEXT },
    { "soap", WSP_RESPONSE_XML },
    { "svg", WSP_RESPONSE_SVG },
    { "ttf", WSP_RESPONSE_TTF },
    { "eot", WSP_RESPONSE_EOT },
    { "woff", WSP_RESPONSE_WOFF },
    { "woff2", WSP_RESPONSE_WOFF },
    { "g711a", WSP_RESPONSE_G711 },
    { "g711u", WSP_RESPONSE_G711 },
    { "g722", WSP_RESPONSE_G722 },
    { "g729", WSP_RESPONSE_G729 },
    { "jpeg", WSP_RESPONSE_JPEG },
    { "mp4", WSP_RESPONSE_MP4 },
    { "webm", WSP_RESPONSE_WEBM },
    { "pem", WSP_RESPONSE_PEM },
    { "mobileconfig", WSP_RESPONSE_MOBILECONFIG },
    { "appcache", WSP_RESPONSE_CACHE_MANIFEST },
    { "opus-nb", WSP_RESPONSE_OPUS },
    { "opus-wb", WSP_RESPONSE_OPUS },
};


inline wsr_type_t GetResponseTypeForFileName(const char * fileName)
{
    char * p = strrchr(const_cast<char *>(fileName), '.');
    if (p != NULL) {
        p++; // Remove '.'
        for (size_t i = 0; i < sizeof(suffixes) / sizeof(ws_type_sfx_t); i++) {
            if (strcmp(p, suffixes[i].sfx) == 0)
                return suffixes[i].type;
        }
    }

    return WSP_RESPONSE_NO_TYPE;
}


typedef enum {
    WSP_NORMAL_CLOSE,                // The app itself initiated the shutdown
    WSP_REGISTER_PATH_INVALID,       // The given path is invalid
    WSP_WEBSOCKET_PATH_INVALID,      // The given Websocket listen path is invalid.
    WSP_WEBSOCKET_PATH_ALREADY_LISTENING, // Someone alrady is listening to that path for websocekt connections
    WSP_PATH_ALREADY_REGISTERD,      // A data provider already registered to that resource
    WSP_ADDRESS_INVALID,             // The address the application tried to connect to was invalid
    WSP_CONNECTION_ERROR             // An connection error occured (see log, if exists),
} wsp_close_reason_t;


inline const char * WSPCloseReasonToStr(wsp_close_reason_t cr)
{
    const char * result;
    switch (cr)
    {
    case WSP_NORMAL_CLOSE: result = "WSP_NORMAL_CLOSE"; break;
    case WSP_REGISTER_PATH_INVALID: result = "WSP_REGISTER_PATH_INVALID"; break;
    case WSP_WEBSOCKET_PATH_INVALID: result = "WSP_WEBSOCKET_PATH_INVALID"; break;
    case WSP_WEBSOCKET_PATH_ALREADY_LISTENING: result = "WSP_WEBSOCKET_PATH_ALREADY_LISTENING"; break;
    case WSP_PATH_ALREADY_REGISTERD: result = "WSP_PATH_ALREADY_REGISTERD"; break;
    case WSP_ADDRESS_INVALID: result = "WSP_ADDRESS_INVALID"; break;
    case WSP_CONNECTION_ERROR: result = "WSP_CONNECTION_ERROR"; break;
    default: result = "<Unkown wsp_close_reason_t>"; break;
    }
    return result;
}


typedef enum {
    WSCR_NORMAL_CLOSE,
    WSCR_BUFFER_OVERFLOW,
    WSCR_SOCKET_LOST,
    WSCR_ERROR,
} ws_close_reason_t;


typedef enum {
    WS_REQUEST_GET          = 0x0001,
    WS_REQUEST_POST         = 0x0002,
    WS_REQUEST_PUT          = 0x0004,
    WS_REQUEST_PASSTHROUGH  = 0x0008,
    WS_REQUEST_PROPFIND     = 0x0010,
    WS_REQUEST_MOVE         = 0x0020,
    WS_REQUEST_COPY         = 0x0040,
    WS_REQUEST_MKCOL        = 0x0080,
    WS_REQUEST_DELETE       = 0x0100,
    WS_REQUEST_OPTIONS      = 0x0200,
    WS_REQUEST_LOCK         = 0x0400,
    WS_REQUEST_UNLOCK       = 0x0800,
    WS_REQUEST_PROPPATCH    = 0x1000
} ws_request_type_t;


// Give this to SetTransferInfo as dataSize to tell the Webserver that your data
// will need to be sent chunk encoded.
static const size_t WS_RESPONSE_CHUNKED = 0xFFFFFFFF;

// Webserver Plugin
class IWebserverPluginProvider {
public:
    virtual ~IWebserverPluginProvider() {}
    virtual class IWebserverPlugin * CreateWebserverPlugin(class IIoMux * const iomux,
                                                           class ISocketProvider * localSocketProvider,
                                                           class UWebserverPlugin * const user,
                                                           const char * webserverAddress,
                                                           const char * appWebRoot,
                                                           class IInstanceLog * const log) = 0;
};

extern IWebserverPluginProvider * CreateWebserverPluginProvider();

class IWebserverPlugin {
public:
    virtual ~IWebserverPlugin() {};

    virtual void SendCertificate(const char * password, const byte * certBuf, size_t certLen, const char * hostName = NULL, UWebserverPlugin * user = NULL) = 0;
    virtual void HttpListen(const char * path = NULL, UWebserverPlugin * user = NULL, const char * authUser = NULL, const char * authUserPwd = NULL, const char * staticFilePrefix = NULL) = 0;
    virtual void HttpListen(const char * path, UWebserverPlugin * user, bool dynamicAuth, const char * staticFilePrefix = NULL) = 0;
    virtual void PassthroughListen(const char * path = NULL, UWebserverPlugin * user = NULL) = 0;
    virtual void WebsocketListen(const char * path = NULL, UWebserverPlugin * user = NULL) = 0;

    virtual void Cancel(wsr_cancel_type_t reason) = 0;
    virtual void Redirect(const char * newDestination) = 0;
    virtual bool BuildRedirect(const char * resourceName, const char * build, unsigned buildLen) = 0;

    virtual void Accept(class UWebserverGet * const user) = 0;
    virtual void Accept(class UWebserverPost * const user) = 0;
    virtual void Accept(class UWebserverPut * const user) = 0;
    virtual void Accept(class UWebserverPassthrough * const user) = 0;
    virtual void Accept(class UWebserverPropfind * const user) = 0;
    virtual void Accept(class UWebserverMove * const user) = 0;
    virtual void Accept(class UWebserverMkCol * const user) = 0;
    virtual void Accept(class UWebserverCopy * const user) = 0;
    virtual void Accept(class UWebserverDelete * const user) = 0;
    virtual void Accept(class UWebserverLock * const user) = 0;
    virtual void Accept(class UWebserverUnlock * const user) = 0;
    virtual void Accept(class UWebserverProppatch * const user) = 0;
    virtual void Accept(class UWebserverOptions * const  user) = 0;
    virtual void WebsocketAccept(class UWebsocket * user) = 0;

    virtual void RequestUserPasswordResult(dword connectionID, const char * user, const char * password) = 0;

    virtual void Close() = 0;
};


class UWebserverPlugin {
public:
    virtual ~UWebserverPlugin() {}

    virtual void WebserverPluginClose(IWebserverPlugin * plugin, wsp_close_reason_t reason, bool lastUser)
    {
        if (lastUser) delete plugin;
    }
    
    virtual void WebserverPluginHttpListenResult(IWebserverPlugin * plugin, ws_request_type_t requestType, char * resourceName, const char * registeredPathForRequest, size_t dataSize)
    {
        plugin->Cancel(WSP_CANCEL_NOT_FOUND);
    }

    virtual void WebserverPluginPassthroughListenResult(IWebserverPlugin * plugin, char * resourceName, const char * registeredPathForRequest, size_t dataSize)
    {
        plugin->Cancel(WSP_CANCEL_NOT_FOUND);
    }

    virtual void WebserverPluginWebsocketListenResult(IWebserverPlugin * plugin, const char * path, const char * registeredPathForRequest, const char * host)
    {
        plugin->WebsocketAccept(NULL);
    }

    virtual void WebserverPluginConnected() {}
    virtual void WebserverPluginSendCertificateResult(IWebserverPlugin * plugin, byte * certBuffer) {}
    virtual void WebserverPluginRegisterPathResult(IWebserverPlugin * plugin, const char * pathName, wsp_path_type_t pathType) {}
    virtual void WebserverPluginRequestUserPassword(IWebserverPlugin * plugin, dword connectionID, char * resourceName, const char * registeredPathForRequest, const char * host, const char * user) { ASSERT(false, "UWebserverPlugin::WebserverPluginRequestUserPassword() not implemented!"); }
};


// Webserver Plugin - Get
class IWebserverGetRange {
public:
    IWebserverGetRange() {}
    virtual ~IWebserverGetRange() {}

    enum range_type_t {
        RANGE_NONE       = 0x00,
        RANGE_START_END  = 0x01,
        RANGE_START_ONLY = 0x02,
        RANGE_LAST_BYTES = 0x03
    } rangeType;

    size_t start;
    size_t end;
};


class IWebserverGet {
public:
    virtual ~IWebserverGet() {}

    virtual const char * GetResourceName() = 0;
    virtual const char * GetRegisteredPathForRequest() = 0;
    virtual const char * GetETag() = 0;
    virtual size_t GetRangeCount() = 0;
    virtual IWebserverGetRange * GetRange(size_t idx) = 0;
    virtual const char * GetHeaderFieldValue(const char * fieldName) = 0;

    virtual void Cancel(wsr_cancel_type_t reason) = 0;
    virtual void SetTransferInfo(wsr_type_t resourceType, size_t dataSize, wsr_flags_t flags = WSP_FLAG_NONE, const char * etag = NULL) = 0;
    virtual void SetTransferRange(size_t rangeStart, size_t rangeEnd) = 0;
    virtual void SetHeaderField(const char * fname, const char * fvalue) = 0;
    virtual void ForceDownloadResponse(const char * fileName = NULL) = 0;
    virtual void Send(const void * buffer, size_t len) = 0;
    virtual void Close() = 0;
};


class UWebserverGet {
public:
    virtual ~UWebserverGet() {}

    virtual void WebserverGetRequestAcceptComplete(IWebserverGet * const webserverGet) = 0;
    virtual void WebserverGetSendResult(IWebserverGet * const webserverGet) = 0;
    virtual void WebserverGetCloseComplete(IWebserverGet * const webserverGet) = 0;
};


// Webserver Plugin - Post
class IWebserverPost {
public:
    virtual ~IWebserverPost() {}

    virtual const char * GetResourceName() = 0;
    virtual const char * GetRegisteredPathForRequest() = 0;
    virtual const char * GetHeaderFieldValue(const char * fieldName) = 0;
    virtual size_t GetDataSize() = 0;
    virtual bool DataIsChunkEncoded() = 0;
    
    virtual void SetTransferInfo(wsr_type_t resourceType, size_t dataSize, wsr_flags_t flags = WSP_FLAG_NONE, const char * etag = NULL) = 0;
    virtual void ForceDownloadResponse(const char * fileName = NULL) = 0;
    virtual void SetHeaderField(const char * fname, const char * fvalue) = 0;
    virtual void Cancel(wsr_cancel_type_t reason) = 0;
    virtual void Send(const void * buffer, size_t len) = 0;
    virtual void Recv(void * buffer = NULL, size_t len = 0) = 0;
    virtual void Close() = 0;
};


class UWebserverPost {
public:
    virtual ~UWebserverPost() {}

    virtual void WebserverPostRequestAcceptComplete(IWebserverPost * const webserverPost) = 0;
    virtual void WebserverPostSendResult(IWebserverPost * const webserverPost) {}
    virtual void WebserverPostRecvResult(IWebserverPost * const webserverPost, void * buffer, size_t len) = 0;
    virtual void * WebserverPostRecvBuffer(size_t len) { return NULL; }
    virtual void WebserverPostRecvCanceled(IWebserverPost * const webserverPost, void * buffer) = 0;
    virtual void WebserverPostCloseComplete(IWebserverPost * const webserverPost) = 0;
};


// Webserver Plugin - Passthrough
class IWebserverPassthrough {
public:
    virtual ~IWebserverPassthrough() {}

    virtual const char * GetResourceName() = 0;
    virtual const char * GetRegisteredPathForRequest() = 0;
    virtual const char * GetHeaderFieldValue(const char * fieldName) = 0;
    virtual bool IsEncryptedConnection() = 0;

    virtual void Cancel(wsr_cancel_type_t reason) = 0;
    virtual void Send(const void * buffer, size_t size) = 0;
    virtual void Recv(void * buffer = NULL, size_t len = 0) = 0;
    virtual void Close() = 0;
};


class UWebserverPassthrough {
public:
    virtual ~UWebserverPassthrough() {}

    virtual void WebserverPassthroughRequestAcceptComplete(IWebserverPassthrough * const webserverPassthrough) = 0;
    virtual void WebserverPassthroughSendResult(IWebserverPassthrough * const webserverPassthrough) = 0;
    virtual void WebserverPassthroughRecvResult(IWebserverPassthrough * const webserverPassthrough, void * buffer, size_t len) = 0;
    virtual void * WebserverPassthroughRecvBuffer(size_t len) { return NULL; }
    virtual void WebserverPassthroughRecvCanceled(IWebserverPassthrough * const webserverPassthrough, void * buffer) = 0;
    virtual void WebserverPassthroughCloseComplete(IWebserverPassthrough * const webserverPassthrough) = 0;
};


// Webserver Plugin - Put
class IWebserverPut {
public:
    virtual ~IWebserverPut() {}

    virtual const char * GetResourceName() = 0;
    virtual const char * GetRegisteredPathForRequest() = 0;
    virtual const char * GetHeaderFieldValue(const char * fieldName) = 0;
    virtual size_t GetDataSize() = 0;
    virtual bool DataIsChunkEncoded() = 0;

    virtual void SetResultCode(ws_webdav_result_t result, size_t dataSize = 0) = 0;
    virtual void SetHeaderField(const char * fname, const char * fvalue) = 0;
    virtual void Cancel(wsr_cancel_type_t reason) = 0;
    virtual void Send(const void * buffer, size_t len) = 0;
    virtual void Recv(void * buffer = NULL, size_t len = 0) = 0;
    virtual void Close() = 0;
};


class UWebserverPut {
public:
    virtual ~UWebserverPut() {}

    virtual void WebserverPutRequestAcceptComplete(IWebserverPut * const webserverPut) = 0;
    virtual void WebserverPutSendResult(IWebserverPut * const webserverPut) = 0;
    virtual void WebserverPutRecvResult(IWebserverPut * const webserverPut, void * buffer, size_t len) = 0;
    virtual void * WebserverPutRecvBuffer(size_t len) { return NULL; }
    virtual void WebserverPutRecvCanceled(IWebserverPut * const webserverPut, void * buffer) = 0;
    virtual void WebserverPutCloseComplete(IWebserverPut * const webserverPut) = 0;
};


// Webserver Plugin - Propfind
class IWebserverPropfind {
public:
    virtual ~IWebserverPropfind() {}

    virtual const char * GetResourceName() = 0;
    virtual const char * GetRegisteredPathForRequest() = 0;
    virtual const char * GetHeaderFieldValue(const char * fieldName) = 0;
    virtual size_t GetDataSize() = 0;
    virtual bool DataIsChunkEncoded() = 0;

    virtual void SetResultCode(ws_webdav_result_t result, size_t dataSize = 0) = 0;
    virtual void SetHeaderField(const char * fname, const char * fvalue) = 0;
    virtual void Cancel(wsr_cancel_type_t reason) = 0;
    virtual void Recv(void * buffer = NULL, size_t len = 0) = 0;
    virtual void Send(const void * buffer, size_t len) = 0;
    virtual void Close() = 0;
};


class UWebserverPropfind {
public:
    virtual ~UWebserverPropfind() {};
    virtual void WebserverPropfindRequestAcceptComplete(IWebserverPropfind * const webserverPropfind) = 0;
    virtual void WebserverPropfindSendResult(IWebserverPropfind * const webserverPropfind) = 0;
    virtual void WebserverPropfindRecvResult(IWebserverPropfind * const webserverPropfind, void * buffer, size_t len) = 0;
    virtual void * WebserverPropfindRecvBuffer(size_t len)
    {
        return NULL;
    }
    virtual void WebserverPropfindRecvCanceled(IWebserverPropfind * const webserverPropfind, void * buffer) = 0;
    virtual void WebserverPropfindCloseComplete(IWebserverPropfind * const webserverPropfind) = 0;
};


// Webserver Plugin - Move
class IWebserverMove {
public:
    virtual ~IWebserverMove() {}

    virtual const char * GetResourceName() = 0;
    virtual const char * GetRegisteredPathForRequest() = 0;
    virtual const char * GetHeaderFieldValue(const char * fieldName) = 0;

    virtual void SetResultCode(ws_webdav_result_t result, size_t dataSize = 0) = 0;
    virtual void SetLocation(const char * location) = 0;
    virtual void SetHeaderField(const char * fname, const char * fvalue) = 0;
    virtual void Cancel(wsr_cancel_type_t reason) = 0;
    virtual void Send(const void * buffer, size_t len) = 0;
    virtual void Close() = 0;
};


class UWebserverMove {
public:
    virtual ~UWebserverMove() {};
    virtual void WebserverMoveRequestAcceptComplete(IWebserverMove * const webserverMove) = 0;
    virtual void WebserverMoveSendResult(IWebserverMove * const webserverMove) = 0;
    virtual void WebserverMoveCloseComplete(IWebserverMove * const webserverMove) = 0;
};


// Webserver Plugin - MkCol
class IWebserverMkCol {
public:
    virtual ~IWebserverMkCol() {}

    virtual const char * GetResourceName() = 0;
    virtual const char * GetRegisteredPathForRequest() = 0;
    virtual const char * GetHeaderFieldValue(const char * fieldName) = 0;

    virtual void SetResultCode(ws_webdav_result_t result, size_t dataSize = 0) = 0;
    virtual void SetLocation(const char * location) = 0;
    virtual void SetHeaderField(const char * fname, const char * fvalue) = 0;
    virtual void Cancel(wsr_cancel_type_t reason) = 0;
    virtual void Send(const void * buffer, size_t len) = 0;
    virtual void Close() = 0;
};


class UWebserverMkCol {
public:
    virtual ~UWebserverMkCol() {};
    virtual void WebserverMkColRequestAcceptComplete(IWebserverMkCol * const webserverMkCol) = 0;
    virtual void WebserverMkColSendResult(IWebserverMkCol * const webserverMkCol) = 0;
    virtual void WebserverMkColCloseComplete(IWebserverMkCol * const webserverMkCol) = 0;
};


// Webserver Plugin - Copy
class IWebserverCopy {
public:
    virtual ~IWebserverCopy() {}

    virtual const char * GetResourceName() = 0;
    virtual const char * GetRegisteredPathForRequest() = 0;
    virtual const char * GetHeaderFieldValue(const char * fieldName) = 0;

    virtual void SetResultCode(ws_webdav_result_t result, size_t dataSize = 0) = 0;
    virtual void SetHeaderField(const char * fname, const char * fvalue) = 0;
    virtual void Cancel(wsr_cancel_type_t reason) = 0;
    virtual void Send(const void * buffer, size_t len) = 0;
    virtual void Close() = 0;
};


class UWebserverCopy {
public:
    virtual ~UWebserverCopy() {};
    virtual void WebserverCopyRequestAcceptComplete(IWebserverCopy * const webserverCopy) = 0;
    virtual void WebserverCopySendResult(IWebserverCopy * const webserverCopy) = 0;
    virtual void WebserverCopyCloseComplete(IWebserverCopy * const webserverCopy) = 0;
};


// Webserver Plugin - Delete
class IWebserverDelete {
public:
    virtual ~IWebserverDelete() {}

    virtual const char * GetResourceName() = 0;
    virtual const char * GetRegisteredPathForRequest() = 0;
    virtual const char * GetHeaderFieldValue(const char * fieldName) = 0;

    virtual void SetResultCode(ws_webdav_result_t result, size_t dataSize = 0) = 0;
    virtual void SetHeaderField(const char * fname, const char * fvalue) = 0;
    virtual void Cancel(wsr_cancel_type_t reason) = 0;
    virtual void Send(const void * buffer, size_t len) = 0;
    virtual void Close() = 0;
};


class UWebserverDelete {
public:
    virtual ~UWebserverDelete() {};
    virtual void WebserverDeleteRequestAcceptComplete(IWebserverDelete * const webserverDelete) = 0;
    virtual void WebserverDeleteSendResult(IWebserverDelete * const webserverDelete) = 0;
    virtual void WebserverDeleteCloseComplete(IWebserverDelete * const webserverDelete) = 0;
};


// Webserver Plugin - Lock
class IWebserverLock {
public:
    virtual ~IWebserverLock() {}

    virtual const char * GetResourceName() = 0;
    virtual const char * GetRegisteredPathForRequest() = 0;
    virtual const char * GetHeaderFieldValue(const char * fieldName) = 0;

    virtual void SetResultCode(ws_webdav_result_t result, size_t dataSize = 0) = 0;
    virtual void SetHeaderField(const char * fname, const char * fvalue) = 0;
    virtual void Cancel(wsr_cancel_type_t reason) = 0;
    virtual void Recv(void * buffer = NULL, size_t len = 0) = 0;
    virtual void Send(const void * buffer, size_t len) = 0;
    virtual void Close() = 0;
};


class UWebserverLock {
public:
    virtual ~UWebserverLock() {};
    virtual void WebserverLockRequestAcceptComplete(IWebserverLock * const webserverLock) = 0;
    virtual void WebserverLockSendResult(IWebserverLock * const webserverLock) = 0;
    virtual void WebserverLockRecvResult(IWebserverLock * const webserverLock, void * buffer, size_t len) = 0;
    virtual void * WebserverLockRecvBuffer(size_t len)
    {
        return NULL;
    }
    virtual void WebserverLockRecvCanceled(IWebserverLock * const webserverLock, void * buffer) = 0;
    virtual void WebserverLockCloseComplete(IWebserverLock * const webserverLock) = 0;
};


// Webserver Plugin - Unlock
class IWebserverUnlock {
public:
    virtual ~IWebserverUnlock() {}

    virtual const char * GetResourceName() = 0;
    virtual const char * GetRegisteredPathForRequest() = 0;
    virtual const char * GetHeaderFieldValue(const char * fieldName) = 0;

    virtual void SetResultCode(ws_webdav_result_t result, size_t dataSize = 0) = 0;
    virtual void SetHeaderField(const char * fname, const char * fvalue) = 0;
    virtual void Cancel(wsr_cancel_type_t reason) = 0;
    virtual void Send(const void * buffer, size_t len) = 0;
    virtual void Close() = 0;
};


class UWebserverUnlock {
public:
    virtual ~UWebserverUnlock() {};
    virtual void WebserverUnlockRequestAcceptComplete(IWebserverUnlock * const webserverUnlock) = 0;
    virtual void WebserverUnlockSendResult(IWebserverUnlock * const webserverUnlock) = 0;
    virtual void WebserverUnlockCloseComplete(IWebserverUnlock * const webserverUnlock) = 0;
};


// Webserver Plugin - Proppatch
class IWebserverProppatch {
public:
    virtual ~IWebserverProppatch() {}

    virtual const char * GetResourceName() = 0;
    virtual const char * GetRegisteredPathForRequest() = 0;
    virtual const char * GetHeaderFieldValue(const char * fieldName) = 0;

    virtual void SetResultCode(ws_webdav_result_t result, size_t dataSize = 0) = 0;
    virtual void SetHeaderField(const char * fname, const char * fvalue) = 0;
    virtual void Cancel(wsr_cancel_type_t reason) = 0;
    virtual void Recv(void * buffer = NULL, size_t len = 0) = 0;
    virtual void Send(const void * buffer, size_t len) = 0;
    virtual void Close() = 0;
};


class UWebserverProppatch {
public:
    virtual ~UWebserverProppatch() {};
    virtual void WebserverProppatchRequestAcceptComplete(IWebserverProppatch * const webserverProppatch) = 0;
    virtual void WebserverProppatchSendResult(IWebserverProppatch * const webserverProppatch) = 0;
    virtual void WebserverProppatchRecvResult(IWebserverProppatch * const webserverProppatch, void * buffer, size_t len) = 0;
    virtual void * WebserverProppatchRecvBuffer(size_t len)
    {
        return NULL;
    }
    virtual void WebserverProppatchRecvCanceled(IWebserverProppatch * const webserverProppatch, void * buffer) = 0;
    virtual void WebserverProppatchCloseComplete(IWebserverProppatch * const webserverProppatch) = 0;
};


// Webserver Plugin - Options
class IWebserverOptions {
public:
    virtual ~IWebserverOptions() {}

    virtual const char * GetResourceName() = 0;
    virtual const char * GetRegisteredPathForRequest() = 0;
    virtual const char * GetHeaderFieldValue(const char * fieldName) = 0;

    virtual void SetSupportedRequests(dword requestList) = 0;
    virtual void SetHeaderField(const char * fname, const char * fvalue) = 0;
    virtual void Close() = 0;
};


class UWebserverOptions {
public:
    virtual ~UWebserverOptions() {}
    virtual void WebserverOptionsRequestAcceptComplete(IWebserverOptions * const webserverOptions)
    {
        webserverOptions->SetSupportedRequests(WS_REQUEST_GET | WS_REQUEST_POST | WS_REQUEST_PUT |
                                               WS_REQUEST_PROPFIND | WS_REQUEST_MOVE | WS_REQUEST_COPY |
                                               WS_REQUEST_MKCOL | WS_REQUEST_DELETE | WS_REQUEST_OPTIONS |
                                               WS_REQUEST_LOCK | WS_REQUEST_UNLOCK | WS_REQUEST_PROPPATCH);
        webserverOptions->Close();
    }

    virtual void WebserverOptionsCloseComplete(IWebserverOptions * const webserverOptions) = 0;
};


// Webserver Plugin - Websocket
class IWebsocket {
public:
    virtual ~IWebsocket() {}

    virtual const char * GetHost() = 0;
    virtual const char * GetPath() = 0;
    virtual bool IsSysClientAuthenticated() = 0;
    virtual bool IsLocalHost() = 0;
    virtual bool IsEncryptedConnection() = 0;

    virtual void Send(const void * buffer, size_t len, bool text = true) = 0;
    virtual void Recv(void * buf = NULL, size_t len = 0) = 0;
    virtual void Close() = 0;
};


class UWebsocket {
public:
    virtual ~UWebsocket() {}
    virtual void WebsocketAcceptComplete(class IWebsocket * websocket) = 0;
    virtual void WebsocketSendResult(class IWebsocket * websocket) = 0;
    virtual void WebsocketRecvResult(class IWebsocket * websocket, void * buffer, size_t len, bool text, bool isFragmented) = 0;
    virtual void * WebsocketRecvBuffer(size_t len) { return NULL; }
    virtual void WebsocketRecvCanceled(class IWebsocket * websocket, void * buffer) = 0;
    virtual void WebsocketCloseComplete(class IWebsocket * websocket, ws_close_reason_t reason) = 0;
};
