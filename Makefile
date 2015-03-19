INCDIR=include
SRCDIR=src
LIBDIR=lib
CC=gcc -std=c99 -Ofast -march=native

all: test.exe

${LIBDIR}/matrixlib.o:	${SRCDIR}/matrixlib.c ${INCDIR}/matrixlib.h
	${CC} -o $@ -c $< -I${INCDIR} -lm

${LIBDIR}/mt64.o:	${SRCDIR}/mt19937-64.c ${INCDIR}/mt64.h
	${CC} -o $@ -c $< -I${INCDIR} -lm

test.exe: ${SRCDIR}/test.c ${LIBDIR}/matrixlib.o ${LIBDIR}/mt64.o
	${CC} -o $@ $^ -I${INCDIR} -lm

clean:
	@rm ${LIBDIR}/matrixlib.o
	@rm ${LIBDIR}/mt64.o
	@rm test.exe
