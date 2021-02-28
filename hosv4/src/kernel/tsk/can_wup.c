/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �^�X�N�t�������@�\                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_tsk.h"



/* �^�X�N�N���v���̃L�����Z�� */
ER_UINT can_wup(
		ID tskid)	/* �N���v���̃L�����Z���Ώۂ̃^�X�NID�ԍ� */
{
	T_KERNEL_TCB_RAM *tcb_ram;
	ER_UINT ercd;

	/* ID �͈̓`�F�b�N */
#ifdef HOS_ERCHK_E_ID
	if ( tskid != TSK_SELF && (tskid < KERNEL_TMIN_TSKID || tskid > KERNEL_TMAX_TSKID) )
	{
		return (ER_UINT)E_ID;	/* �s��ID�ԍ� */
	}
#endif

	mknl_loc_sys();	/* �V�X�e���̃��b�N */

	/* �^�X�N�R���g���[���u���b�N�擾 */
	if ( tskid == TSK_SELF )
	{
		/* ���^�X�N�w�莞�̕ϊ� */
#ifdef HOS_ERCHK_E_ID
		if ( mknl_sns_ctx() )
		{
			/* ��^�X�N�R���e�L�X�g�� TSK_SELF�w��͕s�� */
			mknl_unl_sys();			/* �V�X�e���̃��b�N���� */
			return (ER_UINT)E_ID;	/* �s��ID�ԍ� */
		}
#endif
		tcb_ram = kernel_get_run_tsk();
	}
	else
	{
		/* �^�X�NID�w�莞�̕ϊ� */
		tcb_ram = KERNEL_TSKID_TO_TCB_RAM(tskid);

		/* �I�u�W�F�N�g���݃`�F�b�N */
#ifdef HOS_ERCHK_E_NOEXS
		if ( tcb_ram == NULL )
		{
			mknl_unl_sys();				/* �V�X�e���̃��b�N���� */
			return (ER_UINT)E_NOEXS;	/* �I�u�W�F�N�g������ */
		}
#endif
	}

	/* �I�u�W�F�N�g�̏�ԃ`�F�b�N */
#ifdef HOS_ERCHK_E_OBJ
	if ( mknl_get_tskstat(&tcb_ram->mtcb) == TTS_DMT )
	{
		mknl_unl_sys();	/* �V�X�e���̃��b�N���� */
		return (ER_UINT)E_OBJ;	/* �I�u�W�F�N�g��ԃG���[ */
	}
#endif

	/* �N���v���̃L�����Z�� */
	ercd = tcb_ram->wupcnt;
	tcb_ram->wupcnt = 0;

	mknl_unl_sys();	/* �V�X�e���̃��b�N���� */

	return ercd;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
