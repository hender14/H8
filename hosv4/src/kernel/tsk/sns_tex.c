/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �^�X�N��O�����@�\                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_tsk.h"



/* �^�X�N��O�����֎~��Ԃ̎Q�� */
BOOL sns_tex(void)
{
	BOOL state;
	
	mknl_loc_sys();	/* �V�X�e���̃��b�N */

	state = mknl_sns_tex();		/* �^�X�N��O�����֎~��Ԃ̎Q�� */

	mknl_unl_sys();	/* �V�X�e���̃��b�N���� */

	return state;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
