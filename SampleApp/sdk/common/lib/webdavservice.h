/*---------------------------------------------------------------------------*/
/* webdavservice.h                                                           */
/* copyright (c) innovaphone 2016 - 2017                                     */
/*                                                                           */
/*---------------------------------------------------------------------------*/

#define DAV_PROP_CREATIONDATE       0x00000001
#define DAV_PROP_DISPLAYNAME        0x00000002
#define DAV_PROP_GETCONTENTLANGUAGE 0x00000004
#define DAV_PROP_GETCONTENTLENGTH   0x00000008
#define DAV_PROP_GETCONTENTTYPE     0x00000010
#define DAV_PROP_GETETAG            0x00000020
#define DAV_PROP_GETLASTMODIFIED    0x00000040
#define DAV_PROP_LOCKDISCOVERY      0x00000080
#define DAV_PROP_RESOURCETYPE       0x00000100
#define DAV_PROP_SOURCE             0x00000200
#define DAV_PROP_SUPPORTEDLOCK      0x00000400
#define DAV_PROP_ALLPROPS           0xffffffff

#define DAV_DEPTH_INFINITY          0xffffffff

class WebdavLock;

class UWebdavNotification 
{
public:
    virtual void PutCompleted(const char * appName, const char * path, ulong64 id) = 0;
    virtual void DeleteCompleted(const char * appName, const char * path) = 0;
    virtual void MoveCompleted(const char * appName, const char * path) = 0;
};

class WebdavNotification : public istd::listElement < WebdavNotification >
{
public:
    class UWebdavNotification * webdavNotification;
    char * appName;
    WebdavNotification(class UWebdavNotification * notification, const char * appName);
    virtual ~WebdavNotification();
    
};

class UWebdavService {
public:
    virtual void WebdavServiceClosed() = 0;
    virtual void WebdavServiceInitComplete(){}
};

class IWebdavServiceTask {
public:
    virtual void CloseComplete(class UWebdavServiceTask * task) = 0;
};

class UWebdavServiceTask : public istd::listElement<UWebdavServiceTask> {
public:
    virtual void Close() = 0;
};

class WebdavService : public UTask, public UIoExec {

    // private Members
    class IIoMux * iomux;
    class IDbFiles * dbFiles;
    class IDatabase * database;
    class IInstanceLog * log;
    friend class WebdavServiceGet;
    friend class WebdavServiceGetDBFiles;
    friend class WebdavServicePut;
    friend class WebdavServicePost;
    friend class WebdavServicePropfind;
    friend class WebdavServiceMkCol;
    friend class WebdavServiceMove;
    friend class WebdavServiceCopy;
    friend class WebdavServiceDelete;
    friend class WebdavServiceOptions;
    friend class WebdavServiceLock;
    friend class WebdavServiceUnLock;
    friend class WebdavServiceProppatch;
    bool completed;
    char * webserverPath;
    bool closing;
    
    class istd::list<WebdavNotification> notifications;
    class istd::list<WebdavLock> locks;
    class istd::list<UWebdavServiceTask> tasks;
    class UWebdavService * service;
    char * rootFolder;
    // UTask
    void TaskComplete(class ITask * const task) override;
    void TaskFailed(class ITask * const task) override;
    // UIoExec
    void IoExec(void * execContext) override;

    bool InsertLock(class WebdavLock * lock);
    class WebdavLock * LockLookup(const char * resource);
    class WebdavLock * LockLookup(const char * resource, const char * token);

    void CloseComplete(class UWebdavServiceTask * task);
    

public:
    WebdavService(class IIoMux * const iomux, class UWebdavService * service, class IDbFiles * dbFiles, class IDatabase * database, class IInstanceLog * const log, const char * webserverPath, const char * rootFolder = 0);
    virtual ~WebdavService();

    bool WebRequestWebdavService(IWebserverPlugin * const webserverPlugin, ws_request_type_t requestType, char * resourceName, size_t dataSize);
    bool GetCompleted() { return completed; }
    void Start();
    void RegisterforNotification(class UWebdavNotification * notification, const char * appName);
    void DeregisterforNotification(class UWebdavNotification * notification);
    void Close();
};

//**********************************************************************************************************//
//************************************** Get Requests ******************************************************//
//**********************************************************************************************************//

