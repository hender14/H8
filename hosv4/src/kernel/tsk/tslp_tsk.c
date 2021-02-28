/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �^�X�N�t�������@�\                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_tsk.h"



/* �^�X�N�̋N���҂�(�^�C���A�E�g����) */
ER tslp_tsk(
			TMO tmout)
{
	T_KERNEL_TCB_RAM *tcb_ram;
	ER ercd;

	/* �p�����[�^�[�`�F�b�N */
#ifdef HOS_ERCHK_E_PAR 
	if ( tmout != TMO_FEVR && tmout < 0 )
	{
		return E_PAR;
	}
#endif

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

	/* �N���v���L���[�C���O�̃`�F�b�N */
	if ( tcb_ram->wupcnt > 0 )
	{
		tcb_ram->wupcnt--;
		mknl_unl_sys();		/* �V�X�e���̃��b�N���� */
		return E_OK;
	}

	/* �|�[�����O�w��Ȃ�^�C���A�E�g */
	if ( tmout == TMO_POL )
	{
		mknl_unl_sys();		/* �V�X�e���̃��b�N���� */
		return E_TMOUT;
	}
	
	/* �҂���Ԃɐݒ� */
	 mknl_wai_tsk(&tcb_ram->mtcb, TTW_SLP);
	
	/* �^�C���A�E�g�҂��s��ɒǉ� */
	if ( tmout != TMO_FEVR )
	{
		mknl_add_tmout(&tcb_ram->mtcb, (RELTIM)tmout);
	}
	
	ercd = (ER)mknl_exe_dsp();	/* �^�X�N�f�B�X�p�b�`�̎��s */
	mknl_exe_tex();				/* ��O�����̎��s */
	
	mknl_unl_sys();	/* �V�X�e���̃��b�N���� */
	
	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
