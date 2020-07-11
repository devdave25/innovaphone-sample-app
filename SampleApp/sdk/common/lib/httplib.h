
/*---------------------------------------------------------------------------*/
/* httpparser.h                                                              */
/* copyright (c) innovaphone 2015                                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/

#define CLRF                 "\r\n"

#define HTTP_GET_KEY         "GET"       
#define HTTP_HEAD_KEY        "HEAD"      
#define HTTP_POST_KEY        "POST"      
#define HTTP_PUT_KEY         "PUT"       
#define HTTP_CONNECT_KEY     "CONNECT"   
#define HTTP_OPTIONS_KEY     "OPTIONS"   
#define HTTP_TRACE_KEY       "TRACE"     
#define HTTP_PROPFIND_KEY    "PROPFIND"
#define HTTP_MKCOL_KEY       "MKCOL"
#define HTTP_COPY_KEY        "COPY"
#define HTTP_MOVE_KEY        "MOVE"
#define HTTP_DELETE_KEY      "DELETE"
#define HTTP_LOCK_KEY        "LOCK"
#define HTTP_UNLOCK_KEY      "UNLOCK"
#define HTTP_PROPPATCH_KEY   "PROPPATCH"
#define HTTP_SYSCLIENT_KEY   "SYSCLIENT"

#define HTTP_VERSION_1_0    0x0100
#define HTTP_VERSION_1_1    0x0101

class HTTPLib {
public:
    // HTTP Request Methods
    typedef enum {
        HTTP_NONE,                  // (NO HTTP VALUE!!!) Dummy value to initialize variable
        HTTP_GET,                   // Transfer a current representation of the target resource.
        HTTP_HEAD,                  // Same as GET, but only transfer the status line and header section.
        HTTP_POST,                  // Perform resource - specific processing on the request payload.
        HTTP_PUT,                   // (WebDAV) Replace all current representations of the target resource with the request payload.
        HTTP_CONNECT,               // Establish a tunnel to the server identified by the target resource.
        HTTP_OPTIONS,               // (WebDAV) Describe the communication options for the target resource.
        HTTP_TRACE,                 // (WebDAV) Perform a message loop - back test along the path to the target resource.
        HTTP_PROPFIND,              // (WebDAV) Used to revceive properties for the given resource.
        HTTP_MKCOL,                 // (WebDAV) Creates a new collection at the specified location.
        HTTP_COPY,                  // (WebDAV) Copy the given resource to a specificed location.
        HTTP_MOVE,                  // (WebDAV) Moves the given resource to a specified location.
        HTTP_DELETE,                // (WebDAV) Deletes the given resource.
        HTTP_LOCK,                  // (WebDAV) Locks the given resource.
        HTTP_UNLOCK,                // (WebDAV) Unlocks the previously locked resource
        HTTP_PROPPATCH,             // (WebDAV) Patches the properties of the given resource
        HTTP_SYSCLIENT              // Sysclient request to authenticate localsocket requests
    } http_request_method_t;


    static inline const char * GetHTTPRequestMethodName(http_request_method_t method)
    {
        switch (method)
        {
        case HTTP_GET: return HTTP_GET_KEY; break;
        case HTTP_HEAD: return HTTP_HEAD_KEY; break;
        case HTTP_POST: return HTTP_POST_KEY; break;
        case HTTP_PUT: return HTTP_PUT_KEY; break;
        case HTTP_CONNECT: return HTTP_CONNECT_KEY; break;
        case HTTP_OPTIONS: return HTTP_OPTIONS_KEY; break;
        case HTTP_TRACE: return HTTP_TRACE_KEY; break;
        case HTTP_PROPFIND: return HTTP_PROPFIND_KEY; break;
        case HTTP_MKCOL: return HTTP_MKCOL_KEY; break;
        case HTTP_COPY: return HTTP_COPY_KEY; break;
        case HTTP_MOVE: return HTTP_MOVE_KEY; break;
        case HTTP_DELETE: return HTTP_DELETE_KEY; break;
        case HTTP_LOCK: return HTTP_LOCK_KEY; break;
        case HTTP_UNLOCK: return HTTP_UNLOCK_KEY; break;
        case HTTP_PROPPATCH: return HTTP_PROPPATCH_KEY; break;
        case HTTP_SYSCLIENT: return HTTP_SYSCLIENT_KEY; break;
        default: return "NONE"; break;
        }
    }


    typedef enum {
        HTTP_CONNECTION_NONE = 0x00,
        HTTP_CONNECTION_KEEP_ALIVE = 0x01,
        HTTP_CONNECTION_CLOSE = 0x02,
        HTTP_CONNECTION_UPGRADE = 0x04
    } http_connection_t;


    typedef enum {
        HTTP_UPGRADE_NONE,      // Default
        HTTP_UPGRADE_WEBSOCKET
    } http_upgrade_t;


    typedef enum {
        HTTP_ENCODING_NONE,      // Default
        HTTP_ENCODING_GZIP
    } http_encoding_t;


    typedef struct {
        int code;
        const char * description;
        size_t descLen;
    } http_result_t;


    // HTTP Result Codes. See RFC 7231, Page 41 (https://tools.ietf.org/html/rfc7231#page-49)
    static const http_result_t HTTP_100; // Continue
    static const http_result_t HTTP_101; // Switching Protocols
    static const http_result_t HTTP_200; // OK
    static const http_result_t HTTP_201; // Created
    static const http_result_t HTTP_202; // Accepted
    static const http_result_t HTTP_203; // Non-Authoritative Information
    static const http_result_t HTTP_204; // No Content
    static const http_result_t HTTP_205; // Reset Content
    static const http_result_t HTTP_206; // Partial Content
    static const http_result_t HTTP_207; // Multi-Status
    static const http_result_t HTTP_300; // Multiple Choices
    static const http_result_t HTTP_301; // Moved Permanently
    static const http_result_t HTTP_302; // Found
    static const http_result_t HTTP_303; // See Other
    static const http_result_t HTTP_304; // Not Modified
    static const http_result_t HTTP_305; // Use Proxy
    static const http_result_t HTTP_307; // Temporary Redirect
    static const http_result_t HTTP_400; // Bad Request
    static const http_result_t HTTP_401; // Unauthorized
    static const http_result_t HTTP_402; // Payment Required
    static const http_result_t HTTP_403; // Forbidden
    static const http_result_t HTTP_404; // Not Found
    static const http_result_t HTTP_405; // Method Not Allowed
    static const http_result_t HTTP_406; // Not Acceptable
    static const http_result_t HTTP_407; // Proxy Authentication Required
    static const http_result_t HTTP_408; // Request Timeout
    static const http_result_t HTTP_409; // Conflict
    static const http_result_t HTTP_410; // Gone
    static const http_result_t HTTP_411; // Length Required
    static const http_result_t HTTP_412; // Precondition Failed
    static const http_result_t HTTP_413; // Payload Too Large
    static const http_result_t HTTP_414; // URI Too Long
    static const http_result_t HTTP_415; // Unsupported Media Type
    static const http_result_t HTTP_416; // Range Not Satisfiable
    static const http_result_t HTTP_417; // Expectation Failed
    static const http_result_t HTTP_423; // Locked
    static const http_result_t HTTP_426; // Upgrade Required
    static const http_result_t HTTP_500; // Internal Server Error
    static const http_result_t HTTP_501; // Not Implemented
    static const http_result_t HTTP_502; // Bad Gateway
    static const http_result_t HTTP_503; // Service Unavailable
    static const http_result_t HTTP_504; // Gateway Timeout
    static const http_result_t HTTP_505; // HTTP Version Not Supported
    static const http_result_t HTTP_507; // Insufficient Storage
};


/*---------------------------------------------------------------------------*/
/* class HTTPHeader                                                          */
/*---------------------------------------------------------------------------*/

