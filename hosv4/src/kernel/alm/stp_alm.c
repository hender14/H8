/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �A���[���n���h��                                        */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_alm.h"



/* �A���[���n���h���̓����~ */
ER stp_alm(
		ID almid)	/* �����~�Ώۂ̃A���[���n���h����ID�ԍ� */
{
	T_KERNEL_ALMCB_RAM *almcb_ram;

	/* ID �̃`�F�b�N */
#ifdef HOS_ERCHK_E_ID
	if ( almid < KERNEL_TMIN_ALMID || almid > KERNEL_TMAX_ALMID )
	{
		return E_ID;
	}
#endif

	mknl_loc_sys();	/* �V�X�e���̃��b�N */

	almcb_ram = KERNEL_ALMID_TO_ALMCB_RAM(almid);

	/* �I�u�W�F�N�g���݃`�F�b�N */
#ifdef HOS_ERCHK_E_NOEXS
	if ( almcb_ram == NULL )
	{
		mknl_unl_sys();		/* �V�X�e���̃��b�N���� */
		return E_NOEXS;
	}
#endif
	
	/* �^�C�}���X�g����O�� */
	kernel_rmv_tml((T_KERNEL_TIM *)almcb_ram);
	
	mknl_unl_sys();		/* �V�X�e���̃��b�N���� */

	return E_OK;	
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
