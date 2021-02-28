/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �^�X�N�Ǘ��@�\                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_tsk.h"


/* �^�X�N�̐���(ID�ԍ��������t��) */
ER_ID acre_tsk(
		const T_CTSK *pk_ctsk)	/* �^�X�N����������ꂽ�p�P�b�g�ւ̃|�C���^ */
{
	ID tskid;
	ER ercd;

	mknl_loc_sys();	/* �V�X�e���̃��b�N */

	/* ��ID�̌��� */
	for ( tskid = KERNEL_TMAX_TSKID; tskid >= KERNEL_TMIN_TSKID; tskid-- )
	{
		if ( KERNEL_TSKID_TO_TCB_RAM(tskid) == NULL )
		{
			break;
		}
	}
	if ( tskid < KERNEL_TMIN_TSKID )
	{
		mknl_unl_sys();		/* �V�X�e���̃��b�N���� */
		return E_NOID;		/* ID�ԍ��s�� */
	}
	
	/* �^�X�N�̐��� */
	ercd = kernel_cre_tsk(tskid, pk_ctsk);

	mknl_unl_sys();	/* �V�X�e���̃��b�N���� */

	if ( ercd != E_OK )
	{
		return (ER_ID)ercd;	/* �G���[���� */
	}

	return (ER_ID)tskid;		/* ���� */
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
