
/*---------------------------------------------------------------------------*/
/* stask.h                                                                   */
/* copyright (c) innovaphone 2017                                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/

class STaskThread;

class STaskContext {
public:
    STaskContext(class IIoMux * iomux) {
        this->iomux = iomux;
    };

    class IIoMux * iomux;
    istd::list<STaskThread> threadsIdle;
    istd::list<STaskThread> threadsBusy;
};

class STaskComplete {};
class STaskFailed {};
class STaskProgress {};

class STask : public ITask,
    public UIoExecSubclass<STaskComplete>,
    public UIoExecSubclass<STaskFailed>,
    public UIoExecSubclass<STaskProgress>
{
    void IoExec(STaskComplete * execContext);
    void IoExec(STaskFailed * execContext);
    void IoExec(STaskProgress * execContext);

    class STaskContext * context;

protected:
    void TaskComplete();
    void TaskFailed();
    void TaskProgress(dword progress = 0);

    class STaskThread * thread;

public:
    STask(class STaskContext * context);
    virtual ~STask();
    void Start(class UTask * user);
    virtual void SStart() = 0;
};

class STaskThread : public istd::listElement<STaskThread> {
public:
    virtual void startTask(class STask * task) = 0;
    virtual void wait() = 0;
    virtual void cont() = 0;
};