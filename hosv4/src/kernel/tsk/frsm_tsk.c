/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �^�X�N�t�������@�\                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_tsk.h"



/* �����҂���Ԃ���̋����ĊJ */
ER frsm_tsk(
		ID tskid)	/* �ĊJ�Ώۂ̃^�X�N��ID�ԍ� */
{
		T_KERNEL_TCB_RAM *tcb_ram;

	/* ID �͈̓`�F�b�N */
#ifdef HOS_ERCHK_E_ID
	if ( tskid < KERNEL_TMIN_TSKID || tskid > KERNEL_TMAX_TSKID )
	{
		return E_ID;	/* �s��ID�ԍ� */
	}
#endif

	mknl_loc_sys();	/* �V�X�e���̃��b�N */

	tcb_ram = KERNEL_TSKID_TO_TCB_RAM(tskid);

	/* �I�u�W�F�N�g���݃`�F�b�N */
#ifdef HOS_ERCHK_E_NOEXS
	if ( tcb_ram == NULL )
	{
		mknl_unl_sys();	/* �V�X�e���̃��b�N���� */
		return E_NOEXS;	/* �I�u�W�F�N�g������ */
	}
#endif

	/* �I�u�W�F�N�g��ԃ`�F�b�N */
#ifdef HOS_ERCHK_E_OBJ
	if ( !(mknl_get_tskstat(&tcb_ram->mtcb) & TTS_SUS) )
	{
		/* �����҂���ԂłȂ���� */
		mknl_unl_sys();	/* �V�X�e���̃��b�N���� */
		return E_OBJ;	/* �I�u�W�F�N�g�̏�ԕs�� */
	}
#endif

	/* �^�X�N�̋����҂��������� */
	tcb_ram->suscnt = 0;
	mknl_rsm_tsk(&tcb_ram->mtcb);
	
	mknl_exe_dsp();		/* �^�X�N�f�B�X�p�b�`�̎��s */
	mknl_exe_tex();		/* ��O�����̎��s */
	
	mknl_unl_sys();		/* �V�X�e���̃��b�N���� */

	return E_OK;
}			


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
