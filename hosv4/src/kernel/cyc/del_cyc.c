/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �����n���h��                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_cyc.h"
#include "knl_mem.h"



/* �����n���h���̍폜 */
ER del_cyc(
		ID cycid)	/* �폜�Ώۂ̎����n���h����ID�ԍ� */
{
	T_KERNEL_CYCCB_RAM *cyccb_ram;

	/* ID �̃`�F�b�N */
#ifdef HOS_ERCHK_E_ID
	if ( cycid < KERNEL_TMIN_CYCID || cycid > KERNEL_TMAX_CYCID )
	{
		return E_ID;	/* �s��ID */
	}
#endif

	mknl_loc_sys();		/* �V�X�e���̃��b�N */

	cyccb_ram = KERNEL_CYCID_TO_CYCCB_RAM(cycid);

	/* �I�u�W�F�N�g���݃`�F�b�N */
#ifdef HOS_ERCHK_E_NOEXS
	if ( cyccb_ram == NULL )
	{
		mknl_unl_sys();	/* �V�X�e���̃��b�N���� */
		return E_NOEXS;	/* �I�u�W�F�N�g������ */
	}
#endif
	
	/* �^�C�}���X�g����O�� */
	kernel_rmv_tml((T_KERNEL_TIM *)cyccb_ram);
	
	/* �������̉�� */
	kernel_fre_mem(cyccb_ram);

	KERNEL_CYCID_TO_CYCCB_RAM(cycid) = NULL;
	
	mknl_unl_sys();		/* �V�X�e���̃��b�N���� */

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
