# Makefile for the proj driver.

COMPILER_TYPE= gnu

CC=gcc

PROG=	proj
SRCS=	proj.c timer.c keyboard.c mouse.c events.c button.c menu.c

CCFLAGS= -Wall

DPADD+=	${LIBDRIVER} ${LIBSYS}
LDADD+= -ldriver -lsys

LDFLAGS+= -L .

MAN=

.include <bsd.prog.mk>
.include <bsd.gcc.mk>

