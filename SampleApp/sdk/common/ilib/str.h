/*----------------------------------------------------------------------------*/
/* str.h                                                                 	  */
/* copyright (c) innovaphone 2010                                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#ifndef _STR_H_
#define _STR_H_

NAMESPACE_BEGIN

#define PARSE_ARGS_DECODE_URL               1
#define PARSE_ARGS_STRIP_EXCESSIVE_SPACES   2
#define PARSE_ARGS_DECODE_FORM    (PARSE_ARGS_DECODE_URL + PARSE_ARGS_STRIP_EXCESSIVE_SPACES)

class str
{
	static const word ucs2_to_upper_case[0x800];
	static const word ucs2_to_lower_case[0x800];
	static const word ucs2_to_coll_order[0x800];
	static const word ucs2_to_icoll_order[0x800];
	static const word ucs2_to_latin1_transcribe[0x800];
	static const byte hexindex[256];

	static int tcoll(const char * s1, const char * s2, const word coll_order[0x800]);
	static int wtcoll(const word * w1, dword w1_len, const word * w2, dword w2_len, const word coll_order[0x800]);

	static dword ichar(const char * p, const char * e, const char ** r);
	static bool imatch(const char * p, const char * p_end, const char * s, const char * s_end);
	static bool latin1_imatch(const char * p, const char * p_end, const char * s, const char * s_end);

public:

	//	utf8 string handler
    static int cmp(const char * s1, const char * s2);
	static int icmp(const char * s1, const char * s2);
	static int n_icmp(const char * s1, const char * s2, dword num);
	static bool imatch_pattern(const char * pattern, dword len_pattern, const char * string, dword len_string);
	static int coll(const char * s1, const char * s2)  { return tcoll(s1, s2, ucs2_to_coll_order);  }
	static int icoll(const char * s1, const char * s2) { return tcoll(s1, s2, ucs2_to_icoll_order); }
	static const char * next(const char * s, const char * s_end);
	static const char * prev(const char * s, const char * s_1st);
	static dword ucs4_char(const char * s, const char * s_end, const char ** next);

	//	utf8 / latin1 and vice versa
	static bool may_be_utf8(const char * in);
	static bool n_may_be_utf8(const char * in, dword len);
	static bool must_be_utf8(const char * in);
	static bool n_must_be_utf8(const char * in, dword len);
 	static dword to_latin1(char * inout);
    static dword to_latin1(const char * in, char * out, dword len);
    static dword to_latin1_transcribe(const char * in, char * out, dword len);
    static dword to_latin1_xml(const char * in, char * out, dword len);
    static dword n_to_latin1(const char * in, dword num, char * out, dword len);
	static dword n_to_latin1_n(const char * in, dword cnt, char * out, dword len);
    static dword from_latin1(const char * in, char * out, dword len);
	static dword from_latin1_n(const char * in, dword num, char * out, dword len);
    static dword from_latin1_n_len(const char * in, dword num);
	static dword n_from_latin1_n(const char * in, dword num, char * out, dword len);

	//	latin1 / ucs2 and vice versa
	static dword ucs2_n_to_latin1(const word * in, dword num, char * out, dword len);
	static dword latin1_to_ucs2_n(const char * in, word * out, dword num);

	//	ucs2 string handler
	static int ucs2_cmp(const word * w1, const word * w2);
	static int ucs2_cmp(const word * w1, dword w1_cnt, const word * w2, dword w2_cnt);
	static int ucs2_icmp(const word * w1, const word * w2);
	static int ucs2_icmp(const word * w1, dword w1_cnt, const word * w2, dword w2_cnt);
	static int ucs2_coll(const word * w1, dword w1_cnt, const word * w2, dword w2_cnt)
						{ return wtcoll(w1, w1_cnt, w2, w2_cnt, ucs2_to_coll_order); }
	static int ucs2_icoll(const word * w1, dword w1_cnt, const word * w2, dword w2_cnt)
						{ return wtcoll(w1, w1_cnt, w2, w2_cnt, ucs2_to_icoll_order); }
	static dword ucs2_cnt(const word * in);										//	'in' NUL terminated
	static dword ucs2_to_ucs2(const word * in, word * out, dword cnt);			//	'in' NUL terminated
    static word ucs2_chr2lwr(word w) { return (w < (sizeof(ucs2_to_lower_case)/sizeof(ucs2_to_lower_case[0]))) ? ucs2_to_lower_case[w] : w; }
    static word ucs2_chr2upr(word w) { return (w < (sizeof(ucs2_to_upper_case)/sizeof(ucs2_to_upper_case)[0])) ? ucs2_to_upper_case[w] : w; }
    static dword ucs2_to_le_n(const word * in, byte * out, dword cnt);          //  write as little endian
    static dword ucs2_to_net_n(const word * in, byte * out, dword cnt);         //  write as big endian

	//	utf8 / ucs2 and vice versa
    static dword to_ucs2(const char * in, word * out, dword cnt);				//	'out' NUL terminated
	static dword to_ucs2_n(const char * in, word * out, dword cnt);
    static dword n_to_ucs2(const char * in, dword num, word * out, dword cnt);
    static dword from_ucs2(const word * in, char * out, dword len);				//	'in' NUL terminated
    static dword from_ucs2_n(const word * in, dword num, char * out, dword len);

    //  utf8 / utf8
    static dword to_utf8(const char * in, char * out, dword len);               //  copy valid and complete utf8 chars only
    static dword utf8_cnt(const char * in);

	//	utf8 / url and vice versa
	static dword to_url(const char * in, char * out, dword len);
	static dword to_url_cfg(const char * in, char * out, dword len);
	static dword from_url(char * inout);
	static dword from_url(const char * in, char * out, dword len);

    // utf8 / punycode and vice versa
    static dword to_punycode(const char * in, char * out, dword len);
    static dword from_punycode(const char * in, char * out, dword len);

	//	command option handler ('case' means ascii case insensitive)
    static char * args_find(int argc, char * argv[], const char * arg);
    static char * parse_args(int argc, char * argv[], int & i, const char * args_tbl[], int & index, char * & value, int * arg=0, byte decode=0);
	static bool match(const char * ref, const char * s, char ** ptr);		//	latin1::str_match() substitute, case dependent
	static bool casematch(const char * ref, const char * s, char ** ptr);	//	strmatchi() substitute, permits mixed case in both strings
	static int  casecmp(const char * s1, const char * s2);					//  strcasecmp() substitute when not in standard library
	static int  n_casecmp(const char * s1, const char * s2, dword num);		//  strncasecmp() substitute when not in standard library
	static void caselwr(char * inout);										//  strlwr() substitute when not in standard library
	static void n_caselwr(char * inout, dword num);							//	not in standard library
	static void caseupr(char * inout);										//  strupr() substitute when not in standard library
	static void n_caseupr(char * inout, dword num);							//	not in standard library
	static char chr2lwr(char c);
	static char chr2upr(char c);

	//	latin1 code helper
	static int latin1_icmp(const char * s1, const char * s2);
	static int latin1_n_icmp(const char * s1, const char * s2, dword num);
	static bool latin1_imatch_pattern(const char * pattern, dword len_pattern, const char * string, dword len_string);
	static char latin1_chr2lwr(char c);
	static char latin1_chr2upr(char c);

	//	plain string helper
    static int   diff(const char * s1, const char * s2);
	static dword to_hexmem(const char * s, byte * mem, dword len, bool fill = false);
	static dword to_hexmem(const char * s, char ** ptr, byte * mem, dword len, bool fill=true);
    static dword to_str(const char * in, char * out, dword len);
    static dword to_strx(const char * in, char * out, dword len);           // copy zero terminated in string to size limited zero terminated out string. Only copy complete utf-8 char.
    static dword to_xml(const char * in, char * out, dword len);
    static ulong64 to_id(const char * str);
	static bool  to_tm(const char * s, char ** ptr, struct tm & tm);
    static char * from_hexmem(const byte * mem, const dword len, char * s);
#if !defined(PLATFORM_NO_IPADDR)
    static IPaddr to_ip(const char * s, char ** ptr=0, word * prefix=0);
    static IP4addr to_ip4(const char * s, char ** ptr);
    static bool to_ip6(const char * str, IPaddr * addr, word * prefix, char ** ptr);
    static bool to_eaddr(const char * str, char ** ptr, Eaddr * eaddr);
#endif
	static byte chr2hexval(char c);
    static bool is_dial_string(const char * s);
    static dword from_ie_number(const byte * ie, char * out, dword len);
	static bool is_true(const char * s);
    static dword n_len(const char * in, dword len);
    static bool is_ip_unconfigured(const char * s);
    static char * strip_whitespace(char * in);
    static void replace(const char * in, char * out, dword len, const char * placeholder, const char * replace);
    static dword split(char * in, char * tokens[], dword max_tokens, const char * separator);
    static dword join(char * out, dword len, char * tokens[], dword num_tokens, const char * separator);

    // quoted string
    static char * escape_quoted(char * in, char * &out, unsigned len);
    
    // quoted-printable (RFC 2045)
    static char * escape_quoted_printable(char * in, char * out, unsigned out_size, bool escape_q_string_chars = false);

    // transcribe (for sorting)
    static unsigned transcribe_to_basic_latin(char * buf, unsigned size_of_buf);

    static dword fnv1a_hash(const char *s);
    static dword fnv1a_hash(const byte *s, word length);

#if defined(PLATFORM_MALLOC)
    static char * malloc_strcpy(const char * s);
#endif

	//	latin 1 character type table, public to simplify the macros
	static const byte ctype[256];
};

#define	_latin1_u_	0x01	/* upper case	*/
#define	_latin1_l_	0x02	/* lower case	*/
#define	_latin1_n_	0x04	/* numeric		*/
#define	_latin1_e_	0x08	/* E164 char	*/
#define _latin1_p_	0x10	/* punctuation	*/
#define _latin1_c_	0x20	/* control		*/
#define _latin1_x_	0x40	/* hex digit	*/
#define	_latin1_b_	0x80	/* blank char	*/

