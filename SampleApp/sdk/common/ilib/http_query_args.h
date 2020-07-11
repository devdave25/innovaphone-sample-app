
/*---------------------------------------------------------------------------*/
/* http_query_args.h                                                         */
/* copyright (c) innovaphone 2016                                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/
NAMESPACE_BEGIN
class HttpQueryArg{
public:
    char * name;
    char * value;

    HttpQueryArg();
};

class HttpQueryArgs
{
    char * query;
    char * pos;
    class HttpQueryArg current;

    class HttpQueryArg * Reset();

public:
    HttpQueryArgs(char * query);

    class HttpQueryArg * Current();
    class HttpQueryArg * Next();
};
NAMESPACE_END
