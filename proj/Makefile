# Makefile for the proj driver.

COMPILER_TYPE= gnu

CC=gcc

PROG=	proj
SRCS=	aliens.c proj.c timer.c keyboard.c mouse.c events.c button.c menu.c video_gr.c vbe.c read_xpm.c singleplayer.c player_ship.c shield.c projectile.c highscore.c

CCFLAGS= -Wall

DPADD+=	${LIBDRIVER} ${LIBSYS}
LDADD+= -llm -ldriver -lsys

LDFLAGS+= -L .

MAN=

.include <bsd.prog.mk>
.include <bsd.gcc.mk>

