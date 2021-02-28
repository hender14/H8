/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    �J�[�l���������Ǘ�                                                    */
/*                                                                          */
/*                                  Copyright (C) 1998-2006 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_mem.h"



/* �O���[�o���ϐ� */
T_KERNEL_HEPCB kernel_mem_hep;		/* �J�[�l���p�������q�[�v */


/* �������Ǘ��������� */
void kernel_ini_mem(
		void *p_base,		/* �Ǘ�����̈�̐擪�A�h���X */
		SIZE size)			/* �Ǘ�����̈�̃T�C�Y */
{
	kernel_cre_hep(&kernel_mem_hep, p_base, size);
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2006 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