enum GetStates
{
    GETPATHREQUEST = 0,
    GETREADFILE,
    GETCLOSE
};

class WebdavServiceGetWebserver : public UWebserverGet, public UWebdavServiceTask {
    // UWebserverGet
    void WebserverGetRequestAcceptComplete(IWebserverGet * const webserverGet) override;
    void WebserverGetSendResult(IWebserverGet * const webserverGet) override;
    void WebserverGetCloseComplete(IWebserverGet * const webserverGet) override;

    class IWebserverGet * webserverget;
    class WebdavServiceGet * webdavServiceGet;

public:
    WebdavServiceGetWebserver( class WebdavServiceGet * webdavServiceGet);
    ~WebdavServiceGetWebserver();

    void Cancel(wsr_cancel_type_t type);
    void Send(const void * data, size_t len);
    void SetTransferInfo(wsr_type_t resourceType, size_t dataSize, const char * filename);
    void SetTransferRange(size_t start, size_t end);
    size_t GetRangeCount();
    IWebserverGetRange* GetRange(size_t idx);
    void Close() override;
};

class WebdavServiceGetDBFiles : public UTask, public UWebdavServiceTask {
    // UTask
    void TaskComplete(class ITask * const task) override;
    void TaskFailed(class ITask * const task) override;
    void TaskProgress(class ITask * const task, dword progress) override;

    unsigned state;
    class IDbFilesGet * filesget;
    class IDbFilesPathInfo * pathinfo;
    class WebdavServiceGet * webdavServiceGet;
    class IDbFiles * dbFiles;

public:
    WebdavServiceGetDBFiles(class WebdavServiceGet * webdavServiceGet, class IDbFiles * dbFiles);
    virtual ~WebdavServiceGetDBFiles();

    void LookPath(char * path);
    void GetFile(ulong64 id, unsigned int offset);
    void ReadFile();
    void Close() override;
};

class WebdavServiceGet : public IWebdavServiceTask, public UWebdavServiceTask {
    class WebdavServiceGetDBFiles * webdavServiceGetDBFiles;
    class WebdavServiceGetWebserver * webdavServiceGetWebserver;
    class WebdavService * webdavservice;
    char * path;
    bool pendingRequestWebserver;
    bool pendingRequestDBFiles;
    size_t requestedLength;
    size_t sendedLength;
public:
    WebdavServiceGet(IWebserverPlugin * const webserverPlugin, class WebdavService * webdavservice, char * path);
    ~WebdavServiceGet();

    void AcceptReceived();
    void PathCompleted(bool completed, ulong64 id, const char * name, unsigned length, bool isFolder, ulong64 created, ulong64 modified);
    void GetCompleted(bool completed);
    void GetProgress(const byte * data, unsigned len);
    void SendResult();
    void Close() override;
    void CloseComplete(class UWebdavServiceTask * task) override;
    bool Cancel(wsr_cancel_type_t type);
    
    class WebdavService * GetWebdavService(){ return webdavservice ? webdavservice : 0;}
    char * GetPath() { return path ? path : 0; }
};

//**********************************************************************************************************//
//************************************** Put Requests ******************************************************//
//**********************************************************************************************************//

enum PutStates
{
    PUTPATHREQUEST = 0,
    PUTPARENTFOLDERREQUEST,
    PUTWRITEFILE,
    PUTCLOSE
};

class WebdavServicePutWebserver : public UWebserverPut, public UWebdavServiceTask {
    // UWebserverPut
    void WebserverPutRequestAcceptComplete(IWebserverPut * const webserverPut) override;
    void WebserverPutSendResult(IWebserverPut * const webserverPut) override;
    void WebserverPutRecvResult(IWebserverPut * const webserverPut, void * buffer, size_t len) override;
    void * WebserverPutRecvBuffer(size_t len) override;
    void WebserverPutRecvCanceled(IWebserverPut * const webserverPut, void * buffer) override;
    void WebserverPutCloseComplete(IWebserverPut * const webserverPut) override;

    class IWebserverPut * webserverPut;
    class WebdavServicePut * webdavServicePut;

public:
    WebdavServicePutWebserver(class WebdavServicePut * webdavServicePut);
    ~WebdavServicePutWebserver();

    void Cancel(wsr_cancel_type_t type);
    void Recv();
    void Send(const void * data, size_t len);
    void SetResultCode(ws_webdav_result_t result);
    bool DataIsChunkEncoded();
    void Close() override;
};

