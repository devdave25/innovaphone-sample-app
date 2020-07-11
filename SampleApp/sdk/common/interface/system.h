/*---------------------------------------------------------------------------*/
/* system.h                                                                  */
/* copyright (c) innovaphone 2016                                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/

typedef enum {
    ARM,
    X86_64
} architecture_t;

class ISystem {
public:
    static void GetArchitecture(char * buffer, size_t len);
    static architecture_t GetArchitecture();
    static void Sync();
    static const char * Label();
    static const char * ReleaseState();
	static bool SetBindServiceCapability(const char * path);
    static bool IsVirtualMachine();
};
