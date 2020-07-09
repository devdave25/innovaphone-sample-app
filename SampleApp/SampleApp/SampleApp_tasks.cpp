
/*-----------------------------------------------------------------------------------------------*/
/* Based on innovaphone App template                                                             */
/* copyright (c) innovaphone 2018                                                                */
/*                                                                                               */
/*-----------------------------------------------------------------------------------------------*/

#include "platform/platform.h"
#include "common/interface/database.h"
#include "common/interface/task.h"
#include "common/lib/tasks_postgresql.h"
#include "common/lib/database_switch.h"
#include "SampleApp_tasks.h"

TaskDatabaseInit::TaskDatabaseInit(IDatabase * database)
	: initUsers(database, "users"),
      initCounter(database, "counter")
{
    // users
    initUsers.AddColumn("id", "BIGSERIAL PRIMARY KEY NOT NULL");
    initUsers.AddColumn("guid", "UUID UNIQUE");
    initUsers.AddColumn("sip", "VARCHAR(256) UNIQUE NOT NULL");
    initUsers.AddColumn("dn", "VARCHAR(256)");
    initUsers.AddColumn("count", "BIGINT");
    // counter
    initCounter.AddColumn("id", "BIGSERIAL PRIMARY KEY NOT NULL");
    initCounter.AddColumn("name", "VARCHAR(32) UNIQUE NOT NULL");
    initCounter.AddColumn("value", "BIGINT");
}

TaskDatabaseInit::~TaskDatabaseInit()
{
}

void TaskDatabaseInit::Start(class UTask * user)
{
    this->user = user;
    initUsers.Start(this);
}

void TaskDatabaseInit::TaskComplete(class ITask * const task)
{
    if (task == &initUsers) initCounter.Start(this);
    else if (task == &initCounter) Complete();
    else ASSERT(false, "TaskDatabaseInit::TaskComplete");
}

void TaskDatabaseInit::TaskFailed(class ITask * const task)
{
    Failed();
}

/*-----------------------------------------------------------------------------------------------*/
/* TaskReadWriteCount                                                                            */
/*-----------------------------------------------------------------------------------------------*/

TaskReadWriteCount::TaskReadWriteCount(IDatabase * database, const char * sip, const char * dn, long64 count, bool update)
{
    this->database = database;
    this->sip = _strdup(sip);
    this->dn = _strdup(dn);
    this->count = count;
    this->update = update;

    id = 0;
}

TaskReadWriteCount::~TaskReadWriteCount()
{
    if (sip) free((void *)sip);
    if (dn) free((void *)dn);
}

void TaskReadWriteCount::Start(class UTask * user)
{
    this->user = user;
    if (update) {
        database->InsertSQL(this, "INSERT INTO counter (name, value) VALUES ('user', %llu) ON CONFLICT (name) DO UPDATE SET value=EXCLUDED.value", count);
    }
    else if (count < 0) {
        database->ExecSQL(this, DB_EXEC_FETCH_ALL, "SELECT value FROM counter WHERE name='user'");
    }
    else {
        WriteCount();
    }
}

void TaskReadWriteCount::DatabaseExecSQLResult(IDatabase * const database, class IDataSet * dataset)
{
    count = !dataset->Eot() ? dataset->GetULong64Value(dataset->GetColumnID("value")) : 0;
    delete dataset;

    WriteCount();
}

void TaskReadWriteCount::WriteCount()
{
    if (sip && dn) database->InsertSQL(this, "INSERT INTO users (sip, dn, count) VALUES (%s, %s, %llu) ON CONFLICT (sip) DO UPDATE SET dn=EXCLUDED.dn, count=EXCLUDED.count", sip, dn, count);
    else Complete();
}

void TaskReadWriteCount::DatabaseInsertSQLResult(IDatabase * const database, ulong64 id)
{
    if (update) {
        update = false;
        WriteCount();
    }
    else {
        this->id = id;
        Complete();
    }
}

void TaskReadWriteCount::DatabaseError(IDatabase * const database, db_error_t error)
{
    Failed();
}

/*-----------------------------------------------------------------------------------------------*/
/* TaskReadUserCount                                                                             */
/*-----------------------------------------------------------------------------------------------*/

TaskReadUserCount::TaskReadUserCount(IDatabase * database, const char * sip)
{
    this->database = database;
    this->sip = _strdup(sip);
    count = 0;
}

TaskReadUserCount::~TaskReadUserCount()
{
    if (sip) free((void *)sip);
}

void TaskReadUserCount::Start(class UTask * user)
{
    this->user = user;
    database->ExecSQL(this, DB_EXEC_FETCH_ALL, "SELECT count FROM users WHERE sip=%s", sip);
}

void TaskReadUserCount::DatabaseExecSQLResult(IDatabase * const database, class IDataSet * dataset)
{
    if (!dataset->Eot()) count = dataset->GetULong64Value(dataset->GetColumnID("count"));
    delete dataset;
    Complete();
}

void TaskReadUserCount::DatabaseError(IDatabase * const database, db_error_t error)
{
    Failed();
}
