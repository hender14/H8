# -----------------------------------------------------------------------------
#  HOS-V4                                                                      
#   �R���t�B�M�����[�^�[���C�N�t�@�C�� GCC�p                       
#                                                                              
#                                       Copyright (C) 1998-2002 by Project HOS 
#                                       http://sourceforge.jp/projects/hos/    
# -----------------------------------------------------------------------------



# �c�[��
CC   = g++
LINK = g++


# �I�v�V����
CFLAGS = -O2 -pipe -Wall
LFLAGS = 


# �^�[�Q�b�g
TARGET  = hos4cfg


# �I�u�W�F�N�g�t�@�C��
OBJS = hos4cfg.o \
       analyze.o \
       parpack.o \
       read.o \
       defercd.o \
       intstk.o \
       idlstk.o \
       knlheap.o \
       maxtpri.o \
       apidef.o \
       apiinc.o \
       cretsk.o \
       deftex.o \
       cresem.o \
       creflg.o \
       credtq.o \
       crembx.o \
       crempf.o \
       crempl.o \
       crembf.o \
       timtic.o \
       crecyc.o \
       crealm.o \
       defexc.o \
       attini.o \
       attisr.o



# �^�[�Q�b�g����
$(TARGET): $(OBJS)
	$(LINK) $(OBJS) -o $(TARGET)

clean:
	rm -f $(TARGET) $(TARGET).exe $(OBJS)

.cpp.o:
	$(CC) $(CFLAGS) -c $<

.c.o:
	$(CC) $(CFLAGS) -c $<


# -----------------------------------------------------------------------------
#  Copyright (C) 1998-2002 by Project HOS                                      
# -----------------------------------------------------------------------------
