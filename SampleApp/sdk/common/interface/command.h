/*---------------------------------------------------------------------------*/
/* command.h                                                               */
/* copyright (c) innovaphone 2017                                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/

class ICommandProvider * CreateCommandProvider(class IIoMux * iomux);

class ICommandProvider {
public:
    virtual ~ICommandProvider() {}
    virtual class ICommand * CreateCommand(class IInstanceLog * const log, class UTask * user, const char * command, int expectedExitCode, size_t initialReadLength = 0) = 0;
};

enum {
    COMMAND_PROGRESS_READ = 0,
    COMMAND_PROGRESS_WRITE
};

class ICommand : public ITask {
public:
    virtual void Write(byte * data, size_t length, bool last = false) = 0;
    virtual void Read(size_t length) = 0;
    virtual void Get(const byte * & data, size_t & length) = 0;
    virtual void Close() = 0;
    virtual const char * Error() = 0;
    virtual int GetExitCode() = 0;
};
