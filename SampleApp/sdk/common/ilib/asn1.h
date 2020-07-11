/*---------------------------------------------------------------------------*/
/* asn1.h                                                                    */
/* copyright (c) innovaphone 1997, 1998, 2007                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/

NAMESPACE_BEGIN

#define ASN1_EXTENSION      1
#define ASN1_OPTIONAL       2
#define ASN1_DEFAULT        4

#define ASN1_EXTENDED       0x10000

#define ASN1_TAG_UNIVERSAL      0x0000
#define ASN1_TAG_APPLICATION    0x4000
#define ASN1_TAG_CONTEXT        0x8000
#define ASN1_TAG_PRIVATE        0xc000

#define ASN1_TAG_CONSTRUCTED    0x2000

#define ASN1_TAG_UNIVERSAL_BOOLEAN              1
#define ASN1_TAG_UNIVERSAL_INTEGER              2
#define ASN1_TAG_UNIVERSAL_BITSTRING            3
#define ASN1_TAG_UNIVERSAL_OCTETSTRING          4
#define ASN1_TAG_UNIVERSAL_NULL                 5
#define ASN1_TAG_UNIVERSAL_OBJECT_IDENTIFIER    6
#define ASN1_TAG_UNIVERSAL_OBJECT_DESCRIPTOR    7
#define ASN1_TAG_UNIVERSAL_EXTERNAL             8
#define ASN1_TAG_UNIVERSAL_REAL                 9
#define ASN1_TAG_UNIVERSAL_ENUMERATED           10
#define ASN1_TAG_UNIVERSAL_UTF8STRING			12
#define ASN1_TAG_UNIVERSAL_SEQUENCE             16
#define ASN1_TAG_UNIVERSAL_SET                  17
#define ASN1_TAG_UNIVERSAL_NUMERICSTRING        18
#define ASN1_TAG_UNIVERSAL_PRINTABLESTRING		19
#define ASN1_TAG_UNIVERSAL_TELETEXSTRING		20
#define ASN1_TAG_UNIVERSAL_T61STRING			20
#define ASN1_TAG_UNIVERSAL_VIDEOTEXSTRING		21
#define ASN1_TAG_UNIVERSAL_IA5STRING            22
#define ASN1_TAG_UNIVERSAL_UTCTIME				23
#define ASN1_TAG_UNIVERSAL_GENERALIZEDTIME		24
#define ASN1_TAG_UNIVERSAL_GRAPHICSTRING		25
#define ASN1_TAG_UNIVERSAL_VISIBLESTRING		26
#define ASN1_TAG_UNIVERSAL_ISO646STRING			26
#define ASN1_TAG_UNIVERSAL_GENERALSTRING		27
#define ASN1_TAG_UNIVERSAL_UNIVERSALSTRING		28
#define ASN1_TAG_UNIVERSAL_CHARACTER_STRING		29
#define ASN1_TAG_UNIVERSAL_BMPSTRING			30

#define SEQ_OF_MIN_MASK     3

void read_object_identifier(byte * in, dword * out);
void write_object_identifier(dword * in, byte * out);

enum asn1_type { ASN1_TYPE_NULL,
                 ASN1_TYPE_BOOLEAN,
                 ASN1_TYPE_INT,
                 ASN1_TYPE_INTS,
                 ASN1_TYPE_INTE,
                 ASN1_TYPE_INT8,
                 ASN1_TYPE_INT16,
                 ASN1_TYPE_BITSTRING,
                 ASN1_TYPE_ENUMERATED,
                 ASN1_TYPE_OCTET_ARRAY,
                 ASN1_TYPE_IA5_STRING,
                 ASN1_TYPE_OCTET_STRING,
                 ASN1_TYPE_WORD_STRING,
                 ASN1_TYPE_OBJECT_IDENTIFIER,
                 ASN1_TYPE_SEQUENCE,
				 ASN1_TYPE_SET,
				 ASN1_TYPE_CHOICE,
                 ASN1_TYPE_SEQUENCE_OF,
				 ASN1_TYPE_SET_OF,
                 ASN1_TYPE_NUMERIC_STRING,
                 ASN1_TYPE_ANY,
				 ASN1_TYPE_UTF8STRING,
				 ASN1_TYPE_PRINTABLESTRING,
				 ASN1_TYPE_TELETEXSTRING,
				 ASN1_TYPE_VIDEOTEXSTRING,
				 ASN1_TYPE_GRAPHICSTRING,
				 ASN1_TYPE_VISIBLESTRING,
				 ASN1_TYPE_GENERALSTRING,
				 ASN1_TYPE_UNIVERSALSTRING,
				 ASN1_TYPE_BMPSTRING,
				 ASN1_TYPE_UTCTIME,
				 ASN1_TYPE_GENERALIZEDTIME,

                 ASN1_TYPE_INNO_DUMMY};

class asn1_out {
public:
    virtual void bit(bool v)=0;
    virtual void bit_field(dword v, int len)=0;
    virtual void octet(byte v)=0;
    virtual void octet_field(byte * v, int len)=0;
    virtual void align()=0;
    virtual void * new_stream(void * stream)=0;
    virtual void append(void * stream)=0;
    virtual dword length()=0;
    virtual void get_reference(void * & buffer, int & offset)=0;
};

class asn1_in {
public:
    virtual bool bit()=0;
    virtual dword bit_field(int len)=0;
    virtual byte octet()=0;
    virtual void octet_field(byte * v, int len)=0;
    virtual void align()=0;
    virtual int left()=0;
    virtual void abort()=0;
    virtual int get_count()=0;
    virtual void set_count(int count)=0;
    virtual void skip(int count)=0;
    virtual void save()=0;
    virtual void restore()=0;
    virtual void get_reference(void * & buffer, int & offset)=0;
};

struct asn1_tag {
    dword tag;
    void * content;
};

class asn1_context {
protected:
    int tag_buffer_size;
    int tag_index;
    struct asn1_tag * tag_buffer;
    int content_buffer_size;
    int content_index;
    byte * content_buffer;
    unsigned fix_mask;
    bool trace;

public:
    asn1_context(struct asn1_tag * tag_buffer, int tag_buffer_size, void * content_buffer, int content_buffer_size, bool trace);
    struct asn1_tag * new_tag(word tag);
    struct asn1_tag * new_tag(word tag, int size, dword align);
    struct asn1_tag * find_tag(word tag);
    void set_seq(int num);
    dword get_mask();
    dword set_mask(dword mask);
    bool trace_on() { return trace; };
    void set_fix(unsigned fix_mask) { this->fix_mask = fix_mask; };
    int get_content_index() { return content_index; };

    virtual void read(class asn1 & asn1, class asn1_in & in)=0;
    virtual void write(class asn1 & asn1, class asn1_out & out)=0;

    int level;

    dword seq_of;
    dword seq_mask;
};

class asn1 {

public:
    word tag;
    word type;
    const char * name;

    asn1(int & tag, const char * name);

    bool is_present(class asn1_context & context);
    virtual void fix(unsigned fix_mask) {};
};

class asn1_null : public asn1 {

public:
    asn1_null(int & tag, const char * name);

    void put_content(class asn1_context & context);
};

class asn1_boolean : public asn1 {

public:
    asn1_boolean(int & tag, const char * name);

    bool get_content(class asn1_context & context);
    void put_content(class asn1_context & context, bool content);
};

class asn1_int : public asn1 {

public:
    byte count_bits;

    asn1_int(int & tag, const char * name, byte count_bits);

    dword get_content(class asn1_context & context);
    void put_content(class asn1_context & context, dword content);
};

class asn1_ints : public asn1 {

public:
    asn1_ints(int & tag, const char * name);

    int get_content(class asn1_context & context);
    void put_content(class asn1_context & context, int content);
};

class asn1_inte : public asn1 {

public:
    byte count_bits;
    dword max;

    asn1_inte(int & tag, const char * name, byte count_bits, dword max);

    dword get_content(class asn1_context & context);
    void put_content(class asn1_context & context, dword content);
};

class asn1_int8 : public asn1 {

public:
    asn1_int8(int & tag, const char * name);

    dword get_content(class asn1_context & context);
    void put_content(class asn1_context & context, dword content);
};

class asn1_int16 : public asn1 {

public:
    asn1_int16(int & tag, const char * name);

    dword get_content(class asn1_context & context);
    void put_content(class asn1_context & context, dword content);
};

class asn1_bitstring : public asn1 {

public:
    word min_length;
    word max_length;
    byte len_bits;

    asn1_bitstring(int & tag, const char * name, int min_length, int max_length, int len_bits);

    byte * get_content(class asn1_context & context, int * length);
    void put_content(class asn1_context & context, byte * s, int length);
    void put_content(class asn1_context & context, class packet * data);
    word get_offset(class asn1_context & context, class packet * data);
};

class asn1_enumerated : public asn1 {

public:
    byte properties;
    dword count;
    byte count_bits;

    asn1_enumerated(int & tag, const char * name, byte properties, byte count, byte count_bits);

    dword get_content(class asn1_context & context);
    void put_content(class asn1_context & context, dword content);
};

class asn1_octet_array : public asn1 {

public:
    word length;

    asn1_octet_array(int & tag, const char * name, word length);

    byte * get_content(class asn1_context & context);
    void put_content(class asn1_context & context, byte * content);
};

struct octet_string_buffer {
    int len;
    byte * b_ptr;
    void * in_buffer;
    int in_offset;
    byte b[1];
};

class asn1_ia5_string : public asn1 {

public:
    word min_length;
    word max_length;
    byte len_bits;
    byte char_bits;
    const char * from;

    asn1_ia5_string(int & tag, const char * name, int min_length, int max_length, byte len_bits, byte char_bits, const char * from);

    byte * get_content(class asn1_context & context, int * length);
    void put_content(class asn1_context & context, byte * s, int length);
};

class asn1_octet_string : public asn1 {
	
public:
	int std_tag;
	word min_length;
    word max_length;
    byte len_bits;

    asn1_octet_string(int & tag, const char * name, int min_length, int max_length, int len_bits);

    byte * get_content(class asn1_context & context, int * length);
    void put_content(class asn1_context & context, byte * s, int length);
    void put_content(class asn1_context & context, class packet * data);
};

struct word_string_buffer {
    int len;
    word * b_ptr;
    word b[1];
};

class asn1_word_string : public asn1 {

public:
    word min_length;
    word max_length;
    byte len_bits;

    asn1_word_string(int & tag, const char * name, int min_length, int max_length, int len_bits);

    word * get_content(class asn1_context & context, int * length);
    void put_content(class asn1_context & context, word * s, int length);
};

class asn1_object_identifier : public asn1 {

public:
    asn1_object_identifier(int & tag, const char * name);

    byte * get_content(class asn1_context & context);
    void put_content(class asn1_context & context, byte * content);
};

class asn1_sequence : public asn1 {

public:
    byte properties;
    byte count;
    class asn1 ** table;
    byte * flags;
    word * tag_table;
    byte ext_count;

    asn1_sequence(int & tag, const char * name, byte properties, byte count, class asn1 ** table, byte * flags, byte ext_count=0, word * tag_table=0);

    bool get_content(class asn1_context & context);
    void put_content(class asn1_context & context, bool content);
};

class asn1_choice : public asn1 {

public:
    byte properties;
    byte count;
    byte count_bits;
    class asn1 ** table;
    word * tag_table;
    byte ext_count;

    asn1_choice(int & tag, const char * name, byte properties, byte count, byte count_bits, class asn1 ** table, byte ext_count=0, word * tag_table=0);

    dword get_content(class asn1_context & context);
    void put_content(class asn1_context & context, dword content);
};

class asn1_sequence_of : public asn1 {

public:
	byte count_bits;
    byte min_length;
    class asn1 * seq;

    asn1_sequence_of(int & tag, const char * name, byte count_bits, byte min_length, class asn1 * seq);

    dword set_mask(class asn1_context & context);
    dword get_content(class asn1_context & context);
    void put_content(class asn1_context & context, dword content);
};

class asn1_set_of : public asn1 {

public:
	byte count_bits;
    byte min_length;
    class asn1 * seq;

    asn1_set_of(int & tag, const char * name, byte count_bits, byte min_length, class asn1 * seq);

    dword set_mask(class asn1_context & context);
    dword get_content(class asn1_context & context);
    void put_content(class asn1_context & context, dword content);
};

class asn1_numeric_string : public asn1 {

public:
    word min_length;
    word max_length;
    byte len_bits;

    asn1_numeric_string(int & tag, const char * name, int min_length, int max_length, int len_bits);

    byte * get_content(class asn1_context & context, int * length);
    void put_content(class asn1_context & context, byte * s, int length);
    void put_content(class asn1_context & context, class packet * data);
};

class asn1_any : public asn1 {
public:
    asn1_any(int & tag, const char * name);

    bool get_content(class asn1_context & context);
    void put_content(class asn1_context & context);

    virtual class asn1 * get_actual(class asn1_context & context) {
        return 0;
    }
};

class asn1_inno_dummy : public asn1 {

public:
    asn1_inno_dummy(int & tag, const char * name);

    byte * get_content(class asn1_context & context, int * length);
    void put_content(class asn1_context & context, byte * s, int length);
};

/*---------------------------------------------------------------------------*/
/* STRING TYPES                                                              */
/*---------------------------------------------------------------------------*/

