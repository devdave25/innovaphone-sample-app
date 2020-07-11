
/*---------------------------------------------------------------------------*/
/* httpfile.h                                                                */
/* copyright (c) innovaphone 2015                                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/

// This defines only exists to be compatible with the firmware and the used tool
// that creates the staic files...

// These flags are the same as inside the firmware and maybe will be used later.
//#define  HTTP_CACHE      0x01
//#define  HTTP_NOPWD      0x02
//#define  HTTP_FORCENOPWD 0x04
//#define  ALLOW_TFTP      0x08
//#define  HTTP_ADMINLOGIN 0x10       // send login to command, not to the destination module
//#define  HTTP_CMD_NO_LOG 0x20
//#define	 HTTP_CMD_OVERWRITE 0x40    // allow to overwrite CMD with the query string
//#define  HTTP_SEND_503   0x80   // used for firmware download
//#define  HTTP_LEVEL1     0x100

#define HTTP_CACHE      0
#define HTTP_NOPWD      0
#define HTTP_ADMINLOGIN 0
#define HTTP_FORCENOPWD 0
#define SERVLET_STATIC  0
#define   HTTP_GZIP       0x200

extern class btree * staticFilesRoot;

class httpfile: public btree {
protected:
    word flags;
    char * fileName;
    char md5str[33];
    byte * data;
    size_t dataSize;
    word type;

    virtual int btree_compare(void * key);
    virtual int btree_compare(class btree * b);

public:
    httpfile(const char * fileName, word /* servlettype unused */, word theFlags, byte * data, size_t dataSize);
    ~httpfile();

    const char * GetFileName() { return fileName; }
    const byte * GetData() { return data; }
    size_t GetSize() { return dataSize; }
    word GetResourceType() { return type; }
    word GetFlags() { return flags; }
    const char * GetMD5String() { return md5str; }
};
