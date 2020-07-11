/*---------------------------------------------------------------------------*/
/* media.h                                                                   */
/* copyright (c) innovaphone 2017                                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/

#define DEFAULT_MTU            1292
#define ETH_HEADER_LEN         14
#define IP_HEADER_LEN          20
#define UDP_HEADER_LEN          8
#define RTP_HEADER_LEN         12
#define RTCP_HEADER_LEN         8
#define RTP_H264_HEADER_LEN     2
#define TURN_HEADER_LEN         4
#define TURN_PADDING_LEN        3
#define SRTP_PADDING_LEN        3
#define SRTP_AUTH_LEN          10
#define TURN_HEADER_LEN         4
#define TURN_PADDING_LEN        3
#define DTLS_HEADER_DATA_LEN   13
#define SCTP_HEADER_DATA_LEN   28

class IMediaProvider * CreateMediaProvider();

class IMediaProvider {
public:
    virtual ~IMediaProvider() {}
    virtual class IMedia * CreateMedia(class IIoMux * const iomux, class UMedia * const user, class IInstanceLog * log) = 0;
};

enum AudioCoder {
    UNDEFINED = 0,
    G711_A,
    G711_U,
    G723_53,
    G723_63,
    G729,
    G729A,
    G729B,
    G729AB,
    G726_40,
    G726_32,
    G726_24,
    G726_16,
    GSM,
    DVI4,
    LPC,
    L16,
    ILBC,
    SPEEX,
    DTMF,
    CN,
    RED,
    G722,
    G7221,
    CLEARCHANNEL,
    OPUS_NB,
    OPUS_WB,
    AMR_WB,
};

enum VideoCoder {
    H264 = 128,
    VP8,
    VP9
};

enum AppSharingCoder {
    JRFB = 192,
};

enum MediaType {
    AUDIO = 0,
    VIDEO,
    APPSHARING,
    MP4_CONTAINER,
    WEBM_VP8_CONTAINER,
    WEBM_VP9_CONTAINER,
    APPSHARING_CONTAINER,
};

enum ConnectionType {
    REMOTE_RTP = 0,
    REMOTE_VIDEO_STREAM,
    LOCAL_VIDEO_STREAM,
};

#define CoderMediaType(c) (((c) < ((int) VideoCoder::H264)) ? MediaType::AUDIO : (((c) < ((int) AppSharingCoder::JRFB)) ? MediaType::VIDEO : MediaType::APPSHARING))

#define DEFAULT_PAYLOAD_TYPE_G711_U 0
#define DEFAULT_PAYLOAD_TYPE_G726   2
#define DEFAULT_PAYLOAD_TYPE_GSM    3
#define DEFAULT_PAYLOAD_TYPE_G723   4
#define DEFAULT_PAYLOAD_TYPE_DVI4   5
#define DEFAULT_PAYLOAD_TYPE_LPC    7
#define DEFAULT_PAYLOAD_TYPE_G711_A 8
#define DEFAULT_PAYLOAD_TYPE_G722   9
#define DEFAULT_PAYLOAD_TYPE_L16    10
#define DEFAULT_PAYLOAD_TYPE_G729   18
#define DEFAULT_PAYLOAD_TYPE_CN     19
#define DEFAULT_PAYLOAD_TYPE_DTMF   101
#define DEFAULT_PAYLOAD_TYPE_H264   102
#define DEFAULT_PAYLOAD_TYPE_VP8    107
#define DEFAULT_PAYLOAD_TYPE_VP9    108
#define DEFAULT_PAYLOAD_TYPE_OPUS   109
#define DEFAULT_PAYLOAD_TYPE_AMR    110

#define DEFAULT_SCTP_CHANNEL_NUMBER 5000

#define CHANNEL_CANDIDATE_HOST      0
#define CHANNEL_CANDIDATE_SRFLX     1
#define CHANNEL_CANDIDATE_PRFLX     2
#define CHANNEL_CANDIDATE_RELAY     3

class MediaConfiguration {
public:
    MediaConfiguration(bool turnOnly, int appSharingNumUpdates, int appSharingCaptureTimer, int appSharingBitrate, int appSharingJpegQuality, int appSharingUpdateSum, int appSharingWaitMsForAck, int mediaDropPacketsTx, int mediaDropPacketsRx, bool phoneLoad,
                       byte * cert = NULL, size_t certLen = 0) {
        this->turnOnly = turnOnly;
        this->phoneLoad = phoneLoad; 
        this->appSharingNumUpdates = appSharingNumUpdates;
        this->appSharingCaptureTimer = appSharingCaptureTimer;
        this->appSharingBitrate = appSharingBitrate;
        this->appSharingJpegQuality = appSharingJpegQuality;
        this->appSharingUpdateSum = appSharingUpdateSum;
        this->appSharingWaitMsForAck = appSharingWaitMsForAck;
        this->mediaDropPacketsTx = mediaDropPacketsTx;
        this->mediaDropPacketsRx = mediaDropPacketsRx;
        this->certLen = certLen;
        if (cert) {
            this->cert = (byte *)(malloc(certLen));
            memcpy(this->cert, cert, certLen);
        }
        else {
            this->cert = NULL;
        }
    }
    ~MediaConfiguration() {
        if (cert) free(cert);
    };

    bool turnOnly;
    int appSharingNumUpdates;
    int appSharingCaptureTimer;
    int appSharingBitrate;
    int appSharingJpegQuality;
    int appSharingUpdateSum;
    int appSharingWaitMsForAck;
    int mediaDropPacketsTx;
    int mediaDropPacketsRx;
    bool phoneLoad;
    byte * cert;
    size_t certLen;
};

// Codecs: h264, vp8, FB
class Codec: public istd::listElement<Codec> {
public:
    Codec() {
        coder = AudioCoder::UNDEFINED;
        this->addr = NULL; 
        this->mcAddr = NULL; 
    };
    ~Codec() { 
        if(addr) free(addr); 
        if(mcAddr) free(mcAddr); 
    };
public:
    int coder;
    int number;
    int xmitPacket;
    int recvPacket;
    int rate;
    char * addr;
    int port;
    char * mcAddr;
    int mcPort;
    int flags;
    int pt;
};

class IceCandidate : public istd::listElement<IceCandidate> {
public:
    IceCandidate() { 
        this->addr = NULL;
        this->relatedAddr = NULL;
        this->foundation = NULL;
        this->rtpPort = 0;
        this->rtcpPort = 0;
        this->relatedRtpPort = 0;
        this->relatedRtcpPort = 0;
        this->rtpPriority = 0;
        this->rtcpPriority = 0;
        this->type = 0;
    };
    ~IceCandidate() { 
        if(addr) free(addr);
        if(relatedAddr) free(relatedAddr);
        if(foundation) free(foundation);
    };
public:
    char * addr;
    char * relatedAddr;
    word rtpPort;
    word rtcpPort;
    word relatedRtpPort;
    word relatedRtcpPort;
    dword rtpPriority;
    dword rtcpPriority;
    dword type;
    char * foundation;
};

class IceCandidates {
public:
    IceCandidates() { 
        this->fingerprint = NULL;
        this->iceUfrag = NULL;
        this->icePwd = NULL;
        this->lIceUfrag = NULL;
        this->lIcePwd = NULL;
        this->rtcpMux = false;
    };
    ~IceCandidates() { 
        if(fingerprint) free(fingerprint);
        if(iceUfrag) free(iceUfrag);
        if(icePwd) free(icePwd);
        if(lIceUfrag) free(lIceUfrag);
        if(lIcePwd) free(lIcePwd);
        while(this->candidateList.front()) {
            delete this->candidateList.front();
        }
    };
public:
    char * fingerprint;
    char * iceUfrag;
    char * icePwd;
    char * lIceUfrag;
    char * lIcePwd;
    bool rtcpMux;
    istd::list<class IceCandidate> candidateList;
};

class MediaConfig {
public:
    MediaConfig() { this->ice = NULL; this->defAddr = NULL; this->mcAddr = NULL; this->mcPort = 0; };
    ~MediaConfig() { 
        if(ice) delete ice;
        while(this->codecList.front()) {
            delete this->codecList.front();
        }
        if(defAddr) free(defAddr);
        if(mcAddr) free(mcAddr);
    };

public:
    enum MediaType type;
    char * defAddr;
    word defPort;
    class IceCandidates * ice;
    istd::list<class Codec> codecList;
    char * mcAddr;
    word mcPort;
};

class IMedia {
public:
    virtual ~IMedia() {};
    virtual void Initialize(ISocketProvider * udpSocketProvider, ISocketProvider * tcpSocketProvider, class ISocketContext * socketContext, byte * certificateFingerprint, word minPort, word maxPort, const char * stunServers, const char * turnServers, const char * turnUsername, const char * turnPassword, enum MediaType media, bool stunSlow, bool turnOnly, int dropMediaTx, int dropMediaRx) = 0;
    virtual void Connect(class MediaConfig *remoteMediaConfig, bool iceControlling) = 0;
    virtual void RtpSend(const void * buf, size_t len, dword timestamp) = 0;
    virtual void RtpDtmf(char digit, byte pt) = 0;
    virtual void SctpSend(const void * buf, size_t len, unsigned num) = 0;
    virtual void Recv(void * buf, size_t len, bool recvPartial = false) = 0;
    virtual void Close() = 0;
};

enum MediaEndpointEvent {
    CHANNEL_FULL_INTRA_REQUEST = 0,
};

class UMedia {
public:
    virtual void MediaInitializeComplete(IMedia * const media, class MediaConfig *localMediaConfig) {};
    virtual void MediaConnectResult(IMedia * const media, const char * error) {};
    virtual void MediaRtpSendResult(IMedia * const media) {};
    virtual void MediaSctpSendResult(IMedia * const media) {};
    virtual void MediaRtpRecvResult(IMedia * const media, void * buf, size_t len, dword timestamp) {};
    virtual void MediaSctpRecvResult(IMedia * const media, void * buf, size_t len) {};
    virtual void MediaSctpRecvAck(IMedia * const media, unsigned num) {};
    virtual void MediaCloseComplete(IMedia * const media) {};
    virtual void MediaEventReceived(IMedia * const media, enum MediaEndpointEvent event) {};
    virtual void MediaRtpRecv(IMedia * const media, const char * src_addr, word src_port, dword ssrc, word pt) {};
    virtual void MediaRtpDtmfNearStart(char digit) {};
    virtual void MediaRtpDtmfNear(char digit) {};
};

class IMediaEndpoint {
public:
    virtual ~IMediaEndpoint() {};
    virtual void Recv(char * buf, int len, dword timestamp, short sequenceNumberDiff, bool marker) = 0;
    virtual void Send(char * buf, int len, dword timestamp, unsigned num) = 0;
};

class UMediaEndpoint {
public:
    virtual void RtpRecvResult(char * buf, int len, dword timestamp) {};
    virtual void RtpSendResult() {};
    virtual void RtpSend(char * buf, int len, dword timestamp, bool marker = false) = 0;
    virtual void RtcpSend(char * buf, int len) = 0;
    virtual void SctpRecvResult(char * buf, int len) {};
    virtual void SctpRecvAck(unsigned num) {};
    virtual void SctpSendResult() {};
    virtual void SctpSend(char * buf, int len, unsigned num) = 0;
};

class IMediaIoChannel {
public:
    virtual ~IMediaIoChannel() {};
    virtual void Open() = 0;
    virtual void RtpRecv(void * buf, size_t len, dword timestamp) = 0;
    virtual void RtpSendResult() {};
    virtual void SctpRecv(void * buf, size_t len) = 0;
    virtual void SctpRecvAck(unsigned num) {};
    virtual void SctpSendResult() {};
    virtual void Close() = 0;
    virtual void EventRecv(enum MediaEndpointEvent event) = 0;
};

class UMediaIoChannel {
public:
    virtual void MediaIoRtpSend(const void * buf, size_t len, dword timestamp) = 0;
    virtual void MediaIoSctpSend(const void * buf, size_t len, unsigned num) = 0;
    virtual void MediaIoCloseComplete(class IMediaIoChannel * const mediaIoChannel) = 0;
};

class IDeviceIo {
public:
    virtual void QueryDevices(void * context) = 0; // Calls DeviceAdded() for all present devices.
    virtual const char * StartDevice(void * context, const char *deviceId, int deviceMode) = 0;
    virtual void StopDevice(void * context, const char *deviceId) = 0;
};

class UDeviceIo {
public:
    virtual void MediaIoDeviceAdded(IDeviceIo * deviceIo, void * context, const char *deviceId, int deviceType, unsigned deviceCapabilities, const char *deviceName) = 0;
    virtual void MediaIoDeviceRemoved(IDeviceIo * deviceIo, void * context, const char *deviceId) = 0;
    virtual void MediaIoQueryDevicesResult(IDeviceIo * deviceIo, void * context) = 0;
};

class IAudioIoChannel : public IMediaIoChannel {
public:
    static class IAudioIoChannel * Create(class IAudioIo * audioIo, class UMediaIoChannel * const user);
    static unsigned AvailableCoderCount();
    static enum AudioCoder AvailableCoder(unsigned coderNumber);
    virtual ~IAudioIoChannel() {};
    virtual void Initialize(enum AudioCoder coder, bool sc, unsigned mediaPacketizationMs, unsigned execInterval8khz,
        unsigned execJitter8khz, unsigned pullSampleRate, unsigned putSampleRate) = 0;
    virtual bool Pull() = 0;
    virtual const short *PulledSamples() = 0;
    virtual const short *FeedbackSamples() = 0;
    virtual void PutSamples(const short *buffer) = 0;
};

#define AUDIO_IO_DUAL_TONE_MODULATE     0x00000001
#define AUDIO_IO_DUAL_TONE_LOOP         0x00000002
#define AUDIO_IO_DUAL_TONE_AUTOOFF      0x00000004
#define AUDIO_IO_DUAL_TONE_PASSTHROUGH  0x00000008
#define AUDIO_IO_DUAL_TONE_PEER         0x00000010 /* local / peer */
#define AUDIO_IO_DUAL_TONE_BOTH         0x00000020 /* local + full peer / peer + attenuated local */

