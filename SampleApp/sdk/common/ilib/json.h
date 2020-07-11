/*---------------------------------------------------------------------------*/
/* json.h                                                                    */
/* copyright (c) innovaphone 2013 - 2017                                     */
/*                                                                           */
/*---------------------------------------------------------------------------*/

NAMESPACE_BEGIN

#define JSON_MAX_ITEM               3072

#define JSON_TYPE_OBJECT            0
#define JSON_TYPE_ARRAY             1
#define JSON_TYPE_VALUE             2
#define JSON_TYPE_CONTENT_PACKET    3
#define JSON_TYPE_ANY               0xff

#define JSON_FLAG_QUOTED            1
#define JSON_FLAG_INCOMPLETE        2

#define JSON_ID_ROOT                0xffff
#define JSON_ID_NONE                0xffff

class json_io {
    friend class test_json;

    char * buffer;
    word index;
    word base;
    
    struct {
        word count;
        byte type;
        byte flags;
        word base;
        word spare;
        const char * name;
        const char * info;
    } content[JSON_MAX_ITEM];

    bool read(char * & p);
    bool read(char * & p, word base, const char * name=0);

    word add(byte type, byte flags, word base, const char * name, const char * info, word len=0xffff);
    
    word nextindex(word i);
    word get_first(byte type, word base);
    word get_next(byte type, word base, word last);
    word get_type(word handle) { return content[handle].type; };

    const char * get_value(word base, byte flags, const char * name);
    const char * get_value(word base, byte flags, word & last);
    word get_id(word base, byte flags, const char * name);

    static word escape(const char * in, word length, char * out);
    static word unescape(char * out, const char * in);
    static bool whitespace(char c);
    static bool unquoted(char c);
    static char skip_whitespace(char * & p);
    static bool skip(char * & p, char skip);

public:
    json_io(char * buffer);
    
    void reset();
    bool decode();
    word encode();
    word encode(word handle, char * buffer) { char * p = buffer;  write(handle, p); return (word)(p - buffer); };
    class packet * encode_to_packet(class packet * data=0);
    void write(word current, char * & p, word incomplete = 0xffff);
    class packet * write_to_packet(word current, word & count, class packet * data);
    void dump();
    word to_url(word base, char * b, word l, const char * prefix = 0, bool cont = false);
    word get_index() { return index; };

    const char * get_name(word handle) { return content[handle].name; };
    const char * get_info(word handle) { return content[handle].info; };

    void add_json_data(word base, class packet * data, const char * name=0);
    
    word add_object(word base, const char * name);
    word add_array(word base, const char * name);
    void add_string(word base, const char * name, const char * value, word len=0xffff);
    void add_string(word base, const char * name, const word * value, word len=0xffff);
    void add_replace_string(word base, const char * name, const char * value, word len=0xffff);
    void add_json(word base, const char * name, const char * value, word len=0xffff);
    void add_int(word base, const char * name, int c, char * & tmp);
    void add_unsigned(word base, const char * name, dword c, char * & tmp);
    void add_long64(word base, const char * name, long64 c, char * & tmp);
    void add_ulong64(word base, const char * name, ulong64 c, char * & tmp);
#if !defined(PLATFORM_NO_IPADDR)
    void add_ip(word base, const char * name, const IPaddr & a, char * & tmp);
    void add_guid(word base, const char * name, OS_GUID * guid, char * & tmp);
#endif
    void add_printf(word base, const char * name, char * & tmp, const char * format, ...);
    void add_hexstring(word base, const char * name, const byte * hex, word hex_len, char * & tmp);
    void add_bool(word base, const char * name, bool value);
    void add_null(word base, const char * name);
 
    word get_object(word base, const char * name);
    word get_object(word base, word & last);
    word get_array(word base, const char * name);
    word get_array(word base, word & last);
    word get_next(word base, word last, byte & type, byte & flags, const char * & name, const char * & info);
    const char * get_string(word base, const char * name);
    const char * get_string(word base, word & last);
    int get_int(word base, const char * name, bool * present=0);
    int get_int(word base, word & last, bool * present=0);
    dword get_unsigned(word base, const char * name, bool * present=0);
    dword get_unsigned(word base, word & last, bool * present=0);
    long64 get_long64(word base, const char * name, bool * present = 0);
    long64 get_long64(word base, word & last, bool * present = 0);
    ulong64 get_ulong64(word base, const char * name, bool * present = 0);
    ulong64 get_ulong64(word base, word & last, bool * present = 0);
#if !defined(PLATFORM_NO_IPADDR)
    IPaddr get_ip(word base, const char * name, bool * present=0);
    IPaddr get_ip(word base, word & last, bool * present=0);
    OS_GUID get_guid(word base, const char * name, bool * present = 0);
#endif
    bool get_bool(word base, const char * name, bool * present=0);
    bool get_bool(word base, word & last, bool * present=0);
    bool get_bool_int(word base, const char * name, int & iret, byte * present=0);
    char * last;
    char * name_last;
    char * incomplete;
};

NAMESPACE_END
