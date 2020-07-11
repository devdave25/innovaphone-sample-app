/*---------------------------------------------------------------------------*/
/* base64.h                                                                  */
/* copyright (c) innovaphone 2002, 2007                                      */
/*                                                                           */
/* BASE64 encoding/decoding                                                  */
/*---------------------------------------------------------------------------*/

#ifndef _BASE64_H_
#define _BASE64_H_

NAMESPACE_BEGIN

unsigned decode_base64_bin(const char * in, byte * out, unsigned size_of_out);
dword decode_base64(const char * in, byte * out, int n);
dword encode_base64(const byte * in, char * out, int len);

NAMESPACE_END

#endif /* _BASE64_H_ */
