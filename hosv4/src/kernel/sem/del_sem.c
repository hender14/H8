/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �Z�}�t�H                                                */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_sem.h"
#include "knl_mem.h"


/* �Z�}�t�H�̍폜 */
ER del_sem(
		ID semid)	/* �폜�Ώۂ̃Z�}�t�H��ID�ԍ� */
{
	T_KERNEL_SEMCB_RAM *semcb_ram;

	/* ID �̃`�F�b�N */
#ifdef HOS_ERCHK_E_ID
	if ( semid < KERNEL_TMIN_SEMID || semid > KERNEL_TMAX_SEMID )
	{
		return E_ID;	/* �s��ID */
	}
#endif

	mknl_loc_sys();	/* �V�X�e���̃��b�N */

	semcb_ram = KERNEL_SEMID_TO_SEMCB_RAM(semid);

	/* �I�u�W�F�N�g���݃`�F�b�N */
#ifdef HOS_ERCHK_E_NOEXS
	if ( semcb_ram == NULL )
	{
		mknl_unl_sys();	/* �V�X�e���̃��b�N���� */
		return E_NOEXS;	/* �I�u�W�F�N�g������ */
	}
#endif
	
	/* �҂��^�X�N�̉��� */
	mknl_clr_que(&semcb_ram->que);
	
	/* �������̉�� */
	kernel_fre_mem(semcb_ram);
	KERNEL_SEMID_TO_SEMCB_RAM(semid) = NULL;
	
	mknl_exe_dsp();		/* �^�X�N�f�B�X�p�b�`�̎��s */
	mknl_exe_tex();		/* ��O�����̎��s */
	
	mknl_unl_sys();	/* �V�X�e���̃��b�N���� */

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
