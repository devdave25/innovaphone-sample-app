/*---------------------------------------------------------------------------*/
/* process.h                                                                  */
/* copyright (c) innovaphone 2015                                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/

class IProcess {
public:
    static int Spawn(const char *filename, int argc, char ** argv, class IInstanceLog * const log);					// create new child process.
    static int Kill(int pid, int signalNr, class IInstanceLog * const log);											// send a kill signal.
    static bool ProcessExist(int pid, class IInstanceLog * const log);												// check if process ID <pid> exists.
    static int GetOwnPID(class IInstanceLog * const log);
    static int GetParentPID(class IInstanceLog * const log);
    static bool SetProcessGroupID(int pid, int pgid, class IInstanceLog * const log);                               // sets the pgid of the process specified by pid
    static void GetOwnName(char * buffer, size_t len, class IInstanceLog * const log);                        // stores the name of the current process into the buffer
    static int System(class IInstanceLog * const log, const char * command, ...);
};

