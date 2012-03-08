/*
 * Copyright (c) 2011 Paul Tagliamonte <tag@pault.ag>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#define _GNU_SOURCE 1
/* This horseshit hack brought to you by the fine folks over at wherever
 * the fuck this came from. This breaks in Cygwin. Not that that really
 * matters in this small case.
 *
 * Because fuck you, that's why.
 *  -- Someone with GNU, I'm sure.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dlfcn.h>

#include "domain_expander.h"
#include "getaddrinfo.h"

/**
 * POSIX call to resolve a DNS name to all sorts of different goodies.
 *
 * This function will mangle the `node` param into something which can be
 * actually resolved, in the case of shorthand addresses. In the case we can't
 * mangle, we'll pass through. Otherwise, we pass the mangled address back to
 * the system default lib.
 *
 * @param node address to resolve
 * @param service same as the backing impl
 * @param hints same as the backing impl
 * @param res same as the backing impl
 */
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
