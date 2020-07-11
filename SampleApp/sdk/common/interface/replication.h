
/*---------------------------------------------------------------------------*/
/* replication.h                                                             */
/* copyright (c) innovaphone 2017                                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/

enum ReplicationType {
    ReplicationString,
    ReplicationULong64,
    ReplicationUnsigned,
    ReplicationBool,
    ReplicationTristate,
    ReplicationArray
};

class IReplicator : public UJsonApiContext {
public:
    virtual ~IReplicator() {};
    virtual void Update(const char * domain, const char * instance) = 0;
    virtual void AddColumn(const char * remote, const char * local, enum ReplicationType type, bool update) = 0;
    virtual class IReplicatorArray * AddArray(const char * remote, const char * local, bool update, const char * reference) = 0;
    virtual void Initialize(const char * row) = 0;
    virtual void Added(ulong64 id) = 0;
    virtual void Deleted(ulong64 id) = 0;
    virtual void DeletedConfirm(ulong64 id) = 0;
    virtual void Updated(ulong64 id, ulong64 mask=0xffffffffffffffffLL) = 0;
    virtual void Start() = 0;
    virtual void Stop() = 0;

    static class IReplicator * createReplicator(class UReplicator * user, const char * remote, const char * domain, const char * instance, const char * domainProperty, const char * instanceProperty, class IDatabase * database, const char * local, bool add, bool del);
};

class UReplicator {
public:
    virtual void ReplicatorInitialized() = 0;
    virtual void ReplicatorAdded(ulong64 id) = 0;
    virtual void ReplicatorDeleted(ulong64 id) = 0;
    virtual void ReplicatorDeletedConfirm(ulong64 id) = 0;
    virtual void ReplicatorDeletedConfirmComplete(ulong64 id) = 0;
    virtual void ReplicatorUpdated(ulong64 id, ulong64 mask) = 0;
    virtual void ReplicatorSessionInitializing() {}
    virtual void ReplicatorSessionInitialized() {}
    virtual void ReplicatorSessionClosed() {}
    virtual void ReplicatorStopped() = 0;

    virtual void ReplicatorUpdate(class json_io & msg, word base, bool initial) {};
    virtual void ReplicatorStart(class json_io & msg, word base, char * & tmp) {};
};

class IReplicatorArray {
public:
    virtual ~IReplicatorArray() {};
    virtual void AddColumn(const char * remote, const char * local, enum ReplicationType type, bool update) = 0;
};

class IPublisher : public UJsonApiContext  {
public:
    virtual ~IPublisher() {};
    virtual void AddColumn(const char * remote, const char * local, enum ReplicationType type, bool update) = 0;
    virtual void Initialize(const char * row) = 0;
    virtual void Added(ulong64 id) = 0;
    virtual void Deleted(ulong64 id) = 0;
    virtual void DeletedConfirm(ulong64 id) = 0;
    virtual void Updated(ulong64 id, ulong64 mask) = 0;
    virtual void Stop() = 0;

    static class IPublisher * createPublisher(class UPublisher * user, const char * remote, class IDatabase * database, const char * local, bool add, bool del);
};

class UPublisher {
public:
    virtual void PublisherInitialized() = 0;
    virtual void PublisherAdded(ulong64 id) = 0;
    virtual void PublisherDeleted(ulong64 id) = 0;
    virtual void PublisherDeletedConfirm(ulong64 id) = 0;
    virtual void PublisherUpdated(ulong64 id, ulong64 mask) = 0;
    virtual void PublisherStopped() = 0;
};
