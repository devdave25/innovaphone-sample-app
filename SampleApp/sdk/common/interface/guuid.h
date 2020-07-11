/*---------------------------------------------------------------------------*/
/* guuid.h                                                                  */
/* copyright (c) innovaphone 2015                                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/

#define GUID_SIZE   37

typedef struct { byte b[16]; } OS_GUID;

class IGuuid{

public:
    static void GenerateUUID(char * uid);
    static void GenerateBinaryUUID(OS_GUID * uid);
};