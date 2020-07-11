
/*---------------------------------------------------------------------------*/
/* task.h                                                                    */
/* copyright (c) innovaphone 2016                                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/

#define TASK_PROGRESS_USER 0x80000000

class UTask {
public:
    virtual ~UTask() {};
    virtual void TaskComplete(class ITask * const task) = 0;
    virtual void TaskFailed(class ITask * const task) = 0;
    virtual void TaskProgress(class ITask * const task, dword progress = 0) {};
};

class ITask {
protected:
    class UTask * user;

public:
    ITask() { user = 0; error = false; stopped = false; }
    virtual ~ITask() {}
    virtual void Start() {};
    virtual void Start(class UTask * user) = 0;
    virtual void Stop() { stopped = true; };
    virtual void Complete() { if (user) user->TaskComplete(this); };
    virtual void Failed() { if (user) user->TaskFailed(this); };
    virtual void Progress(dword progress) { if (user) user->TaskProgress(this, progress); };
    virtual void Finished() {};
    bool error;
    bool stopped;
};

template <class B, class T> class UTaskTemplate : public UTask {
    B * base;
    void (B::* taskComplete)(T * const task);
    void (B::* taskFailed)(T * const task);
    void (B::* taskProgress)(T * const task, dword progress);
    void TaskComplete(class ITask * const task) {
        ASSERT(taskComplete, "taskComplete undefined");
        task->error = false;
        (*base.*(taskComplete))((T *)task);
    }
    void TaskFailed(class ITask * const task) {
        ASSERT(taskFailed, "taskFailed undefined");
        task->error = true;
        (*base.*(taskFailed))((T *)task);
    }
    void TaskProgress(class ITask * const task, dword progress) {
        if (taskProgress) {
            (*base.*(taskProgress))((T *)task, progress);
        }
    }
public:
    UTaskTemplate(B * base,
                  void (B::* taskComplete)(T * task),
                  void (B::* taskFailed)(T * task) = 0,
                  void (B::* taskProgress)(T * task, dword progress) = 0) {
        this->base = base;
        this->taskComplete = taskComplete;
        this->taskFailed = taskFailed;
        this->taskProgress = taskProgress;
    };
};

#define ITASK_ARGS0()
#define ITASK_ARGS1(a1) a1
#define ITASK_ARGS2(a1, a2) a1, a2
#define ITASK_ARGS3(a1, a2, a3) a1, a2, a3
#define ITASK_ARGS4(a1, a2, a3, a4) a1, a2, a3, a4
#define ITASK_ARGS5(a1, a2, a3, a4, a5) a1, a2, a3, a4, a5
#define ITASK_ARGS6(a1, a2, a3, a4, a5, a6) a1, a2, a3, a4, a5, a6
#define ITASK_ARGS7(a1, a2, a3, a4, a5, a6, a7) a1, a2, a3, a4, a5, a6, a7
#define ITASK_ARGS8(a1, a2, a3, a4, a5, a6, a7, a8) a1, a2, a3, a4, a5, a6, a7, a8
#define ITASK_ARGS9(a1, a2, a3, a4, a5, a6, a7, a8, a9) a1, a2, a3, a4, a5, a6, a7, a8, a9

#define ITASK(B, U, T, AD, A) \
class U : public T, public UTaskTemplate<B, T> { \
public: \
    void Start() { ((ITask *)this)->Start(this); }; \
    U (AD, B * base, void (B::* taskComplete)(T * task), void (B::* taskFailed)(T * task) = 0, void (B::* taskProgress)(T * task, dword progress) = 0) : T(A), UTaskTemplate(base, taskComplete, taskFailed, taskProgress) {} \
};

