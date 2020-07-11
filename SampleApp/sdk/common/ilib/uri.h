/*----------------------------------------------------------------------------------------*/
/* uri.h                                                                                  */
/* copyright (c) innovaphone 2005                                                         */
/*                                                                                        */
/* uri_dissector::dissect_uri():                                                          */
/*   Simple URI parsing. A few hints can be found in RFC3986.                             */
/*   The input buffer will be left untouched.                                             */
/*   Samples of rather complicated URIs, that can be parsed here:                         */
/*   uri_dissector uri;                                                                   */
/*   uri.dissect_uri("http://admin:ip800@172.16.16.43/bla#funny?cgpn=73&cdpn=123");       */
/*   uri.dissect_uri("sip:1234@anywhere.de;user=phone");                                  */
/*                                                                                        */
/*   The result of a parsing/dissection run is a set of pointers pointing to the          */
/*   start and end of a syntactic element.                                                */
/*   E.g. "http" can be accessed by scheme and e_scheme                                   */
/*                                                                                        */
/* uri_dissector::compose():                                                              */
/*   Either compose the complete URI from what was parsed before or access single syntac- */
/*   tic elements and write them into a buffer.                                           */
/*   Samples:                                                                             */
/*   uri_dissector uri;                                                                   */
/*   char buf[256];                                                                       */
/*   uri.dissect_uri("sip:1234@anywhere.de:8888;user=phone");                             */
/*   uri.compose(buf,sizeof(buf),COMPOSE_PARAMS);   => yields "user=phone"                */
/*   uri.compose(buf,sizeof(buf),COMPOSE_USR);      => yields "1234"                      */
/*   uri.compose(buf,sizeof(buf),COMPOSE_HOST);     => yields "anywhere.de"               */
/*   uri.compose(buf,sizeof(buf),COMPOSE_PORT);     => yields "8888"                      */
/*                                                                                        */
/*   uri.dissect_uri("file:///C:/X%20and%20Y/mst/Desktop/second.txt");                    */
/*   uri.compose(buf,sizeof(buf),COMPOSE_PATH); => yields "/C:/X%20and%20Y/mst/Desktop/"  */
/*   uri.compose(buf,sizeof(buf),COMPOSE_FILE); => yields "second.txt"                    */
/*----------------------------------------------------------------------------------------*/

NAMESPACE_BEGIN

class uri_dissector {
    bool is_ip(char * startPos);

public:
	char *scheme, *e_scheme;      /* e.g.: http */
	char *hier, *e_hier;        /* hierarchy e.g.: // */
	char *usr, *e_usr;         /* user */
	char *pwd, *e_pwd;         /* password */
	char *ip, *e_ip;          /* host part is an ip address */
	char *fqdn, *e_fqdn;        /* host part is a fully qualified domain name */
	char *port, *e_port;        /* port past ip/fqdn */
	char *path, *e_path;
	char *file, *e_file;
	char *anchor, *e_anchor;      /* eg: #bla */
	char *query, *e_query;       /* '?' cgi query string */
	char *params, *e_params;      /* ';' host parameters */

	uri_dissector();

	bool dissect_uri(char *uri);
	bool path_to_argv(char *buf, int sz, int &argc, char * argv[]);
	bool querystring_to_argv(char *buf, int sz, int &argc, char * argv[]);

#define COMPOSE_SCHEME  0x01
#define COMPOSE_HIER    0x02
#define COMPOSE_USR     0x04
#define COMPOSE_PWD     0x08
#define COMPOSE_HOST    0x10
#define COMPOSE_PORT    0x20
#define COMPOSE_PATH    0x40
#define COMPOSE_FILE    0x80
#define COMPOSE_ANCHOR  0x100
#define COMPOSE_QUERY   0x200
#define COMPOSE_PARAMS  0x400

#define COMPOSE_ALL     0xFFFFFFFF
#define COMPOSE_ALL_NO_USERPWD COMPOSE_ALL&~COMPOSE_USR&~COMPOSE_PWD

	char* compose(char *buf, dword len_buf, dword flags = COMPOSE_ALL);
};

NAMESPACE_END
