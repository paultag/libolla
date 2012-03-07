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

#include <stdlib.h>
#include <stdio.h>

#include "domain_expander.h"

/**
 * Fetch a substring of a given string. Please note that this doesn't return a
 * char pointer, rather it returns a bool. Please pass in the result into
 * the function.
 *
 * @param host string to get the substring *out* of
 * @param res where we should copy the output *to* (unmalloc'd please)
 * @param start index to start from
 * @param len length of the substring
 * @return 1 on success, <= 0 on failure.
 */
int substr( const char * host, char ** res, int start, int len ) {
    if ( strlen( host ) < start + len ) {
        return -1;
    }

    char * result = malloc( sizeof(char) * ( len + 1 ));

    int i;
    for ( i = start; i < ( start + len ); ++i ) {
        result[i - start] = host[i];
    }
    result[i - start] = '\0';

    *res = result;

    return 1;
}

/**
 * Check the ending of a string
 *
 * @warning internal use only
 *
 * @param host string to check
 * @param tld  string to check if the host ends with
 * @param expand not sure. do we need this?
 * @return 1 if host ends with tld, otherwise <= 0
 *
 */
int _check_ender( const char * host, const char * tld, const char * expand ) {
    char * res;
    if ( substr( host, &res, (strlen(host) - strlen(tld)), strlen(tld) ) ) {
        if ( strcmp( res, tld ) == 0 ) {
            return 1;
        } else {
            return -1;
        }
    } else {
        return -2;
    }
}

/**
 * Expand a hostname into it's fqdn
 *
 * @warning internal use only
 *
 * @param c char to mangle
 * @param result where to put the mangled hostname
 * @param tld thing to expand
 * @param domain what to expand tld to
 *
 */
int _inner_expand( const char * c, char ** result,
    const char * tld, const char * domain
) {
    if ( _check_ender( c, tld, domain ) > 0 ) {
        char * subdomain;
        substr( c, &subdomain, 0, (strlen(c) - strlen(tld)) );
        *result = malloc( sizeof(char) * strlen(subdomain) + strlen(domain));
        strcpy( *result, subdomain );
        strcat( *result, domain );
        return 1;
    } else {
        return -1;
    }
}

/**
 * Expand a domain name as expected
 *
 * @param c thing to expand
 * @param result where to put the result
 *
 */
int expand_domain( const char * c, char ** result ) {

    if ( c == NULL )
        return -1;

    int ret = -1;

    char line[256];
    FILE * fd;

    fd = fopen( "/etc/olla.conf", "r" );
    if ( ! fd ) {
        return -1;
    }

    int alive = 1;

    while ( fgets( line, sizeof(line), fd) != NULL && alive ) {
        char * key   = strtok(line, ":");
        char * value = strtok(NULL, ":");

        if ( key != NULL && value != NULL ) {

            int vlen = strlen(value) - 1;
            if ( value[vlen] == '\n' ) {
                value[vlen] = '\0';
            }

            int rez = _inner_expand( c, result, key, value );

            if ( rez > 0 ) {
                alive = 0;
                ret   = 1;
            }
        }
    }
    fclose( fd );

    return ret;
}