class WebdavServicePutDBFiles : public UTask, public UWebdavServiceTask {
    // UTask
    void TaskComplete(class ITask * const task) override;
    void TaskFailed(class ITask * const task) override;
    void TaskProgress(class ITask * const task, dword progress) override;

    unsigned state;
    class IDbFilesPut * filesput;
    class IDbFilesPathInfo * pathinfo;
    class WebdavServicePut * webdavServicePut;
    class IDbFiles * dbFiles;

public:
    WebdavServicePutDBFiles(class WebdavServicePut * webdavServicePut, class IDbFiles * dbFiles);
    virtual ~WebdavServicePutDBFiles();

    void LookPath(char * path);
    void WriteFile(byte * data, unsigned len, bool last);
    void PutFile(char * filename, ulong64 folder );
    void GetFailed(ulong64 & parent, bool & isFolder, const char * &path);
    ulong64 GetFileId();
    void Close() override;
};

class WebdavServicePut : public IWebdavServiceTask, public UWebdavServiceTask {
    class WebdavServicePutDBFiles * webdavServicePutDBFiles;
    class WebdavServicePutWebserver * webdavServicePutWebserver;
    class WebdavService * webdavservice;
    ulong64 id;
    char * path;
    size_t dataSize;
    char * filename;
    bool chunkEncoded;
    bool pendingRequestWebserver;
    bool pendingRequestDBFiles;

public:
    WebdavServicePut(IWebserverPlugin * const webserverPlugin, class WebdavService * webdavservice, char * path, size_t dataSize);
    ~WebdavServicePut();

    bool Send(const void * data, size_t len);
    void AcceptReceived();
    void PathCompleted(bool completed, ulong64 id, const char * name, unsigned length, bool isFolder, ulong64 created, ulong64 modified);
    void WriteCompleted(bool completed);
    void Close() override;
    void CloseComplete(class UWebdavServiceTask * task) override;
    void WebserverRecv(void * buffer, size_t len);
    void SendResult();
    void WriteProgress();
    bool Cancel(wsr_cancel_type_t type);
    bool SetTransferInfo(wsr_type_t resourceType, size_t dataSize);
    class WebdavService * GetWebdavService(){ return webdavservice ? webdavservice : 0; }
    char * GetPath() { return path ? path : 0; }
};


//**********************************************************************************************************//
//************************************** Propfind Requests *************************************************//
//**********************************************************************************************************//

enum PropfindStates
{
    PROPFINDPATHREQUEST = 0,
    PROPFINDLIST,
    PROPFINDCOMPLETE,
    PROPFINDCLOSE
};

class WebdavServicePropfindWebserver : public UWebserverPropfind, public UWebdavServiceTask {
    // UWebserverPropfind
    void WebserverPropfindRequestAcceptComplete(IWebserverPropfind * const webserverpropfind) override;
    void WebserverPropfindSendResult(IWebserverPropfind * const webserverPropfind) override;
    void WebserverPropfindRecvResult(IWebserverPropfind * const webserverPropfind, void * buffer, size_t len) override;
    void * WebserverPropfindRecvBuffer(size_t len) override;
    void WebserverPropfindRecvCanceled(IWebserverPropfind * const webserverPropfind, void * buffer) override;
    void WebserverPropfindCloseComplete(IWebserverPropfind * const webserverPropfind) override;

    class IWebserverPropfind * webserverPropfind;
    class WebdavServicePropfind * webdavServicePropfind;

public:
    WebdavServicePropfindWebserver(class WebdavServicePropfind * webdavServicePropfind);
    ~WebdavServicePropfindWebserver();

    void Cancel(wsr_cancel_type_t type);
    void Recv();
    void Send(const void * data, size_t len);
    void SetResultCode(ws_webdav_result_t result, size_t datasize = 0);
    bool DataIsChunkEncoded();
    const char * GetHeaderFieldValue(const char * field);
    void Close() override;
};

class WebdavServicePropfindDBFiles : public UTask, public UWebdavServiceTask {
    // UTask
    void TaskComplete(class ITask * const task) override;
    void TaskFailed(class ITask * const task) override;
    void TaskProgress(class ITask * const task, dword progress) override;