struct AudioIoDualTone {
    word onTimeMs;
    word offTimeMs;
    word frequency0; /* Hz */
    short level0; /* (0x8000:-infinity, 0x8001:-127.996 dBm ... 0x7fff:127.996 dBm) */
    word frequency1; /* Hz */
    short level1; /* (0x8000:-infinity, 0x8001:-127.996 dBm ... 0x7fff:127.996 dBm) */
};

class IAudioIo : public IDeviceIo {
public:
    static class IAudioIo * Create(class IIoMux * const iomux, class IAudioPhone * const audioPhone, unsigned execInterval8khz);
    virtual ~IAudioIo() {};
    virtual class IAudioPhone *Initialize(class UAudioIo * const user, class UDeviceIo * const deviceIoUser) = 0;
    virtual void AudioExec(class IAudioExec *audioExec) = 0;

    virtual void StartMonitoring(const char *deviceId, int deviceMode) = 0;
    virtual void StopMonitoring(const char *deviceId) = 0;

    virtual void StartHookDevice(const char *deviceId) = 0;
    virtual void StopHookDevice(const char *deviceId) = 0;
    virtual void SendHookKey(const char *deviceId, byte key, byte callId) = 0;

    virtual void Mute(bool microphone, bool speaker) = 0;

    virtual void StartDualTones(dword toneFlags, unsigned toneCount, const struct AudioIoDualTone *tones) = 0;
    virtual void StopDualTones() = 0;

