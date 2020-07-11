
/*---------------------------------------------------------------------------*/
/* config.h                                                                  */
/* copyright (c) innovaphone 2017 - 2019                                     */
/*                                                                           */
/*---------------------------------------------------------------------------*/

#define CFG_TYPE_CHOICE     "CHOICE"
#define CFG_TYPE_BOOL       "BOOL"
#define CFG_TYPE_INT        "INT"
#define CFG_TYPE_DWORD      "DWORD"
#define CFG_TYPE_LONG64     "LONG64"
#define CFG_TYPE_ULONG64    "ULONG64"
#define CFG_TYPE_STRING     "STRING"

class UConfigContextApi {
public:
    virtual ~UConfigContextApi() {}
    virtual void SendConfig(class IJsonApiConnection * connection, const char * mt, const char * src) = 0;
    virtual void UpdateConfig(class IJsonApiConnection * connection, class json_io * json, dword base, const char * src) = 0;
    virtual void SendConfigItems(class IJsonApiConnection * connection, const char * src) = 0;
};


class ConfigApiContext : public istd::listElement<ConfigApiContext>, public JsonApi {
private:
    IJsonApiConnection * const connection;
    UConfigContextApi * const user;
    IInstanceLog * const log;

public:
    ConfigApiContext(IJsonApiConnection * connection, UConfigContextApi * user, IInstanceLog * const log);
    ~ConfigApiContext();

    const char * Name() override;
    IJsonApiConnection * GetConnection();
    void Message(class json_io & msg, word base, const char * mt, const char * src) override;
    void JsonApiConnectionClosed() override;
    char * readSrc;
};


class ConfigContext : public UTask, public UJsonApiContext, public UConfigContextApi {
private:
    friend class ConfigItem;
    friend class TaskWriteConfigItems;
    friend class TaskWriteValue;

    class IDatabase * database;
    class IInstanceLog * const log;

    class istd::list<class ConfigItem> items;
    class istd::list<class ConfigApiContext> apiContextList;

    class ITask * CreateUpdateConfigTask(class json_io * json, dword base);
    void TaskComplete(class ITask * const task) override;
    void TaskFailed(class ITask * const task) override;

    void RegisterConfigItem(class ConfigItem * item);

    void SendWriteConfigResult(class IJsonApiConnection * connection, const char * src, const char * result);
    void SendConfig(class IJsonApiConnection * connection, const char * mt, const char * src) override;
    void UpdateConfig(class IJsonApiConnection * connection, class json_io * json, dword base, const char * src) override;
    void SendConfigItems(class IJsonApiConnection * connection, const char * src) override;

    class JsonApi * CreateJsonApi(class IJsonApiConnection * connection, class json_io & msg, word base) override { return 0; };
    class JsonApi * JsonApiRequested(class IJsonApiConnection * connection) override;
    const char * Name() override { return "Config"; }

protected:
    virtual void ConfigChanged() {}
    virtual void ConfigChangedUnmanaged() {}
    virtual bool CanReadConfig(IJsonApiConnection * const connection) { return true; }
    virtual bool CanWriteConfig(IJsonApiConnection * const connection) { return true; }
    class ITask * UpdateUnmanagedItems();
    class ITask * UpdateManagedItems();

public:
    ConfigContext(class IDatabase * database, class IInstanceLog * log);
    virtual ~ConfigContext();

    class ITask * CreateInitTask(class IDatabase * database = 0);
    void ResetChangedFlag();
    class ITask * WriteItemValue(ConfigItem * item, const char * value, bool notify);
};


class ConfigItem : public istd::listElement<ConfigItem> {
private:
    char * name;

protected:
    friend class TaskWriteConfig;
    friend class TaskWriteConfigItems;
    friend class TaskInitConfig;
    friend class ConfigContext;

    class IInstanceLog * const log;
    bool changed;
    bool unmanaged;

