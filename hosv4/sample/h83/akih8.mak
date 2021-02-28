# --------------------------------------------------------------------------- 
#  Hyper Operating System V4  �T���v���v���O����                              
#    ���C�N�t�@�C���i���� H8300H  �H��C�R���p�C���Łj                         
#                                                                             
#                                   Copyright (C) 1998-2002 by Project HOS    
#                                   http://sourceforge.jp/projects/hos/       
# --------------------------------------------------------------------------- 



# Borland-C++ Ver 5.5 �t�� make �ɂē���m�F���Ă��܂��B
# system.cfg �̃v���v���Z�b�T�����ɂ� Borland-C++ Ver 5.5 �𗘗p���Ă��܂��B



# �p�X
INCH8DIR = \akih8c			# C�R���p�C���̐ݒ�ɂ��킹�ď��������Ă�������
HOSROOT  = ..\..
INCDIR   = $(HOSROOT)\include
LIBDIR   = $(HOSROOT)\lib\h83\akih8


# �c�[��
CC     = cc38h
CPP    = cpp32				# BC55 �̃v���v���Z�b�T�𗘗p
ASM    = a38h
LINK   = l38h
OBJCNV = c38h


# �I�v�V����
CFLAGS   = -CPU=300HA -INCLUDE=$(INCH8DIR),$(INCDIR)
CPPFLAGS = -P-
AFLAGS   = 
LFLAGS   = 

# �^�[�Q�b�g
TARGET = sample.mot

#�C���N���[�h�t�@�C��
INCS = kernel_id.h sample.h ostimer.h h8_sci.h

# �I�u�W�F�N�g�t�@�C��
OBJS = vector.obj crt0.obj sample.obj ostimer.obj h8_sci.obj kernel_cfg.obj



# ���C�u��������
$(TARGET): $(OBJS) link.sub
	$(LINK) /SUB=link.sub
	$(OBJCNV) sample.abs $(TARGET)


# �I�u�W�F�N�g����
kernel_cfg.obj: kernel_cfg.c $(INCS)
	$(CC) $(CFLAGS) kernel_cfg.c

vector.obj: vector.src
	$(ASM) $(AFLAGS) vector.src

crt0.obj: crt0.src
	$(ASM) $(AFLAGS) crt0.src

sample.obj: sample.c $(INCS)
	$(CC) $(CFLAGS) sample.c

ostimer.obj: ostimer.c $(INCS)
	$(CC) $(CFLAGS) ostimer.c

h8_sci.obj: h8_sci.c $(INCS)
	$(CC) $(CFLAGS) h8_sci.c

kernel_cfg.c kernel_id.h: system.cfg
	$(CPP) $(CPPFLAGS) -osystem.i system.cfg
	hos4cfg system.i


# �N���[���i�b�v
clean:
	-del *.i
	-del *.abs
	-del *.obj
	-del kernel_cfg.c
	-del kernel_id.h
	-del $(TARGET)



# --------------------------------------------------------------------------- 
#  Copyright (C) 1998-2002 by Project HOS                                     
# --------------------------------------------------------------------------- 
