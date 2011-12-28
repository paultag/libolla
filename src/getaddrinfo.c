#define _GNU_SOURCE 1
/* This horseshit hack brought to you by the fine folks over at wherever
 * the fuck this came from. This breaks in Cygwin.
 * 
 * Because fuck you, that's why.
 *  -- Someone with GNU, I'm sure.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dlfcn.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include "domain_expander.h"

int getaddrinfo ( const char * node, const char * service,
    const struct addrinfo * hints, struct addrinfo ** res
) {
    int (*orig_addr)(const char *, const char *, const struct addrinfo *,
        struct addrinfo **) = dlsym(RTLD_NEXT, "getaddrinfo");

    char * result;

    if ( expand_domain( node, &result ) > 0 ) {
        return orig_addr(result, service, hints, res );
    }

    return orig_addr(node, service, hints, res);
}
