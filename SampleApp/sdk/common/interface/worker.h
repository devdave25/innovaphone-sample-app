/*---------------------------------------------------------------------------*/
/* worker.h                                                                     */
/* copyright (c) innovaphone 2016                                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/
typedef void(*NOTIFICATION_FUNC)(class UWorker * const user, class IWorker * const task, char* notification);
typedef int(*WORKER_TASK)(const char * job, class UWorker * const user, char** result, class IWorker * const task, NOTIFICATION_FUNC notificationFunc);
class IWorker {
public:
    static IWorker* Create(class IIoMux * const iomux,unsigned int numThreads);
    virtual ~IWorker(){};
    virtual void WorkerScheduleJob(const char * job, WORKER_TASK workerTask, class UWorker * const user)=0;
};

class UWorker {
public:
    virtual void WorkerJobComplete(class IWorker * const task, const char * jobResult) = 0;
    virtual void WorkerJobProgress(class IWorker * const task, const char * notification) {};
    virtual void WorkerJobFailed(class IWorker * const task, int error) = 0;
};