    virtual void ReadValueFromDataset(class IDataSet * dataset) = 0;
    virtual void ReadValueFromJSON(class json_io * json, dword base, class IJsonApiConnection * connection) = 0;
    virtual void WriteValueToJSON(class json_io * json, dword base, char * & convBuf, class IJsonApiConnection * connection) = 0;
    virtual int WriteValueToString(char * dest) = 0;
    virtual void SetWriteValue(const char * value) = 0;
    virtual void WriteItemTypeToJSON(class json_io * json, dword base, char * & convBuf) = 0;

public:
    ConfigItem(ConfigContext * context, const char * name, bool unmanaged);
    virtual ~ConfigItem();

    const char * GetName() const { return this->name; }
    bool Changed() const { return this->changed; }
    virtual bool HasDefaultValue() const = 0;
    virtual void Reset() = 0;
};


class ConfigChoice : public ConfigItem {
private:
    size_t optionsCount;
    size_t defValueIdx;
    size_t valueIdx;
    const char ** choiceValues;

protected:
    friend class ConfigContext;
    virtual void SetWriteValue(const char * value);
    virtual void ReadValueFromDataset(class IDataSet * dataset) override;
    virtual void ReadValueFromJSON(class json_io * json, dword base, class IJsonApiConnection * connection) override;
    virtual void WriteValueToJSON(class json_io * json, dword base, char * & convBuf, class IJsonApiConnection * connection) override;
    virtual int WriteValueToString(char * dest) override;
    virtual void WriteItemTypeToJSON(class json_io * json, dword base, char * & convBuf) override;

public:
    ConfigChoice(ConfigContext * context, const char * name, size_t defVal, const char ** options, bool unmanaged = false);
    virtual ~ConfigChoice();

    int ValueIdx() const { return (int)this->valueIdx; }
    const char * Value() const { return (this->valueIdx < this->optionsCount ? this->choiceValues[this->valueIdx] : NULL); }
    void SetValue(const char * option);
    void SetValueIdx(size_t valudIdx);
    bool HasDefaultValue() const override;
    void Reset() override;
};


class ConfigBool : public ConfigItem {
private:
    bool defValue;
    bool value;

protected:
    friend class ConfigContext;
    virtual void SetWriteValue(const char * value);
    virtual void ReadValueFromDataset(class IDataSet * dataset) override;
    virtual void ReadValueFromJSON(class json_io * json, dword base, class IJsonApiConnection * connection) override;
    virtual void WriteValueToJSON(class json_io * json, dword base, char * & convBuf, class IJsonApiConnection * connection) override;
    virtual int WriteValueToString(char * dest) override;
    virtual void WriteItemTypeToJSON(class json_io * json, dword base, char * & convBuf) override;

public:
    ConfigBool(ConfigContext * context, const char * name, bool defVal, bool unmanaged = false);
    virtual ~ConfigBool();

    bool Value() const { return this->value; }
    void SetValue(bool value);
    bool HasDefaultValue() const override;
    void Reset() override;
};


class ConfigInt: public ConfigItem {
private:
    int defValue;
    int value;
    int minVal;
    int maxVal;

protected:
    friend class ConfigContext;
    virtual void SetWriteValue(const char * value);
    virtual void ReadValueFromDataset(class IDataSet * dataset) override;
    virtual void ReadValueFromJSON(class json_io * json, dword base, class IJsonApiConnection * connection) override;
    virtual void WriteValueToJSON(class json_io * json, dword base, char * & convBuf, class IJsonApiConnection * connection) override;
    virtual int WriteValueToString(char * dest) override;
    virtual void WriteItemTypeToJSON(class json_io * json, dword base, char * & convBuf) override;

public:
    ConfigInt(ConfigContext * context, const char * name, int defVal, bool unmanaged = false, int minVal = INT32_MIN, int maxVal = INT32_MAX);
    virtual ~ConfigInt();

    int Value() const { return this->value; }
    void SetValue(int value);
    bool HasDefaultValue() const  override;
    void Reset() override;
};


