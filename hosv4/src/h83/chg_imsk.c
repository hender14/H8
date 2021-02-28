/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*   �v���Z�b�T���ۉ��R���|�[�l���g (���� H8/300H �p)                       */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "kernel.h"



/* ���荞�݃}�X�N�̃x�[�X�l�̕ύX */
ER chg_imsk(
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
	
	/* �x�[�X�}�X�N�l�̕ύX */
	kernel_h83_ibmsk = imsk;
	
	if ( mknl_sns_ctx() )
	{
		/* ���荞�݃R���e�L�X�g�Ȃ�}�X�N���x��UP�̂ݔ��f */
		kernel_h83_imsk |= imsk;
	}
	else
	{
		/* �^�X�N�R���e�L�X�g�Ȃ猻�݂̃}�X�N�l�������ύX */
		kernel_h83_imsk = imsk;
	}
	
	mknl_unl_sys();		/* �V�X�e���̃A�����b�N */
	
	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
