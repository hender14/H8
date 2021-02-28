/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  �T���v���v���O����                           */
/*    H8/3664 �p OS�^�C�} (Timer A�𗘗p)                                   */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */
#include "kernel.h"
#include "kernel_id.h"
#include "h83664f.h"
#include "ostimer.h"



/* OS�^�C�}�̏����� */
void OsTimer_Initialize(VP_INT exinf)
{
	/* TMA������
	   16MHz��8.192msec�̃C���^�[�o���^�C�}�Ƃ��Đݒ� */
	IO.PMR1.BYTE = 0x02;
	IO.PCR1 = 0xff;
	TA.TMA.BYTE =  0x03;    /* 00000011 */
	IENR1.BIT.IENTA = 1;	/* �^�C�}���荞�݋��� */
}

/* �^�C�}�p���荞�݃n���h�� */
void OsTimer_TimerHandler(VP_INT exinf)
{
	/* ���荞�ݗv���N���A */
	IRR1.BYTE &= 0xbf; /* 10111111 */
	
	/* �^�C���e�B�b�N���� */
	isig_tim();
}

/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
