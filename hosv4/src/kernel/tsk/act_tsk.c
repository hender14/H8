/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �^�X�N�Ǘ��@�\                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_tsk.h"



/* �^�X�N�̋N�� */
ER act_tsk(
		ID tskid)	/* �^�X�NID */
{
	const T_KERNEL_TCB_ROM *tcb_rom;
	T_KERNEL_TCB_RAM       *tcb_ram;

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

	/* �I�u�W�F�N�g��Ԕ��� */
	if ( mknl_get_tskstat(&tcb_ram->mtcb) != TTS_DMT )
	{
		/* ���Ɏ��s��ԂȂ�N���v�����L���[�C���O */
#ifdef HOS_ERCHK_E_QOVR
		if ( tcb_ram->actcnt >= TMAX_ACTCNT )
		{
			mknl_unl_sys();	/* �V�X�e���̃��b�N���� */
			return E_QOVR;	/* �L���[�C���O�I�[�o�[�t���[ */
		}
#endif

		/* �N���v�����L���[�C���O */
		tcb_ram->actcnt++;
	}
	else
	{
		/* �x�~��ԂȂ�^�X�N���N������ */
		tcb_rom = tcb_ram->tcb_rom;
	
		/* ���s�R���e�L�X�g�o�^ */
		mknl_sta_tsk(
				&tcb_ram->mtcb,			/* �o�^����^�X�N */
				tcb_rom->exinf,			/* �^�X�N�̊g����� */
				(FP)kernel_task_entry,	/* �^�X�N�̋N���Ԓn */
				tcb_rom->itskpri,		/* �^�X�N�̋N�����D��x */
				tcb_rom->stksz,			/* �^�X�N�̃X�^�b�N�̈�T�C�Y */
				tcb_rom->stk			/* �^�X�N�̃X�^�b�N�̈�̐擪�Ԓn */
			);	
		tcb_ram->suscnt = 0;	/* �����҂��l�X�g�N���A */
		tcb_ram->wupcnt = 0;	/* �҂������v���L���[�C���O�N���A */
		
		mknl_exe_dsp();			/* �^�X�N�f�B�X�p�b�`�̎��s */
		mknl_exe_tex();			/* ��O�����̎��s */
	}

	mknl_unl_sys();	/* �V�X�e���̃��b�N���� */

	return E_OK;	/* ���� */
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