    virtual class IAudioIoChannel *CreateChannel(class UMediaIoChannel * const user) = 0;
    virtual void InitializeChannel(class IAudioIoChannel *audioIoChannel, enum AudioCoder coder, bool sc, unsigned mediaPacketizationMs) = 0;

    virtual void ChannelOpened(class IAudioIoChannel *audioIoChannel) = 0;
    virtual void ChannelClosed(class IAudioIoChannel *audioIoChannel) = 0;
    virtual void ChannelDestroyed(class IAudioIoChannel *audioIoChannel) = 0;

    virtual void Close(class UAudioIo * user) = 0;
};

class UAudioIo {
public:
    virtual void HookKeyReceived(IAudioIo * audioIo, const char *deviceId, byte key) = 0;
    virtual void CloseAudioIoComplete() = 0;
};

enum VideoDeviceType {
    Webcam = 128,
    VideoScreen,
};

class IVideoIoChannel : public IMediaIoChannel {
public:
    static class IVideoIoChannel * Create(class IIoMux * const iomux, class IVideoIo * videoIo, class UMediaIoChannel * const user, class IInstanceLog * log);
    static unsigned AvailableCoderCount();
    static enum VideoCoder AvailableCoder(unsigned coderNumber);
    virtual ~IVideoIoChannel() {};
    virtual void Initialize(void * context, const char * channelId, enum VideoCoder coder, ConnectionType connType) = 0;
};

