/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �V�X�e����ԊǗ�                                        */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_sys.h"



/* �^�X�NID�̎擾 */
ID kernel_get_tid(T_KERNEL_TCB_RAM *tcb_ram)
{
	ID tskid;
	
	/* �^�X�NID������ */
	for ( tskid = KERNEL_TMAX_TSKID; tskid >= KERNEL_TMIN_TSKID; tskid-- )
	{
		if ( tcb_ram == KERNEL_TSKID_TO_TCB_RAM(tskid) )
		{
			break;
		}
	}
	
	return tskid;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
