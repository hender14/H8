/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �ʃJ�[�l�� �^�X�N����                                                 */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



/* �^�X�N��O�����̗v�� */
void mknl_ras_tex(
		T_MKNL_TCB *mtcb)	/* ��O������v������^�X�N */
{
	if ( mtcb == mknl_run_mtcb && !(mtcb->texstat & MKNL_TTS_DRAS) )
	{
		/* ���s���^�X�N�ŁA��O�֎~�łȂ���Η�O���s */
		do
		{
			mtcb->texstat = 0;
			kernel_tex_entry();
		} while ( mtcb->texstat != 0 );	/* ��O�v�����Ȃ��Ȃ�܂Ń��[�v */
	}
	else
	{
		/* ��O��ۗ����� */
		mtcb->texstat &= MKNL_TTS_RDLY;
	}
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
