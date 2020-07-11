/*---------------------------------------------------------------------------*/
/* iomux.h	                                                                 */
/* copyright (c) innovaphone 2013                                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/

class ISignalConsumer {

public:
	virtual void OnSignal(int signr) = 0;
};

class IShutdownHandler {
public:
    virtual void Shutdown() = 0;
    virtual void ShutdownTimeout() = 0;
};

class IChildExitedHandler {

public:
    virtual void ChildExited(signed int pid, int signr, int exitCode, bool sigFault) = 0;
};

class UIoContext {
protected:
    int		FDIIoMux;	// File descriptor	
public:
    bool    isError, isHangup, isOpened;
    class UserDataIoContext * ctx;

    UIoContext();
    virtual ~UIoContext();

    int	 GetFd();
    void SetFd(int fd);

    virtual void IoContextNotify(bool indRX, bool indTX) = 0;
};

class UIoExec {
	friend class IoMux;
    void * execContext;
    UIoExec * contextOwner;
    UIoExec * contextNext;
    UIoExec * contextPrev;
    UIoExec * ioExecNext;
    UIoExec * ioExecPrev;

public:
    UIoExec();
    virtual ~UIoExec();
    virtual void IoExec(void * execContext) = 0;
};

class IIoMux {
public:
	IIoMux();
	virtual ~IIoMux();
    static IIoMux * Create(bool locking=true, unsigned rlimitNoFile=0);

    virtual void Run() = 0;
    virtual void FDAdd(int fd, UIoContext * context, bool pollOut) = 0;
    virtual void FDClose(UIoContext * context) = 0;
    virtual void FDUnblock(int fd) = 0;
    virtual bool CanAcceptFD() = 0;
    virtual void RegisterSignalConsumer(ISignalConsumer * consumer) = 0;
    virtual void RegisterShutdownHandler(IShutdownHandler * shutdownHandler) = 0;
    virtual void RegisterChildExitedHandler(IChildExitedHandler * childExitedHandler) = 0;
    virtual void UnRegisterChildExitedHandler(IChildExitedHandler * childExitedHandler) = 0;
    virtual void Lock() = 0;
    virtual void UnLock() = 0;
    virtual void SetExec(UIoExec * ioContext, void * execContext) = 0;
    virtual void SetExecLocked(UIoExec * ioContext, void * execContext) = 0;
    virtual void CancelSetExec(UIoExec * const ioContext) = 0;
    virtual void Shutdown() = 0;
    virtual void ShutdownTimeout() = 0;
    virtual void ShutdownComplete(IShutdownHandler * shutdownHandler) = 0;
};

template <class IoExecContext> class UIoExecSubclass : public UIoExec {
    void IoExec(void * execContext) { IoExec((IoExecContext *) execContext); };
public:
    virtual void IoExec(IoExecContext * execContext) = 0;
};


class ITimer;
class UTimer {
public:
    virtual void TimerOnTimeout(ITimer * timer) = 0;
};

class ITimer : public btree {
    friend class IoMux;
    IIoMux * ioMux;
    UTimer * owner;

    bool running;
    dword expires;
    dword delta;
    class ITimer * next;
    class ITimer * prev;

    int btree_compare(void * key) { return *(dword *)key - expires; };
    int btree_compare(class btree * b) { return ((class ITimer *)b)->expires - expires; };
public:

    ITimer(IIoMux * ioMux, UTimer * owner);
    ~ITimer();

    void Start(unsigned timeoutMs);
    void StartLocked(unsigned timeoutMs);
    void Cancel();
    void CancelLocked();
    bool IsRunning() const { return running; };
};

template <class ITimerSubclass> class UTimerSubclass : public UTimer {
    void TimerOnTimeout(ITimer * timer) { TimerOnTimeout(static_cast<ITimerSubclass *>(timer)); };
public:
    virtual void TimerOnTimeout(ITimerSubclass * timer) = 0;
};

class ITimerAbsolute : public UIoContext {
private:
    class IIoMux * const iomux;
    class UTimerAbsolute * const user;
    bool running;

    virtual void IoContextNotify(bool indRX, bool indTX);

public:
    ITimerAbsolute(class IIoMux * iomux, class UTimerAbsolute * user);
    virtual ~ITimerAbsolute();
    
    void Start(long64 timeOutTimeAbs);
    void Cancel();
    bool IsRunning() const { return running; }
};

class UTimerAbsolute {
public:
    UTimerAbsolute() {}
    virtual ~UTimerAbsolute() {}

    virtual void TimerAbsoluteOnTimeout(ITimerAbsolute * timer) = 0;
};