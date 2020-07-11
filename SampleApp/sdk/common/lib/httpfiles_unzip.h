/*---------------------------------------------------------------------------*/
/* httpfiles_unzip.h                                                         */
/* copyright (c) innovaphone 2018                                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/


class Httpfiles_unzipItem : public istd::listElement<Httpfiles_unzipItem>
{
    class httpfile * file;
    byte * data;
    char * path;
public:
    Httpfiles_unzipItem(char * filePath, byte * fileData, size_t fileLength);
    ~Httpfiles_unzipItem();
};

class Httpfiles_unzip 
{
    class IInstanceLog * log;
    void ScanFiles(class IDirectory * dir, char * absoluteFilePath, char * filePath);
    void ReadFile(char * path, char * name);
    class istd::list<Httpfiles_unzipItem> listItems;
public:
    Httpfiles_unzip(class IInstanceLog * log, const char * appName);
    ~Httpfiles_unzip();
    
};

