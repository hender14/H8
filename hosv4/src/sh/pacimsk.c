/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*   �v���Z�b�T���ۉ��R���|�[�l���g (SH�p)  ���荞�݃}�X�N�Ǘ�              */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "kernel.h"



/* �O���[�o���ϐ���` */
UW hospac_sh_imsk      = 0;		/* ���荞�݃}�X�N */
UW hospac_sh_imsk_base = 0;		/* ���荞�݃}�X�N�x�[�X�l */



/* ���荞�݃}�X�N�w�� */
ER chg_imsk(IMSK imsk)
{
	/* �p�����[�^�[�`�F�b�N */
#ifdef HOS_ERCHK_E_PAR
	if ( imsk < 0 || imsk > 15 )
	{
		return E_PAR;
	}
#endif

	mknl_loc_sys();		/* �V�X�e���̃��b�N */
	
	hospac_sh_imsk_base = (imsk << 4);
	if ( mknl_sns_ctx() || hospac_sh_imsk < hospac_sh_imsk_base )
	{
		hospac_sh_imsk = hospac_sh_imsk_base;
	}
	
	mknl_unl_sys();		/* �V�X�e���̃A�����b�N */

	return E_OK;
}


/* ���荞�݃}�X�N�̎Q�� */
ER get_imsk(IMSK *p_imsk)
{
	*p_imsk = hospac_sh_imsk_base >> 4;
	
	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
