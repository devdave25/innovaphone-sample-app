/*---------------------------------------------------------------------------*/
/* xml.h                                                                     */
/* copyright (c) innovaphone 2001                                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/

NAMESPACE_BEGIN

#define XML_TYPE_TAG            0
#define XML_TYPE_ATTRIB         1
#define XML_TYPE_ATTRIB_VALUE   2
#define XML_TYPE_CONTENT        3
#define XML_TYPE_CONTENT_PACKET 4
#define XML_TYPE_HREF           5
#define XML_TYPE_ANY            0xff

#define XML_FLAG_COMPLETE       1

#define XML_ROOT_TAG            0xffff
#define XML_NO_TAG              0xffff

#define XML_MAX_TAG             4094
#define XML_MAX_ID              32

struct xml_id_content {
    char * id;
    word handle;
};

#define XML_ERROR_INCOMPLETE    1
#define XML_ERROR_FATAL         2

class xml_io {
    byte error;
    char * buffer;
    char * last;
    char * eod;
    word index;
    byte state;
    word base;
    const char * namespc;

    struct {
        word count;
        byte type;
        byte href;
        word base;
        byte flags;
        byte spare;
        const char * info;
    } content[XML_MAX_TAG];

    char * current_id;
    word current_id_tag;
    struct xml_id_content * id_list;
    struct xml_id_content * href_list;
    word id_count;
    word href_count;
    char * encoding;

    bool keep_whitespaces;

    bool whitespace(char c) {
        return c==' ' || c=='\r' || c=='\n' || c=='\t';
    }
    bool is_tagstart(const char * p);
    bool find_id(word handle, const char * href);
    bool find_href(const char * id, word handle);

    int nextindex(int i) { return content[i].type==XML_TYPE_TAG? (i+content[i].count+1):(i+1); };

public:
    xml_io(char * buffer, bool keep_whitespaces=false);
    void init();
    void reset() { index=0; error=false; };

    void setnamespace(const char *name) {namespc=name; };
    void set_buffer(char * buffer) { this->buffer = buffer; };
    char * get_encoding() { return encoding; };
    word get_index() { return index; };

    byte read();
    void read(char * & p);
    void read_start(char * & p);
    void read_tag_start(char * & p);
    void read_tag_end(char * & p);
    void read_attrib_name(char * & p);
    void read_attrib_value(char * & p);
    void read_content(char * & p);

    bool save(char * buffer, int sz, int & len, byte & state, word & base);
    void restore(byte state, word base);
    void save(class packet * & save_xml_io, class packet * & save_buffer);
    void restore(class packet * & save_xml_io, class packet * & save_buffer);
    void save(char * & save_xml_io, unsigned & xml_len, char * & save_buffer, unsigned & buffer_len);
    void restore(char * & save_xml_io, unsigned xml_len, char * & save_buffer, unsigned buffer_len);

    void save_incomplete(word root, word base,xml_io & to);
    void copy_out(word base, class xml_io & to, word & to_base, char * & to_p);
    void copy_in(word base, class xml_io & to, word to_base, char * & to_p);
    int ofs() { return (int)(eod-buffer); };

    bool read_tag(char * & p);
    bool decode(bool href = false, word * decoded =  0);
    char * info(word handle) { return (char *) content[handle].info; };
    word count(word handle) { return content[handle].count; };
    byte type(word handle) { return content[handle].type; };
    bool complete(word handle) { return (content[handle].flags &XML_FLAG_COMPLETE)!=0; };
    word get_first(byte type, word base);
    word get_next(byte type, word base, word last);
    bool get_xpath(word base, char * xpath, word * handle, char ** attrib);

    word get_attrib_handle(word base, const char * name);
    word del_attrib(word base, const char * name);
    char * get_attrib(word base, const char * name);
    char * get_attrib(word base, const char * name, word & length);
#if !defined(PLATFORM_NO_IPADDR)
    IPaddr get_attrib_ip(word base, const char * name, bool * present=0);
    IPaddr get_attrib_ip6(word base, const char * name, bool * present=0);
    IPaddr_prefix get_attrib_ip6_net(word base, const char * name, bool * present=0);
    Eaddr get_attrib_eaddr(word base, const char * name, bool * present=0);
#endif
    int get_attrib_int(word base, const char * name, bool * present=0);
    unsigned get_attrib_unsigned(word base, const char * name, bool * present=0);
    int get_attrib_hex(word base, const char * name, bool * present=0);
    int get_attrib_dec(word base, const char * name, bool * present=0);
    bool get_attrib_bool(word base, const char * name);

    word get_tag(word base, const char * name, const char * ns=0);
    word get_next_tag(word base, const char * name, word last, const char * ns=0);

    word get_content(word base) { return get_first(XML_TYPE_CONTENT,base); }

    word encode();
#if !defined(PLATFORM_NO_PACKET)
    class packet * encode_to_packet(class packet * data=0);
#endif
    void write_tag(word current, char * & p);
    class packet * write_tag_to_packet(word current, class packet * data);
    virtual word add(byte type, word base, const char * s, word len=0xffff);
    virtual void set_complete(word base) {
        content[base].flags = XML_FLAG_COMPLETE;
    }
    virtual word get_base(word base) {
        return content[base].base;
    }
    word add_tag(word base, const char * s);
    void add_attrib(word base, const char * name, const char * value, word len=0xffff);
#if !defined(PLATFORM_NO_IPADDR)
    void add_attrib_ip4(word base, const char * name, IP4addr addr, char * & tmp);
    void add_attrib_ip(word base, const char * name, const IPaddr & a, char * & tmp);
    void add_attrib_ip(word base, const char * name, const IPaddr_prefix & a, char * & tmp);
#endif
    void add_attrib_int(word base, const char * name, int c, char * & tmp);
    void add_attrib_unsigned(word base, const char * name, dword c, char * & tmp);
    void add_attrib_hex(word base, const char * name, int c, char * & tmp);
    void add_attrib_hexstring(word base, const char * name, const byte * hex, word hex_len, char * & tmp);
    void add_attrib_url(word base, const char * name, const char * value, char * & tmp);
#if !defined(PLATFORM_NO_IPADDR)
    void add_attrib_id(word base, const char * name, ulong64 id, char * & tmp);
#endif
    void add_attrib_bool(word base, const char * name, bool value);
#if !defined(PLATFORM_NO_IPADDR)
    void add_attrib_unicode(word base, const char * name, word * n, word len, char * & tmp);
#endif
    void add_attrib_printf(word base, const char * name, char * & tmp, const char * format, ...);
    void add_content(word base, const char * s, word len=0xffff);
#if !defined(PLATFORM_NO_PACKET)
    void add_content(word base, class packet * data);
#endif
    void change_info(word handle, char * info);
#if !defined(PLATFORM_NO_DEBUG)
    void dump();
#endif

    static class packet * str_to_xml_packet(class packet * data, const char * buffer, word length);
    static class packet * latin1_to_xml_packet(class packet * data, const char * buffer, word length);
    static word str_to_xml(const char * buffer, word length, char * out);
    static word latin1_to_xml(const char * buffer, word length, char * out, bool latin1);
    static word unicode_to_xml(const word * buffer, word length, char * out);
    static word xml_packet_to_str(char * buffer, class packet * data);
    static word xml_packet_to_latin1(char * buffer, class packet * data);
    static word xml_to_str(char * buffer, const char * in, word in_len = 65535);
    static word xml_to_latin1(char * buffer, const char * in, bool latin1);
    static class packet * str_packet_to_xml_packet(class packet * data);
    static class packet * latin1_packet_to_xml_packet(class packet * data);
    static int wellformed(const char * xml, unsigned maxlen);
};

NAMESPACE_END

