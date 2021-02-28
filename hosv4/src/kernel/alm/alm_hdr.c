/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �A���[���n���h��                                        */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_alm.h"



/* �A���[���n���h���̃^�C�}�n���h�� */
void kernel_alm_hdr(
		T_KERNEL_TIM *timobj,	/* �^�C�}�I�u�W�F�N�g */
		RELTIM       tic)		/* �^�C���e�B�b�N */
{
	const T_KERNEL_ALMCB_ROM *almcb_rom;
	T_KERNEL_ALMCB_RAM *almcb_ram;
	
	/* upper cast */
	almcb_ram = (T_KERNEL_ALMCB_RAM *)timobj;
	
	/* �A���[���^�X�N�̎��s */
	if ( almcb_ram->lefttim <= tic )
	{
		almcb_rom = almcb_ram->almcb_rom;
				
		/* �A���[���n���h�����^�C�}���X�g����O�� */
		kernel_rmv_tml((T_KERNEL_TIM *)almcb_ram);

		/* �A���[���n���h���Ăяo�� */
		mknl_unl_sys();							/* �V�X�e���̃��b�N���� */		
		almcb_rom->almhdr(almcb_rom->exinf);	/* �n���h���Ăяo�� */
		mknl_loc_sys();							/* �V�X�e���̃��b�N */
	}
	else
	{
		almcb_ram->lefttim -= tic;		/* �c�莞�Ԃ����Z */
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
