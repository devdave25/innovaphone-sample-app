/*---------------------------------------------------------------------------*/
/* platform.h                                                                */
/* copyright (c) innovaphone 2013 - 2018                                     */
/*                                                                           */
/*---------------------------------------------------------------------------*/

#if __INTELLISENSE__
#undef __cplusplus
#define __cplusplus 201402L
#define __attribute__(q)
#define __builtin_va_list void*
#define __builtin_va_start(a,b)
#define __builtin_va_end(a)
#define __CHAR_BIT__ 8
typedef unsigned short char16_t;
typedef unsigned int char32_t;
typedef float __float128;
#define constexpr const
#define __SIZE_TYPE__ unsigned int
#define NO_LEGACY
#define _GLIBCXX_STDLIB_H 1
#endif

#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <time.h>
#include <assert.h>
#include <dlfcn.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <deque>
#include <queue>
#include <set>
#include <vector>

extern const char * _BUILD_STRING_;
extern const char * __BUILD_STRING__;
extern const char * _VERSION_STR_;
extern const char * _RELEASE_STATE_;

#if __INTELLISENSE__
#undef __cplusplus
#define __cplusplus 1
#endif
#include <list>
#include <map>
#if __INTELLISENSE__
#undef __cplusplus
#define __cplusplus 201402L
#endif
#include <unordered_map>
#include <unordered_set>

#define NAMESPACE_BEGIN
#define NAMESPACE_END
#define USING_NAMESPACE

#define TEST_WATCH(x)

// btree.h needs the NAMESPACE_* defines. Because of that the file will be included after the defines had been set.
#include "common/ilib/btree.h"

#if defined(NO_LEGACY)
#define PLATFORM_NO_PACKET
#define PLATFORM_NO_IPADDR
#endif

#define PLATFORM_MALLOC

#define _printf vsprintf
#define _sprintf sprintf
#define _snprintf snprintf
inline char * _ip_strdup(const char * s) {
    if (!s) return 0;
    size_t l = strlen(s) + 1;
    return (char *)memcpy(malloc(l), s, l);
}
#define _strdup(x) _ip_strdup(x)

#define DEFAULT_OPUS_COMPLEXITY 5

#undef  BIGENDIAN	/* may be defined on command line already */

typedef unsigned char byte;
typedef unsigned short word;
typedef short int16;
typedef unsigned int dword;
typedef long long long64;
typedef unsigned long long ulong64;
typedef intptr_t intp;
typedef uintptr_t uintp;
typedef int int32;

typedef dword interrupt_mask;

#define PLATFORM_VIRTUAL virtual

#define MIN(a,b) ((a)>(b) ? (b) : (a))
#define MAX(a,b) ((a)>(b) ? (a) : (b))
#define SWAP(t,a,b) { t c=a; a=b; b=c; }
#define GET_BASE(p,s,m) ((s *)((char *)p - (char *)&((s *)0)->m))
#define GET_OFS(s,m) ((int)((char *)(&((s *)0)->m) - (char *)0))

#define READ_WORD_NET(a) ( (((byte *)(a))[0]<<8) + ((byte *)(a))[1] )
#define READ_DWORD_NET(a) ( (((byte *)(a))[0]<<24) + (((byte *)(a))[1]<<16) + (((byte *)(a))[2]<<8) + ((byte *)(a))[3] )
#define READ_QUAD_NET(a) ((ulong64(READ_DWORD_NET(((byte *)(a)))) << 32) + READ_DWORD_NET(((byte *)((a) + 4))))

