/*---------------------------------------------------------------------------*/
/* sql.h	                                                             */
/* copyright (c) innovaphone 2013                                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/

class ISql;
class USql {
    friend class Sql;

    static		unsigned s_idIFrontendContext;
    bool		isQueued;
    char		* cmd;

public:
    class Parameters {
    public:
        char	* stringVal;
        unsigned uVal;
        Parameters(char * stringVal, unsigned uVal) { this->Set(stringVal, uVal); }
        void Set(char * stringVal, unsigned uVal) { this->stringVal = stringVal; this->uVal = uVal; }
    };

    typedef enum {
        CommandUnknown = 0,
        CommandQuery,
    } CommandType;

    typedef enum {
        NotifyUnknown = 0,
        QueryDone,
    } NotifyType;

    struct {
        unsigned long long timeStampQuery_us;
        void Clear() { memset(this, 0, sizeof(*this)); }

    } stats;

    bool		isRootDSESearch;
    unsigned	idIFrontendContext;
    unsigned	idSqlConn;
    CommandType	commandType;
    IDebug::TraceLabel  traceLabel;

    USql();
    virtual ~USql();
    void SetCommand(USql::CommandType commandType, char * cmd);
    char * GetCommand();
    void StatsProfileStart();
    void StatsProfileEnd();
    void StatsPrint();

    virtual void SqlTupleBegin(char * attr, void * val, unsigned lenVal) = 0;
    virtual void SqlTupleAddFieldValue(char * attr, void * val, unsigned lenVal) = 0;
    virtual void SqlTupleEnd() = 0;
    virtual void SqlNotify(USql::NotifyType notify, USql::Parameters * parameters) = 0;
};


class ISql {
public:

    static ISql * Create(IIoMux * ioMux, const char * sqlType, unsigned numConnections, const char * host, const char * dbName, const char * user, const char * pw);
    virtual ~ISql() {};

    virtual void Query(USql * feContext) = 0;
    virtual void Abort(USql * feContext) = 0;
    virtual void GetFilterForRootDSESearch(char * buf, unsigned sz) = 0;

    virtual unsigned EscapeSQLCommandString(char * to, const char * from, unsigned length) = 0;
    virtual unsigned EscapeSQLCommandWildcardString(char * to, const char * from, unsigned length) = 0;
    virtual unsigned EscapeSQLCommandBinaryValue(unsigned lenIn, void * bufIn, unsigned lenOut, void * bufOut) = 0;
    virtual void EscapeSQLCommandString(unsigned lenIn, void * bufIn, unsigned * lenOut, void ** bufOut, bool wildcard = false) = 0;
};
