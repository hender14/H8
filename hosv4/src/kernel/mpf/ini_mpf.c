/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �Œ蒷�������v�[��                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mpf.h"



/* �Œ蒷�������v�[���̏����� */
void kernel_ini_mpf(void)
{
	const T_KERNEL_MPFCB_ROM *mpfcb_rom;
	T_KERNEL_MPFCB_RAM       *mpfcb_ram;
	UB   *ptr;
	INT  i;
	UINT j;

	/* �Œ蒷�������v�[���R���g���[���u���b�N�̏����� */
	for ( i = KERNEL_TMIN_MPFID; i <= KERNEL_TMAX_MPFID; i++ )
	{
		mpfcb_ram = KERNEL_MPFID_TO_MPFCB_RAM(i);
		if ( mpfcb_ram != NULL )
		{
			mpfcb_rom = mpfcb_ram->mpfcb_rom;
			
			/* �u���b�N�̏����� */
			mpfcb_ram->free = mpfcb_rom->mpf;
			ptr             = (UB *)mpfcb_rom->mpf;
			for ( j = 0; j < mpfcb_rom->blkcnt - 1; j++ )
			{
				*(VP *)ptr = (VP)(ptr + mpfcb_rom->blksz);
				ptr += mpfcb_rom->blksz;
			}
			*(VP *)ptr = NULL;	/* �ŏI�u���b�N */
		}
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
