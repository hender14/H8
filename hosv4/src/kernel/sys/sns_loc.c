/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �V�X�e����ԊǗ�                                        */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_sys.h"



/* CPU���b�N��Ԃ̎Q�� */
BOOL sns_loc(void)
{
	BOOL state;
	
	mknl_loc_sys();	/* �V�X�e���̃��b�N */

	state = mknl_sns_loc();		/* CPU���b�N��Ԃ̎Q�� */

	mknl_unl_sys();	/* �V�X�e���̃��b�N���� */

	return state;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