class asn1_utf8_string : public asn1_octet_string {
public:
	asn1_utf8_string(int & tag, const char * name, int min_length, int max_length, int len_bits);
};

class asn1_printable_string : public asn1_octet_string {
public:
	asn1_printable_string(int & tag, const char * name, int min_length, int max_length, int len_bits);
};

class asn1_teletex_string : public asn1_octet_string {
public:
	asn1_teletex_string(int & tag, const char * name, int min_length, int max_length, int len_bits);
};

typedef asn1_teletex_string asn1_t61_string;

class asn1_videotex_string : public asn1_octet_string {
public:
	asn1_videotex_string(int & tag, const char * name, int min_length, int max_length, int len_bits);
};

class asn1_graphic_string : public asn1_octet_string {
public:
	asn1_graphic_string(int & tag, const char * name, int min_length, int max_length, int len_bits);
};

class asn1_visible_string : public asn1_octet_string {
public:
	asn1_visible_string(int & tag, const char * name, int min_length, int max_length, int len_bits);
};

typedef asn1_visible_string asn1_iso646_string;

class asn1_general_string : public asn1_octet_string {
public:
	asn1_general_string(int & tag, const char * name, int min_length, int max_length, int len_bits);
};

class asn1_universal_string : public asn1_octet_string {
public:
	asn1_universal_string(int & tag, const char * name, int min_length, int max_length, int len_bits);
};

class asn1_bmp_string : public asn1_octet_string {
public:
	asn1_bmp_string(int & tag, const char * name, int min_length, int max_length, int len_bits);
};

/*---------------------------------------------------------------------------*/
/* TIME TYPES                                                                */
/*---------------------------------------------------------------------------*/

class asn1_utc_time : public asn1_universal_string {
public:
	asn1_utc_time(int & tag, const char * name);
};

class asn1_generalized_time : public asn1_universal_string {
public:
	asn1_generalized_time(int & tag, const char * name);
};

NAMESPACE_END
