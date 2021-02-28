/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  �T���v���v���O����                           */
/*    H8/3048 �p OS�^�C�} (ITU0�𗘗p)                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "kernel.h"
#include "kernel_id.h"
#include "h8_3048.h"
#include "ostimer.h"



/* OS�^�C�}�̏����� */
void OsTimer_Initialize(VP_INT exinf)
{
	/* ITU0 (�V�X�e���^�C�}�j������ */
	TCR0   = 0x23;		/* ��/8�ŃJ�E���g */
	TSR0  &= 0xfe;		/* �X�e�[�^�X���W�X�^�N���A */
	TIER0  = 0x01;		/* ���荞�݋��� */
	GRA0   = 2000 - 1;	/* 1 msec �̃C���^�[�o���i16MHz���j */
	TSTR  |= 0x01;		/* TCNT0����J�n */
}


/* �^�C�}�p���荞�݃n���h�� */
void OsTimer_TimerHandler(VP_INT exinf)
{
	/* ���荞�ݗv���N���A */
	TSR0 &= 0xfe;
	
	/* �^�C���e�B�b�N���� */
	isig_tim();
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
