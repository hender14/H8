/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  �T���v���v���O����                           */
/*   OS�p�^�C�}                                                             */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "kernel.h"
#include "sh7045.h"
#include "ostimer.h"



/* OS�p�^�C�}������ */
void ostim_init(VP_INT exinf)
{
	/* �^�C�}������ */
	*SH_CMCSR0 = 0x0040;
	*SH_CMCOR0 = (UH)(INT)exinf;
	*SH_CMSTR  = 0x0001;
	*SH_IPRG   = 0x00f0;
}


/* ���荞�݃n���h���T���v�� */
void ostim_hdr(VP_INT exinf)	/* OS�^�C�}�p�n���h�� */
{
	*SH_CMCSR0 &= 0xff7f;
	
	isig_tim();		/* �^�C���e�B�b�N�̋��� */
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
