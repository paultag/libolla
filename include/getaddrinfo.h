#ifndef _GETADDRINFO_H_
#define _GETADDRINFO_H_ I_CAN_HAS

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int getaddrinfo ( const char * node, const char * service,
    const struct addrinfo * hints, struct addrinfo ** res
);

#endif
