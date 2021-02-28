/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �^�X�N�Ǘ��@�\                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_tsk.h"



/* �^�X�N�̋����I�� */
ER ter_tsk(
		ID tskid)	/* �����I���Ώۂ̃^�X�NID�ԍ� */
{						
	const T_KERNEL_TCB_ROM *tcb_rom;
	T_KERNEL_TCB_RAM *tcb_ram;

	/* ID �͈̓`�F�b�N */
#ifdef HOS_ERCHK_E_ID
	if ( tskid < KERNEL_TMIN_TSKID || tskid > KERNEL_TMAX_TSKID )
	{
		return E_ID;	/* �s��ID�ԍ� */
	}
#endif

	mknl_loc_sys();	/* �V�X�e���̃��b�N */

	/* ID����^�X�N�R���g���[���u���b�NRAM���擾 */
	tcb_ram = KERNEL_TSKID_TO_TCB_RAM(tskid);

	/* �I�u�W�F�N�g���݃`�F�b�N */
#ifdef HOS_ERCHK_E_NOEXS
	if ( tcb_ram == NULL )
	{
		mknl_unl_sys();	/* �V�X�e���̃��b�N���� */
		return E_NOEXS;	/* �I�u�W�F�N�g������ */
	}
#endif

	/* �T�[�r�X�R�[���s���g�p�`�F�b�N */
#ifdef HOS_ERCHK_E_ILUSE
	if ( mknl_get_run_tsk() == &tcb_ram->mtcb )		/* ���s���̃^�X�N�Ȃ� */
	{
		mknl_unl_sys();	/* �V�X�e���̃��b�N���� */
		return E_ILUSE;	/* �T�[�r�X�R�[���s���g�p */
	}
#endif

	/* �I�u�W�F�N�g�̏�ԃ`�F�b�N */
#ifdef HOS_ERCHK_E_OBJ
	if ( mknl_get_tskstat(&tcb_ram->mtcb) == TTS_DMT )	/* ���łɋx�~��ԂȂ�� */
	{
		mknl_unl_sys();	/* �V�X�e���̃��b�N���� */
		return E_OBJ;	/* �I�u�W�F�N�g��ԃG���[ */
	}
#endif

	/* ���s�^�X�N�̏I�� */
	mknl_rmv_tmout(&tcb_ram->mtcb);		/* �^�C���A�E�g�҂��s��ɂȂ���Ă���Ή��� */
	mknl_ter_tsk(&tcb_ram->mtcb);		/* �^�X�N���폜 */

	/* �N�����L���[�C���O����Ă����Ȃ� */
	if ( tcb_ram->actcnt > 0 )
	{
		tcb_rom = tcb_ram->tcb_rom;

		tcb_ram->actcnt--;	/* �L���[�C���O���Z */

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
	}
	
	mknl_exe_dsp();		/* �^�X�N�f�B�X�p�b�`�̎��s */
	mknl_exe_tex();		/* ��O�����̎��s */
	
	mknl_unl_sys();	/* �V�X�e���̃��b�N���� */
	
	return E_OK;
}


/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2002 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
