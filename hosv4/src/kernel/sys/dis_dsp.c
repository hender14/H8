/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �V�X�e����ԊǗ�                                        */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_sys.h"



/* �f�B�X�p�b�`�̋֎~ */
ER dis_dsp(void)
{
	mknl_loc_sys();	/* �V�X�e���̃��b�N */

	mknl_dis_dsp();	/* �f�B�X�p�b�`�̋֎~ */

	mknl_unl_sys();	/* �V�X�e���̃��b�N���� */

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
