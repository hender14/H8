/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �V�X�e�����ԊǗ�                                        */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_tim.h"



/* �V�X�e�����ԊǗ��p�ϐ� */
SYSTIM kernel_systim;			/* �V�X�e������ */
UW     kernel_tic_cnt = 0;		/* �^�C���e�B�b�N�p�J�E���^ */



/* ���ԊǗ��@�\�̏����� */
void kernel_ini_tim(void)
{
	kernel_tic_cnt = kernel_tic_deno;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