    unsigned state;
    class IDbFilesList * fileslist;
    class IDbFilesPathInfo * pathinfo;
    class WebdavServicePropfind * webdavServicePropfind;
    class IDbFiles * dbFiles;

public:
    WebdavServicePropfindDBFiles(class WebdavServicePropfind * webdavServicePut, class IDbFiles * dbFiles);
    virtual ~WebdavServicePropfindDBFiles();

    void LookPath(char * path);
    void List(ulong64 folderId);
    void Next();
    void Close() override;
};

class WebdavServicePropfind : public IWebdavServiceTask, public UWebdavServiceTask {
    class WebdavServicePropfindDBFiles * webdavServicePropfindDBFiles;
    class WebdavServicePropfindWebserver * webdavServicePropfindWebserver;
    class WebdavService * webdavservice;

    ulong64 id;
    char * path;
    char * rootFolderPath;
    size_t dataSize;
    dword properties;
    dword depth;
    const char * host;
    bool pendingRequestWebserver;
    bool pendingRequestDBFiles;
    bool propfindComplete;
    dword GetRequestedProperties(void * buffer);
    dword GetDepthHeader();
    const char * GetHostHeader();
    void SendItem(const char * name, unsigned contentlength, bool is_folder, ulong64 created, ulong64 modified);

public:
    WebdavServicePropfind(IWebserverPlugin * const webserverPlugin, class WebdavService * webdavservice, char * path, size_t dataSize, char * rootFolderPath = 0);
    ~WebdavServicePropfind();

    bool Send(const void * data, size_t len);
    void AcceptReceived();
    void PathCompleted(bool completed, ulong64 id, const char * name, unsigned length, bool isFolder, ulong64 created, ulong64 modified);
    void ListCompleted(bool completed);
    void Close() override;
    void CloseComplete(class UWebdavServiceTask * task) override;
    void WebserverRecv(void * buffer, size_t len);
    void SendResult();
    void ListProgress(ulong64 id, const char * name, unsigned length, bool isFolder, ulong64 created, ulong64 modified);
    bool Cancel(wsr_cancel_type_t type);
    
    class WebdavService * GetWebdavService(){ return webdavservice ? webdavservice : 0; }
    char * GetPath() { return path ? path : 0; }
};

//**********************************************************************************************************//
//************************************** Move Requests *****************************************************//
//**********************************************************************************************************//

enum MoveStates
{
    MOVEPATHREQUESTSOURCE = 0,
    MOVEPATHREQUESTDESTINATION,
    MOVEDELETEDESTINATION,
    MOVEWRITETODESTINATION,
    MOVECLOSE
};

class WebdavServiceMoveWebserver : public UWebserverMove, public UWebdavServiceTask {
    // UWebserverMove
    void WebserverMoveRequestAcceptComplete(IWebserverMove * const webserverMove) override;
    void WebserverMoveSendResult(IWebserverMove * const webserverMove) override;
    void WebserverMoveCloseComplete(IWebserverMove * const webserverMove) override;

    class IWebserverMove * webserverMove;
    class WebdavServiceMove * webdavServiceMove;

public:
    WebdavServiceMoveWebserver(class WebdavServiceMove * webdavServiceMove);
    ~WebdavServiceMoveWebserver();

    void Cancel(wsr_cancel_type_t type);
    void Recv();
    void Send(const void * data, size_t len);
    void SetResultCode(ws_webdav_result_t result, size_t datasize = 0);
    const char * GetHeaderFieldValue(const char * field);
    void Close() override;
};

class WebdavServiceMoveDBFiles : public UTask, public UWebdavServiceTask {
    // UTask
    void TaskComplete(class ITask * const task) override;
    void TaskFailed(class ITask * const task) override;
    void TaskProgress(class ITask * const task, dword progress) override;

    unsigned state;
    class IDbFilesMove * filesMove;
    class WebdavServiceMove * webdavServiceMove;
    class IDbFiles * dbFiles;
    class IDbFilesDel * filesDelete;
    class IDbFilesPathInfo * srcpathinfo;
    class IDbFilesPathInfo * dstpathinfo;

public:
    WebdavServiceMoveDBFiles(class WebdavServiceMove * webdavServiceMove, class IDbFiles * dbFiles);
    virtual ~WebdavServiceMoveDBFiles();

