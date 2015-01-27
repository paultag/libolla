libolla
=======

So, what is libolla?
--------------------

`libolla` is a quirky little library that intercepts calls to `getaddrinfo(3)`,
and translates them according to a very simple shorthand set up in
`/etc/olla.conf`.

For instance, when running the following command (with libolla LD\_PRELOADED):

    ssh paultag@git.d.o

will connect to `git.debian.org`.

`libolla` will translate this request (transparently) (providing d.o is set up
as an alias for debian.org) `ssh` will think d.o is a valid address, since the
`getaddrinfo` call went through, so beware flaky fingerprinting / key stuff.