class HTTPHeader {
protected:
    char * buffer;
    size_t bufferSize;
    size_t contentSize;
    struct {
        int major;
        int minor;
    } httpVersion;

    void GuaranteeSizeInBuffer(size_t sizeNeeded);

public:
    HTTPHeader();
    ~HTTPHeader();

    void SetHTTPVersion(int major, int minor);
    void SetHTTPResult(const HTTPLib::http_result_t * result);
    void SetContentSize(size_t size);
    void SetContentRange(size_t start, size_t end, size_t completeSize);
    void SetContentType(const char * contentType);
    void SetEncoding(HTTPLib::http_encoding_t enc);
    void SetETag(const char * etag);
    void SetConnection(HTTPLib::http_connection_t connection);
    void SetUpgrade(HTTPLib::http_upgrade_t upgrade);
    void SetWebsocketAcceptKey(const char * key);
    void SetCustomField(const char * field);
    void SetCustomField(const char * field, const char * value);
    void SetDate();
    void SetRequest(HTTPLib::http_request_method_t req, const char * resource);

    const char * GetHeaderData() { return buffer; }
    size_t GetHeaderSize() { return contentSize; }
};

/*---------------------------------------------------------------------------*/
/* class HTTPHeaderField                                                     */
/*---------------------------------------------------------------------------*/
class HTTPHeaderField {
protected:
    friend class HTTPParser;
    HTTPHeaderField() : values(nullptr), valueCount(0) {}
    ~HTTPHeaderField() {}

