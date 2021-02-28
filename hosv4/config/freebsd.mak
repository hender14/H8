# Makefile for FreeBSD
# $Id: freebsd.mak,v 1.6 2006/01/21 11:40:20 m-arai Exp $
PROG_CXX  = hos4cfg
SRCS =	hos4cfg.cpp	analyze.cpp	parpack.cpp	read.cpp	\
	defercd.cpp	intstk.cpp	idlstk.cpp	knlheap.cpp	\
	maxtpri.cpp	apidef.cpp	apiinc.cpp	cretsk.cpp	\
	deftex.cpp	cresem.cpp	creflg.cpp	credtq.cpp	\
	crembx.cpp	crempf.cpp	crembf.cpp	timtic.cpp	\
	crecyc.cpp	crealm.cpp	defexc.cpp	attini.cpp	\
	attisr.cpp

NO_MAN =
CFLAGS += -Wall
#BINDIR = /usr/local/bin

.include <bsd.prog.mk>
