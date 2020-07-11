
/*---------------------------------------------------------------------------*/
/* files.h                                                                   */
/* copyright (c) innovaphone 2016                                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/

class IFilesProvider * CreateFilesProvider(class IIoMux * iomux);

class IFilesProvider {
public:
    virtual ~IFilesProvider() {}
    virtual class IFiles * CreateFiles(class IInstanceLog * const log, const char * serviceId, const char * path) = 0;
};

class IFiles {
public:
    virtual ~IFiles() {}
    virtual class IFilesWrite * Write(class UTask * user, ulong64 id) = 0;
    virtual class IFilesRead * Read(class UTask * user, ulong64 id, unsigned length, unsigned offset = 0, bool progress = false) = 0;
    virtual class IFilesDel * Del(class UTask * user, ulong64 id) = 0;
};

class ITempFilesProvider * CreateTempFilesProvider(class IIoMux * iomux);

class ITempFilesProvider {
public:
    virtual ~ITempFilesProvider() {}
    virtual class ITempFiles * CreateTempFiles(class IInstanceLog * const log, const char * serviceId, const char * path) = 0;
};

class ITempFiles {
public:
    virtual ~ITempFiles() {}
    virtual class IFilesWrite * Write(class UTask * user) = 0;
    virtual class IFilesRead * Read(class UTask * user, ulong64 id, unsigned length, unsigned offset = 0, bool progress = false) = 0;
    virtual class IFilesDel * Del(class UTask * user, ulong64 id) = 0;
};

class IFilesWrite : public ITask {
public:
    virtual void Write(const byte * data, unsigned length, bool last) = 0;
    virtual ulong64 GetId() const = 0;
    virtual const char * GetAbsoluteFileName() const = 0;
    virtual void Close() = 0;
};

class IFilesRead : public ITask {
public:
    virtual void Read(unsigned length, bool last) = 0;
    virtual void Get(const byte * & data, unsigned & length) const = 0;
    virtual void Close() = 0;
};

class IFilesDel : public ITask {
public:
};
