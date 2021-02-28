/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �Z�}�t�H                                                */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_sem.h"



/* �Z�}�t�H�̏����� */
void kernel_ini_sem(void)
{
	INT i;

	/* �Z�}�t�H�R���g���[���u���b�N�̏����� */
	for ( i = KERNEL_TMIN_SEMID; i <= KERNEL_TMAX_SEMID; i++ )
	{
		if ( KERNEL_SEMID_TO_SEMCB_RAM(i) != NULL )
		{
			KERNEL_SEMID_TO_SEMCB_RAM(i)->semcnt = KERNEL_SEMID_TO_SEMCB_RAM(i)->semcb_rom->isemcnt;
		}
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
