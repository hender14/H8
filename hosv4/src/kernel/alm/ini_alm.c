/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �A���[���n���h��                                        */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_alm.h"



/* �A���[���n���h���̏����� */
void kernel_ini_alm(void)
{
	T_KERNEL_ALMCB_RAM *almcb_ram;
	int i;
	
	/* �ÓI�������ꂽ�A���[���n���h���������� */
	for ( i = KERNEL_TMIN_ALMID; i <= KERNEL_TMAX_ALMID; i++ )
	{
		almcb_ram = KERNEL_ALMID_TO_ALMCB_RAM(i);
		
		if ( almcb_ram != NULL )
		{
			/* �^�C�}�n���h���o�^ */
			almcb_ram->timobj.timhdr = kernel_alm_hdr;
		}
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