#define IS_DEC_DIGIT(_c_)		(str::ctype[(byte)_c_] & (_latin1_n_))
#define IS_HEX_DIGIT(_c_)		(str::ctype[(byte)_c_] & (_latin1_n_|_latin1_x_))
#define IS_E164_DIGIT(_c_)		(str::ctype[(byte)_c_] & (_latin1_n_|_latin1_e_))
#define	IS_DIAL_DIGIT(_c_)  	((str::ctype[(byte)_c_] & (_latin1_n_|_latin1_e_)) || _c_ == ',')
#define IS_DTMF_DIGIT(_c_)  	((str::ctype[(byte)_c_] & (_latin1_n_|_latin1_e_)) || (_c_>='A' && (_c_<='D' || (_c_>='a' && _c_<= 'd'))))

#define IS_ASCII_SPACE(_c_)		((byte)_c_ <= 0x20)
#define IS_ASCII_CTRL(_c_)		((byte)_c_ <= 0x7f && (str::ctype[(byte)_c_] & (_latin1_c_)))
#define IS_ASCII_ALNUM(_c_)     ((byte)_c_ <= 0x7f && (str::ctype[(byte)_c_] & (_latin1_u_|_latin1_l_|_latin1_n_)))
#define	IS_ASCII_NAME(_c_)   	((byte)_c_ <= 0x7f && ((str::ctype[(byte)_c_] & (_latin1_b_|_latin1_u_|_latin1_l_|_latin1_n_)) || _c_ == '-' ||  _c_ == '_'))

#define IS_LATIN1_ALPHA(_c_)	(str::ctype[(byte)_c_] & (_latin1_u_|_latin1_l_))
#define IS_LATIN1_ALNUM(_c_)	(str::ctype[(byte)_c_] & (_latin1_u_|_latin1_l_|_latin1_n_))
#define IS_LATIN1_H323(_c_)		(str::ctype[(byte)_c_] & (_latin1_p_|_latin1_u_|_latin1_l_|_latin1_n_))
#define IS_LATIN1_TEXT(_c_)   	(str::ctype[(byte)_c_] & (_latin1_p_|_latin1_u_|_latin1_l_|_latin1_n_|_latin1_b_))
#define IS_LATIN1_SPACE(_c_)  	(str::ctype[(byte)_c_] & (_latin1_c_|_latin1_b_))
#define IS_LATIN1_UPPER(_c_)  	(str::ctype[(byte)_c_] & (_latin1_u_))
#define IS_LATIN1_LOWER(_c_)  	(str::ctype[(byte)_c_] & (_latin1_l_))

NAMESPACE_END

#endif /* _STR_H_ */
