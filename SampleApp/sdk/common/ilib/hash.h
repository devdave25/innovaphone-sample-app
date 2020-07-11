/*---------------------------------------------------------------------------*/
/* hash.h                                                                    */
/* copyright (c) innovaphone 2015                                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/

NAMESPACE_BEGIN

#define HASH_SIZE_MD4       16
#define HASH_SIZE_MD5       16
#define HASH_SIZE_SHA1      20
#define HASH_SIZE_SHA224    28
#define HASH_SIZE_SHA256    32
#define HASH_SIZE_SHA384    48
#define HASH_SIZE_SHA512    64
#define HASH_SIZE_MAX       64

enum hash_t {
    HASH_UNDEFINED,
    HASH_MD4,
    HASH_MD5,
    HASH_SHA1,
    HASH_SHA224,
    HASH_SHA256,
    HASH_SHA384,
    HASH_SHA512
};

class hash {
    ulong64 context[27];
    hash_t type;

public:
    hash();
    void init(hash_t type);
    void update(const void * in, size_t len);
    void final(void * out);
    void copy(class hash * from);
    size_t size();
};

class hmac {
    ulong64 a2[16];
    class hash h;
    hash_t type;

public:
    hmac();
    void init(hash_t type, const void * key, size_t len);
    void update(const void * in, size_t len);
    void final(void * out);
    void copy(class hmac * from);
    size_t size();
};

NAMESPACE_END
