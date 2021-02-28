/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �^�X�N�t�������@�\                                      */
/*                                                                          */
/*                                  Copyright (C) 1998-2004 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_tsk.h"



/* �����҂���Ԃւ̈ڍs */
ER sus_tsk(
		ID tskid)	/* �ڍs�Ώۂ̃^�X�NID�ԍ� */
{
	T_KERNEL_TCB_RAM *tcb_ram;

	/* ID �͈̓`�F�b�N */
#ifdef HOS_ERCHK_E_ID
	if ( tskid != TSK_SELF && (tskid < KERNEL_TMIN_TSKID || tskid > KERNEL_TMAX_TSKID) )
	{
		return E_ID;	/* �s��ID�ԍ� */
	}
#endif

	mknl_loc_sys();	/* �V�X�e���̃��b�N */

	/* �^�X�N�R���g���[���u���b�N�擾 */
	if ( tskid == TSK_SELF )
	{
		/* ���^�X�N�w�莞�̕ϊ� */
#ifdef HOS_ERCHK_E_CTX
		if ( mknl_sns_dsp() )
		{
			/* �f�B�X�p�b�`�֎~��Ԃ� TSK_SELF�w��͕s�� */
			mknl_unl_sys();		/* �V�X�e���̃��b�N���� */
			return E_CTX;		/* �R���e�L�X�g�s�� */
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

	/* �R���e�L�X�g�`�F�b�N */
#ifdef HOS_ERCHK_E_CTX
	if ( tcb_ram == kernel_get_run_tsk() && mknl_sns_dsp() )
	{
		mknl_unl_sys();		/* �V�X�e���̃��b�N���� */
		return E_CTX;		/* �R���e�L�X�g�s�� */
	}
#endif

	/* �I�u�W�F�N�g��ԃ`�F�b�N */
#ifdef HOS_ERCHK_E_OBJ
	if ( mknl_get_tskstat(&tcb_ram->mtcb) == TTS_DMT )
	{
		mknl_unl_sys();		/* �V�X�e���̃��b�N���� */
		return E_OBJ;		/* �I�u�W�F�N�g��ԕs�� */
	}
#endif

	/* �I�u�W�F�N�g��Ԕ��� */
	if ( mknl_get_tskstat(&tcb_ram->mtcb) & TTS_SUS )
	{
		/* �L���[�C���O�I�[�o�[�t���[�`�F�b�N */
#ifdef HOS_ERCHK_E_QOVR
		if ( tcb_ram->suscnt >= TMAX_SUSCNT )
		{
			mknl_unl_sys();	/* �V�X�e���̃��b�N���� */
			return E_QOVR;
		}
#endif
		tcb_ram->suscnt++;
	}
	else
	{
		/* �^�X�N�̋����҂� */
		mknl_sus_tsk(&tcb_ram->mtcb);
	}

	/* �Ώۂ����^�X�N�̏ꍇ�A�f�B�X�p�b�`���s */
	if ( tcb_ram == kernel_get_run_tsk())
	{
		mknl_exe_dsp();	/* �^�X�N�f�B�X�p�b�`�̎��s */
		mknl_exe_tex();	/* ��O�����̎��s */
	}

	mknl_unl_sys();	/* �V�X�e���̃��b�N���� */

	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2004 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
