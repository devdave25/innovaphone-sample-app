/*---------------------------------------------------------------------------*/
/* cipher.h                                                                  */
/* copyright (c) innovaphone 2016                                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/

NAMESPACE_BEGIN

#define DES_DATA_SIZE       8
#define DES_KEY_SIZE        7

enum cipher_t {
    CIPHER_UNDEFINED,
    CIPHER_DES,
    CIPHER_AES,
    CIPHER_RC4
};

class Cipher {
protected:
    bool encrypt;
    cipher_t type;
    ulong64 ctx[129];

public:
    Cipher();
    void Init(cipher_t type, const byte * key, int keyLen, bool encrypt = true);
    void Reset();

    void Block(const byte * in, byte * out);
    void Crypt(const byte * in, byte * out, int len);
    void CtrCrypt(const byte * in, byte * out, int len, byte * iv);
};

NAMESPACE_END
