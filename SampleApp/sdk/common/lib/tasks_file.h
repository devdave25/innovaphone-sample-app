
/*---------------------------------------------------------------------------*/
/* tasks_file.h                                                              */
/* copyright (c) innovaphone 2016                                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/

class TaskFileWrite : public STask {
    void SStart();

    char * workingPath;
    char * fileName;
    bool append;
    class IFileWrite * file;
    byte * buffer;
    unsigned length;
    bool last;

public:
    TaskFileWrite(class STaskContext * context, const char * workingPath, const char * fileName, bool append);
    ~TaskFileWrite();

    void write(byte * buffer, unsigned length, bool last);
    void writeBuffer(byte * buffer, unsigned length, bool last);
};

class TaskFileRead : public STask {
    void SStart();

    char * workingPath;
    char * fileName;
    class IFileRead * file;
    byte * buffer;
    unsigned length;
    bool last;
public:
    TaskFileRead(class STaskContext * context, const char * workingPath, const char * fileName, unsigned length, bool last);
    ~TaskFileRead();

    void read(unsigned length, bool last);
    unsigned getLength() { return length; };
    void getData(byte * buffer, unsigned length) { memcpy(buffer, this->buffer, length); };
};