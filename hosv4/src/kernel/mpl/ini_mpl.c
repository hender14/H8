/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �ϒ��������v�[��                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2006 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mpl.h"



/* �ϒ��������v�[���̏����� */
void kernel_ini_mpl(void)
{
	const T_KERNEL_MPLCB_ROM *mplcb_rom;
	T_KERNEL_MPLCB_RAM       *mplcb_ram;
	INT  i;

	/* �ϒ��������v�[���R���g���[���u���b�N�̏����� */
	for ( i = KERNEL_TMIN_MPLID; i <= KERNEL_TMAX_MPLID; i++ )
	{
		mplcb_ram = KERNEL_MPLID_TO_MPLCB_RAM(i);
		if ( mplcb_ram != NULL )
		{
			/* �q�[�v�̏����� */
			mplcb_rom = mplcb_ram->mplcb_rom;
			kernel_cre_hep(&mplcb_ram->hep, mplcb_rom->mpl, mplcb_rom->mplsz);
		}
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2006 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
