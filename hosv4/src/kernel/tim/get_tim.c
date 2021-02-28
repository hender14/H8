/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �V�X�e�����ԊǗ�                                        */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_tim.h"



/* �V�X�e�������̎Q�� */
ER get_tim(
		SYSTIM *p_systim)		/* �V�X�e�������ɐݒ肷�鎞�� */
{
	mknl_loc_sys();		/* �V�X�e���̃��b�N */

	/* �V�X�e�������̎擾 */
	*p_systim = kernel_systim;

	mknl_unl_sys();		/* �V�X�e���̃��b�N���� */

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
