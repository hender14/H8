# ------------------------------------------------------------------------
#  Hyper Operating System V4  サンプルプログラム                      
#                                                                     
#                                  Copyright (C) 1998-2007 by Project HOS
#                                  http://sourceforge.jp/projects/hos/
# ------------------------------------------------------------------------

CC     = mipsel-semb-elf-gcc
CPP    = mipsel-semb-elf-gcc
ASM    = mipsel-semb-elf-gcc
LINK   = mipsel-semb-elf-gcc
OBJCNV = mipsel-semb-elf-objcopy
HOSCFG = ../../config/hos4cfg

TARGET = sample.bin

LIBDIR = ../../lib/mips/mipsgcc
INCDIR = ../../include

CFLAGS = -c -O2 -mips4 -EL -Wall -I$(INCDIR) -I/usr/local/mipsel-semb-elf/include
AFLAGS = -c -mips4 -EL -Wall -pipe
LDSCRIPT = semb1200a-rom.ld
LFLAGS = -mips4 -mrelax -nostartfiles -L$(LIBDIR) -Wl,-v,-t,-Map,sample.map,-T${LDSCRIPT}
LDSTART1 = -Wl,--section-start,.text=0x9FC80000,-Map,sample.map

CFGFLAGS = -E -x c -Wall  -I$(INCDIR) -pipe

INCS = kernel_id.h
OBJS = crt0.o kernel_cfg.o sample.o ostimer.o 
LIBS = -lh4mips -lsemb

all: $(TARGET)

%.bin: %.out
	$(OBJCNV) -O binary $< $@

sample.out: $(OBJS)
	$(CC) $^ -o $@ $(LDSTART1) $(LFLAGS) $(LIBS)

kernel_cfg.c kernel_id.h: system.cfg
	$(CPP) $(CFGFLAGS) system.cfg | $(HOSCFG) -

clean:
	rm -f $(TARGET) *.out *.o *.map kernel_id.h kernel_cfg.c *~

# ------------------------------------------------------------------------
#                                  Copyright (C) 1998-2007 by Project HOS
#                                  http://sourceforge.jp/projects/hos/
# ------------------------------------------------------------------------
