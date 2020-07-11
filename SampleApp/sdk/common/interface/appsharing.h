/*---------------------------------------------------------------------------*/
/* appsharing.h                                                              */
/* copyright (c) innovaphone 2018                                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/

enum MessageMouseType {
    LBUTTONDOWN = 0,
    LBUTTONUP,
    LBUTTONDOWNDBLCLK,
    RBUTTONDOWN,
    RBUTTONUP,
    RBUTTONDOWNDBLCLK,
    MOUSEMOVE,
    MOUSEWHEEL,
    KEYPRESSED,
    KEYPRESSED_DOWN,
    KEYPRESSED_DOWN_UP,
    KEYPRESSED_UP,
    STOP_HOOK,
    STOP_HOOK_THREAD
};

#define REMOTE_CONTROL_MSG_TYPE  0
#define REMOTE_CONTROL_X_COOR    1
#define REMOTE_CONTROL_Y_COOR    3
#define REMOTE_CONTROL_X_DIM     5
#define REMOTE_CONTROL_Y_DIM     9
#define REMOTE_CONTROL_VK       13
#define REMOTE_CONTROL_UNICODE  15

enum MouseType {
    Arrow = 0,
    Hand,
    Wait,
    AppStarting,
    Ibeam,
    Cross,
    Help,
    No,
    SizeAll,
    SizeWs,
    SizeNwse,
    SizeWe,
    UpArrow
};

enum CompressionType {
    PNG = 0,
    JPEG
};

#define JPEG_MIN_SIZE   4
#define PNG_MIN_SIZE   45  // 33 + 12 header + end chunk

static const byte jpegHeader[2] = { 0xFF, 0xD8 };  // JPEG, Start of Image
static const byte pngHeader[8] = { 0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A };  // PNG
static const byte pngHeader2[8] = { 0x00, 0x00, 0x00, 0x0D, 0x49, 0x48, 0x44, 0x52 }; // IHDR

struct Png_infos {
    char name_png[256];
    int offset_png; //where we stopped last time we read the "file"
    unsigned char *datas_png;
};

typedef struct pixel_ {
    byte blue;
    byte green;
    byte red;
    byte alpha;
} pixel_t;

typedef struct rgb_ {
    byte blue;
    byte green;
    byte red;
} rgb_t;

#define NUM_STANDARD_CURSORS      14
#define NUM_NON_STANDARD_CURSORS  5

enum AppSharingMessages {
   CREATE_SESSION = 0x0,
   CREATE_SESSION_ACK,
   DELETE_SESSION,
   DELETE_SESSION_ACK,
   UPDATE_SESSION,
   UPDATE_SESSION_ACK,
   IMAGE_MESSAGE,
   IMAGE_MESSAGE_ACK,
   MOUSE_CURSOR,
   MOUSE_MOVE,
   INFO_MESSAGE,
   INFO_MESSAGE_ACK,
   LOW_QUALITY_IMAGE_MESSAGE,
};

class UImageBuffer {
public:
    virtual void Add(unsigned int id, const char * name, const char * description, const char * icon,  const char * thumbnail, void * handle) {};
    virtual void Update(unsigned int id, const char * name, const char * description, const char * icon,  const char * thumbnail) {};
    virtual void Remove(unsigned int id) {};
    virtual void MousePosition(int coorX, int coorY, int type, unsigned int appId) = 0;
    virtual void CloseComplete() {};
};


class IImageBuffer {
public:
    static IImageBuffer * CreateImageBuffer(class IIoMux * const iomux, class UImageBuffer * const user, class IInstanceLog * const log, class MediaConfiguration * mediaConfiguration);

    virtual ~IImageBuffer() {};
    virtual void Capture(unsigned int appId, class IScreenBuffer * screenBuffer) = 0;  // MakeCapture, CreateDiffBlocks and CompressDiffBlocks

    virtual bool Mark(unsigned int appId, int coorX, int coorY, int dimX, int dimY) = 0;
    virtual void Clean(unsigned int appId) = 0;
    virtual bool GetWindowPosition(byte appId, word * x, word * y, int * aspectRatio) = 0;

    virtual void SubscribeApplications(void) = 0;
    virtual void UnsubscribeApplications(void) = 0;

    virtual void CloseImageBuffer(void) = 0;
};

class IImage {
public:
    IImage(unsigned char *buf, int len) {
        this->buf = buf;
        this->len = len;
        this->version = 0;
        this->update = 0;
        this->posX = 0; 
        this->posY = 0;
        this->dimX = 128;
        this->dimY = 128;
        this->type = CompressionType::JPEG;
    };
    ~IImage() { if(this->buf) free(this->buf); };

    int x;
    int y;
    int posX;
    int posY;
    int dimX;
    int dimY;
    int version;
    int update;
    CompressionType type;
    unsigned char *buf;
    int len;
};

class ILowQualityImage {
public:
    ILowQualityImage(unsigned char *buf, int len) {
        this->buf = buf;
        this->len = len;
        this->type = CompressionType::JPEG;
    };
    ~ILowQualityImage() { if(this->buf) free(this->buf); };

    CompressionType type;
    unsigned char *buf;
    int len;
};

#define MAX_X_BLOCKS 30
#define MAX_Y_BLOCKS 17

class IScreenBuffer {
public:
    static IScreenBuffer * Create(class IInstanceLog * const log);
    virtual ~IScreenBuffer() {}

    // Stores a new version of a block or an update of an existing block
    // Called by an image source (capture, unreliable network transmission)
    // Drop blocks and updates with an older version
    // Queue updates that need the block with the right version or previous updates
    // Only trigger calls in IScreenSink for the consistent part of the current block
    //virtual void Set(byte x, byte y, class IImage * image, byte version, byte update) = 0;
    virtual void Set(class IImage * image) = 0;

    virtual void Set(class ILowQualityImage * image) = 0;

    // Returns the number of updates of the specified block
    // Called by IScreenSink to get the image for displaying or network transmission
    virtual byte GetNumUpdates(byte x, byte y) = 0;

    // Returns the current version of the specified block
    // Called by IScreenSink to get the image for displaying or network transmission
    virtual class IImage * Get(byte x, byte y) = 0;

    // Returns the specified update of the specified block
    // Called by IScreenSink to get the image for displaying or network transmission
    virtual class IImage * GetUpdate(byte x, byte y, byte update) = 0;

    virtual void RegisterScreenSink(class IScreenSink * sink) = 0;
    virtual void UnregisterScreenSink(class IScreenSink * sink) = 0;

    virtual void UpdateAppResolution(int w, int h) = 0;
};

class IScreenSink {
public:
    static IScreenSink * Create(class IIoMux * const iomux, class UScreenSink * const user, class IScreenBuffer * const screenBuffer, byte sessionId, int bitrate, int waitingMsForAck, const char * appName, const char * appDesc, const char * senderName, class IInstanceLog * const log);
    virtual ~IScreenSink() {}

    // Notification that a new version of a block is ready for displaying / transmission
    // Senders should mark this block version in the local state
    virtual void ImageAdded(byte x, byte y, byte version) {};
    virtual void LowQualityImage(class ILowQualityImage * image) {};

    // Notification that a new update of a block is ready for displaying / transmission
    // Senders should mark this update in the local state
    virtual void ImageUpdated(byte x, byte y, byte update) {};

    virtual void UpdateAppResolution(int w, int h) {};

    virtual void Recv(void * buf, int len) {};
    virtual void RecvAck(unsigned num) {};

    virtual void Stop() {};
};

class UScreenSink {
public:
    virtual void SendSinkMessage(void * buf, size_t len, unsigned num) = 0;
    virtual void ReceiveMessage(void * buf, size_t len) = 0;
};

class IRemoteControl {
public:
    static IRemoteControl * Create(class URemoteControl * const user, class IInstanceLog * const log);
    virtual ~IRemoteControl() {}

    virtual void SendCommand(word coorX, word coorY, int aspectRatio, const char * cmd, int len) = 0;
    virtual void MouseMove(word coorX, word coorY, word rPosX, word rPosY, word posX, word posY, int aspectRatio) = 0;
    virtual void Close() = 0;
};

class URemoteControl {
public:
    virtual void RemoteControlCloseComplete() = 0;
};
