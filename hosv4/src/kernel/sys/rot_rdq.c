/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �V�X�e����ԊǗ�                                        */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_sys.h"



/* �^�X�N�D�揇�ʂ̉�] */
ER rot_rdq(
		PRI tskpri)		/* �D�揇�ʂ���]����Ώۂ̗D��x */
{
	T_MKNL_TCB* mtcb;

	/* ���^�X�N�D��x�w��̏��� */
	if ( tskpri == TPRI_SELF )
	{
#ifdef HOS_ERCHK_E_PAR
		if ( sns_ctx() )
		{
			return E_PAR;
		}
		mtcb   = mknl_get_run_tsk();	/* ���s���^�X�N�̎擾 */
		tskpri = mknl_get_pri(mtcb);	/* �D��x�̎擾 */
#endif
	}

	/* �p�����[�^�[�͈̓`�F�b�N */
#ifdef HOS_ERCHK_E_PAR
	if ( tskpri < TMIN_TPRI ||  tskpri > TMAX_TPRI )
	{
		return E_PAR;
	}
#endif

	mknl_loc_sys();			/* �V�X�e���̃��b�N */

	mknl_rot_rdq(tskpri);	/* �^�X�N�D�揇�ʂ̉�] */
	
	mknl_exe_dsp();			/* �^�X�N�f�B�X�p�b�`�̎��s */
	mknl_exe_tex();			/* ��O�����̎��s */
	
	mknl_unl_sys();			/* �V�X�e���̃��b�N���� */
	
	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
