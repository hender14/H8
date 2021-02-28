/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �C�x���g�t���O                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2004 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_flg.h"



/* �C�x���g�t���O�̏����� */
void kernel_ini_flg(void)
{
	INT i;

	/* �C�x���g�t���O�̏����� */
	for ( i = KERNEL_TMIN_FLGID; i <= KERNEL_TMAX_FLGID; i++ )
	{
		if ( KERNEL_FLGID_TO_FLGCB_RAM(i) != NULL )
		{
			KERNEL_FLGID_TO_FLGCB_RAM(i)->flgptn = KERNEL_FLGID_TO_FLGCB_RAM(i)->flgcb_rom->iflgptn;
		}
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2004 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