    void LookSrcPath(char * path);
    void LookDstPath(char * path);
    void WriteFile(byte * data, unsigned len, bool last);
    void PutFile(char * filename, ulong64 folder);
    void SrcGetFailed(ulong64 & parent, bool & isFolder, const char * &path);
    void DstGetFailed(ulong64 & parent, bool & isFolder, const char * &path);
    void Delete(ulong64 id);
    void Move(ulong64 id, char * name, ulong64 folder);
    void Close() override;
};

class WebdavServiceMove : public IWebdavServiceTask, public UWebdavServiceTask {
    class WebdavServiceMoveDBFiles * webdavServiceMoveDBFiles;
    class WebdavServiceMoveWebserver * webdavServiceMoveWebserver;
    class WebdavService * webdavservice;
    ulong64 srcId;
    ulong64 parentId;
    
    char * path;
    char * destination;
    char * filename;
    const char * host;
    dword depth;
    bool overwrite;
    bool iscollection;
    size_t dataSize;
    bool pendingRequestWebserver;
    bool pendingRequestDBFiles;
    dword GetDepthHeader();
    const char * GetDestinationHeader();
    const char * GetHostHeader();
    bool GetOverwriteHeader();

public:
    WebdavServiceMove(IWebserverPlugin * const webserverPlugin, class WebdavService * webdavservice, char * path, size_t dataSize);
    ~WebdavServiceMove();

    bool Send(const void * data, size_t len);
    void AcceptReceived();
    void SrcPathCompleted(bool completed, ulong64 id, const char * name, unsigned length, bool isFolder, ulong64 created, ulong64 modified);
    void DstPathCompleted(bool completed, ulong64 id, const char * name, unsigned length, bool isFolder, ulong64 created, ulong64 modified);
    void MoveCompleted(bool completed);
    void DeleteCompleted(bool completed);
    void Close() override;
    void CloseComplete(class UWebdavServiceTask * task) override;
    void WebserverRecv(void * buffer, size_t len);
    void SendResult();
    void WriteProgress();
    bool Cancel(wsr_cancel_type_t type);
    bool SetTransferInfo(wsr_type_t resourceType, size_t dataSize);
    class WebdavService * GetWebdavService(){ return webdavservice ? webdavservice : 0; }
    char * GetPath() { return path ? path : 0; }
};

//**********************************************************************************************************//
//************************************** MkCol Requests ****************************************************//
//**********************************************************************************************************//


enum MkColStates
{
    MKCOLPATHREQUEST = 0,
    MKCOLPARENTFOLDERREQUEST,
    MKCOLNOCOLLECTIONFOUND,
    MKCOLCLOSE
};

class WebdavServiceMkColWebserver : public UWebserverMkCol, public UWebdavServiceTask {
    // UWebserverMkCol
    void WebserverMkColRequestAcceptComplete(IWebserverMkCol * const webserverMkCol) override;
    void WebserverMkColSendResult(IWebserverMkCol * const webserverMkCol) override;
    void WebserverMkColCloseComplete(IWebserverMkCol * const webserverMkCol) override;

    class IWebserverMkCol * webserverMkCol;
    class WebdavServiceMkCol * webdavServiceMkCol;

public:
    WebdavServiceMkColWebserver(class WebdavServiceMkCol * webdavServiceMkCol);
    ~WebdavServiceMkColWebserver();

    void Cancel(wsr_cancel_type_t type);
    void Send(const void * data, size_t len);
    void SetResultCode(ws_webdav_result_t result);
    const char * GetHeaderFieldValue(const char * field);
    void Close() override;
};

class WebdavServiceMkColDBFiles : public UTask, public UWebdavServiceTask {
    // UTask
    void TaskComplete(class ITask * const task) override;
    void TaskFailed(class ITask * const task) override;
    void TaskProgress(class ITask * const task, dword progress) override;

    unsigned state;
    class IDbFilesPut * filesmkcol;
    class IDbFilesPathInfo * pathinfo;
    class WebdavServiceMkCol * webdavServiceMkCol;
    class IDbFiles * dbFiles;

public:
    WebdavServiceMkColDBFiles(class WebdavServiceMkCol * webdavServiceMkCol, class IDbFiles * dbFiles);
    virtual ~WebdavServiceMkColDBFiles();

    void LookPath(char * path);
    void WriteFolder(char * foldername, ulong64 folder);
    void GetFailed(ulong64 & parent, bool & isFolder, const char * &path);
    void Close() override;
};