#define WRITE_WORD_NET(a,w) { word wx=(w); ((byte *)(a))[0]=(wx>>8); ((byte *)(a))[1]=(wx&0xff); }
#define WRITE_DWORD_NET(a,w) { dword wx=(w); ((byte *)(a))[0]=(byte)((wx>>24)); ((byte *)(a))[1]=(byte)((wx>>16)&0xff); ((byte *)(a))[2]=(byte)((wx>>8)&0xff); ((byte *)(a))[3]=(byte)((wx)&0xff); }
#define WRITE_QUAD_NET(a,w) { ulong64 wx=(w); ((byte *)(a))[0]=(byte)((wx>>56)); ((byte *)(a))[1]=(byte)((wx>>48)&0xff); ((byte *)(a))[2]=(byte)((wx>>40)&0xff); ((byte *)(a))[3]=(byte)((wx>>32)&0xff); ((byte *)(a))[4]=(byte)((wx>>24)&0xff); ((byte *)(a))[5]=(byte)((wx>>16)&0xff); ((byte *)(a))[6]=(byte)((wx>>8)&0xff); ((byte *)(a))[7]=(byte)((wx)&0xff); }

#define READ_DWORD_LE(a) ( (((byte *)(a))[0]) + (((byte *)(a))[1]<<8) + (((byte *)(a))[2]<<16) + (((byte *)(a))[3]<<24) )
#define READ_24BIT_LE(a) ( (((byte *)(a))[0]) + (((byte *)(a))[1]<<8) + (((byte *)(a))[2]<<16) )
#define READ_WORD_LE(a) ( (((byte *)(a))[0]) + (((byte *)(a))[1]<<8) )
#define WRITE_WORD_LE(a,w) { word wx=(w); ((byte *)(a))[0]=(wx&0xff); ((byte *)(a))[1]=(wx>>8);  }
#define WRITE_24BIT_LE(a,w) { dword wx=(w); ((byte *)(a))[0]=(byte)((wx)&0xff); ((byte *)(a))[1]=(byte)((wx>>8)&0xff); ((byte *)(a))[2]=(byte)((wx>>16));}
#define WRITE_DWORD_LE(a,w) { dword wx=(w); ((byte *)(a))[0]=(byte)((wx)&0xff); ((byte *)(a))[1]=(byte)((wx>>8)&0xff); ((byte *)(a))[2]=(byte)((wx>>16)&0xff); ((byte *)(a))[3]=(byte)((wx>>24));}
#define WRITE_QUAD_LE(a,w)  { ulong64 wx=(w); ((byte *)(a))[0]=(byte)((wx)&0xff); ((byte *)(a))[1]=(byte)((wx>>8)&0xff); ((byte *)(a))[2]=(byte)((wx>>16)&0xff); ((byte *)(a))[3]=(byte)((wx>>24)&0xff); ((byte *)(a))[4]=(byte)((wx>>32)&0xff); ((byte *)(a))[5]=(byte)((wx>>40)&0xff); ((byte *)(a))[6]=(byte)((wx>>48)&0xff); ((byte *)(a))[7]=(byte)((wx>>56));}

#define _CONCAT_(x,y) x ## y
#define CONCAT(x,y) _CONCAT_(x,y)
#define ANONYMOUS CONCAT(_anonymous, __LINE__)

#if !defined(NO_LEGACY)
#define TRACE_NAME_MAX_LEN      16
#define CONFIG_BUFFER_SIZE      30000
#endif

void dprintf(const char * format, ...);
extern void outchar(char c);

#define ASSERT(a, s) { if (!(a)) { if(debug) { debug->printf("ASSERT: %s (%s:%u)", s, __FUNCTION__, __LINE__); } sync(); raise(SIGSEGV); abort(); } }
#define ASSERT_NO_PRINTF(a) { if (!(a)) { sync(); raise(SIGSEGV); abort(); } }
//extern void assert(unsigned line, const char * file, const char * why);

#define BUILTIN_CALLER __builtin_return_address(0)
//#define alloca(size) __builtin_alloca(size)

extern "C" void * malloc_uncached(size_t size);

#define MAX_CODER_BUF	8192

#define MODULE_ERROR(m,e) (m<<16 | e)

#define OSCONST const

#define TLS_DEFAULT_CERTIFICATE_PATH    "/home/root/ssl_cert/server.pem"

#include "common/os/debug.h"
#include "common/ilib/ilist.h"