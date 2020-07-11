
typedef std::deque<class UDatabase *> UserQueue;

class DatabaseSwitch : public IDatabase, public UDatabase {
    UserQueue users;
    class DataSetSwitch * dataSet;

    // Udatabase definitions
    void DatabaseConnectComplete(IDatabase * const database) override;
    void DatabaseError(IDatabase * const database, db_error_t error) override;
    void DatabaseShutdown(IDatabase * const database, db_error_t error) override;
    void DatabaseExecSQLResult(IDatabase * const database, class IDataSet * dataset) override;
    void DatabaseInsertSQLResult(IDatabase * const database, ulong64 id) override;
    void DatabaseBeginTransactionResult(IDatabase * const database) override;
    void DatabaseEndTransactionResult(IDatabase * const database) override;
    void DatabasePrepareStatementResult(IDatabase * const database, class IPreparedStatement * statement) override;

protected:
    class IDatabase * database;

public:
    DatabaseSwitch(class IDatabase * database);
    virtual ~DatabaseSwitch();
    IDatabase * GetDatabase();

    // IDatabase definitions
    void Connect(const char * address, const char * dbname, const char * user, const char * password) override;
    bool Connected() override;
    void Shutdown() override;
    size_t QueryPrint(char * buffer, size_t bufferSize, const char * sqlcmd, ...) override;
    size_t QueryPrintV(char * buffer, size_t bufferSize, const char * sqlcmd, va_list argList) override;
    void ExecSQL(UDatabase * const user, dword flags, const char * sqlcmd, ...) override;
    void ExecSQLV(UDatabase * const user, dword flags, const char * sqlcmd, va_list argList) override;
    void InsertSQL(UDatabase * const user, const char * sqlcmd, ...) override;
    void InsertSQLV(UDatabase * const user, const char * sqlcmd, va_list argList) override;
    void BeginTransaction(UDatabase * const user, const char * lockTableCmd = NULL) override;
    void EndTransaction(UDatabase * const user, bool doRollback = false) override;
    void PrepareStatement(UDatabase * user, const char * sqlcmd) override;
    void ExecSQL(UDatabase * const user, dword flags, class IPreparedStatement * const statement) override;
    void InsertSQL(UDatabase * const user, class IPreparedStatement * const statement) override;
    size_t EscapeSearchLiterals(const char * value, char * buffer, size_t bufferSize) override;
    const char * GetLastErrorMessage() override;
    void DataSetDeleted();
};

class DataSetSwitch : public IDataSet {
    class IDataSet * dataSet;
    class DatabaseSwitch * databaseSwitch;

public:
    DataSetSwitch(class IDataSet * dataSet, class DatabaseSwitch * databaseSwitch)
    {
        this->dataSet = dataSet;
        this->databaseSwitch = databaseSwitch;
    }

    ~DataSetSwitch()
    {
        delete this->dataSet;
        this->databaseSwitch->DataSetDeleted();
    }

    size_t GetColumnCount() override { return dataSet->GetColumnCount(); }
    bool Eot() override { return dataSet->Eot(); }
    void Next() override { return dataSet->Next(); }
    void FetchNextRow() override { return dataSet->FetchNextRow(); }
    bool IsSingleRowMode() override { return dataSet->IsSingleRowMode(); }
    ulong64 GetAffectedRows() override { return dataSet->GetAffectedRows(); }

    const char * GetColumnName(int column) override { return dataSet->GetColumnName(column); }
    int GetColumnID(const char * columnName) override { return dataSet->GetColumnID(columnName); }

    bool ColumnIsNull(const char * columnName) override { return dataSet->ColumnIsNull(columnName); }
    bool ColumnIsNull(int column) override { return dataSet->ColumnIsNull(column); }

    int GetIntValue(const char * columnName) override { return dataSet->GetIntValue(columnName); }
    dword GetUIntValue(const char * columnName) override { return dataSet->GetUIntValue(columnName); }
    long64 GetLong64Value(const char * columnName) override { return dataSet->GetLong64Value(columnName); }
    ulong64 GetULong64Value(const char * columnName) override { return dataSet->GetULong64Value(columnName); }
    bool GetBoolValue(const char * columnName) override { return dataSet->GetBoolValue(columnName); }
    double GetDoubleValue(const char * columnName) override { return dataSet->GetDoubleValue(columnName); }
    const char * GetStringValue(const char * columnName) override { return dataSet->GetStringValue(columnName); }
    const char * GetStringValueWithNull(const char * columnName) override { return dataSet->GetStringValueWithNull(columnName); }
    size_t GetDataSize(const char * columnName) override { return dataSet->GetDataSize(columnName); }
    const byte * GetDataValue(const char * columnName) override { return dataSet->GetDataValue(columnName); }

    int GetIntValue(int column) override { return dataSet->GetIntValue(column); }
    dword GetUIntValue(int column) override { return dataSet->GetUIntValue(column); }
    long64 GetLong64Value(int column) override { return dataSet->GetLong64Value(column); }
    ulong64 GetULong64Value(int column) override { return dataSet->GetULong64Value(column); }
    bool GetBoolValue(int column) override { return dataSet->GetBoolValue(column); }
    double GetDoubleValue(int column) override { return dataSet->GetDoubleValue(column); }
    const char * GetStringValue(int column) override { return dataSet->GetStringValue(column); }
    const char * GetStringValueWithNull(int column) override { return dataSet->GetStringValueWithNull(column); }
    size_t GetDataSize(int column) override { return dataSet->GetDataSize(column); }
    const byte * GetDataValue(int column) override { return dataSet->GetDataValue(column); }
};
