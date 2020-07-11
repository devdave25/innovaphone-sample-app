
/*---------------------------------------------------------------------------*/
/* language.h                                                                */
/* copyright (c) innovaphone 2017                                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/

typedef struct { const char * lang; const char * utf8; const char * langIso639_2; } LanguageTableEntry;

typedef enum {
    LANGUAGE_PARAM_TYPE_STRING = 0,
    LANGUAGE_PARAM_TYPE_UINT32,
    LANGUAGE_PARAM_TYPE_INT32,
    LANGUAGE_PARAM_TYPE_UINT64,
    LANGUAGE_PARAM_TYPE_INT64
} language_param_type_t;

class Language {
public:
    static int GetLanguageId(const char * lang, LanguageTableEntry languages[], int numLangs, int defaultLang);
    static size_t ReplaceArgs(const char * translatedString, char * buffer, size_t bufferLen, ...);
};
