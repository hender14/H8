/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*   �v���Z�b�T���ۉ��R���|�[�l���g (���� H8/300H �p)                       */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "kernel.h"



/* ���݂̊����݃}�X�N�l�̋����ύX */
ER fchg_imsk(
		IMSK imsk)		/* �ݒ肷��}�X�N�l */
{
	/* �p�����[�^�[�`�F�b�N */
#ifdef HOS_ERCHK_E_PAR
	if ( (imsk & ~(H83_IMSK_I_BIT | H83_IMSK_UI_BIT)) != 0 )
	{
		return E_PAR;
	}
#endif
	
	mknl_loc_sys();		/* �V�X�e���̃��b�N */
	
	/* �����I�Ɍ��ݒl��ύX */
	kernel_h83_imsk = imsk;		/* ���荞�݃}�X�N�̐ݒ� */
	
	mknl_unl_sys();		/* �V�X�e���̃A�����b�N */
	
	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
