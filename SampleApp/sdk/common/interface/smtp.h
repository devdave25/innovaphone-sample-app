
/*---------------------------------------------------------------------------*/
/* smtp.h                                                                 */
/* copyright (c) innovaphone 2016                                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/

/*#define TEXT_PLAIN      "text/plain"  //[RFC1521]
#define TEXT_HTML       "text/html"   //[RFC1866]
#define IMG_JPG         "image/jpeg"  //[RFC1521]
#define IMG_GIF         "image/gif"   //[RFC1521]
#define VIDEO_MPEG      "video/mpeg"  //[RFC1521]
#define APPLICATION_GZIP    "application/gzip"
#define APPLICATION_PDF    "application/pdf"*/


class ISmtpProvider * CreateSmtpProvider();

class ISmtpProvider {
public:
    virtual ~ISmtpProvider() {}
    virtual class ISmtp * CreateSmtp(class IIoMux * iomux, class ISocketProvider * tcpSocketProvider, class ISocketProvider * tlsSocketProvider, class IInstanceLog * const log) = 0;
};

#define smtp_ROOT 1

class ISmtp {
public:
    virtual ~ISmtp() {}
    virtual class ISmtpSend * CreateSend(const char *from, const char *fromName, const char *subject, const char *host, const char *server, const char *userSmtp, const char *password) = 0;
    virtual void SendChunk(const char *attachmentChunk, int sChunk, bool lastChunk, dword fileIndex) = 0;
};

class ISmtpSend : public ITask {
public:
    virtual void AddAttachment(const char *attachmentUrl) = 0;
    virtual void AddTo(const char *rcpt) = 0;
    virtual void AddCc(const char *rcpt) = 0;
    virtual void AddBcc(const char *rcpt) = 0;
    virtual void AddBody(const char *data, const char *format, const char *charset) = 0;
};