class WebdavServiceMkCol : public IWebdavServiceTask, public UWebdavServiceTask {
    class WebdavServiceMkColDBFiles * webdavServiceMkColDBFiles;
    class WebdavServiceMkColWebserver * webdavServiceMkColWebserver;
    class WebdavService * webdavservice;
    ulong64 id;
    char * foldername;
    char * path;
    const char * host;
    
    size_t dataSize;
    const char * GetHostHeader();
    bool pendingRequestWebserver;
    bool pendingRequestDBFiles;

public:
    WebdavServiceMkCol(IWebserverPlugin * const webserverPlugin, class WebdavService * webdavservice, char * path, size_t dataSize);
    ~WebdavServiceMkCol();

    bool Send(const void * data, size_t len);
    void AcceptReceived();
    void PathCompleted(bool completed, ulong64 id, const char * name, unsigned length, bool isFolder, ulong64 created, ulong64 modified);
    void WriteCompleted(bool completed);
    void Close() override;
    void CloseComplete(class UWebdavServiceTask * task) override;
    void WebserverRecv(void * buffer, size_t len);
    void SendResult();
    bool Cancel(wsr_cancel_type_t type);
    
    class WebdavService * GetWebdavService(){ return webdavservice ? webdavservice : 0; }
    char * GetPath() { return path ? path : 0; }
};

//**********************************************************************************************************//
//************************************** Delete Requests ***************************************************//
//**********************************************************************************************************//

enum DeleteStates
{
    DELETEPATHREQUEST = 0,
    DELETEREQUEST,
    DELETECLOSE
};

class WebdavServiceDeleteWebserver : public UWebserverDelete, public UWebdavServiceTask {
    // UWebserverDelete
    void WebserverDeleteRequestAcceptComplete(IWebserverDelete * const webserverDelete) override;
    void WebserverDeleteSendResult(IWebserverDelete * const webserverDelete) override;
    void WebserverDeleteCloseComplete(IWebserverDelete * const webserverDelete) override;

    class IWebserverDelete * webserverDelete;
    class WebdavServiceDelete * webdavServiceDelete;

public:
    WebdavServiceDeleteWebserver(class WebdavServiceDelete * webdavServiceDelete);
    ~WebdavServiceDeleteWebserver();

    void Cancel(wsr_cancel_type_t type);
    void Send(const void * data, size_t len);
    void Close() override;
    void SetResultCode(ws_webdav_result_t result, size_t datasize=0);
};

class WebdavServiceDeleteDBFiles : public UTask, public UWebdavServiceTask {
    // UTask
    void TaskComplete(class ITask * const task) override;
    void TaskFailed(class ITask * const task) override;
    void TaskProgress(class ITask * const task, dword progress) override;

    unsigned state;
    class IDbFilesDel * filesDelete;
    class IDbFilesPathInfo * pathinfo;
    class WebdavServiceDelete * webdavServiceDelete;
    class IDbFiles * dbFiles;

public:
    WebdavServiceDeleteDBFiles(class WebdavServiceDelete * webdavServiceDelete, class IDbFiles * dbFiles);
    virtual ~WebdavServiceDeleteDBFiles();

    void LookPath(char * path);
    void Delete(ulong64 id);
    
    void Close() override;
};

class WebdavServiceDelete : public IWebdavServiceTask, public UWebdavServiceTask {
    class WebdavServiceDeleteDBFiles * webdavServiceDeleteDBFiles;
    class WebdavServiceDeleteWebserver * webdavServiceDeleteWebserver;
    class WebdavService * webdavservice;

    ulong64 id;
    bool pathinfocalled;
    char * path;
    
    
    size_t dataSize;
    bool pendingRequestWebserver;
    bool pendingRequestDBFiles;

public:
    WebdavServiceDelete(IWebserverPlugin * const webserverPlugin, class WebdavService * webdavservice, char * path, size_t dataSize);
    ~WebdavServiceDelete();

    void AcceptReceived();
    void PathCompleted(bool completed, ulong64 id, const char * name, unsigned length, bool isFolder, ulong64 created, ulong64 modified);
    void DeleteCompleted(bool completed);
    void SendResult();
    void Close() override;
    void CloseComplete(class UWebdavServiceTask * task) override;
    bool Cancel(wsr_cancel_type_t type);
    
