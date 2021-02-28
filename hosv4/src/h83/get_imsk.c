/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*   �v���Z�b�T���ۉ��R���|�[�l���g (���� H8 �p)                            */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "kernel.h"



/* ���荞�݃}�X�N�̃x�[�X�l�̎Q�� */
ER get_imsk(
		IMSK *p_imsk)	/* ���݂̃}�X�N�l�̊i�[�Ԓn */
{
	mknl_loc_sys();		/* �V�X�e���̃��b�N */
	
	*p_imsk = kernel_h83_ibmsk;		/* ���荞�݃}�X�N�x�[�X�l�̎擾 */
	
	mknl_unl_sys();		/* �V�X�e���̃A�����b�N */
	
	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
