# Makefile for the proj driver.

COMPILER_TYPE= gnu

CC=gcc

PROG=	proj
SRCS=	proj.c
SRCS+=	timer.c keyboard.c mouse.c video_gr.c vbe.c bitmap.c
SRCS+=	aliens.c events.c button.c menu.c singleplayer.c player.c shield.c projectile.c highscore.c options.c state.c start_menu.c  

CCFLAGS= -Wall -O3

DPADD+=	${LIBDRIVER} ${LIBSYS}
LDADD+= -llm -ldriver -lsys

LDFLAGS+= -L .

MAN=

.include <bsd.prog.mk>
.include <bsd.gcc.mk>

