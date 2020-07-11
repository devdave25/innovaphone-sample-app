/*---------------------------------------------------------------------------*/
/* pbx.h                                                                     */
/* copyright (c) innovaphone 2017                                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/

#define PBX_API_PROGRESS_SUBSCIPTION 1
#define PBX_API_PROGRESS_PRESENCE 2

extern class IPbxApi * CreatePbxApi(class IJsonApiConnection * conn);

class IPbxApi {
public:
    virtual ~IPbxApi() {};
    virtual class ITask * CreateSetPresence(const char * guid, const char * sip, const char * contact, const char * activity, const char * note) = 0;
    virtual class IPbxApiPresenceSubscription * CreatePresenceSubscription(const char * sip, const char * num, const char * sourceSip = 0) = 0;
    virtual class IPbxApiTaskGetNodeInfo * CreateGetNodeInfo(const char * pbx, const char * domain) = 0;

};

class IPbxApiPresenceSubscription : public ITask {
public:
    virtual ~IPbxApiPresenceSubscription() {}
    virtual void Start(class UTask * user) = 0;
    virtual void Stop() = 0;

    virtual bool IsUp() = 0;
    virtual const char * GetSip() = 0;
    virtual const char * GetDn() = 0;
    virtual const char * GetNum() = 0;
    virtual const char * GetEmail() = 0;
    virtual class IPbxApiPresence * GetPresence() = 0;
};

class IPbxApiPresence {
public:
    virtual const char * GetContact() = 0;
    virtual const char * GetStatus() = 0;
    virtual const char * GetActivity() = 0;
    virtual const char * GetNote() = 0;
    virtual class IPbxApiPresence * GetNext() = 0;
};

class IPbxApiTaskGetNodeInfo : public ITask {
public:
    virtual ~IPbxApiTaskGetNodeInfo() {}
    virtual void Start(class UTask * user) = 0;
    virtual void Stop() = 0;

    virtual const char * GetName() = 0;
    virtual const char * GetPrefixIntl() = 0;
    virtual const char * GetPrefixNtl() = 0;
    virtual const char * GetPrefixSubs() = 0;
    virtual const char * GetAreaCode() = 0;
    virtual const char * GetCountryCode() = 0;
};
