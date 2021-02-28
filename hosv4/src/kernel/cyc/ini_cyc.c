/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �����n���h��                                            */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_cyc.h"



/* �����n���h���̏����� */
void kernel_ini_cyc(void)
{
	T_KERNEL_CYCCB_RAM *cyccb_ram;
	int i;
	
	/* �ÓI�������ꂽ�����n���h���������� */
	for ( i = KERNEL_TMIN_CYCID; i <= KERNEL_TMAX_CYCID; i++ )
	{
		cyccb_ram = KERNEL_CYCID_TO_CYCCB_RAM(i);
		
		if ( cyccb_ram != NULL )
		{
			/* �^�C�}�n���h���o�^ */
			cyccb_ram->timobj.timhdr = kernel_cyc_hdr;
			
			/* TA_STA �����̂��̂��J�n���� */
			if ( cyccb_ram->cyccb_rom->cycatr & TA_STA )
			{
				/* �^�C�}���X�g�ɒǉ� */
				cyccb_ram->lefttim = cyccb_ram->cyccb_rom->cyctim;
				kernel_add_tml((T_KERNEL_TIM *)cyccb_ram);
			}
		}
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
