/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �V�X�e����ԊǗ�                                        */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_sys.h"



/* �R���e�L�X�g�̎Q�� */
BOOL sns_ctx(void)
{
	BOOL state;

	mknl_loc_sys();	/* �V�X�e���̃��b�N */

	state = mknl_sns_ctx();	/* �R���e�L�X�g�̎Q�� */

	mknl_unl_sys();	/* �V�X�e���̃��b�N���� */

	return state;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */