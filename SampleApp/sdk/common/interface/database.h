/*---------------------------------------------------------------------------*/
/* database.h                                                                */
/* copyright (c) innovaphone 2016                                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/

#define DB_EXEC_FETCH_ALL           0x01

typedef enum {
    DB_OK = 0,
    DB_SHUTDOWN_NORMAL = DB_OK,
    DB_ERR_CONNECT_FAILED,
    DB_ERR_SQL_COMMAND_FAILED,
    DB_ERR_SHUTDOWN_STATE,
    DB_ERR_SERVER_ERROR
} db_error_t;


inline const char * DBErrorToStr(db_error_t err)
{
    const char * result = "<unkown error>";
    switch (err) {
    case DB_OK:
        result = "DB_OK";
        break;

    case DB_ERR_CONNECT_FAILED:
        result = "DB_ERR_CONNECT_FAILED";
        break;

    case DB_ERR_SQL_COMMAND_FAILED:
        result = "DB_ERR_SQL_COMMAND_FAILED";
        break;

    case DB_ERR_SHUTDOWN_STATE:
        result = "DB_ERR_SHUTDOWN_STATE";
        break;

    case DB_ERR_SERVER_ERROR:
        result = "DB_ERR_SERVER_ERROR";
        break;
    }

    return result;
}


class IDatabaseProvider {
public:
    virtual ~IDatabaseProvider() {}
    virtual class IDatabase * CreateDatabase(class IIoMux * const iomux, class UDatabase * const user, class IInstanceLog * log) = 0;
};


class IPreparedStatement {
public:
    virtual ~IPreparedStatement() {}
    virtual void SetParam(dword idx, int value) = 0;
    virtual void SetParam(dword idx, dword value) = 0;
    virtual void SetParam(dword idx, long64 value) = 0;
    virtual void SetParam(dword idx, ulong64 value) = 0;
    virtual void SetParam(dword idx, bool value) = 0;
    virtual void SetParam(dword idx, double value) = 0;
    virtual void SetParam(dword idx, int * value) = 0;
    virtual void SetParam(dword idx, dword * value) = 0;
    virtual void SetParam(dword idx, long64 * value) = 0;
    virtual void SetParam(dword idx, ulong64 * value) = 0;
    virtual void SetParam(dword idx, double * value) = 0;
    virtual void SetParam(dword idx, bool * value) = 0;
    virtual void SetParam(dword idx, const char * value) = 0;
    virtual void SetParam(dword idx, const byte * buffer, size_t size) = 0;
};


class IDatabase {
public:
    virtual ~IDatabase() {}
    virtual void Connect(const char * address, const char * dbname, const char * user, const char * password) = 0;
    virtual bool Connected() = 0;
    virtual void Shutdown() = 0;
    virtual size_t QueryPrint(char * buffer, size_t bufferSize, const char * sqlcmd, ...) = 0;
    virtual size_t QueryPrintV(char * buffer, size_t bufferSize, const char * sqlcmd, va_list argList) = 0;
    virtual void ExecSQL(UDatabase * const user, dword flags, const char * sqlcmd, ...) = 0;
    virtual void ExecSQLV(UDatabase * const user, dword flags, const char * sqlcmd, va_list argList) = 0;
    virtual void InsertSQL(UDatabase * const user, const char * sqlcmd, ...) = 0;
    virtual void InsertSQLV(UDatabase * const user, const char * sqlcmd, va_list argList) = 0;
    virtual void BeginTransaction(UDatabase * const user, const char * lockTableCmd = NULL) = 0;
    virtual void EndTransaction(UDatabase * const user, bool doRollback = false) = 0;
    virtual void PrepareStatement(UDatabase * user, const char * sqlcmd) = 0;
    virtual void ExecSQL(UDatabase * const user, dword flags, class IPreparedStatement * const statement) = 0;
    virtual void InsertSQL(UDatabase * const user, class IPreparedStatement * const statement) = 0;
    virtual size_t EscapeSearchLiterals(const char * value, char * buffer, size_t bufferSize) = 0;
    virtual const char * GetLastErrorMessage() = 0;
};


class UDatabase {
public:
    virtual void DatabaseConnectComplete(IDatabase * const database) {};
    virtual void DatabaseShutdown(IDatabase * const database, db_error_t reason) {};
    virtual void DatabaseError(IDatabase * const database, db_error_t error) = 0;
    virtual void DatabaseExecSQLResult(IDatabase * const database, class IDataSet * dataset) {};
    virtual void DatabaseInsertSQLResult(IDatabase * const database, ulong64 id) {};
    virtual void DatabaseBeginTransactionResult(IDatabase * const database) {};
    virtual void DatabaseEndTransactionResult(IDatabase * const database) {};
    virtual void DatabasePrepareStatementResult(IDatabase * const database, class IPreparedStatement * statement) {};
};


class IDataSet {
public:
    virtual ~IDataSet() {}

    virtual size_t GetColumnCount() = 0;
    virtual bool Eot() = 0;
    virtual void Next() = 0;
    virtual void FetchNextRow() = 0;
    virtual bool IsSingleRowMode() = 0;
    virtual ulong64 GetAffectedRows() = 0;

    virtual const char * GetColumnName(int column) = 0;
    virtual int GetColumnID(const char * columnName) = 0;

    virtual bool ColumnIsNull(const char * columnName) = 0;
    virtual bool ColumnIsNull(int column) = 0;

    virtual int GetIntValue(const char * columnName) = 0;
    virtual dword GetUIntValue(const char * columnName) = 0;
    virtual long64 GetLong64Value(const char * columnName) = 0;
    virtual ulong64 GetULong64Value(const char * columnName) = 0;
    virtual bool GetBoolValue(const char * columnName) = 0;
    virtual double GetDoubleValue(const char * columnName) = 0;
    virtual const char * GetStringValue(const char * columnName) = 0;
    virtual const char * GetStringValueWithNull(const char * columnName) = 0;
    virtual size_t GetDataSize(const char * columnName) = 0;
    virtual const byte * GetDataValue(const char * columnName) = 0;

    virtual int GetIntValue(int column) = 0;
    virtual dword GetUIntValue(int column) = 0;
    virtual long64 GetLong64Value(int column) = 0;
    virtual ulong64 GetULong64Value(int column) = 0;
    virtual bool GetBoolValue(int column) = 0;
    virtual double GetDoubleValue(int column) = 0;
    virtual const char * GetStringValue(int column) = 0;
    virtual const char * GetStringValueWithNull(int column) = 0;
    virtual size_t GetDataSize(int column) = 0;
    virtual const byte * GetDataValue(int column) = 0;
};


extern IDatabaseProvider * CreatePostgreSQLDatabaseProvider();
extern IDatabaseProvider * CreateMySQLDatabaseProvider();