class IVideoIo : public IDeviceIo {
public:
    static class IVideoIo * Create(class IIoMux * const iomux, class IInstanceLog * log);
    virtual ~IVideoIo() {};
    virtual void Initialize(class UVideoIo * const user, class UDeviceIo * const deviceIoUser) = 0;
    virtual void AddLocalContainer(void * context, void * container, enum MediaType coder) = 0;
    virtual void RemoveLocalContainer(void * container, enum MediaType coder) = 0;
    virtual void AddRemoteContainer(void * context, void * container, const char * channelId, enum MediaType coder) = 0;
    virtual void RemoveRemoteContainer(void * container, enum MediaType coder) = 0;
    virtual void StartVideoEncoder(void * context, const char * channelId, int codec) = 0;
    virtual void Close() = 0;
};

class UVideoIo {
public:
    virtual void CloseVideoIoComplete() = 0;
    virtual void MediaIoVideoContainerSend(const void * buf, size_t len, dword timestamp, const void * context, bool local, enum MediaType type) = 0;
    virtual void MediaIoVideoContainerInit(const void * context, bool local, enum MediaType type) = 0;
};

enum AppSharingDeviceType {
    FrameBuffer = 192,
    Canvas,
};

class IAppSharingIoChannel : public IMediaIoChannel {
public:
    static class IAppSharingIoChannel * Create(class IIoMux * const iomux, class IAppSharingIo * appSharingIo, class UMediaIoChannel * const user, class IInstanceLog * log, const char * dn);
    static unsigned AvailableCoderCount();
    static enum AppSharingCoder AvailableCoder(unsigned coderNumber);
    virtual ~IAppSharingIoChannel() {};
    virtual void Initialize(void * context, const char * channelId, enum AppSharingCoder coder) = 0;
};

