/*---------------------------------------------------------------------------*/
/* tasks_postgresql.h                                                        */
/* copyright (c) innovaphone 2016                                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/

class PostgreSQLTableColumn {
public:
    PostgreSQLTableColumn(const char * name, const char * type);
    ~PostgreSQLTableColumn();
    char * name;
    char * type;
    bool exists;
};

class PostgreSQLTableConstraint {
public:
    PostgreSQLTableConstraint(const char * name, const char * value);
    ~PostgreSQLTableConstraint();
    char * name;
    char * value;
    bool exists;
};

class PostgreSQLTableIndex {
public:
    PostgreSQLTableIndex(const char * name, const char * value, bool unique);
    ~PostgreSQLTableIndex();
    char * name;
    char * value;
    bool unique;
    bool exists;
};


class TaskPostgreSQLInitTable : public ITask, public UDatabase {
private:
    char * tableName;
    class IDatabase * database;
    dword constraintCount;
    dword indexCount;
    enum { Idle, CreateTable, GetColumns, AddMissingColumns, GetConstraints, AddMissingConstraints, GetIndexes, AddMissingIndexes, Finished } state;
    std::deque<class PostgreSQLTableColumn *> columns;
    std::deque<class PostgreSQLTableConstraint *> constraints;
    std::deque<class PostgreSQLTableIndex *> indexes;

    void DatabaseExecSQLResult(IDatabase * const database, class IDataSet * dataset) override;
    void DatabaseError(IDatabase * const database, db_error_t error) override;
    
    void GetConstraintsQuery();
    void GetIndexesQuery();

public:
    TaskPostgreSQLInitTable(class IDatabase * database, const char * tableName);
    virtual ~TaskPostgreSQLInitTable();

    void AddColumn(const char * name, const char * type);
    void AddConstraint(const char * name, const char * value);
    void AddIndex(const char * name, const char * value, bool unique);

    void Start(class UTask * user) override;
};


class TaskPostgreSQLInitEnum : public ITask, public UDatabase {
private:
    char * enumName;
    int sqlCmdCnt;
    class IDatabase * database;
    enum { Idle, GetEnum, CreateEnumType, GetEnumValues, AddEnumItem, Finished } state;
    std::deque<char *> enumValues;

    void DatabaseError(IDatabase * const database, db_error_t error) override;
    void DatabaseExecSQLResult(IDatabase * const database, class IDataSet * dataset) override;

    void CreateEnum();
    void UpdateEnum(IDataSet * dataset);

public:
    TaskPostgreSQLInitEnum(IDatabase * const database, const char * enumName);
    virtual ~TaskPostgreSQLInitEnum();

    void AddValue(const char * name);
    void Start(class UTask * user) override;
};
