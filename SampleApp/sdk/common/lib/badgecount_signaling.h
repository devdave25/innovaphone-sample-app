
/*-----------------------------------------------------------------------------------------------*/
/* badgecount_signaling.h                                                                        */
/* copyright (c) innovaphone 2018                                                                */
/*                                                                                               */
/*-----------------------------------------------------------------------------------------------*/

class UBadgeCountSignaling {

public:
    virtual void CreateBadgeCountPresenceMonitor(class BadgeCountSignaling * signaling, int call, const char * user, const char * topic) = 0;
};

class BadgeCountSignaling : public JsonApi {
    const char * Name() { return "PbxSignal"; };
    void Message(class json_io & msg, word base, const char * mt, const char * src);
    void JsonApiConnectionClosed();

public:
    BadgeCountSignaling(class UBadgeCountSignaling * user, class AppUpdatesSession * session);
    ~BadgeCountSignaling();
    int nextCall();

    class UBadgeCountSignaling * user;
    class AppUpdatesSession * session;
    class btree * calls;
    int call;
};

class BadgeCountCall : public btree {
    int btree_compare(void * key) { return (int)(intp)key - call; };
    int btree_compare(class btree * b) { return ((class BadgeCountCall *)b)->call - call; };
public:
    BadgeCountCall(class BadgeCountSignaling * signaling, int call);
    virtual ~BadgeCountCall();

    virtual void Signaling(class json_io & msg, word base, const char * src, const char * type) = 0;

    void SendConn();
    void SendRel();

    class BadgeCountSignaling * signaling;
    int call;
    byte state;
};

class BadgeCountPresenceMonitor : public BadgeCountCall {
    void Signaling(class json_io & msg, word base, const char * src, const char * type) override;

public:
    BadgeCountPresenceMonitor(class BadgeCountSignaling * signaling, int call);
    ~BadgeCountPresenceMonitor();

    void SendBadge(ulong64 count);
};

