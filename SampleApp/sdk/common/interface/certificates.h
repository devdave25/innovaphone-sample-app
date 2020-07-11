
/*---------------------------------------------------------------------------*/
/* certificates.h															 */
/* copyright (c) innovaphone 2017                                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/

typedef enum {
    CERTIFICATE_OK = 0,
    CERTIFICATE_PARSING_FAILED,
    CERTIFICATE_PUBLIC_KEY_INVALID,
    CERTIFICATE_PRIVATE_KEY_INVALID,
    CERTIFICATE_CHAIN_INVALID
} certificate_error_t;

typedef enum {
    CERTIFICATE_PEM = 0
} certificate_type_t;

typedef enum {
    FINGERPRINT_MD5,
    FINGERPRINT_SHA1,
    FINGERPRINT_SHA224,
    FINGERPRINT_SHA256,
    FINGERPRINT_SHA384,
    FINGERPRINT_SHA512
} fingerprint_t;

class ICertificates {
public:
    static certificate_error_t ValidateCertificate(class IInstanceLog * log, const byte * cert, size_t certLen);
    virtual byte * CertificateFingerprint(class IInstanceLog * log, const byte * cert, size_t certLen, fingerprint_t type = FINGERPRINT_SHA256) = 0;
    virtual byte * CreateCertificate(class IInstanceLog * log, size_t * certLen, certificate_type_t type = CERTIFICATE_PEM) = 0;
};
