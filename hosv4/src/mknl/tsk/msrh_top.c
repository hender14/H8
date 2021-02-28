/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �ʃJ�[�l�� �^�X�N����                                                 */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



/* ���f�B�[�L���[�擪�̃^�X�N��T�� */
T_MKNL_TCB* mknl_srh_top(void)
{
	INT i;

	/* �ō��D��x�̎��s�\�^�X�N��T�� */
	for ( i = 0; i < mknl_rdq_cnt; i++ )	/* �D��x�̍����L���[���珇�Ɍ��� */
	{
		if ( mknl_rdq_tbl[i].head != NULL )	/* ���f�B�L���[�ɂ͎��s�\�^�X�N�����Ȃ� */
		{
			return mknl_rdq_tbl[i].head;
		}
	}

	return NULL;	/* ���s�\�^�X�N���� */
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
