# --------------------------------------------------------------------------- 
#  Hyper Operating System V4  �T���v���v���O����                              
#    ���C�N�t�@�C���ih8300-hms  GNUC�R���p�C���Łj                            
#                                                                             
#                                   Copyright (C) 1998-2003 by Project HOS    
#                                   http://sourceforge.jp/projects/hos/       
# --------------------------------------------------------------------------- 


# FreeBSD 4.6R�t��make�AGNU make 3.79.1�ɂē���m�F���Ă��܂��B


# �p�X
HOSROOT  = ../..
INCDIR   = $(HOSROOT)/include
HINCDIR  = .
PACDIR   = $(HOSROOT)/include/h83
LIBDIR   = $(HOSROOT)/lib/h83/gcc

# �c�[��
CC     = h8300-hms-gcc
CPP    = h8300-hms-gcc
ASM    = h8300-hms-gcc -x assembler-with-cpp
LINK   = h8300-hms-gcc
OBJCNV = h8300-hms-objcopy -O srec
HOSCFG = ../../config/hos4cfg

RM     = rm -f
#RM    = command /c del
#RM    = del

# �I�v�V����
CFLAGS   = -O2 -fomit-frame-pointer -Wall -I$(INCDIR) -I$(PACDIR) -I$(HINCDIR) -mh -mn -c -pipe
CPPFLAGS = -E -mh -mn -x c
AFLAGS   = -mh -mn -c
LFLAGS   = -mh -mn -mrelax -nostartfiles -nostdlib -Wl,-Map,$(TARGET).map \
		-Wl,-T$(LDSCRIPT) -L$(LIBDIR)
LIBS	 = -lgcc -lh4h83n
# �^�[�Q�b�g
TARGET = sample

#�C���N���[�h�t�@�C��
INCS = kernel_id.h sample.h h8t_sci.h

#�����J�X�N���v�g
LDSCRIPT = h83664.x

# �I�u�W�F�N�g�t�@�C��
OBJS = crt0.o vector.o sample.o h8t_sci.o kernel_cfg.o ostimer.o

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

h8t_sci.o: h8t_sci.c $(INCS)
	$(CC) $(CFLAGS) h8t_sci.c

ostimer.o: ostimer.c $(INCS)
	$(CC) $(CFLAGS) ostimer.c

kernel_cfg.c kernel_id.h: system.cfg
	$(CPP) $(CPPFLAGS) system.cfg | $(HOSCFG) -

# �t���b�V����������
write: $(TARGET).mot
	h8write -3664 $(TARGET).mot /dev/cuaa0

# �N���[���i�b�v
clean:
	$(RM) $(TARGET).coff
	$(RM) $(TARGET).mot
	$(RM) $(TARGET).map
	$(RM) *.o
	$(RM) kernel_id.h
	$(RM) kernel_cfg.c
	$(RM) *~

# --------------------------------------------------------------------------- 
#  Copyright (C) 1998-2003 by Project HOS                                     
# --------------------------------------------------------------------------- 
