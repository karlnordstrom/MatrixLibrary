INCDIR=include
SRCDIR=src
LIBDIR=lib
CC=gcc
CFLAGS=-std=c99 -Ofast -march=native -fPIC

## Get the first part of the string passed separated by :
STRINGPATH = $(firstword $(subst :, ,$1))

all: test.exe
library: ${LIBDIR}/libmatrix.so
install: library
	@echo "Installing library..."
	cp -f ${LIBDIR}/libmatrix.so $(call STRINGPATH, $(LD_LIBRARY_PATH))
	cp -f ${INCDIR}/matrixlib.h $(call STRINGPATH, $(LD_LIBRARY_PATH))/../include

${LIBDIR}/matrixlib.o:	${SRCDIR}/matrixlib.c ${INCDIR}/matrixlib.h
	${CC} ${CFLAGS} -o $@ -c $< -I${INCDIR} -lm

${LIBDIR}/mt64.o:	${SRCDIR}/mt19937-64.c ${INCDIR}/mt64.h
	${CC} ${CFLAGS} -o $@ -c $< -I${INCDIR} -lm

${LIBDIR}/libmatrix.so: ${LIBDIR}/mt64.o ${LIBDIR}/matrixlib.o
	${CC} -shared -o $@ $^ -lm

test.exe: ${SRCDIR}/test.c ${LIBDIR}/matrixlib.o ${LIBDIR}/mt64.o
	${CC} ${CFLAGS} -o $@ $^ -I${INCDIR} -lm

clean:
	@rm ${LIBDIR}/mt64.o
	@rm ${LIBDIR}/matrixlib.o
	@rm ${LIBDIR}/libmatrix.so
	@rm test.exe
