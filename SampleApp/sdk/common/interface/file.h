
/*---------------------------------------------------------------------------*/
/* file.h																     */
/* copyright (c) innovaphone 2016                                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/

class FileSystem {
public:
    static class IFileWrite * OpenWriteFile(const char * fileName, bool append, class IInstanceLog * log);
    static class IFileRead * OpenReadFile(const char * fileName, class IInstanceLog * log);
    static class IDirectory * OpenDirectory(const char * directoryPath, class IInstanceLog * log);
    static class IElfBinary * OpenElfBinary(const char * bin, class IInstanceLog * log);
    static bool ReadWholeFile(const char * filename, char * readBuffer, size_t size, class IInstanceLog * log);
    static bool WriteWholeFile(const char * filename, const char * writeBuffer, size_t size, class IInstanceLog * log);
    static bool ScanFile(class IInstanceLog * log, const char * filename, const char * format, ...);
    static bool FileExists(const char * filename, class IInstanceLog * log);
    static time_t GetLastWriteTime(const char * filename, class IInstanceLog * log);
    static off_t GetFileSize(const char * filename, class IInstanceLog * log);
    static off_t GetFileBlockSize(const char * filename, class IInstanceLog * log);
    static bool Rename(const char * oldName, const char * newName, class IInstanceLog * log);
    static bool RemoveFile(const char * filename, class IInstanceLog * log);
    static bool CreateDirectory(const char * absolutePath, int mode, class IInstanceLog * log);
    static bool RemoveDirectory(const char * directoryPath, class IInstanceLog * log);
    static bool ChangeOwner(const char * path, const char * newOwner, const char * newGroup, class IInstanceLog * log);
    static bool ChangeMode(const char * path, int mode, class IInstanceLog * log);
    static ulong64 GetFileSystemTotalSize(const char * path, class IInstanceLog * log);
    static ulong64 GetFileSystemUsedSpace(const char * path, class IInstanceLog * log);
    static bool CheckSystemUser(const char * user, const char * group, class IInstanceLog * log);
    static char * GetFileSystemUser(const char * filepath, class IInstanceLog * log);
};

class IFileWrite {
public:
    virtual ~IFileWrite() {};
    virtual bool IsOpen() const = 0;
    virtual bool Write(const void * buffer, size_t len) = 0;
    virtual void Flush() = 0;
    virtual bool Close() = 0;
};

class IFileRead {
public:
    virtual ~IFileRead() {};
    virtual bool IsOpen() const = 0;
    virtual size_t Read(void * buffer, size_t len) = 0;
    virtual bool Close() = 0;
};

class IDirectory {
public:
    virtual ~IDirectory() {};
    virtual bool IsOpen() const = 0;
    virtual class IDirectoryEntry * ReadNext() = 0;
    virtual bool Close() = 0;
};

class IDirectoryEntry {
public:
    virtual ~IDirectoryEntry() {};
    virtual const char * GetName() const = 0;
    virtual bool IsFile() const = 0;
};

typedef enum {
    ELF_UNKOWN,
    ELF_ARM,
    ELF_X86_64
} elf_architecture_t;

class IElfBinary {
public:
    virtual ~IElfBinary(){};
    virtual bool IsOpen() = 0;
    virtual bool IsElfBinary() = 0;
    virtual bool IsExecutable() = 0;
    virtual elf_architecture_t GetArchitecture() = 0;
    virtual bool Close() = 0;
};