class ConfigDword : public ConfigItem {
private:
    dword defValue;
    dword value;
    dword minVal;
    dword maxVal;

protected:
    friend class ConfigContext;
    virtual void SetWriteValue(const char * value);
    virtual void ReadValueFromDataset(class IDataSet * dataset) override;
    virtual void ReadValueFromJSON(class json_io * json, dword base, class IJsonApiConnection * connection) override;
    virtual void WriteValueToJSON(class json_io * json, dword base, char * & convBuf, class IJsonApiConnection * connection) override;
    virtual int WriteValueToString(char * dest) override;
    virtual void WriteItemTypeToJSON(class json_io * json, dword base, char * & convBuf) override;

public:
    ConfigDword(ConfigContext * context, const char * name, dword defVal, bool unmanaged = false, dword minVal = 0, dword maxVal = UINT32_MAX);
    virtual ~ConfigDword();

    dword Value() const { return this->value; }
    void SetValue(dword value);
    bool HasDefaultValue() const override;
    void Reset() override;
};


class ConfigLong64 : public ConfigItem {
private:
    long64 defValue;
    long64 value;
    long64 minVal;
    long64 maxVal;

protected:
    friend class ConfigContext;
    virtual void SetWriteValue(const char * value);
    virtual void ReadValueFromDataset(class IDataSet * dataset) override;
    virtual void ReadValueFromJSON(class json_io * json, dword base, class IJsonApiConnection * connection) override;
    virtual void WriteValueToJSON(class json_io * json, dword base, char * & convBuf, class IJsonApiConnection * connection) override;
    virtual int WriteValueToString(char * dest) override;
    virtual void WriteItemTypeToJSON(class json_io * json, dword base, char * & convBuf) override;

public:
    ConfigLong64(ConfigContext * context, const char * name, long64 defVal, bool unmanaged = false, long64 minVal = INT64_MIN, long64 maxVal = INT64_MAX);
    virtual ~ConfigLong64();

    long64 Value() const { return this->value; }
    void SetValue(long64 value);
    bool HasDefaultValue() const override;
    void Reset() override;
};


class ConfigUlong64 : public ConfigItem {
private:
    ulong64 defValue;
    ulong64 value;
    ulong64 minVal;
    ulong64 maxVal;

protected:
    friend class ConfigContext;
    virtual void SetWriteValue(const char * value);
    virtual void ReadValueFromDataset(class IDataSet * dataset) override;
    virtual void ReadValueFromJSON(class json_io * json, dword base, class IJsonApiConnection * connection) override;
    virtual void WriteValueToJSON(class json_io * json, dword base, char * & convBuf, class IJsonApiConnection * connection) override;
    virtual int WriteValueToString(char * dest) override;
    virtual void WriteItemTypeToJSON(class json_io * json, dword base, char * & convBuf) override;

public:
    ConfigUlong64(ConfigContext * context, const char * name, ulong64 defVal, bool unmanaged = false, ulong64 minVal = 0, ulong64 maxVal = UINT64_MAX);
    virtual ~ConfigUlong64();

    ulong64 Value() const { return this->value; }
    void SetValue(ulong64 value);
    bool HasDefaultValue() const override;
    void Reset() override;
};


class ConfigString : public ConfigItem {
private:
    const char * defValue;
    char * value;
    bool isPassword;

    static const char * CryptKey();
    
protected:
    friend class ConfigContext;
    virtual void SetWriteValue(const char * value);
    virtual void ReadValueFromDataset(class IDataSet * dataset) override;
    virtual void ReadValueFromJSON(class json_io * json, dword base, class IJsonApiConnection * connection) override;
    virtual void WriteValueToJSON(class json_io * json, dword base, char * & convBuf, class IJsonApiConnection * connection) override;
    virtual int WriteValueToString(char * dest) override;
    virtual void WriteItemTypeToJSON(class json_io * json, dword base, char * & convBuf) override;

public:
    ConfigString(ConfigContext * context, const char * name, const char * defVal, bool unmanaged = false, bool isPassword = false);
    virtual ~ConfigString();

    const char * Value() const { return this->value; }
    void SetValue(const char * value);
    bool HasDefaultValue() const override;
    void Reset() override;
    static void Encrypt(const char * seed, const char * password, char * out, size_t len);
    static void Decrypt(const char * seed, const char * password, char * out, size_t len);
};