class IAppSharingIo : public IDeviceIo {
public:
    static class IAppSharingIo * Create(class IIoMux * const iomux, class IInstanceLog * log, class MediaConfiguration * mediaConfiguration);
    virtual ~IAppSharingIo() {};
    virtual void Initialize(class UAppSharingIo * const user, class UDeviceIo * const deviceIoUser) = 0;
    virtual void SignalingMessage(void * context, void * buffer, int len) = 0;
    virtual void SubscribeApplications() = 0;
    virtual void UnsubscribeApplications() = 0;
    virtual void ShareApplication(void * context, unsigned int id) = 0;
    virtual void UnshareApplication(void * context, unsigned int id) = 0;
    virtual void UnshareAllApplications(void * context) = 0;
    virtual void GiveControlToUser(void * context, unsigned int sessionId) = 0;
    virtual void RemoveControlFromUser(void * context, unsigned int sessionId) = 0;
    virtual void RequestControlFromUser(void * context, unsigned int sessionId) = 0;
    virtual void AddRemoteContainer(void * context, void * container, const char * channelId, enum MediaType coder) = 0;
    virtual void RemoveRemoteContainer(void * container, enum MediaType coder) = 0;
    virtual void Close() = 0;
};

class UAppSharingIo {
public:
    virtual void AddAppSharingApplication(unsigned int id, const char * name, const char * desc, const char * icon,  const char * thumbnail) = 0;
    virtual void RemoveAppSharingApplication(unsigned int id) = 0;
    virtual void UpdateAppSharingApplication(unsigned int id, const char * name, const char * desc, const char * icon,  const char * thumbnail) = 0;
    virtual void CloseAppSharingIoComplete() = 0;
    virtual void MediaIoAppSharingContainerSend(const void * buf, size_t len, dword timestamp, const void * context, bool local, enum MediaType type) = 0;
    virtual void RequestAppSharingControl(unsigned int userId) = 0;
};

class IJitterBuffer {
public:
    static IJitterBuffer * Create(class UJitterBuffer * user);
    virtual ~IJitterBuffer() {};

    virtual unsigned Configure(enum AudioCoder coder, unsigned mediaPacketizationMs, unsigned pullInterval8khz,
        unsigned minBufferMs, unsigned initialBufferMs, unsigned maxBufferMs) = 0;
    virtual void Adjust(unsigned initialBufferMs) = 0;
    virtual unsigned GetDelay() = 0;
    virtual void Push(const void * buf, size_t len, dword timestamp) = 0;
    virtual bool Pull(bool discard) = 0;
};

class UJitterBuffer {
public:
    virtual void JitterBufferPulled(IJitterBuffer * const jitterBuffer, const void * buf, size_t len) = 0;
};

class ISrtpSession {
public:
    static ISrtpSession * Create(byte * srtpMasterkey, byte * srtpMastersalt, const char * profile);
    virtual ~ISrtpSession() {};

    virtual byte * Protect(byte * header, int hLen, byte * payload, int pLen, int * olen) = 0;
    virtual int Unprotect(char * srtpPacket, int len) = 0;
    virtual byte * SrtcpProtect(byte * rtcpPacket, int pLen, int * olen) = 0;
    virtual int SrtcpUnprotect(char * srtcpPacket, int len) = 0;
};

