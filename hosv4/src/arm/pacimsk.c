/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*   �v���Z�b�T���ۉ��R���|�[�l���g (ARM�p)                                 */
/*   ���荞�݃}�X�N�Ǘ�                                                     */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "mknl.h"



/* �O���[�o���ϐ���` */
UW hospac_arm_imsk  = ARM_IMSK_USR_MODE;		/* ���荞�݃}�X�N */
UW hospac_arm_bimsk = ARM_IMSK_USR_MODE;		/* �x�[�X���荞�݃}�X�N */


/* ���荞�݃}�X�N�w�� */
ER chg_imsk(IMSK imsk)
{
	/* �p�����[�^�[�`�F�b�N */
#ifdef HOS_ERCHK_E_PAR
	if ( (imsk & ~(ARM_IMSK_FIQ | ARM_IMSK_IRQ)) != 0 )
	{
		return E_PAR;
	}
#endif

	mknl_loc_sys();		/* �V�X�e���̃��b�N */

	hospac_arm_bimsk = (imsk | ARM_IMSK_USR_MODE);
	
	if ( !mknl_sns_ctx() )
	{
		hospac_arm_imsk = hospac_arm_bimsk;
	}
	else
	{
		hospac_arm_imsk |= hospac_arm_bimsk;
	}

	mknl_unl_sys();		/* �V�X�e���̃A�����b�N */

	return E_OK;
}


/* ���荞�݃}�X�N�̎Q�� */
ER get_imsk(IMSK *p_imsk)
{
	*p_imsk = (hospac_arm_bimsk & (ARM_IMSK_FIQ | ARM_IMSK_IRQ));
	
	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
