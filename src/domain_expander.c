#include <stdlib.h>
#include <stdio.h>

#include "domain_expander.h"

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

int expand_domain( const char * c, char ** result ) {

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
                printf( "Expanding TLD: %s to %s\n", key, value );
                alive = 0;
                ret   = 1;
            }
        }
    }
    fclose( fd );
}

