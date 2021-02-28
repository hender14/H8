# --------------------------------------------------------------------------- 
#  Hyper Operating System V4  �T���v���v���O����                              
#    ���C�N�t�@�C���ih8300-hms  GNUC�R���p�C���Łj                            
#                                                                             
#                                   Copyright (C) 1998-2002 by Project HOS    
#                                   http://sourceforge.jp/projects/hos/       
# --------------------------------------------------------------------------- 


# FreeBSD 4.6R�t��make�AGNU make 3.79.1�ɂē���m�F���Ă��܂��B


# �p�X
HOSROOT  = ../..
INCDIR   = $(HOSROOT)/include
PACDIR   = $(HOSROOT)/include/h83
LIBDIR   = $(HOSROOT)/lib/h83/gcc


# �c�[��
CC     = h8300-hms-gcc
CPP    = h8300-hms-gcc
ASM    = h8300-hms-gcc
LINK   = h8300-hms-gcc
OBJCNV = h8300-hms-objcopy -O srec
HOSCFG = ../../config/hos4cfg


# �I�v�V����
CFLAGS   = -Os -Wall -I$(INCDIR) -I$(PACDIR) -mh -c -pipe
CPPFLAGS = -E -mh -x c
AFLAGS   = -mh -c
LFLAGS   = -mh -mrelax -nostartfiles -nostdlib -Wl,-Map,$(TARGET).map \
		-Wl,-T$(LDSCRIPT) -L$(LIBDIR)
LIBS	 = -lgcc -lh4h83
# �^�[�Q�b�g
TARGET = sample

#�C���N���[�h�t�@�C��
INCS = kernel_id.h sample.h h8_sci.h

#�����J�X�N���v�g
LDSCRIPT = h83048.x

# �I�u�W�F�N�g�t�@�C��
OBJS = crt0.o vector.o sample.o h8_sci.o kernel_cfg.o ostimer.o


# �^�[�Q�b�g���W���[������
$(TARGET).mot: $(OBJS) $(LDSCRIPT)
	$(LINK) $(LFLAGS) -o $(TARGET).coff $(OBJS) $(LIBS)
	$(OBJCNV) $(TARGET).coff $(TARGET).mot


# �I�u�W�F�N�g����
kernel_cfg.o: kernel_cfg.c $(INCS)
	$(CC) $(CFLAGS) kernel_cfg.c

vector.o: vector.s
	$(ASM) $(AFLAGS) vector.s

crt0.o: crt0.s
	$(ASM) $(AFLAGS) crt0.s

sample.o: sample.c $(INCS)
	$(CC) $(CFLAGS) sample.c

h8_sci.o: h8_sci.c $(INCS)
	$(CC) $(CFLAGS) h8_sci.c

ostimer.o: ostimer.c $(INCS)
	$(CC) $(CFLAGS) ostimer.c

kernel_cfg.c kernel_id.h: system.cfg
	$(CPP) $(CPPFLAGS) system.cfg | $(HOSCFG) -

# �t���b�V����������
write:
	h8write -3048 $(TARGET).mot /dev/cuaa0


# �N���[���i�b�v
clean:
	rm  -f  $(TARGET).coff $(TARGET).mot $(TARGET).map \
		$(OBJS) kernel_id.h kernel_cfg.c *~


# --------------------------------------------------------------------------- 
#  Copyright (C) 1998-2002 by Project HOS                                     
# --------------------------------------------------------------------------- 
