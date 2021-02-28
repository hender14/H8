/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �^�X�N��O�����@�\                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_tsk.h"
#include "knl_sys.h"



/* �^�X�N��O�����̋��� */
ER ena_tex(void)
{
	T_KERNEL_TCB_RAM *tcb_ram;

	/* �R���e�L�X�g�`�F�b�N */
#ifdef HOS_ERCHK_E_CTX
	if ( sns_ctx() )
	{
		return E_CTX;	/* �R���e�L�X�g�s�� */
	}
#endif

	tcb_ram = kernel_get_run_tsk();

	mknl_loc_sys();	/* �V�X�e���̃��b�N */

	/* �I�u�W�F�N�g��ԃ`�F�b�N */
#ifdef HOS_ERCHK_E_OBJ
	if ( tcb_ram->texcb == NULL )
	{
		mknl_unl_sys();		/* �V�X�e���̃��b�N���� */
		return E_OBJ;		/* �I�u�W�F�N�g��ԕs�� */
	}
#endif

	/* ��O�����̋֎~ */
	mknl_ena_tex(&tcb_ram->mtcb);

	/* �ۗ����ꂽ��O����������΂̎��s */
	mknl_exe_tex();

	mknl_unl_sys();		/* �V�X�e���̃��b�N���� */

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
