/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �^�X�N�Ǘ��@�\                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_tsk.h"


/* �^�X�N�̐��� */
ER cre_tsk(
		ID           tskid,		/* �����Ώۂ̃^�X�NID�ԍ� */
		const T_CTSK *pk_ctsk)	/* �^�X�N����������ꂽ�p�P�b�g�ւ̃|�C���^ */
{
	ER ercd;

	/* ID �͈̓`�F�b�N */
#ifdef HOS_ERCHK_E_ID
	if ( tskid < KERNEL_TMIN_TSKID || tskid > KERNEL_TMAX_TSKID )
	{
		return E_ID;	/* �s��ID�ԍ� */
	}
#endif

	mknl_loc_sys();	/* �V�X�e���̃��b�N */

	/* �^�X�N���o�^�\���`�F�b�N */
#ifdef HOS_ERCHK_E_OBJ
	if ( KERNEL_TSKID_TO_TCB_RAM(tskid) != NULL )
	{
		mknl_unl_sys();	/* �V�X�e���̃��b�N���� */
		return E_OBJ;	/* ���ɓo�^�ς� */
	}
#endif
	
	/* �^�X�N�̐��� */
	ercd = kernel_cre_tsk(tskid, pk_ctsk);

	mknl_unl_sys();	/* �V�X�e���̃��b�N���� */

	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
