PREFIX:=
BINDIR:=/usr/local/bin/
EXECBIN:=\/usr\/local\/bin\/cailogin
CGIDIR:=/var/www/localhost/cgi-bin/
BITMAPSDIR:=/var/lib/cailogin/bitmaps/
DBDIR:=/var/lib/cailogin/
CFLAGS:=-Os -I.
LDFLAGS:=
VERSION:=1.0
SOURCES:=cailogin.c file.c filters.c image.c
OBJECTS:=cailogin.o file.o filters.o image.o

TIMETHRESHOLD:=600
MAXDBENTRIES:=300

all: vars.h cailogin cailogin.cgi
	sed -i 's/^EXECBIN.*$$/EXECBIN=${EXECBIN}/g' login.cgi	

vars.h:
	echo "#define EXECBIN \"${BINDIR}cailogin\"" > vars.h
	echo "#define BITMAPSDIR \"${BITMAPSDIR}\"" >> vars.h
	echo "#define DBDIR \"${DBDIR}\"" >> vars.h
	echo "#define VERSION \"${VERSION}\"" >> vars.h
	echo "#define TIMETHRESHOLD ${TIMETHRESHOLD}" >> vars.h
	echo "#define MAXDBENTRIES ${MAXDBENTRIES}" >> vars.h

cailogin: ${OBJECTS}
	gcc -o cailogin ${OBJECTS}

cailogin.cgi: cailogin.cgi.o
	gcc -o cailogin.cgi cailogin.cgi.o

cailogin.cgi.o: cailogin.cgi.c
	gcc -c cailogin.cgi.c

${OBJECTS}: ${SOURCES}
	gcc -c ${SOURCES}

install: cailogin
	-mkdir -p ${PREFIX}/${BINDIR} 2> /dev/null
	-mkdir -p ${PREFIX}/${DBDIR} 2> /dev/null
	-mkdir -p ${PREFIX}/${CGIDIR} 2> /dev/null
	-mkdir -p ${PREFIX}/${BITMAPSDIR} 2> /dev/null
	install -g root -o root -m 755 cailogin ${PREFIX}/${BINDIR}/
	install -g root -o root -m 644 bitmaps/* ${PREFIX}/${BITMAPSDIR}/
	install -g root -o root -m 666 cailogin.db ${PREFIX}/${DBDIR}/
	install -g root -o root -m 755 cailogin.cgi ${PREFIX}/${CGIDIR}/

clean:
	-rm *.o
	-rm vars.h
	-rm cailogin cailogin.cgi

strip:
	strip -s cailogin
	-strip -s cailogin.cgi

release:
	-rm CAILogin-*.tar.gz
	tar c * > /tmp/CAILogin-${VERSION}.tar
	gzip -9 /tmp/CAILogin-${VERSION}.tar
	mv /tmp/CAILogin-${VERSION}.tar.gz .
