/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �V�X�e����ԊǗ�                                        */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_sys.h"



/* ���s��ԃ^�X�NID�̎Q�� */
ER get_tid(ID *p_tskid)
{
	T_KERNEL_TCB_RAM *tcb_ram;

	mknl_loc_sys();	/* �V�X�e���̃��b�N */

	tcb_ram = kernel_get_run_tsk();	/* ���s���̃^�X�N���擾 */
	if ( tcb_ram == NULL )
	{
		*p_tskid = TSK_NONE;	/* ���s���̃^�X�N�����݂��Ȃ� */
	}
	else
	{
		*p_tskid = kernel_get_tid(tcb_ram);	/* ���s���̃^�X�N���擾 */
	}

	mknl_unl_sys();	/* �V�X�e���̃��b�N���� */

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
