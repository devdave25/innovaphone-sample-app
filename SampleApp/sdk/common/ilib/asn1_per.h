/*---------------------------------------------------------------------------*/
/* asn1_per.h                                                                */
/* copyright (c) innovaphone 1997, 1998                                      */
/*                                                                           */
/* ASN1 packed encoding rules definitions                                    */
/*---------------------------------------------------------------------------*/

NAMESPACE_BEGIN

class asn1_context_per : public asn1_context {
    void read_null(class asn1_null & asn1, class asn1_in & in);
    void write_null(class asn1_null & asn1, class asn1_out & out);
    void read_boolean(class asn1_boolean & asn1, class asn1_in & in);
    void write_boolean(class asn1_boolean & asn1, class asn1_out & out);
    void read_int(class asn1_int & asn1, class asn1_in & in);
    void write_int(class asn1_int & asn1, class asn1_out & out);
    void read_ints(class asn1_int & asn1, class asn1_in & in);
    void write_ints(class asn1_int & asn1, class asn1_out & out);
    void read_inte(class asn1_inte & asn1, class asn1_in & in);
    void write_inte(class asn1_inte & asn1, class asn1_out & out);
    void read_int8(class asn1_int8 & asn1, class asn1_in & in);
    void write_int8(class asn1_int8 & asn1, class asn1_out & out);
    void read_int16(class asn1_int16 & asn1, class asn1_in & in);
    void write_int16(class asn1_int16 & asn1, class asn1_out & out);
    void read_bitstring(class asn1_bitstring & asn1, class asn1_in & in);
    void write_bitstring(class asn1_bitstring & asn1, class asn1_out & out);
    void read_enumerated(class asn1_enumerated & asn1, class asn1_in & in);
    void write_enumerated(class asn1_enumerated & asn1, class asn1_out & out);
    void read_octet_array(class asn1_octet_array & asn1, class asn1_in & in);
    void write_octet_array(class asn1_octet_array & asn1, class asn1_out & out);
    void read_ia5_string(class asn1_ia5_string & asn1, class asn1_in & in);
    void write_ia5_string(class asn1_ia5_string & asn1, class asn1_out & out);
    void read_octet_string(class asn1_octet_string & asn1, class asn1_in & in);
    void write_octet_string(class asn1_octet_string & asn1, class asn1_out & out);
    void read_word_string(class asn1_word_string & asn1, class asn1_in & in);
    void write_word_string(class asn1_word_string & asn1, class asn1_out & out);
    void read_object_object_identifier(class asn1_object_identifier & asn1, class asn1_in & in);
    void write_object_object_identifier(class asn1_object_identifier & asn1, class asn1_out & out);
    void read_sequence(class asn1_sequence & asn1, class asn1_in & in);
    void write_sequence(class asn1_sequence & asn1, class asn1_out & out);
    void read_choice(class asn1_choice & asn1, class asn1_in & in);
    void write_choice(class asn1_choice & asn1, class asn1_out & out);
    void read_sequence_of(class asn1_sequence_of & asn1, class asn1_in & in);
    void write_sequence_of(class asn1_sequence_of & asn1, class asn1_out & out);
    void read_any(class asn1_any & asn1, class asn1_in & in);
    void write_any(class asn1_any & asn1, class asn1_out & out);

public:
    asn1_context_per(struct asn1_tag * tag_buffer, int tag_buffer_size, void * content_buffer, int content_buffer_size, bool trace, unsigned fix_mask=0) : asn1_context(tag_buffer,tag_buffer_size,content_buffer,content_buffer_size,trace) { set_fix(fix_mask); };
    void * operator new(size_t s, void * a) { return a; };

    void read(class asn1 & asn1, class asn1_in & in);
    void write(class asn1 & asn1, class asn1_out & out);
};

NAMESPACE_END
