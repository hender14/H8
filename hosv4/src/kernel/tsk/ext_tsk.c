/* ------------------------------------------------------------------------ */
/*  Hyper Operating System V4  ��ITRON4.0�d�l Real-Time OS                  */
/*    ITRON�J�[�l�� �^�X�N�Ǘ��@�\                                          */
/*                                                                          */
/*                                  Copyright (C) 1998-2002 by Project HOS  */
/*                                  http://sourceforge.jp/projects/hos/     */
/* ------------------------------------------------------------------------ */


#include "knl_tsk.h"


static void kernel_ext_tsk(VP_INT exinf);	/* �^�X�N�̏I������(�V�X�e���^�X�N�Ŏ��s) */



/* ���^�X�N�̏I�� */
void ext_tsk(void)
{
	T_KERNEL_TCB_RAM *tcb_ram;
	T_MKNL_TCB       *mtcb_run;

	/* ���s���^�X�N�̎擾 */
	mtcb_run = mknl_get_run_tsk();
	tcb_ram  = KERNEL_STATIC_CAST(T_KERNEL_TCB_RAM, mtcb, mtcb_run);

	mknl_loc_sys();		/* �V�X�e���̃��b�N */

	/* �V�X�e���^�X�N���珈�����s�� */
	mknl_exe_sys((FP)kernel_ext_tsk, (VP_INT)tcb_ram);
}



/* �^�X�N�̏I������(�V�X�e���^�X�N�Ŏ��s) */
void kernel_ext_tsk(VP_INT exinf)
{
	const T_KERNEL_TCB_ROM *tcb_rom;
	T_KERNEL_TCB_RAM       *tcb_ram;
	
	tcb_ram = (T_KERNEL_TCB_RAM *)exinf;
	tcb_rom = tcb_ram->tcb_rom;
	
	/* �^�X�N���I�������� */
	mknl_ter_tsk(&tcb_ram->mtcb);

	/* �N�����L���[�C���O����Ă����Ȃ� */
	if ( tcb_ram->actcnt > 0 )
	{
		tcb_ram->actcnt--;		/* �L���[�C���O���Z */
		tcb_ram->suscnt = 0;	/* �����҂��l�X�g�N���A */
		tcb_ram->wupcnt = 0;	/* �҂������v���L���[�C���O�N���A */

		/* �ēx�^�X�N�𐶐� */
		mknl_sta_tsk(
				&tcb_ram->mtcb,			/* �o�^����^�X�N */
				tcb_rom->exinf,			/* �^�X�N�̊g����� */
				(FP)kernel_task_entry,	/* �^�X�N�̋N���Ԓn */
				tcb_rom->itskpri,		/* �^�X�N�̋N�����D��x */
				tcb_rom->stksz,			/* �^�X�N�̃X�^�b�N�̈�T�C�Y */
				tcb_rom->stk			/* �^�X�N�̃X�^�b�N�̈�̐擪�Ԓn */
			);	
	}
	
	/* �^�X�N�f�B�X�p�b�`�̎��s */
	mknl_exe_dsp();
}



/* ------------------------------------------------------------------------ */
/*  Copyright (C) 1998-2006 by Project HOS                                  */
/* ------------------------------------------------------------------------ */
