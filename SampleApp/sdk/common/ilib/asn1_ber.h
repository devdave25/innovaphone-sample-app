/*---------------------------------------------------------------------------*/
/* asn1_ber.h                                                                */
/* copyright (c) innovaphone 1997, 1998                                      */
/*                                                                           */
/* ASN1 packed encoding rules definitions                                    */
/*---------------------------------------------------------------------------*/

NAMESPACE_BEGIN

class asn1_context_ber : public asn1_context {
    void read(class asn1 & asn1, class asn1_in & in, word tag, int length);
    void write(class asn1 & asn1, class asn1_out & out, word tag);

    void read_null(class asn1_null & asn1, class asn1_in & in, word tag, int length);
    void write_null(class asn1_null & asn1, class asn1_out & out, word tag);
    void read_boolean(class asn1_boolean & asn1, class asn1_in & in, word tag, int length);
    void write_boolean(class asn1_boolean & asn1, class asn1_out & out, word tag);
    void read_int(class asn1_int & asn1, class asn1_in & in, word tag, int length);
    void write_int(class asn1_int & asn1, class asn1_out & out, word tag);
    void read_int8(class asn1_int8 & asn1, class asn1_in & in, word tag, int length);
    void write_int8(class asn1_int8 & asn1, class asn1_out & out, word tag);
    void read_int16(class asn1_int16 & asn1, class asn1_in & in, word tag, int length);
    void write_int16(class asn1_int16 & asn1, class asn1_out & out, word tag);
    void read_octet_array(class asn1_octet_array & asn1, class asn1_in & in, word tag, int length);
    void write_octet_array(class asn1_octet_array & asn1, class asn1_out & out, word tag);
    void read_ia5_string(class asn1_ia5_string & asn1, class asn1_in & in, word tag, int length);
    void write_ia5_string(class asn1_ia5_string & asn1, class asn1_out & out, word tag);
    void read_octet_string(class asn1_octet_string & asn1, class asn1_in & in, word tag, int length);
    void write_octet_string(class asn1_octet_string & asn1, class asn1_out & out, word tag);
	void read_bitstring(class asn1_bitstring & asn1, class asn1_in & in, word tag, int length);
    void write_bitstring(class asn1_bitstring & asn1, class asn1_out & out, word tag);
    void read_numeric_string(class asn1_numeric_string & asn1, class asn1_in & in, word tag, int length);
    void write_numeric_string(class asn1_numeric_string & asn1, class asn1_out & out, word tag);    
    void read_word_string(class asn1_word_string & asn1, class asn1_in & in, word tag, int length);
    void write_word_string(class asn1_word_string & asn1, class asn1_out & out, word tag);
    void read_object_object_identifier(class asn1_object_identifier & asn1, class asn1_in & in, word tag, int length);
    void write_object_object_identifier(class asn1_object_identifier & asn1, class asn1_out & out, word tag);
    void read_enumerated(class asn1_enumerated & asn1, class asn1_in & in, word tag, int length);
    void write_enumerated(class asn1_enumerated & asn1, class asn1_out & out, word tag);
    void read_sequence(class asn1_sequence & asn1, class asn1_in & in, word tag, int length);
    void write_sequence(class asn1_sequence & asn1, class asn1_out & out, word tag);
    void read_choice(class asn1_choice & asn1, class asn1_in & in, word tag, int length);
    void write_choice(class asn1_choice & asn1, class asn1_out & out, word tag);
    void read_sequence_of(class asn1_sequence_of & asn1, class asn1_in & in, word tag, int length);
    void write_sequence_of(class asn1_sequence_of & asn1, class asn1_out & out, word tag);
	void read_set_of(class asn1_set_of & asn1, class asn1_in & in, word tag, int length);
    void write_set_of(class asn1_set_of & asn1, class asn1_out & out, word tag);
    void read_any(class asn1_any & asn1, class asn1_in & in, word tag, int length);
    void write_any(class asn1_any & asn1, class asn1_out & out, word tag);
    void read_inno_dummy(class asn1_octet_string & asn1, class asn1_in & in, word tag, int length);
    void write_inno_dummy(class asn1_octet_string & asn1, class asn1_out & out, word tag);

public:
    asn1_context_ber(struct asn1_tag * tag_buffer, int tag_buffer_size, void * content_buffer, int content_buffer_size, bool trace) : asn1_context(tag_buffer,tag_buffer_size,content_buffer,content_buffer_size,trace) {};

    void read(class asn1 & asn1, class asn1_in & in);
    void write(class asn1 & asn1, class asn1_out & out);
};

class explicit_helper : public asn1_sequence {
    class asn1 * table[1];
    word         tag_table[1];
    byte         flags[1];
    
public:
    explicit_helper(int & tag, const char * name, asn1 &value, word tag_value=0, byte flag_value=0) : asn1_sequence(tag,name,0,1,table,flags,0,tag_table)
    {
        table[0] = &value;
        tag_table[0] = tag_value;
        flags[0] = flag_value;
    }
};

NAMESPACE_END