    class WebdavService * GetWebdavService(){ return webdavservice ? webdavservice : 0; }
    char * GetPath() { return path ? path : 0; }
};

class WebdavServiceOptions : public UWebserverOptions {
    // UWebserverOptions
    void WebserverOptionsRequestAcceptComplete(IWebserverOptions * const webserverOptions) override;
    void WebserverOptionsCloseComplete(IWebserverOptions * const webserverOptions) override;

    class WebdavService * webdavservice;
    class IWebserverOptions * webserveroptions;

public:
    WebdavServiceOptions(class WebdavService * webdavservice, char * path, size_t dataSize);
    ~WebdavServiceOptions();
};

class WebdavLock : public istd::listElement<WebdavLock> {
public:
    bool write;         // type
    bool exclusive;     // scope
    size_t timeout;
    size_t expires;
    const char * owner;
    const char * owner_href;
    const char * token;
    const char * resource;
    WebdavLock();
    ~WebdavLock();
};

class WebdavServiceLock : public UWebserverLock {
    void WebserverLockRequestAcceptComplete(IWebserverLock * const webserverLock) override;
    void WebserverLockSendResult(IWebserverLock * const webserverLock) override;
    void WebserverLockCloseComplete(IWebserverLock * const webserverLock) override;
    void WebserverLockRecvResult(IWebserverLock * const webserverLock, void * buffer, size_t len) override;
    void * WebserverLockRecvBuffer(size_t len) override;
    void WebserverLockRecvCanceled(IWebserverLock * const webserverLock, void * buffer) override;
    class WebdavService * webdavservice;
    class IWebserverLock * webserverLock;
    class WebdavLock * GetLockProperties(void * buffer);
    void SendLockResponse(class WebdavLock * lock);
    size_t dataSize;
    char * path;

public:
    WebdavServiceLock(class WebdavService * webdavservice, char * path, size_t dataSize);
    ~WebdavServiceLock();
};

class WebdavServiceUnLock : public UWebserverUnlock {
    void WebserverUnlockRequestAcceptComplete(IWebserverUnlock * const webserverUnlock) override;
    void WebserverUnlockSendResult(IWebserverUnlock * const webserverUnlock) override;
    void WebserverUnlockCloseComplete(IWebserverUnlock * const webserverUnlock) override;
    class WebdavService * webdavservice;
    char * path;
    class IWebserverUnlock * webserverUnlock;

public:
    WebdavServiceUnLock(class WebdavService * webdavservice, char * path, size_t dataSize);
    ~WebdavServiceUnLock();
};

class SetProperty : public istd::listElement <SetProperty>
{
public:
    char * propname;
    SetProperty(const char * name)
    {
        if (name) this->propname = _strdup(name);
        else this->propname = 0;
    }
    ~SetProperty()
    {
        if (this->propname) free(propname);
    }
};

class RemProperty : public istd::listElement <RemProperty>
{
public:
    char * propname;
    RemProperty(const char * name)
    {
        if (name) this->propname = _strdup(name);
        else this->propname = 0;
    }
    ~RemProperty()
    {
        if (this->propname) free(propname);
    }
};

class WebdavServiceProppatch : public UWebserverProppatch {
    void WebserverProppatchRequestAcceptComplete(IWebserverProppatch * const webserverProppatch) override;
    void WebserverProppatchSendResult(IWebserverProppatch * const webserverProppatch) override;
    void WebserverProppatchRecvResult(IWebserverProppatch * const webserverProppatch, void * buffer, size_t len) override;
    void * WebserverProppatchRecvBuffer(size_t len) override;
    void WebserverProppatchRecvCanceled(IWebserverProppatch * const webserverProppatch, void * buffer) override;
    void WebserverProppatchCloseComplete(IWebserverProppatch * const webserverProppatch) override;
    class WebdavService * webdavservice;
    char * path;
    size_t dataSize;
    class IWebserverProppatch * webserverProppatch;
    void GetProppatchProperties(void * buffer);
    void SendProppatchResponse();
    class istd::list<SetProperty> setProperties;
    class istd::list<RemProperty> remProperties;

public:
    WebdavServiceProppatch(class WebdavService * webdavservice, char * path, size_t dataSize);
    ~WebdavServiceProppatch();
};

