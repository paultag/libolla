libolla
=======

So, what is libolla?
--------------------

`libolla` is a quirky little library that intercepts calls to `getaddrinfo(3)`,
and translates them according to a very simple shorthand set up in
`/etc/olla.conf`.

For instance, when running the following command (with libolla LD\_PRELOADED):

    ssh paultag-guest@git.d.o

will connect to `git.debian.org`.

`libolla` will translate this request (transparently) (providing d.o is set up
as an alias for debian.org) `ssh` will think d.o is a valid address, since the
`getaddrinfo` call went through, so beware flaky fingerprinting / key stuff.

Why is this not GPL'd?
----------------------

Well, simple answer - since this is made to be pre-loaded against applications
which might not be GPL compatable, this may (under some readings of the GPL)
count as linking against the library (or at the least, sharing memory), which
may in fact (INAL) create a situation where the user is violating the GPL during
it's intended use - rather then protecting you, it may open you up to legal
grey-areas.

I do encourage you to consider using the GPL for other projects, the concept
of copyleft is in fact very important to end users.

The shame of it is that in this very odd case, the GPL may actually expose the
user to more risk then a non-GPL license.

I also do acknowlage that the LGPL may be a good fit for this, but I've just
gone Expat.
