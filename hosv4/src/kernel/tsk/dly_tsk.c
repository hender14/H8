/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �^�X�N�t�������@�\                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_tsk.h"



/* ���^�X�N�̒x�� */
ER dly_tsk(RELTIM dlytim)
{
	T_KERNEL_TCB_RAM *tcb_ram;
	ER ercd;

	mknl_loc_sys();	/* �V�X�e���̃��b�N */

	/* �R���e�L�X�g�`�F�b�N */
#ifdef HOS_ERCHK_E_CTX
	if ( mknl_sns_wai() )
	{
		mknl_unl_sys();	/* �V�X�e���̃��b�N���� */
		return E_CTX;	/* �R���e�L�X�g�s�� */
	}
#endif

	/* �^�X�N�R���g���[���u���b�N�擾 */
	tcb_ram = kernel_get_run_tsk();

	/* ���ԑ҂���Ԃɐݒ� */
	mknl_wai_tsk(&tcb_ram->mtcb, TTW_DLY);
	mknl_add_tmout(&tcb_ram->mtcb, dlytim);
	
	ercd = (ER)mknl_exe_dsp();	/* �^�X�N�f�B�X�p�b�`�̎��s */
	
	if ( ercd == E_TMOUT )
	{
		ercd = E_OK;	/* dly_tsk �̓^�C���A�E�g����̂����� */
	}
	
	mknl_exe_tex();		/* ��O�����̎��s */
	
	mknl_unl_sys();		/* �V�X�e���̃��b�N���� */
	
	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