    const char ** values;
    size_t valueCount;

public:
    const char * GetValue(size_t idx) const { return values[idx]; }
    size_t GetValueCount() const { return valueCount; }
};


class HTTPRange {
public:
    HTTPRange() { this->next = nullptr; }
    virtual ~HTTPRange() {}

    enum {
        RANGE_NONE        = 0x00,
        RANGE_START_END   = 0x01,
        RANGE_START_ONLY  = 0x02,
        RANGE_LAST_BYTES  = 0x03
    } rangeType;
    size_t start;
    size_t end;
    HTTPRange * next;
};


class UHTTPParser {
public:
    virtual ~UHTTPParser() {}
    virtual bool HTTPParserValidateRequest(class HTTPParser * httpParser) = 0;
};


class HTTPParser {
    class HTTPHeaderLine * headerLineStart;
    class HTTPHeaderLine * headerLineEnd;
    char * curLineTmpBuf;
    size_t curLineTmpBufSize;
    int parserState;

    const HTTPLib::http_result_t * httpResultCode;
    HTTPLib::http_request_method_t reqMethod;
    char * firstLineBuffer;
    size_t firstLineBufferSize;
    char * requestTarget;
    char * requestParameters;
    bool requestLineLoaded;
    int httpVersion;

    class HTTPFieldList * fieldList;
    size_t fieldListBufferSize;
    HTTPLib::http_encoding_t acceptEncoding;
    size_t contentLength;
    int connectionType;
    const char * cookie;
    const char * contentType;
    const char * host;
    HTTPLib::http_upgrade_t upgradeType;
    HTTPRange * rangeListStart;
    HTTPRange * rangeListEnd;
    size_t rangeCount;
    HTTPLib::http_encoding_t encoding;

    // Special fields for websocket connections
    const char * websocketKey;
    int websocketVersion;
    const char * websocketProtocol;
    const char * origin;
    const char * etag;

    int parseResult;

    void Reset();
    class HTTPHeaderLine * CreateNewLine();
    size_t AddHeaderLines(char * data, size_t len);

    bool ParseResponseLine();
    bool ParseRequestLine(UHTTPParser * user);
    void ParseFieldLines(class HTTPHeaderLine * curLine);
    void SetFieldValue(const char * field, const char * value);

public:
    typedef enum {
        HTTP_PARSE_DONE,
        HTTP_PARSE_NEED_DATA,
        HTTP_PARSE_CANCEL,
        HTTP_PARSE_ERROR
    } parseresult_t;

    HTTPParser();
    ~HTTPParser();

    size_t ParseData(char * data, size_t len, UHTTPParser * user = nullptr);

    parseresult_t GetParseResult() const { return (parseresult_t)parseResult; }
    HTTPLib::http_encoding_t GetAcceptEncoding() const { return acceptEncoding; }
    HTTPLib::http_request_method_t GetRequestMethod() const { return reqMethod; }
    const char * GetRequestTarget() const { return requestTarget; }
    const char * GetRequestParameters() const { return requestParameters; }
    int GetMajorVersion() const { return httpVersion >> 8; }
    int GetMinorVersion() const { return httpVersion & 0x00FF; }
    int GetVersion() const { return httpVersion; }
    const HTTPHeaderField * GetHeaderField(const char * fieldName)  const;

    size_t GetContentLength() const { return contentLength; }
    bool IsConnectionType(HTTPLib::http_connection_t ct) const { return (connectionType & ct) != 0; }
    bool IsChunkedTransfer();
    const char * GetCookie() const { return cookie; }
    const char * GetETag() const { return etag; }
    const char * GetContentType() const { return contentType; }
    const char * GetHost() const { return host; }
    HTTPLib::http_upgrade_t GetUpgrade() const { return upgradeType; }
    const HTTPRange * GetRange() const { return rangeListStart; }
    size_t GetRangeCount() const { return rangeCount; }
    HTTPLib::http_encoding_t GetEncoding() const { return encoding; }

    const char * GetWebsocketKey() const { return websocketKey; }
    int GetWebsocketVersion() const { return websocketVersion; }
    const char * GetOrigin() const { return origin; }

    const HTTPLib::http_result_t * GetHTTPResultCode() const { return httpResultCode; }

    void GetFieldListCopy(byte * & buffer, size_t & bufferSize) const;
};
