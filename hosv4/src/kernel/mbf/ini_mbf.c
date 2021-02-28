/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� ���b�Z�[�W�o�b�t�@                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mbf.h"



/* ���b�Z�[�W�o�b�t�@�̏����� */
void kernel_ini_mbf(void)
{
	const T_KERNEL_MBFCB_ROM *mbfcb_rom;
	T_KERNEL_MBFCB_RAM       *mbfcb_ram;
	INT                      i;

	/* ���b�Z�[�W�o�b�t�@�R���g���[���u���b�N�̏����� */
	for ( i = KERNEL_TMIN_MBFID; i <= KERNEL_TMAX_MBFID; i++ )
	{
		mbfcb_ram = KERNEL_MBFID_TO_MBFCB_RAM(i);
		if ( mbfcb_ram != NULL )
		{
			mbfcb_rom = mbfcb_ram->mbfcb_rom;
			
			/* �󂫃T�C�Y�̏����� */
			mbfcb_ram->fmbfsz = mbfcb_rom->mbfsz;
		}
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
