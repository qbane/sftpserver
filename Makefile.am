# This file is part of the Green End SFTP Server.
# Copyright (C) 2007, 2011,14,16,18 Richard Kettlewell
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
# USA

AM_CPPFLAGS=-DETCDIR=\"$(ETCDIR)\"

# Programs
noinst_PROGRAMS=sftpclient pwtest
noinst_SCRIPTS=run-tests
libexec_PROGRAMS=gesftpserver
noinst_LIBRARIES=libsftp.a

gesftpserver_SOURCES=sftpserver.c readwrite.c
gesftpserver_LDADD=libsftp.a

sftpclient_SOURCES=sftpclient.c readwrite.c
sftpclient_LDADD=libsftp.a $(LIBREADLINE)

libsftp_a_SOURCES=alloc.c alloc.h debug.c debug.h globals.h handle.c	\
handle.h parse.c parse.h queue.c queue.h send.c send.h sftp.h		\
sftpclient.h sftpcommon.h sftpserver.h status.c thread.h types.h	\
users.c users.h utils.c utils.h v3.c xfns.c xfns.h stat.c charset.c	\
charset.h serialize.h serialize.c v4.c realpath.c readlink.c v5.c v6.c	\
stat.h getcwd.c globals.c dirname.c putword.h replaced.h \
sftpconf.c sftpconf.h
libsftp_a_LIBADD=$(LIBOBJS)

pwtest_SOURCES=pwtest.c

# Documentation
man_MANS=gesftpserver.8

gesftpserver.8: gesftpserver.8.in config.status
	sed < ${srcdir}/gesftpserver.8.in > $@.new \
		-e "s,__libexecdir__,${libexecdir},g"
	mv $@.new $@

# Build and test
all: ${SEDOUTPUTS}

check: gesftpserver sftpclient pwtest aliases
	rm -f *.gcda *.gcov
	./pwtest
	srcdir=${srcdir} ${PYTHON3} ${srcdir}/run-tests --directory tests $(TESTS)
	srcdir=${srcdir} ${PYTHON3} ${srcdir}/run-tests --directory tests --no-reorder $(TESTS)
	srcdir=${srcdir} ${PYTHON3} ${srcdir}/run-tests --directory tests --threads 1 $(TESTS)
	srcdir=${srcdir} ${PYTHON3} ${srcdir}/run-tests --directory rotests --server ./gesftpserver-ro $(ROTESTS)
	${GCOV} ${srcdir}/*.c  | ${PYTHON3} ${srcdir}/format-gconv-report --html .

#${srcdir}/paramiko-test

check-valgrind: gesftpserver-valgrind sftpclient-valgrind pwtest aliases
	rm -f ,valgrind*
	srcdir=${srcdir} ${PYTHON3} ${srcdir}/run-tests --debug --directory tests --server ./gesftpserver-valgrind --client ./sftpclient-valgrind $(TESTS)

aliases: gesftpserver-ro gesftpserver-debug gesftpserver-ro-debug \
		gesftpserver-valgrind

gesftpserver-ro:
	rm -f $@
	ln -s gesftpserver $@

gesftpserver-debug:
	rm -f $@
	ln -s gesftpserver $@

gesftpserver-ro-debug:
	rm -f $@
	ln -s gesftpserver $@

gesftpserver-valgrind: gesftpserver
	echo "#! /bin/sh" > $@.new
	echo "set -e" >> $@.new
	echo "exec valgrind --leak-check=full -q --log-file=/dev/tty --num-callers=50 `pwd`/gesftpserver \"\$$@\"" >> $@.new
	chmod +x $@.new
	mv $@.new $@

sftpclient-valgrind: sftpclient
	echo "#! /bin/sh" > $@.new
	echo "set -e" >> $@.new
	echo "exec valgrind --leak-check=full -q --log-file=/dev/tty --num-callers=50 `pwd`/sftpclient \"\$$@\"" >> $@.new
	chmod +x $@.new
	mv $@.new $@

# Cleaning
DISTCLEANFILES=${SEDOUTPUTS} gesftpserver.8
CLEANFILES=*.gcno *.gcda *.gcov gesftpserver-ro gesftpserver-debug gesftpserver-ro-debug gesftpserver-valgrind

# Distribution
EXTRA_DIST=gesftpserver.8.in testing.txt tests rotests README.md run-tests \
format-gconv-report getopt.c getopt1.c gnu-include/getopt.h CHANGES.md

%.s: %.c
	$(COMPILE) -o $@ -S $<

version:
	@echo $(VERSION)
