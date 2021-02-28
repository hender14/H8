/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �^�X�N�Ǘ��@�\                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_tsk.h"



/* �^�X�N�D��x�̕ύX */
ER chg_pri(
		ID tskid,		/* �ύX�Ώۂ̃^�X�NID�ԍ� */
		PRI tskpri)		/* �ύX��̃x�[�X�D��x */
{
	T_KERNEL_TCB_RAM *tcb_ram;

	/* ID �͈̓`�F�b�N */
#ifdef HOS_ERCHK_E_ID
	if ( tskid != TSK_SELF && (tskid < KERNEL_TMIN_TSKID || tskid > KERNEL_TMAX_TSKID) )
	{
		return E_ID;	/* �s��ID�ԍ� */
	}
#endif

	/* �p�����[�^�[�͈̓`�F�b�N */
#ifdef HOS_ERCHK_E_PAR
	if ( tskpri < TMIN_TPRI || tskpri > TMAX_TPRI )
	{
		return E_PAR;	/* �p�����[�^�[�s�� */
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
			mknl_unl_sys();		/* �V�X�e���̃��b�N���� */
			return E_ID;		/* �s��ID�ԍ� */
		}
#endif
		tcb_ram = kernel_get_run_tsk();
	}
	else
	{
		/* ID�ԍ��w�莞�̕ϊ� */
		tcb_ram = KERNEL_TSKID_TO_TCB_RAM(tskid);

		/* �I�u�W�F�N�g���݃`�F�b�N */
#ifdef HOS_ERCHK_E_NOEXS
		if ( tcb_ram == NULL )
		{
			mknl_unl_sys();		/* �V�X�e���̃��b�N���� */
			return E_NOEXS;		/* �I�u�W�F�N�g������ */
		}
#endif
	}

	/* �N�����D��x�w��̏ꍇ */
	if ( tskpri == TPRI_INI )
	{
		tskpri = tcb_ram->tcb_rom->itskpri;
	}

	/* �I�u�W�F�N�g�̏�ԃ`�F�b�N */
#ifdef HOS_ERCHK_E_OBJ
	if ( mknl_get_tskstat(&tcb_ram->mtcb) == TTS_DMT )	/* �x�~��ԂȂ�� */
	{
		return E_OBJ;	/* �I�u�W�F�N�g��ԃG���[ */
	}
#endif

	/* �D��x�ύX */
	mknl_chg_pri(&tcb_ram->mtcb, tskpri);
	
	mknl_exe_dsp();		/* �^�X�N�f�B�X�p�b�`�̎��s */
	mknl_exe_tex();		/* ��O�����̎��s */
	
	mknl_unl_sys();		/* �V�X�e���̃��b�N���� */

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