class UMediaContainer {
public:
    virtual void ContainerSample(char * buf, int len) = 0;
};

class IMediaContainer {
public:
    virtual ~IMediaContainer() {};
    virtual void PutSample(char * buf, int len, dword timestamp) = 0;
    virtual void Initialize(void) = 0;
};

enum VideoFormat {
    VIDEO_FORMAT_UNKNOWN = 0,
    VIDEO_FORMAT_RGB24,
    VIDEO_FORMAT_RGB32,
    VIDEO_FORMAT_NV12,
    VIDEO_FORMAT_YUY2,
    VIDEO_FORMAT_I420,
    VIDEO_FORMAT_YV12,
    VIDEO_FORMAT_IYUV
};

enum VideoInterlaceMode {
    VIDEO_INTERLACE_Unknown = 0,
    VIDEO_INTERLACE_Progressive = 1,
    VIDEO_INTERLACE_FieldInterleavedUpperFirst = 2,
    VIDEO_INTERLACE_FieldInterleavedLowerFirst = 3,
    VIDEO_INTERLACE_FieldSingleUpper = 4,
    VIDEO_INTERLACE_FieldSingleLower = 5,
    VIDEO_INTERLACE_MixedInterlaceOrProgressive	= 6
};

struct VideoRatio {
    int numerator;
    int denominator;
};

struct VideoFrameFormat {
    int width;
    int height;
    int stride;
    int averageBitrate;
    int sampleSize;
    enum VideoFormat format;
    enum VideoInterlaceMode interlace;
    struct VideoRatio frameRate;
    struct VideoRatio aspectRatio;
};

class IWebcam {
public:
    virtual ~IWebcam() {};
    virtual struct VideoFrameFormat * Start() = 0;
    virtual void Stop() = 0;
    virtual void Close() = 0;
    virtual const char * GetWebcamId() = 0;
    virtual const char * GetWebcamName() = 0;
    virtual void FullIntraRequest() {};
};

class UWebcam {
public:
    virtual void WebcamVideoFormat(class IWebcam * const webcam, const struct VideoFrameFormat * format) = 0;
    virtual void WebcamSample(class IWebcam * const webcam, const void * buf, int len, dword timestamp, dword duration, const struct VideoFrameFormat * format) = 0;
};

class IWebcamProvider {
public:
    static class IWebcamProvider * Create(class IIoMux * const iomux, class UWebcamProvider * const webcamProviderUser, class UWebcam * const webcamUser, class IInstanceLog * const log);
    virtual ~IWebcamProvider() {};
    virtual void QueryDevices(void * context) = 0;
    virtual void Close() = 0;
};

class UWebcamProvider {
public:
    virtual void WebcamLost(class IWebcam * const webcam, void * context) = 0;
    virtual void WebcamAdded(class IWebcam * const webcam, void * context) = 0;
    virtual void WebcamQueryResult(void * context) = 0;
    virtual void WebcamClosed(class IWebcam * const webcam) = 0;
    virtual void WebcamProviderCloseResult() = 0;
};

class IMediaEncoder
{
public:
    static class IMediaEncoder * Create(class IIoMux * const iomux, class UMediaEncoder * const user, class IInstanceLog * log, enum VideoCoder coder);
    virtual ~IMediaEncoder() {};
    virtual bool Initialize(struct VideoFrameFormat * const format) = 0;
    virtual void Encode(const void * buf, int len, dword timestamp, dword duration, const struct VideoFrameFormat * f) = 0;
    virtual bool FullIntraRequest() = 0;
    virtual void Close() = 0;
};

class UMediaEncoder
{
public:
    virtual void EncodeResult(class IMediaEncoder * encoder, const void * buf, int len, dword timestamp, dword duration) = 0;
    virtual void MediaEncoderCloseResult(class IMediaEncoder * encoder) = 0;
};

class IMediaDecoder
{
public:
    static class IMediaDecoder * Create(class IIoMux * const iomux, class UMediaDecoder * const user, class IInstanceLog * log, enum VideoCoder coder);
    virtual ~IMediaDecoder() {};
    virtual void Decode(const void *buf, int len, dword timestamp) = 0;
    virtual void Close() = 0;
};

class UMediaDecoder
{
public:
    virtual void DecodeResult(class IMediaDecoder * decoder, const void * buf, int len, dword timestamp, dword duration, struct VideoFrameFormat * f) = 0;
    virtual void MediaDecoderCloseResult(class IMediaDecoder * decoder) = 0;
};
