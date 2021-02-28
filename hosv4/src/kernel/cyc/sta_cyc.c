/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �����n���h��                                            */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_cyc.h"



/* �����n���h���̓���J�n */
ER sta_cyc(
		ID cycid)	/* ����J�n�Ώۂ̎����n���h����ID�ԍ� */
{
	const T_KERNEL_CYCCB_ROM *cyccb_rom;
	T_KERNEL_CYCCB_RAM *cyccb_ram;
	
	/* ID �̃`�F�b�N */
#ifdef HOS_ERCHK_E_ID
	if ( cycid < KERNEL_TMIN_CYCID || cycid > KERNEL_TMAX_CYCID )
	{
		return E_ID;
	}
#endif
	
	mknl_loc_sys();	/* �V�X�e���̃��b�N */
	
	cyccb_ram = KERNEL_CYCID_TO_CYCCB_RAM(cycid);
	
	/* �I�u�W�F�N�g���݃`�F�b�N */
#ifdef HOS_ERCHK_E_NOEXS
	if ( cyccb_ram == NULL )
	{
		mknl_unl_sys();		/* �V�X�e���̃��b�N���� */
		return E_NOEXS;
	}
#endif
	
	cyccb_rom = cyccb_ram->cyccb_rom;
	
	/* �^�C�}�J�E���^�ݒ� */
	cyccb_ram->lefttim = cyccb_rom->cyctim;
	
	/* �^�C�}���X�g�ɓo�^ */
	kernel_add_tml((T_KERNEL_TIM *)cyccb_ram);
	
	mknl_unl_sys();		/* �V�X�e���̃��b�N���� */

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
