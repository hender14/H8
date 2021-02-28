/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �Z�}�t�H                                                */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_sem.h"



/* �Z�}�t�H�����̊l��(�|�[�����O) */
ER pol_sem(
		ID semid)	/* �����l���Ώۂ̃Z�}�t�HID�ԍ� */
{
	T_KERNEL_SEMCB_RAM *semcb_ram;
	ER ercd;

	/* ID �̃`�F�b�N */
#ifdef HOS_ERCHK_E_ID
	if ( semid < KERNEL_TMIN_SEMID || semid > KERNEL_TMAX_SEMID )
	{
		return E_ID;
	}
#endif
	
	mknl_loc_sys();		/* �V�X�e���̃��b�N */

	semcb_ram = KERNEL_SEMID_TO_SEMCB_RAM(semid);

	/* �I�u�W�F�N�g���݃`�F�b�N */
#ifdef HOS_ERCHK_E_NOEXS
	if ( semcb_ram == NULL )
	{
		mknl_unl_sys();		/* �V�X�e���̃��b�N���� */
		return E_NOEXS;
	}
#endif

	/* �Z�}�t�H�������l���ł��ꖳ����΃^�C���A�E�g */
	if ( semcb_ram->semcnt == 0 )
	{
		ercd = E_TMOUT;		/* �^�C���A�E�g */
	}
	else
	{
		semcb_ram->semcnt--;	/* �Z�}�t�H�����̊l�� */
		ercd = E_OK;
	}

	mknl_unl_sys();		/* �V�X�e���̃��b�N���� */

	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
