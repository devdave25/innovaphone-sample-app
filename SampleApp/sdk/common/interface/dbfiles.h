
/*---------------------------------------------------------------------------*/
/* dbfiles.h                                                                 */
/* copyright (c) innovaphone 2016                                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/

class IDbFilesProvider * CreateDbFilesProvider();

class IDbFilesProvider {
public:
    virtual ~IDbFilesProvider() {}
    virtual class IDbFiles * CreateDbFiles(class IIoMux * iomux, class IInstanceLog * const log) = 0;
};

#define DBFILES_ROOT 1

class IDbFiles {
public:
    virtual ~IDbFiles() {}
    virtual class IDbFilesStart * Start(class UTask * user, class IDatabase * database, const char * folder) = 0;
    virtual class IDbFilesPut * Put(class UTask * user, const char * name, ulong64 folder, bool is_folder = false) = 0;
    virtual class IDbFilesGet * Get(class UTask * user, ulong64 id, unsigned offset = 0, bool progress = false) = 0;
    virtual class IDbFilesDel * Del(class UTask * user, ulong64 id) = 0;
    virtual class IDbFilesMove * Move(class UTask * user, ulong64 id, const char * name, ulong64 folder) = 0;
    virtual class IDbFilesList * List(class UTask * user, ulong64 folder, ulong64 limit) = 0;
    virtual class IDbFilesPathInfo * PathInfo(class UTask * user, const char * path) = 0;
};

class IDbFilesStart : public ITask {
public:
};

class IDbFilesPut : public ITask {
public:
    virtual ulong64 Get() = 0;
    virtual const char * GetName() = 0;
    virtual void Write(const byte * data, unsigned length, bool last) = 0;
};

class IDbFilesGet : public ITask {
public:
    virtual void Get(const byte * & data, unsigned & length) = 0;
    virtual void Read(bool last=false) = 0;
};

class IDbFilesDel : public ITask {
public:
};

class IDbFilesMove : public ITask {
public:
};

class IDbFilesList : public ITask {
public:
    virtual bool Get(ulong64 & id, const char * & name, unsigned & length, bool & is_folder, ulong64 * created = 0, ulong64 * modified = 0) = 0;
    virtual void Next() = 0;
};

class IDbFilesPathInfo : public ITask {
public:
    virtual void Get(ulong64 & id, const char * & name, unsigned & length, bool & is_folder, ulong64 * created = 0, ulong64 * modified = 0) = 0;
    virtual void GetFailed(ulong64 & folder, bool & is_folder, const char * & path) = 0;
};
