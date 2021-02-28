# -----------------------------------------------------------------------------
#  Hyper Operating System V4  �R���t�B�M�����[�^�[                             
#   Borland-C++ Version 5.5 �p ���C�N�t�@�C��                                  
#                                                                              
#                                       Copyright (C) 1998-2002 by Project HOS 
#                                       http://sourceforge.jp/projects/hos/    
# -----------------------------------------------------------------------------


# �c�[��
CC   = bcc32
LINK = bcc32


# �I�v�V����
CFLAGS = -c -O2
LFLAGS = 


# �^�[�Q�b�g
TARGET  = hos4cfg.exe


# �I�u�W�F�N�g�t�@�C��
OBJS = hos4cfg.obj \
       analyze.obj \
       parpack.obj \
       read.obj \
       defercd.obj \
       intstk.obj \
       idlstk.obj \
       knlheap.obj \
       maxtpri.obj \
       apidef.obj \
       apiinc.obj \
       cretsk.obj \
       deftex.obj \
       cresem.obj \
       creflg.obj \
       credtq.obj \
       crembx.obj \
       crempf.obj \
       crempl.obj \
       crembf.obj \
       timtic.obj \
       crecyc.obj \
       crealm.obj \
       defexc.obj \
       attini.obj \
       attisr.obj


.suffixes:
.suffixes: .cpp


# �^�[�Q�b�g����
$(TARGET): $(OBJS)
	$(LINK) $(OBJS) -o$(TARGET)

# �N���[���A�b�v
clean:
	del $(OBJS) $(TARGET)

# ���_�K��
.cpp.obj:
	$(CC) $(CFLAGS) $<


# -----------------------------------------------------------------------------
#  Copyright (C) 1998-2002 by Project HOS                                      
# -----------------------------------------------------------------------------
