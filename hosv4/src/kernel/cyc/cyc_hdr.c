/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �����n���h��                                            */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_cyc.h"



/* �����n���h���̃^�C�}�n���h�� */
void kernel_cyc_hdr(
		T_KERNEL_TIM *timobj,	/* �^�C�}�I�u�W�F�N�g */
		RELTIM       tic)		/* �^�C���e�B�b�N */
{
	const T_KERNEL_CYCCB_ROM *cyccb_rom;
	T_KERNEL_CYCCB_RAM *cyccb_ram;
	
	/* upper cast */
	cyccb_ram = (T_KERNEL_CYCCB_RAM *)timobj;
	
	/* �����^�X�N�̎��s */
	if ( cyccb_ram->lefttim <= tic )
	{
		cyccb_rom = cyccb_ram->cyccb_rom;
				
		/* ���̒l��ݒ� */
		cyccb_ram->lefttim += cyccb_rom->cyctim - tic;

		/* �����n���h���Ăяo�� */
		mknl_unl_sys();							/* �V�X�e���̃��b�N���� */		
		cyccb_rom->cychdr(cyccb_rom->exinf);	/* �n���h���Ăяo�� */
		mknl_loc_sys();							/* �V�X�e���̃��b�N */
	}
	else
	{
		cyccb_ram->lefttim -= tic;
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
