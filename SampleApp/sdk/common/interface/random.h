/*---------------------------------------------------------------------------*/
/* random.h                                                                  */
/* copyright (c) innovaphone 2015                                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/

enum random_char_t {
    random_chars_url,
    random_chars_ice
};

class IRandom {
public:
    static void Init(dword seed);
    static dword GetRandom();
    static void GetChars(char * out, dword len, random_char_t type = random_chars_url);
};
