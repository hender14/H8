/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �^�X�N��O�����@�\                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_tsk.h"



/* �^�X�N��O�����G���g���[�|�C���g(�ʃJ�[�l�����Ăяo��) */
void kernel_tex_entry(void)
{
	T_KERNEL_TCB_RAM   *tcb_ram;
	T_KERNEL_TEXCB_RAM *texcb;
	TEXPTN rasptn;
	
	tcb_ram = kernel_get_run_tsk();
	texcb   = tcb_ram->texcb;
	
	/* �^�X�N��O�v���N���A */
	rasptn = texcb->rasptn;
	texcb->rasptn = 0;
	
	mknl_dis_tex(&tcb_ram->mtcb);	/* �^�X�N��O�����̋֎~ */
	mknl_unl_sys();					/* �V�X�e���̃��b�N���� */

	texcb->texrtn(rasptn);			/* �^�X�N��O�������[�`���̌Ăяo�� */

	mknl_loc_sys();					/* �V�X�e���̃��b�N */
	mknl_ena_tex(&tcb_ram->mtcb);	/* �^�X�N��O�����̋��� */
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
