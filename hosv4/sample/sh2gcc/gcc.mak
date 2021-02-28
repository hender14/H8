# --------------------------------------------------------------------------- 
#  Hyper Operating System V4  �T���v���v���O����                              
#    ���C�N�t�@�C�� SH2 gcc�p                                                 
#                                                                             
#                                   Copyright (C) 1998-2002 by Project HOS    
#                                   http://sourceforge.jp/projects/hos/       
# --------------------------------------------------------------------------- 


CC     = sh-hms-gcc
ASM    = sh-hms-gcc
LINK   = sh-hms-gcc
OBJCNV = sh-hms-objcopy


TARGET = sample


CFLAGS = -c -m2 -I../../include
AFLAGS = -c -m2
LFLAGS = -m2 -nostartfiles -Wl,-v,-t,-Map,sample.map,-Tsample.x

INCS   = kernel_id.h sample.h sci.h
OBJS   = crt0.o vector.o sample.o ostimer.o sci.o stmfifo.o kernel_cfg.o
LIBS   = ../../lib/sh/sh2gcc/libh4sh2.a

${TARGET}.mot: ${OBJS} sample.x
	${LINK} ${LFLAGS} -o ${TARGET}.out ${OBJS} ${LIBS}
	${OBJCNV} -O srec ${TARGET}.out ${TARGET}.mot

vector.o: vector.s
	${ASM} ${AFLAGS} vector.s -o vector.o

crt0.o: crt0.s
	${ASM} ${AFLAGS} crt0.s -o crt0.o

sample.o: sample.c ${INCS}
	${CC} ${CFLAGS} sample.c -o sample.o

ostimer.o: ostimer.c ostimer.h
	${CC} ${CFLAGS} ostimer.c -o ostimer.o

sci.o: sci.c sci.h
	${CC} ${CFLAGS} sci.c -o sci.o

stmfifo.o: stmfifo.c stmfifo.h
	${CC} ${CFLAGS} stmfifo.c -o stmfifo.o

kernel_cfg.o: kernel_cfg.c ${INCS}
	${CC} ${CFLAGS} kernel_cfg.c -o kernel_cfg.o

kernel_cfg.c kernel_id.h: system.cfg
	cp system.cfg system_tmp.c
	${CC} -E system_tmp.c -o system.i
	hos4cfg system.i
	rm system.i
	rm system_tmp.c


clean:
	rm -f *.mot
	rm -f *.out
	rm -f *.o
	rm -f kernel_id.h
	rm -f kernel_cfg.c



# --------------------------------------------------------------------------- 
#  Copyright (C) 1998-2002 by Project HOS                                     
# --------------------------------------------------------------------------- 
