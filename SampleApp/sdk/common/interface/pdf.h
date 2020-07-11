/*---------------------------------------------------------------------------*/
/* pdf.h                                                                     */
/* copyright (c) innovaphone 2017                                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/

class IPdfProvider * CreatePdfProvider();

class IPdfProvider {
public:
    virtual ~IPdfProvider() { };
    virtual class IPdf * CreatePdf() = 0;
};

class IPdf {
public:
    virtual ~IPdf() { };

    enum Compressions {
        CompressionNone     = 0x0,
        CompressionText     = 0x1,
        CompressionImage    = 0x2,
        CompressionMetaData = 0x4,
        CompressionAll      = 0xf,
    };
    enum Directions {
        DirectionPortrait,
        DirectionLandscape,
    };
    enum Sizes {
        SizeA4,
    };
    enum StreamTypes {
        StreamTypeCcittG31D,
    };

    virtual void SetCompressionMode(unsigned compressionMode) = 0;

    virtual class IPdfPage * AddPage(enum IPdf::Sizes size = IPdf::SizeA4, 
                                     enum IPdf::Directions direction = IPdf::DirectionPortrait) = 0;
    virtual void Complete() = 0;
    virtual void Get(const byte * & data, unsigned & length, bool * last = 0) = 0;
};

class IPdfPage {
public:
    virtual ~IPdfPage() { };

    virtual void SetSize(enum IPdf::Sizes size) = 0;
    virtual void SetDirection(enum IPdf::Directions direction) = 0;
    virtual float GetWidth() = 0;
    virtual float GetHeight() = 0;

    virtual class IPdfImageStream * AddImageStream(enum IPdf::StreamTypes type) = 0;

    virtual void Complete() = 0;
};

class IPdfImageStream {
public:
    virtual ~IPdfImageStream() { };

    virtual void Write(const byte * data, unsigned length) = 0;
    virtual void SetStreamWidth(unsigned int width) = 0;
    virtual void SetStreamHeight(unsigned int height) = 0;
    virtual void Draw(float x, float y, float width, float height) = 0;
};

